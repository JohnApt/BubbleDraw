#pragma once
#include <set>

struct Circle
{
	SDL_Point center;
	int radius;

	std::set<Circle*> adjacentCircles;
};

struct Line
{
	SDL_Point p1;
	SDL_Point p2;


};

inline bool operator==(const Line& line1, const Line& line2)
{
	return ((line1.p1.x == line2.p1.x && line1.p1.y == line2.p1.y && line1.p2.x == line2.p2.x && line1.p2.y == line2.p2.y) ||
		(line1.p1.x == line2.p2.x && line1.p1.y == line2.p2.y && line1.p2.x == line2.p1.x && line1.p2.y == line2.p1.y));
}

struct Triangle
{
	SDL_Point p1;
	SDL_Point p2;
	SDL_Point p3;

};

inline bool operator==(const Triangle& triangle1, const Triangle& triangle2)
{
	return ((triangle1.p1.x == triangle2.p1.x && triangle1.p1.y == triangle2.p1.y && triangle1.p2.x == triangle2.p2.x && triangle1.p2.y == triangle2.p2.y && triangle1.p3.x == triangle2.p3.x && triangle1.p3.y == triangle2.p3.y) ||
		(triangle1.p1.x == triangle2.p1.x && triangle1.p1.y == triangle2.p1.y && triangle1.p2.x == triangle2.p3.x && triangle1.p2.y == triangle2.p3.y && triangle1.p3.x == triangle2.p2.x && triangle1.p3.y == triangle2.p2.y) ||
		(triangle1.p1.x == triangle2.p2.x && triangle1.p1.y == triangle2.p2.y && triangle1.p2.x == triangle2.p1.x && triangle1.p2.y == triangle2.p1.y && triangle1.p3.x == triangle2.p3.x && triangle1.p3.y == triangle2.p3.y) ||
		(triangle1.p1.x == triangle2.p2.x && triangle1.p1.y == triangle2.p2.y && triangle1.p2.x == triangle2.p3.x && triangle1.p2.y == triangle2.p3.y && triangle1.p3.x == triangle2.p1.x && triangle1.p3.y == triangle2.p1.y) ||
		(triangle1.p1.x == triangle2.p3.x && triangle1.p1.y == triangle2.p3.y && triangle1.p2.x == triangle2.p1.x && triangle1.p2.y == triangle2.p1.y && triangle1.p3.x == triangle2.p2.x && triangle1.p3.y == triangle2.p2.y) ||
		(triangle1.p1.x == triangle2.p3.x && triangle1.p1.y == triangle2.p3.y && triangle1.p2.x == triangle2.p2.x && triangle1.p2.y == triangle2.p2.y && triangle1.p3.x == triangle2.p1.x && triangle1.p3.y == triangle2.p1.y));
}