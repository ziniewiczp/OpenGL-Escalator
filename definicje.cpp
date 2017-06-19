/*

 C++ przez OpenGL - szablon do �wicze� laboratoryjnych
 (C) Micha� Turek.

*/

#ifdef _DEFINICJE


	/******************* SZABLON **************************/

	struct Stair
	{
		int phase;
		float currentX, currentY, currentZ;
	};

	bool drawOnlyStairs = false;
	float rotate = 0;
	int const stairsCount = 78;

	float movementSpeed = 0.1;

	Stair stairs[stairsCount];

	/******************************************************/


#undef _DEFINICJE
#endif
