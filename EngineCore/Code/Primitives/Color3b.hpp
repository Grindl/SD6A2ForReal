#pragma once
#ifndef include_COLOR3B
#define include_COLOR3B

#include "Color4f.hpp"

class Color3b
{
public:
	UCHAR r, g, b;

	Color3b()
	{
		r = 255;
		g = 255;
		b = 255;
	}
	Color3b(Color4f init)
	{
		r = (int)(init.red*255);
		g = (int)(init.green*255);
		b = (int)(init.blue*255);
	}

	const bool operator==(const Color3b& rhs) const
	{
		bool isEqual = true;
		isEqual = isEqual && (r == rhs.r);
		isEqual = isEqual && (g == rhs.g);
		isEqual = isEqual && (b == rhs.b);
		return isEqual;
	}
};

#endif