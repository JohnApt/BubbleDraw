#include "drawLines.h"
#include "../Utils/Utils.h"

std::vector<SDL_Point> PixelizeLines(std::vector<Triangle>& triangles, std::vector<Circle>& circles)
{
	for (size_t i = 0; i < triangles.size(); i++)
	{
		Triangle& triangle = triangles[i];
		Circle& circle1 = circles[findCircleIndexWithCenter(triangle.p1, circles)];
		Circle& circle2 = circles[findCircleIndexWithCenter(triangle.p2, circles)];
		Circle& circle3 = circles[findCircleIndexWithCenter(triangle.p3, circles)];

		SDL_Point circumCenter12 = findTriangleWithTwoPoints(triangle.p1, triangle.p2, triangle, triangles)->circumCenter;
		SDL_Point circumCenter23 = findTriangleWithTwoPoints(triangle.p2, triangle.p3, triangle, triangles)->circumCenter;
		SDL_Point circumCenter31 = findTriangleWithTwoPoints(triangle.p3, triangle.p1, triangle, triangles)->circumCenter;

		SDL_Point outterIntersectionPoint12 = findOutterIntersectionPoint(circle1, circle2, circumCenter12);

		std::vector<SDL_Point> points;
		


	}
}

Triangle* findTriangleWithTwoPoints(SDL_Point point1, SDL_Point point2, Triangle& triangle, std::vector<Triangle>& triangles)
{
	for (size_t i = 0; i < triangles.size(); i++)
	{
		if (triangle == triangles[i])
			continue;
		if (triangles[i].p1 == point1 && triangles[i].p2 == point2)
			return &triangles[i];
		if (triangles[i].p2 == point1 && triangles[i].p3 == point2)
			return &triangles[i];
		if (triangles[i].p3 == point1 && triangles[i].p1 == point2)
			return &triangles[i];
	}
	return nullptr;
}

SDL_Point findOutterIntersectionPoint(Circle& circle1, Circle& circle2, SDL_Point circumCenter)
{
	SDL_Point intersectionPoint;
	
	
	
	return intersectionPoint;
}