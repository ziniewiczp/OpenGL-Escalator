/*

 C++ przez OpenGL - szablon do �wicze� laboratoryjnych
 (C) Micha� Turek.

*/

#ifdef _INTERAKCJA


	/******************* SZABLON **************************/

	// DEFINICJE FUNKCJI OBS�UGUJ�CYCH ZDARZENIA MYSZY I KLAWIATURY	

void PrzyciskMyszyWcisniety (int button, int state, int x, int y)
{
	SzablonPrzyciskMyszyWcisniety (button, state, x, y); // wywolanie standardowej obslugi zdarzen szablonu 


	//*************************************************************
	// tu mo�na umie�ci� kod obs�uguj�cy wci�ni�cie przycisku myszy

}

void RuchKursoraMyszy (int x, int y)
{
	SzablonRuchKursoraMyszy (x, y); // wywolanie standardowej obslugi zdarzen szablonu 

	//****************************************************
	//tu mo�na umie�ci� kod obs�uguj�cy ruch kursora myszy

}

void KlawiszKlawiaturyWcisniety (GLubyte key, int x, int y)
{
	SzablonKlawiszKlawiaturyWcisniety (key, x, y);	// wywolanie standardowej obslugi zdarzen szablonu 
	
	//*******************************************************************************
	// tu mo�na umie�ci� kod obs�uguj�cy wci�ni�cie klawisza klawiatury, przyk�adowo:
	
	switch (key) 
	{
		case 'k':    /* koniec programu */
			exit(1);
			break;
	}

}

void KlawiszSpecjalnyWcisniety (GLint key, int x, int y)
{

}

	/******************************************************/

#undef _INTERAKCJA
#endif
