/*

 C++ przez OpenGL - szablon do �wicze� laboratoryjnych
 (C) Micha� Turek.

*/

#ifdef _DEFINICJE


	/******************* SZABLON **************************/

	struct stair
	{
		int phase;
		float currentX, currentY, currentZ;
	};

	stair stairs[8];

	float movementSpeed = 0.05;

	/******************************************************/


#undef _DEFINICJE
#endif
