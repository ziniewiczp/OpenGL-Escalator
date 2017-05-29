/*

 - szablon do �wicze� laboratoryjnych
 (C) Micha� Turek.

*/

#include <windows.h>
#include "glut.h"
#include "model3DS.h"
#include <time.h>
#include <direct.h>
//#include <GL/glaux.h>
	
//Wymiary okna
int screen_width=640;
int screen_height=480;

bool		animacja_flaga = true;										// Our Variable To Move The Waves Across The siatka
#define		WYMIAR	50													// Defines The WYMIAR Of The X/Z Axis Of The siatka
GLfloat		animacja = 0.0f;										// Our Variable To Move The Waves Across The siatka

// zmienne dot opcji projekscji dla gogli 3D
const bool gogle3D = false;						// czy w��czone
const float gogleRozstawOczu = 5;				// dystans mi�dzy oczami
const float goglePunktPatrzenia = 150;		// odleg�o�� do punktu, na kt�ry patrz� oczy
bool gogleEkran = 0;

// Zmienne dot. kamery

int pozycjaMyszyX; // na ekranie
int pozycjaMyszyY;

double kameraX;
double kameraY;
double kameraZ;
double kameraPunktY;
double kameraPredkoscPunktY;
double kameraPredkosc;
bool kameraPrzemieszczanie; // przemieszczanie lub rozgl�danie

double kameraKat;
double kameraPredkoscObrotu;
#define MIN_DYSTANS 0.5 // minimalny dystans od brzegu obszaru ograniczenia kamery
double obszarKamery = 0;

#define _DEFINICJE
#include "definicje.cpp"


textureBMP *tex1;

//model3DS * modelLand;  // pod�o�e
//model3DS *modelOb1,*modelOb2;  // obiekt
//model3DS *modelLawka, *modelSlupek;


struct przeszkoda{
	przeszkoda *next;
	double posX1;
	double posZ1;
	double posX2;
	double posZ2;
};

przeszkoda *obszarPrzeszkody = NULL;

void initializeStairs() {

	for (int i = 0; i < 11; i++)
	{
		if (i < 6) 
		{
			stairs[i].phase = 1;
			stairs[i].currentX = 0;
			stairs[i].currentY = i * 6;
			stairs[i].currentZ = - i * 6;
		}
		else if (i == 6)
		{
			stairs[i].phase = 2;
			stairs[i].currentX = 0;
			stairs[i].currentY = stairs[i - 1].currentY - 10;
			stairs[i].currentZ = stairs[i - 1].currentZ;
		}
		else if (i < 11) 
		{
			stairs[i].phase = 2;
			stairs[i].currentX = 0;
			stairs[i].currentY = stairs[i-1].currentY - 6;
			stairs[i].currentZ = stairs[i-1].currentZ + 6;
		}
	}
}

void resetKamery(){

	kameraX = 10;
	kameraY = 100;
	kameraZ = 100;
	kameraKat = -0.5;
	kameraPunktY = -30;
	kameraPredkoscPunktY = 0;
	kameraPredkosc = 0;
	kameraPredkoscObrotu = 0;
	kameraPrzemieszczanie = true;
	
}


void ustalObszar (double X){
	obszarKamery = X;	

}


bool wObszarze(double posX, double posZ){ // false - 
	
	if ( posX*posX + posZ*posZ > (obszarKamery-MIN_DYSTANS*2)*(obszarKamery-MIN_DYSTANS*2) ) return false;
	przeszkoda * pom = obszarPrzeszkody;
	while (pom){
		if (pom->posX1 < posX && 
			pom->posX2 > posX && 
			pom->posZ1 < posZ && 
			pom->posZ2 > posZ ) return false;
		pom = pom -> next;
	}
	return true;
}

void rejestrujPrzeszkode(double X1, double Z1, double X2, double Z2){
	przeszkoda * pom = new przeszkoda;
	if (X1 > X2) {double tmp = X1; X1 = X2; X2 = tmp;}
	if (Z1 > Z2) {double tmp = Z1; Z1 = Z2 ;Z2 = tmp;}
	pom -> posX1 = X1;
	pom -> posZ1 = Z1;
	pom -> posX2 = X2;
	pom -> posZ2 = Z2;
	pom -> next = obszarPrzeszkody;
	obszarPrzeszkody = pom;
}



void SzablonPrzyciskMyszyWcisniety (int button, int state, int x, int y)
{
	switch (state)
	{
		case GLUT_UP:
			kameraPredkosc = 0;
			kameraPredkoscObrotu = 0;
			kameraPredkoscPunktY = 0;
		break;
		case GLUT_DOWN:
				pozycjaMyszyX = x;
				pozycjaMyszyY = y;
			if (button == GLUT_LEFT_BUTTON)
				kameraPrzemieszczanie = true;
			else 
				kameraPrzemieszczanie = false;
		break;

	}


}


