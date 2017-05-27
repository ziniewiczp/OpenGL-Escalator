/*

 C++ przez OpenGL - szablon do �wicze� laboratoryjnych
 (C) Micha� Turek.

*/

#ifdef _RYSOWANIE


	/******************* SZABLON **************************/

	// Tekstura podloza jest zapisana w pliku "data/land.bmp", definiowana bezpo�rednio w 3ds. 
	// Wymagany format pliku: bmp, 24 bity na pixel.

	// MODELE 3ds:
	// Modele 3ds znajdujace sie w katalogu /data s� autoamtycznie ladowane i rejestrowane pod nazwami zbieznymi z nazwami plikow
	// Aby narysowa� model nalezy wywo�a� funkcj�: rysujModel ("nazwa_modelu");
	// Nazwa_modelu mo�e by� podana literemi du�ymi lub ma�ymi, z rozszerzeniem pliku lub bez.


	rysujModel("without_stairs.3ds");		

	glTranslatef(17.5, 7.5, -25); // vector
	glRotatef(-35, 0, 1, 0);
	glTranslatef(0, licznik_ruchu / 1.5, -licznik_ruchu);

	//for (licznik_schodkow = 0; licznik_schodkow < 5; licznik_schodkow++) {
		glTranslatef(0, 6, -6);
		rysujModel("one_stair.3ds");
	//}

	licznik_ruchu = licznik_ruchu + 0.1;

	if (licznik_ruchu > 50)
		licznik_ruchu = 0;

	/******************************************************/


#undef _RYSOWANIE
#endif











