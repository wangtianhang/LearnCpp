#pragma once

#include <exception>
#include "./Learn3D/Mathf.h"

struct Color
{
public:
	float r;

	float g;

	float b;

	float a;

	Color() 
	{
		r = 0;
		g = 0;
		b = 0;
		a = 0;
	}

	static Color red()
	{
		return Color(1, 0, 0, 1);
	}

	static Color green()
	{
		return Color(0, 1, 0, 1);
	}

	static Color blue()
	{
		return Color(0, 0, 1, 1);
	}

	static Color white()
	{
		return Color(1, 1, 1, 1);
	}

	static Color black()
	{
		return Color(0, 0, 0, 1);
	}

	static Color yellow()
	{
		return  Color(1, 0.921568632f, 0.0156862754f, 1);
	}

	static Color cyan()
	{
		return Color(0, 1, 1, 1);
	}

	static Color magenta()
	{
		return Color(1, 0, 1, 1);
	}

	static Color gray()
	{
		return Color(0.5, 0.5, 0.5, 1);
	}

	static Color grey()
	{
		return Color(0.5, 0.5, 0.5, 1);
	}

	static Color clear()
	{
		return Color(0, 0, 0, 0);
	}

	float grayscale()
	{
		return 0.299f * r + 0.587f * g + 0.114f * b;
	}

	float& operator[](int i)
	{
		switch (i)
		{
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		case 3:
			return a;
		default:
			throw std::exception("Color no index");
			break;
		}
	}

	Color(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 1;
	}

	static Color Lerp(Color a, Color b, float t)
	{
		t = Mathf::Clamp01(t);
		return Color(a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t, a.a + (b.a - a.a) * t);
	}

	Color RGBMultiplied(float multiplier)
	{
		return Color(r * multiplier, g * multiplier, b * multiplier, a);
	}

	Color AlphaMultiplied(float multiplier)
	{
		return Color(r, g, b, a * multiplier);
	}

	Color RGBMultiplied(Color multiplier)
	{
		return Color(r * multiplier.r, g * multiplier.g, b * multiplier.b, a);
	}

	Color operator+(const Color & b) const
	{
		Color ret = Color();
		ret.r = this->r + b.r;
		ret.g = this->g + b.g;
		ret.b = this->b + b.b;
		ret.a = this->a + b.a;
		return ret;
	}

	Color operator-(const Color & b) const
	{
		Color ret = Color();
		ret.r = this->r - b.r;
		ret.g = this->g - b.g;
		ret.b = this->b - b.b;
		ret.a = this->a - b.a;
		return ret;
	}

	Color operator*(const Color & b) const
	{
		Color ret = Color();
		ret.r = this->r * b.r;
		ret.g = this->g * b.g;
		ret.b = this->b * b.b;
		ret.a = this->a * b.a;
		return ret;
	}

	Color operator*(float b) const
	{
		Color ret = Color();
		ret.r = this->r * b;
		ret.g = this->g * b;
		ret.b = this->b * b;
		ret.a = this->a * b;
		return ret;
	}

	Color operator/(float b) const
	{
		Color ret = Color();
		ret.r = this->r / b;
		ret.g = this->g / b;
		ret.b = this->b / b;
		ret.a = this->a / b;
		return ret;
	}

	bool operator == (const Color & b) const
	{
		return this->r == b.r
			&& this->g == b.g
			&& this->b == b.b
			&& this->a == b.a;
	}

	bool operator != (const Color & b) const
	{
		return !(*this == b);
	}

	friend Color operator *(const float d, Color b);
};

Color operator *(const float d, Color b);