void SzablonRuchKursoraMyszy (int x, int y)
{
	kameraPredkoscObrotu = -(pozycjaMyszyX - x) * 0.001;
	if (kameraPrzemieszczanie)
	{
		kameraPredkosc = (pozycjaMyszyY - y) * 0.02;
		kameraPredkoscPunktY = 0;
	} else {
		kameraPredkoscPunktY = (pozycjaMyszyY - y) * 0.06;
		kameraPredkosc = 0;
	}
}


void SzablonKlawiszKlawiaturyWcisniety (GLubyte key, int x, int y)
{
   switch (key) {

   case 27:    /* Esc - koniec */
      exit(1);
      break;
   case ' ':    
      glutFullScreen();
      break;
   case 'w':
	   kameraY = kameraY + 5;
	   break;
   case 's':
	   kameraY = kameraY - 5;
	   break;
   }

}

#define _INTERAKCJA
#include "interakcja.cpp"


void rozmiar (int width, int height)
{
    screen_width=width; 
    screen_height=height; 

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glViewport(0,0,screen_width,screen_height); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,10000.0f);
    glutPostRedisplay (); // Przerysowanie sceny
}


/**

Zarz�dzanie skladem modeli 3ds

*/


struct model_w_skladzie {
	char * filename;
	model3DS * model;
	struct model_w_skladzie *wsk;
};

struct model_w_skladzie* sklad_modeli = NULL;

void dodajModel (model3DS * _model, char* file_name)
{
    struct model_w_skladzie* tmp;
    tmp = (struct model_w_skladzie *) malloc (sizeof(struct model_w_skladzie));
    tmp -> filename  = (char *) malloc(strlen(file_name)+1);
    strcpy( tmp -> filename, file_name);
    tmp -> model = _model;
    tmp->wsk = sklad_modeli;
    sklad_modeli = tmp;
}


model3DS * pobierzModel (char* file_name)
{
	struct model_w_skladzie* sklad_tmp = sklad_modeli;
	while (sklad_tmp){
		if (!_stricmp(sklad_tmp->filename,file_name)) return sklad_tmp->model;
		char file_name_full[_MAX_PATH];// porownanie tak�e z dosztukowaniem wlasciwego rozszerzenienia
			strcpy (file_name_full,file_name);
			strcat (file_name_full,".3ds");
		if (!_stricmp(sklad_tmp->filename,file_name_full)) return sklad_tmp->model;

		sklad_tmp = sklad_tmp->wsk;
	}
	return NULL;


}

/*
	Rysowanie modelu na podstawie nazwy (takiej samej jak w pliku) jednak - z wersji znajduj�cej si� ju� w pami�ci (w skladzie modeli)
		  
*/

void rysujModel(char * file_name, int tex_num = -1 )
{
	model3DS * model_tmp;	
	if (model_tmp = pobierzModel (file_name))
		if (tex_num == -1) 
			model_tmp -> draw();
		else
			model_tmp -> draw(tex_num, false);
		
}


/**
	�adowanie modeli jednoczesnie do skladu i do pamieci
	Katalog /data jest skanowany w poszukiwaniu plikow .3ds. Pliki s� ladowane automatycznie
**/


void ladujModele()
{
	WIN32_FIND_DATA *fd;
	HANDLE fh;
	model3DS * model_tmp;
	char directory[_MAX_PATH];
	if( _getcwd( directory, _MAX_PATH ) == NULL ) return;
	strcat (directory,"\\data\\*.3ds");
	
	fd = (WIN32_FIND_DATA *)malloc(sizeof(WIN32_FIND_DATA));
	fh = FindFirstFile((LPCSTR) directory,fd);
	if(fh != INVALID_HANDLE_VALUE)
		do {
			if(fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){	// katalogi ignorujemy
				if (FindNextFile(fh,fd)) continue; else break;
			}
			// ladowanie obiektu i dodanie do kontenera
			char filename[_MAX_PATH];
			strcpy (filename,"data\\");
			strcat (filename,fd->cFileName);
			model_tmp = new model3DS (filename,1);
			dodajModel (model_tmp,fd->cFileName);
			printf("[3DS] Model '%s' stored\n",fd->cFileName);
		} while(FindNextFile(fh,fd));
}



/**********************************************************
 		G��wna metoda rysuj�ca
 *********************************************************/
