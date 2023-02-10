#include <cmath>
#include <SDL_video.h>
#include <vector>
#include <iostream>
#include "primitiveStructs.h"
#include "SDL_Util.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

bool isWithinCircumcircle(SDL_Point &point, Triangle &triangle)
{
	double x1 = triangle.p1.x;
	double y1 = triangle.p1.y;
	double x2 = triangle.p2.x;
	double y2 = triangle.p2.y;
	double x3 = triangle.p3.x;
	double y3 = triangle.p3.y;
	double a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	double b = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
	double c = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	double radius = (a * b * c) / (sqrt((a + b + c) * (b + c - a) * (c + a - b) * (a + b - c)));
	double d = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));

	SDL_Point circumCenter;
	circumCenter.x = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / d;
	circumCenter.y = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / d;

	double distance = sqrt((point.x - circumCenter.x) * (point.x - circumCenter.x) + (point.y - circumCenter.y) * (point.y - circumCenter.y));
	
	if (distance > radius)
		return false;
	else return true;
}

bool isUniqueEdge(Line &edge, std::vector<Triangle> &badTriangles, Triangle thisTriangle)
{
	for (Triangle triangle : badTriangles)
	{
		if (triangle == thisTriangle)
			continue;
		Line line1 = { triangle.p1, triangle.p2 };
		Line line2 = { triangle.p2, triangle.p3 };
		Line line3 = { triangle.p3, triangle.p1 };
		if (edge == line1 || edge == line2 || edge == line3)
			return false;
	}
	return true;
}


//See https://en.wikipedia.org/wiki/Bowyer%E2%80%93Watson_algorithm?useskin=vector for algorithm description
std::vector<Triangle> BowyerWatsonAlgorithm(std::vector<SDL_Point> points)
{
	//Create super triangle
	SDL_Point p1 = { 0, 0 };
	SDL_Point p2 = { 0, SCREEN_HEIGHT * 2 };
	SDL_Point p3 = { SCREEN_WIDTH * 2, 0 };
	Triangle superTriangle = { p1, p2, p3 };

	std::vector<Triangle> triangulation = { superTriangle };

	//Add all the points one at a time to the triangulation
	for (SDL_Point point : points)
	{
		std::vector<Triangle> badTriangles;
		for (Triangle &triangle : triangulation)
		{
			//Check if point is inside triangle
			if (isWithinCircumcircle(point, triangle))
			{
				badTriangles.push_back(triangle);
			}
		}
		std::vector<Line> polygon;
		for (Triangle &triangle : badTriangles)
		{
			Line edge1 = { triangle.p1, triangle.p2 };
			Line edge2 = { triangle.p2, triangle.p3 };
			Line edge3 = { triangle.p3, triangle.p1 };
			if (isUniqueEdge(edge1, badTriangles, triangle))
				polygon.push_back(edge1);
			if (isUniqueEdge(edge2, badTriangles, triangle))
				polygon.push_back(edge2);
			if (isUniqueEdge(edge3, badTriangles, triangle))
				polygon.push_back(edge3);
		}
		//Remove bad triangles from triangulation
		for (Triangle triangle : badTriangles)
		{
			for (int i = 0; i < triangulation.size(); i++)
			{
				if (triangulation[i] == triangle)
				{
					triangulation.erase(triangulation.begin() + i);
					break;
				}
			}
		}
		for (Line edge : polygon)
		{
			Triangle newTriangle = { edge.p1, edge.p2, point };
			triangulation.push_back(newTriangle);
		}
	}
	//Remove triangles that contain super triangle points
	for (int i = 0; i < triangulation.size(); i++)
	{
		if (triangulation[i].p1 == superTriangle.p1 || triangulation[i].p1 == superTriangle.p2 || triangulation[i].p1 == superTriangle.p3 ||
			triangulation[i].p2 == superTriangle.p1 || triangulation[i].p2 == superTriangle.p2 || triangulation[i].p2 == superTriangle.p3 ||
			triangulation[i].p3 == superTriangle.p1 || triangulation[i].p3 == superTriangle.p2 || triangulation[i].p3 == superTriangle.p3)
		{
			triangulation.erase(triangulation.begin() + i);
			i--;
		}
	}
	return triangulation;
}
