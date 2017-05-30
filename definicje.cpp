/*

 C++ przez OpenGL - szablon do æwiczeñ laboratoryjnych
 (C) Micha³ Turek.

*/

#ifdef _DEFINICJE


	/******************* SZABLON **************************/

	struct Stair
	{
		int phase;
		float currentX, currentY, currentZ;
	};
	
	int const stairsCount = 21;

	float movementSpeed = 0.1;

	Stair stairs[stairsCount];

	/******************************************************/


#undef _DEFINICJE
#endif