void rysuj(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Kasowanie ekranu
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	if (!gogle3D) gluLookAt (kameraX,kameraY,kameraZ,kameraX + 100*sin(kameraKat),3 + kameraPunktY	,kameraZ - 100*cos(kameraKat),0,1,0); // kamera
	else {
		gogleEkran = !gogleEkran;
		if (gogleEkran){  //  klatka parzysta
			float newKameraX = kameraX - gogleRozstawOczu/2*cos(kameraKat);
			float newKameraZ = kameraZ - gogleRozstawOczu/2*sin(kameraKat);
			gluLookAt (newKameraX,2,newKameraZ,kameraX+0.2 + goglePunktPatrzenia*sin(kameraKat),3 + kameraPunktY	,kameraZ - goglePunktPatrzenia*cos(kameraKat),0,1,0); // kamera
		}
		else {				// klatka nieparzysta
			float newKameraX = kameraX + gogleRozstawOczu/2*cos(kameraKat);
			float newKameraZ = kameraZ + gogleRozstawOczu/2*sin(kameraKat);
			gluLookAt (newKameraX,2,newKameraZ,kameraX+0.2 + goglePunktPatrzenia*sin(kameraKat),3 + kameraPunktY	,kameraZ - goglePunktPatrzenia*cos(kameraKat),0,1,0); // kamera
		}
	}
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glTranslatef(0,500,0); 
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);  // w-�czenie trybu koloryzacji materia-�w
	glEnable(GL_COLOR_MATERIAL); // teraz zmiana koloru materia-u nast�puje poprzez zwykly glColor*()
	glColor3f(0.6,0.6,1.0);
	//auxSolidCylinder(320, 550);
	glDisable(GL_COLOR_MATERIAL); // teraz zmiana koloru materia-u nast�puje poprzez zwykly glColor*()
	glPopMatrix();

	glLoadIdentity();
	glPushMatrix();
	
	glTranslatef(0,1,0);
	
	glEnable(GL_TEXTURE_2D);
	rysujModel("land"); // malowanie pod�o�a

	
	glPopMatrix();

	//if (!(licznik ++ % 60)) printf("*");



	#define _RYSOWANIE

	#include "rysowanie.cpp"

	// rysowanie drzew

	


/******************************************************/

    glFlush(); // rysowanie w buforze
    glutSwapBuffers(); // Wys�anie na ekran

	glMatrixMode(GL_PROJECTION);
    glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

}

void timer()
{


	double kameraXTmp = kameraX+kameraPredkosc*sin(kameraKat);
	double kameraZTmp = kameraZ-kameraPredkosc*cos(kameraKat);

	kameraKat = kameraKat + kameraPredkoscObrotu;
	kameraPunktY = kameraPunktY + kameraPredkoscPunktY;
	
	if (wObszarze(kameraXTmp,kameraZTmp))
	{
		kameraX = kameraXTmp;
		kameraZ = kameraZTmp;
	} else 
		kameraPredkosc = 0;
	//glutTimerFunc(50, timer, 0);
	rysuj();

}



int main(int argc, char **argv)
{
    

	
	// INIT - wszystkie funkcje obs�ugi okna i przetwzrzania zdarze� realizuje GLUT
	glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Szablon");    

	
	// ustawienie renderowania
	glClearColor(0.2, 0.2, 1.0, 0.0);			// T�o
    glShadeModel(GL_SMOOTH);					// cieniowanie

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    glEnable(GL_DEPTH_TEST); 

	
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
	glEnable(GL_LIGHTING);

	
	GLfloat  ambient[4] = {0.3,0.3,0.3,1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient); // o�wietlenie globalne


	GLfloat  ambientLight[4] = {0.3,0.3,0.3,1};
	GLfloat  specularLight[4] = {1.0,1.0,1.0,1};
	GLfloat  diffuseLight[4] = {1,1,1,1};
	GLfloat	 lightPos0[4] = {30,30,-30,1};

	glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);

	glEnable(GL_LIGHT0);  // �wiatlo sceny

	//srand( (unsigned)time( NULL ) ); // generator liczb losowych

	//tex1 = new textureBMP("data/bill.bmp",210);	// metodzie draw() klasy mesh3DS mo�na poda� numer tekstury (zamiast ew. przypisanej w 3DS, lub gdy jej tam nie ma)
											// w po��cznieu z autmatycznym i przekszta�ceniami macierzy teksturowania mo�na teksturowa� siatk� 3ds

	#define _KONFIGURACJA

	#include "konfiguracja.cpp"

	ladujModele();
		int listID=glGenLists(1);// wygenerowanie miejsca dla jednej listt i zwr�cenie do niej uchwytu - mozliwe jest generowanie szeregu list, pod kolejnymi (+1) wartosciami uchwytow, wtedy metoda zwraca uchwyt do pierwszej z nich
		//printf ("laczna liczba list %d \n",listID);

/******************************************************/

    glutDisplayFunc(rysuj);			// def. funkcji rysuj�cej
    glutIdleFunc(timer);			// def. funkcji rysuj�cej
//    glutTimerFunc(20,timer,10);		// def. funkcji rysuj�cej w czasie wolnym procesoora (w efekcie: ci�gle wykonywanej)
    glutReshapeFunc (rozmiar);		// def. obs�ugi zdarzenia resize (GLUT)
	glutKeyboardFunc (KlawiszKlawiaturyWcisniety);		// def. obs�ugi klawiatury
	glutSpecialFunc (KlawiszSpecjalnyWcisniety);		// def. obs�ugi klawiatury (klawisze specjalne)
	glutMouseFunc (PrzyciskMyszyWcisniety); 		// def. obs�ugi zdarzenia przycisku myszy (GLUT)
	glutMotionFunc (RuchKursoraMyszy);			// def. obs�ugi zdarzenia ruchu myszy (GLUT)

	initializeStairs();

	resetKamery();

    glutMainLoop();					// start obs�ugi komunikat�w
    return(0);    
}



