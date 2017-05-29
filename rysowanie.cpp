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



	//rysujModel("without_stairs.3ds");		

	glTranslatef(17.5, 7.5, -25); // vector
	glRotatef(-35, 0, 1, 0);

	for (int i = 0; i < 11; i++)
	{
		glPushMatrix();

		glTranslatef(stairs[i].currentX, stairs[i].currentY, stairs[i].currentZ);

		GLfloat m[16]; glGetFloatv(GL_MODELVIEW_MATRIX, m);

		if (stairs[i].phase == 1 && stairs[i].currentY > 30)
		{
			stairs[i].phase = 2;
			stairs[i].currentY -= 10;
		}
		else if (stairs[i].phase == 2 && stairs[i].currentY < -7)
		{
			stairs[i].phase = 1;
			stairs[i].currentY += 10;
		}

		switch (stairs[i].phase)
		{
			case 1:
				stairs[i].currentY += movementSpeed;
				stairs[i].currentZ -= movementSpeed;

				rysujModel("one_stair.3ds");
				break;

			case 2:				
				stairs[i].currentY -= movementSpeed;
				stairs[i].currentZ += movementSpeed;

				rysujModel("one_stair.3ds");
				break;

			default:
				break;
		}

		

		std::cout << "Matrix position: (" << m[12] << ", " << m[13] << ", " << m[14] << ")";
		std::cout << "\n";
		std::cout << "Stair position: " << i << " " << stairs[i].currentX << ", " << stairs[i].currentY << ", " << stairs[i].currentZ << ")";
		std::cout << "\n";

		glPopMatrix();
	}

	/******************************************************/


#undef _RYSOWANIE
#endif











