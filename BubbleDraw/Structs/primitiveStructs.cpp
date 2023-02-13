#include "primitiveStructs.h"
#include "Utils/SDL_Util.h"

bool operator==(const Line& line1, const Line& line2)
{
	return ((line1.p1 == line2.p1 && line1.p2 == line2.p2) || (line1.p1 == line2.p2 && line1.p2 == line2.p1));
}

bool operator==(const Triangle& triangle1, const Triangle& triangle2)
{
	return ((triangle1.p1 == triangle2.p1 && triangle1.p2 == triangle2.p2 && triangle1.p3 == triangle2.p3) ||
		(triangle1.p1 == triangle2.p1 && triangle1.p2 == triangle2.p3 && triangle1.p3 == triangle2.p2) ||
		(triangle1.p1 == triangle2.p2 && triangle1.p2 == triangle2.p1 && triangle1.p3 == triangle2.p3) ||
		(triangle1.p1 == triangle2.p2 && triangle1.p2 == triangle2.p3 && triangle1.p3 == triangle2.p1) ||
		(triangle1.p1 == triangle2.p3 && triangle1.p2 == triangle2.p1 && triangle1.p3 == triangle2.p2) ||
		(triangle1.p1 == triangle2.p3 && triangle1.p2 == triangle2.p2 && triangle1.p3 == triangle2.p1));
}