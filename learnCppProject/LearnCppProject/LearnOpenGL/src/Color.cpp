#include "./DebugMemory.h"

#include "./Color.h"


Color operator*(const float d, Color b)
{
	Color ret = Color();
	ret.r = b.r * d;
	ret.g = b.g * d;
	ret.b = b.b * d;
	ret.a = b.a * d;
	return ret;
}
