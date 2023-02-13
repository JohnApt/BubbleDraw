#pragma once
#include <SDL.h>
#include <vector>

struct Circle
{
	SDL_Point center;
	int radius;

	std::vector<int> adjacentCircleIndices;

	double powerOfPoint(SDL_Point& point)
	{
		int a = point.x - center.x;
		int b = point.y - center.y;
		return a * a + b * b - radius * radius;
	}
};

struct Line
{
	SDL_Point p1;
	SDL_Point p2;
};

bool operator==(const Line& line1, const Line& line2);

struct Triangle
{
	SDL_Point p1;
	SDL_Point p2;
	SDL_Point p3;

	SDL_Point calculateCircumCenter()
	{
		double x1 = p1.x;
		double y1 = p1.y;
		double x2 = p2.x;
		double y2 = p2.y;
		double x3 = p3.x;
		double y3 = p3.y;

		double a = x1 - x2;
		double b = y1 - y2;
		double c = x1 - x3;
		double d = y1 - y3;
		double e = (x1 * x1 - x2 * x2 + y1 * y1 - y2 * y2) / 2;
		double f = (x1 * x1 - x3 * x3 + y1 * y1 - y3 * y3) / 2;

		double x = (d * e - b * f) / (d * a - b * c);
		double y = (a * f - c * e) / (a * d - b * c);

		return { (int)x, (int)y };
	}
	SDL_Point circumCenter = calculateCircumCenter();
	double a = circumCenter.x - p1.x;
	double b = circumCenter.y - p1.y;
	double circumRadius = sqrt(a * a + b * b);
};

bool operator==(const Triangle& triangle1, const Triangle& triangle2);