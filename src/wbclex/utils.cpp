#include "utils.h"

namespace Utils
{
	char EscapeChar(char c)
	{
		switch(c)
		{
		case 'a':
			return '\a';
		case 'b':
			return '\b';
		case 't':
			return '\t';
		case 'r':
			return '\r';
		case 'v':
			return '\v';
		case 'f':
			return '\f';
		case 'n':
			return '\n';
		default:
			return c;
		}
	}
};