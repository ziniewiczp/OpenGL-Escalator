/*

 C++ przez OpenGL - szablon do �wicze� laboratoryjnych
 (C) Micha� Turek.

*/

#include <windows.h>
#include "glut.h"

#ifdef _RYSOWANIE


	/******************* SZABLON **************************/

	// Tekstura podloza jest zapisana w pliku "data/land.bmp", definiowana bezpo�rednio w 3ds. 
	// Wymagany format pliku: bmp, 24 bity na pixel.

	// MODELE 3ds:
	// Modele 3ds znajdujace sie w katalogu /data s� autoamtycznie ladowane i rejestrowane pod nazwami zbieznymi z nazwami plikow
	// Aby narysowa� model nalezy wywo�a� funkcj�: rysujModel ("nazwa_modelu");
	// Nazwa_modelu mo�e by� podana literemi du�ymi lub ma�ymi, z rozszerzeniem pliku lub bez.


	if (drawOnlyStairs == false )
		rysujModel("without_stairs.3ds");		

	glTranslatef(17.5, 6, -25); // vector
	glRotatef(-35, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0,-4,-9.5);
	glRotatef(90, 0, 0, 1);
	glScalef(0.15,0.15, 0.15);
	if (rotate == 360)
		rotate = 0;
	glRotatef(rotate, 0, 1, 0);
	//rysujModel("cogwheel.3ds");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 115, -210);
	glRotatef(90, 0, 0, 1);
	glScalef(0.15, 0.5, 0.15);
	if (rotate == 360)
		rotate = 0;
	glRotatef(rotate, 0, 1, 0);
	//rysujModel("cogwheel.3ds");
	glPopMatrix();

	rotate += 0.5;

	for (int i = 0; i < stairsCount; i++)
	{
		glPushMatrix();

		glTranslatef(stairs[i].currentX, stairs[i].currentY, stairs[i].currentZ);

		if (stairs[i].phase == 1 && stairs[i].currentY >= 126)
		{
			stairs[i].phase = 4;
			//stairs[i].currentY -= 20;
		}
		else if (stairs[i].phase == 4 && stairs[i].currentY <= 119) 
		{
			stairs[i].phase = 2;
			stairs[i].currentY -= 3.5;
		}
		else if (stairs[i].phase == 2 && stairs[i].currentY <= -14)
		{
			stairs[i].phase = 3;
			//stairs[i].currentY += 21;
		}
		else if (stairs[i].phase == 3 && stairs[i].currentY >= -7)
		{
			stairs[i].phase = 1;
			stairs[i].currentY += 3.5;
		}

		switch (stairs[i].phase)
		{
			case 1:
				stairs[i].currentY += movementSpeed / 1.65;
				stairs[i].currentZ -= movementSpeed;

				rysujModel("one_stair.3ds");
				break;

			case 2:				
				stairs[i].currentY -= movementSpeed / 1.65;
				stairs[i].currentZ += movementSpeed;

				rysujModel("one_stair.3ds");
				break;

			case 3:
				stairs[i].currentY += movementSpeed / 1.65;
				stairs[i].currentZ += movementSpeed;

				rysujModel("one_stair.3ds");
				break;

			case 4:
				stairs[i].currentY -= movementSpeed / 1.65;
				stairs[i].currentZ -= movementSpeed;

				rysujModel("one_stair.3ds");
				break;

			default:
				break;
		}

		/*GLfloat m[16]; glGetFloatv(GL_MODELVIEW_MATRIX, m);

		std::cout << "Matrix position: (" << m[12] << ", " << m[13] << ", " << m[14] << ")";
		std::cout << "\n";
		std::cout << "Stair position: " << i << " " << stairs[i].currentX << ", " << stairs[i].currentY << ", " << stairs[i].currentZ << ")";
		std::cout << "\n";*/

		glPopMatrix();
	}

	/******************************************************/


#undef _RYSOWANIE
#endif











