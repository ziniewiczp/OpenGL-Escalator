/*

 C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
 (C) Micha³ Turek.

*/

#include <windows.h>
#include "glut.h"

#ifdef _RYSOWANIE


	/******************* SZABLON **************************/

	// Tekstura podloza jest zapisana w pliku "data/land.bmp", definiowana bezpoœrednio w 3ds. 
	// Wymagany format pliku: bmp, 24 bity na pixel.

	// MODELE 3ds:
	// Modele 3ds znajdujace sie w katalogu /data s¹ autoamtycznie ladowane i rejestrowane pod nazwami zbieznymi z nazwami plikow
	// Aby narysowaæ model nalezy wywo³aæ funkcjê: rysujModel ("nazwa_modelu");
	// Nazwa_modelu mo¿e byæ podana literemi du¿ymi lub ma³ymi, z rozszerzeniem pliku lub bez.


	if (drawOnlyStairs == false )
		rysujModel("without_stairs.3ds");		

	glTranslatef(14.5, 6.5, -22); // vector
	glRotatef(-35, 0, 1, 0);
	for (int i = 0; i < 2; i++) {
		glPushMatrix();
		glTranslatef(-17+(i*35), -4, -12.5);
		glRotatef(90, 0, 0, 1);
		glScalef(0.15, 0.1, 0.30);
		if (rotate == 360)
			rotate = 0;
		glRotatef(rotate, 0, 1, 0);
		rysujModel("cogwheel.3ds");
		glPopMatrix();
	}
	for (int i = 0; i < 2; i++) {
		glPushMatrix();
		glTranslatef(-17+(i*35), 115, -210);
		glRotatef(90, 0, 0, 1);
		glScalef(0.15, 0.1, 0.30);
		if (rotate == 360)
			rotate = 0;
		glRotatef(rotate, 0, 1, 0);
		rysujModel("cogwheel.3ds");
		glPopMatrix();
	}
	rotate += 0.4;

	for (int i = 0; i < stairsCount; i++)
	{
		glPushMatrix();

		glTranslatef(stairs[i].currentX, stairs[i].currentY, stairs[i].currentZ);

		if (stairs[i].phase == 1 && stairs[i].currentY > 126)
		{
			stairs[i].phase = 4;
		}
		else if (stairs[i].phase == 4 && stairs[i].currentY < 119) 
		{
			stairs[i].phase = 2;
			stairs[i].currentY -= 6;
		}
		else if (stairs[i].phase == 2 && stairs[i].currentY < -13)
		{
			stairs[i].phase = 3;
		}
		else if (stairs[i].phase == 3 && stairs[i].currentY > -6)
		{
			stairs[i].phase = 1;
			stairs[i].currentY += 6;
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

		//std::cout << "Matrix position: (" << m[12] << ", " << m[13] << ", " << m[14] << ")";
		//std::cout << "\n";
		std::cout << "Stair position: " << i << " " << stairs[i].currentX << ", " << stairs[i].currentY << ", " << stairs[i].currentZ << ")";
		std::cout << "\n";*/

		glPopMatrix();
	}

	/******************************************************/


#undef _RYSOWANIE
#endif











