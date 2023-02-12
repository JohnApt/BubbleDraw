#pragma once
#include <set>

struct Circle
{
	SDL_Point center;
	int radius;

	std::set<int> adjacentCircleIndices;

	double powerOfPoint(SDL_Point& point)
	{
		double distance = sqrt(pow(point.x - center.x, 2) + pow(point.y - center.y, 2));
		return distance * distance - radius * radius;
	}
};

struct Line
{
	SDL_Point p1;
	SDL_Point p2;


};

inline bool operator==(const Line& line1, const Line& line2)
{
	return ((line1.p1 == line2.p1 && line1.p2 == line2.p2) || (line1.p1 == line2.p2 && line1.p2 == line2.p1));
}

struct Triangle
{
	SDL_Point p1;
	SDL_Point p2;
	SDL_Point p3;

};

inline bool operator==(const Triangle& triangle1, const Triangle& triangle2)
{
	return ((triangle1.p1 == triangle2.p1 && triangle1.p2 == triangle2.p2 && triangle1.p3 == triangle2.p3) ||
		(triangle1.p1 == triangle2.p1 && triangle1.p2 == triangle2.p3 && triangle1.p3 == triangle2.p2) ||
		(triangle1.p1 == triangle2.p2 && triangle1.p2 == triangle2.p1 && triangle1.p3 == triangle2.p3) ||
		(triangle1.p1 == triangle2.p2 && triangle1.p2 == triangle2.p3 && triangle1.p3 == triangle2.p1) ||
		(triangle1.p1 == triangle2.p3 && triangle1.p2 == triangle2.p1 && triangle1.p3 == triangle2.p2) ||
		(triangle1.p1 == triangle2.p3 && triangle1.p2 == triangle2.p2 && triangle1.p3 == triangle2.p1));
}