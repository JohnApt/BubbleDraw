#include "drawLines.h"
#include "../Utils/Utils.h"
#include "../Utils/SDL_Util.h"


Triangle* findTriangleWithTwoPoints(SDL_Point point1, SDL_Point point2, Triangle& triangle, std::vector<Triangle>& triangles);

SDL_Point findOutterIntersectionPoint(Circle& circle1, Circle& circle2, SDL_Point circumCenter);

double distanceBetweenPoints(SDL_Point point1, SDL_Point point2);

void drawLines(std::vector<Triangle> triangles, std::vector<Circle> circles, SDL_Renderer* gRenderer)
{
	for (size_t i = 0; i < triangles.size(); i++)
	{
		Triangle& triangle = triangles[i];
		Circle& circle1 = circles[findCircleIndexWithCenter(triangle.p1, circles)];
		Circle& circle2 = circles[findCircleIndexWithCenter(triangle.p2, circles)];
		Circle& circle3 = circles[findCircleIndexWithCenter(triangle.p3, circles)];

		SDL_Point circumCenter12;
		if (findTriangleWithTwoPoints(triangle.p1, triangle.p2, triangle, triangles) != nullptr)
		{
			circumCenter12 = findTriangleWithTwoPoints(triangle.p1, triangle.p2, triangle, triangles)->circumCenter;
		}
		else
		{
			circumCenter12.x = -1;
			circumCenter12.y = -1;
		}
		
		SDL_Point circumCenter23;
		if (findTriangleWithTwoPoints(triangle.p2, triangle.p3, triangle, triangles) != nullptr)
		{
			circumCenter23 = findTriangleWithTwoPoints(triangle.p2, triangle.p3, triangle, triangles)->circumCenter;
		}
		else
		{
			circumCenter23.x = -1;
			circumCenter23.y = -1;
		}
		
		SDL_Point circumCenter31;
		if (findTriangleWithTwoPoints(triangle.p3, triangle.p1, triangle, triangles) != nullptr)
		{
			circumCenter31 = findTriangleWithTwoPoints(triangle.p3, triangle.p1, triangle, triangles)->circumCenter;
		}
		else
		{
			circumCenter31.x = -1;
			circumCenter31.y = -1;
		}

		SDL_Point outterIntersectionPoint12 = findOutterIntersectionPoint(circle1, circle2, circumCenter12);
		SDL_Point outterIntersectionPoint23 = findOutterIntersectionPoint(circle2, circle3, circumCenter23);
		SDL_Point outterIntersectionPoint31 = findOutterIntersectionPoint(circle3, circle1, circumCenter31);
		
		if (circumCenter12.x != -1 && circumCenter12.y != -1 && outterIntersectionPoint12.x != -1 && outterIntersectionPoint12.y != -1)
		{
			SDL_RenderDrawLine(gRenderer, circumCenter12.x, circumCenter12.y, outterIntersectionPoint12.x, outterIntersectionPoint12.y);
		}
		if (circumCenter23.x != -1 && circumCenter23.y != -1 && outterIntersectionPoint23.x != -1 && outterIntersectionPoint23.y != -1)
		{
			SDL_RenderDrawLine(gRenderer, circumCenter23.x, circumCenter23.y, outterIntersectionPoint23.x, outterIntersectionPoint23.y);
		}
		if (circumCenter31.x != -1 && circumCenter31.y != -1 && outterIntersectionPoint31.x != -1 && outterIntersectionPoint31.y != -1)
		{
			SDL_RenderDrawLine(gRenderer, circumCenter31.x, circumCenter31.y, outterIntersectionPoint31.x, outterIntersectionPoint31.y);
		}

		


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
	SDL_Point intersectionPoint1;
	SDL_Point intersectionPoint2;
	
	double distanceBetweenCenters = sqrt(pow(circle1.center.x - circle2.center.x, 2) + pow(circle1.center.y - circle2.center.y, 2));
	if (distanceBetweenCenters > circle1.radius + circle2.radius && distanceBetweenCenters < circle1.radius - circle2.radius)
		return { -1, -1 };
	
	double a = (pow(circle1.radius, 2) - pow(circle2.radius, 2) + pow(distanceBetweenCenters, 2)) / (2 * distanceBetweenCenters);
	double h = sqrt(pow(circle1.radius, 2) - pow(a, 2));
	
	intersectionPoint1.x = circle1.center.x + a * (circle2.center.x - circle1.center.x) / distanceBetweenCenters;
	intersectionPoint1.y = circle1.center.y + a * (circle2.center.y - circle1.center.y) / distanceBetweenCenters;
	intersectionPoint2.x = circle1.center.x + a * (circle2.center.x - circle1.center.x) / distanceBetweenCenters;
	intersectionPoint2.y = circle1.center.y + a * (circle2.center.y - circle1.center.y) / distanceBetweenCenters;
	
	intersectionPoint1.x += h * (circle2.center.y - circle1.center.y) / distanceBetweenCenters;
	intersectionPoint1.y -= h * (circle2.center.x - circle1.center.x) / distanceBetweenCenters;
	intersectionPoint2.x -= h * (circle2.center.y - circle1.center.y) / distanceBetweenCenters;
	intersectionPoint2.y += h * (circle2.center.x - circle1.center.x) / distanceBetweenCenters;
	
	if (distanceBetweenPoints(intersectionPoint1, circumCenter) > distanceBetweenPoints(intersectionPoint2, circumCenter))
		return intersectionPoint1;
	else
		return intersectionPoint2;
}