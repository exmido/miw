/*
Copyright (c) <year> Mido

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef UTF_H
#define UTF_H

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <math.h>

typedef unsigned char utf8;

#if __SIZEOF_WCHAR_T__ == 4 || __WCHAR_MAX__ > 0x10000
#define UCS4_T
typedef unsigned short utf16;
#else
#define UCS2_T
typedef wchar_t utf16;
#endif

//ucs
//wctoi
template <typename T>
inline static int wctoi(const T* c)
{
	return (int)*c;
}

//itowc
template <typename T>
inline static void itowc(int i, T* c)
{
	*c = (T)i;
}

//wcnext
template <typename T>
inline static T* wcnext(T** c, int d = 1)
{
	*c += d;
	return *c;
}

//utf8
//wctoi
inline static int wctoi(const utf8* c)
{
	if(*c <= 0x7F)
		return (int)*c;
	else if(*c <= 0xDF)
		return (((int)c[0] & 0x1F) << 6) | (((int)c[1] & 0x3F));
	else if(*c <= 0xEF)
		return (((int)c[0] & 0xF) << 12) | (((int)c[1] & 0x3F) << 6) | ((int)c[2] & 0x3F);
	else
		return (((int)c[0] & 0x7) << 18) | (((int)c[1] & 0x3F) << 12) | (((int)c[2] & 0x3F) << 6) | ((int)c[3] & 0x3F);

	return (int)*c;
}

//itowc
inline static void itowc(int i, utf8* c)
{
	if(i <= 0x7F)
	{
		*c = (utf8)i;
	}
	else if(i <= 0xDF)
	{
		c[0] = ((i >> 6) & 0x1F) | 0xC0;
		c[1] = (i & 0x3F) | 0x80;
	}
	else if(i <= 0xFFFF)
	{
		c[0] = ((i >> 12) & 0x3F) | 0xE0;
		c[1] = ((i >> 6) & 0x3F) | 0x80;
		c[2] = (i & 0x3F) | 0x80;
	}
	else
	{
		c[0] = ((i >> 18) & 0x3F) | 0xF0;
		c[1] = ((i >> 12) & 0x3F) | 0x80;
		c[2] = ((i >> 6) & 0x3F) | 0x80;
		c[3] = (i & 0x3F) | 0x80;
	}
}

//wcnext
inline static utf8* wcnext(utf8** c, int d = 1)
{
	for(; d > 0; --d)
	{
		if(**c <= 0x7F)
			*c += 1;
		else if(**c <= 0xDF)
			*c += 2;
		else if(**c <= 0xEF)
			*c += 3;
		else
			*c += 4;
	}

	return *c;
}

//utf16
//wctoi
inline static int wctoi(const utf16* c)
{
	if(*c <= 0xD7FF)
		return (int)*c;
	else
		return (((int)c[0] & 0x3FF) << 10) | ((int)c[1] & 0x3FF);

	return (int)*c;
}

//itowc
inline static void itowc(int i, utf16* c)
{
	if(i <= 0xD7FF)
	{
		*c = (utf16)i;
	}
	else
	{
		c[0] = ((i >> 10) & 0x3FF) | 0xD800;
		c[1] = (i & 0x3FF) | 0xDC00;
	}
}

//wcnext
inline static utf16* wcnext(utf16** c, int d = 1)
{
	for(; d > 0; --d)
	{
		if(**c <= 0xD7FF)
			*c += 1;
		else
			*c += 2;
	}

	return *c;
}

//function
//wstrcat
template <typename T>
T* wstrcat(T* destination, const T* source)
{
	return wstrcpy<typename T>(destination + wstrlen(destination), source);
}

template <typename T1, typename T2>
T1* wstrcat(T1* destination, const T2* source)
{
	return wstrcpy<typename T1, typename T2>(destination + wstrlen(destination), source);
}

//wstrcmp
template <typename T>
int wstrcmp(const T* str1, const T* str2)
{
	T* c1 = (T*)str1;
	T* c2 = (T*)str2;

	for(; *c1 == *c2 && *c1 != 0; ++c1, ++c2)
		;

	return wctoi(c1) - wctoi(c2);
}

template <typename T1, typename T2>
int wstrcmp(const T1* str1, const T2* str2)
{
	T1* c1 = (T1*)str1;
	T2* c2 = (T2*)str2;

	for(; wctoi(c1) == wctoi(c2) && *c1 != 0; wcnext(&c1), wcnext(&c2))
		;

	return wctoi(c1) - wctoi(c2);
}

//wstrcpy
template <typename T>
T* wstrcpy(T* destination, const T* source)
{
	T* c1 = (T*)destination;

	for(T* c2 = (T*)source; *c2 != 0; ++c1, ++c2)
		*c1 = *c2;

	*c1 = 0;
	return destination;
}

template <typename T1, typename T2>
T1* wstrcpy(T1* destination, const T2* source)
{
	T1* c1 = (T1*)destination;

	for(T2* c2 = (T2*)source; *c2 != 0; wcnext(&c1), wcnext(&c2))
		itowc(wctoi(c2), c1);

	*c1 = 0;
	return destination;
}

//wstrlen
template <typename T>
int wstrlen(const T* str)
{
	T* c = (T*)str;
	while(*c != 0)
		++c;

	return (int)(long long)(c - str);
}

//wstrnum
template <typename T>
int wstrnum(const T* str)
{
	int num = 0;
	for(T* c = (T*)str; *c != 0; ++num)
		wcnext(&c);

	return num;
}

//wstrncat
template <typename T>
T* wstrncat(T* destination, const T* source, int num)
{
	return wstrncpy<typename T>(destination + wstrlen(destination), source, num);
}

template <typename T1, typename T2>
T1* wstrncat(T1* destination, const T2* source, int num)
{
	return wstrncpy<typename T1, typename T2>(destination + wstrlen(destination), source, num);
}

//wstrncmp
template <typename T>
int wstrncmp(const T* str1, const T* str2, int num)
{
	T* c1 = (T*)str1;
	T* c2 = (T*)str2;

	for(; num > 0 && wctoi(c1) == wctoi(c2) && *c1 != 0; --num, wcnext(&c1), wcnext(&c2))
		;

	return wctoi(c1) - wctoi(c2);
}

template <typename T1, typename T2>
int wstrncmp(const T1* str1, const T2* str2, int num)
{
	T1* c1 = (T1*)str1;
	T2* c2 = (T2*)str2;

	for(; num > 0 && wctoi(c1) == wctoi(c2) && *c1 != 0; --num, wcnext(&c1), wcnext(&c2))
		;

	return wctoi(c1) - wctoi(c2);
}

//wstrncpy
template <typename T>
T* wstrncpy(T* destination, const T* source, int num)
{
	T* c1 = (T*)destination;
	T* c2 = (T*)source;

	for(; num > 0; --num)
	{
		if(*c2 != 0)
		{
			itowc(wctoi(c2), c1);
			wcnext(&c2);
		}
		else
		{
			*c1 = 0;
		}

		wcnext(&c1);
	}

	return destination;
}

template <typename T1, typename T2>
T1* wstrncpy(T1* destination, const T2* source, int num)
{
	T1* c1 = (T1*)destination;
	T2* c2 = (T2*)source;

	for(; num > 0; --num)
	{
		if(*c2 != 0)
		{
			itowc(wctoi(c2), c1);
			wcnext(&c2);
		}
		else
		{
			*c1 = 0;
		}

		wcnext(&c1);
	}

	return destination;
}

//wstrchr
template <typename T>
T* wstrchr(const T* str, int c)
{
	for(T* ret = (T*)str; *ret != 0; wcnext(&ret))
	{
		if(wctoi(ret) == c)
			return ret;
	}

	return NULL;
}

//wstrrchr
template <typename T>
T* wstrrchr(const T* str, int c)
{
	T* ret = NULL;
	for(T* tmp = wstrchr(str, c); tmp != NULL; ret = tmp, tmp = wstrchr(tmp + 1, c))
		;

	return ret;
}

//wstrtok
template <typename T>
T* wstrtok(void* str, const T* delimiters)
{
	static T* next = NULL;
	T* ret;

	if(str)
	{
		for(next = (T*)str; next != NULL && *next != 0 && wstrchr(delimiters, wctoi(next));)
		{
			T* c = next;
			wcnext(&next);

			while(c != next)
				(*c++) = 0;
		}
	}

	if(next != NULL && *next != 0)
		ret = next;
	else
		ret = NULL;

	while(next != NULL && *next != 0 && !wstrchr(delimiters, wctoi(next)))
		wcnext(&next);

	while(next != NULL && *next != 0 && wstrchr(delimiters, wctoi(next)))
	{
		T* c = next;
		wcnext(&next);

		while(c != next)
			(*c++) = 0;
	}

	return ret;
}

//ntow
template <typename T1, typename T2>
T2* ntow(T1 number, int i = 0, int f = 6, int exp = 12, bool lower = false, int base = 10, T2* ret = NULL)
{
	static T2 temp[66] = {};

	if(ret == NULL)
		ret = temp;

	T2* p = ret;

	int det = 0;
	int e = 0;

	if(number >= 0)
	{
		*p = '\0';
	}
	else
	{
		number = 0 - number;
		if(number < 0)
		{
			number = -1 - number;
			det = 1;
		}

		*p = '-';
		++p;
	}

	T1 n;
	if(number != 0 && (T1)(0.1) != 0 && exp != 0)
	{
		e = (int)(log((double)number) / log((double)base));
		if(e)
		{
			n = (T1)(number * pow((double)base, -e));

			if(n < 1)
			{
				n *= 10;
				e -= 1;
			}

			if(abs(e) >= exp)
				number = n;
			else
				e = 0;
		}
	}

	n = (T1)(number / base);
	if(i == 0)
	{
		for(i = 1; n >= 1; n = (T1)(n / base))
			++i;
	}

	p += i;
	if((T1)(0.1) != 0 && f > 0)
	{
		*p++ = '.';
		ntow((unsigned long long)((number - (T1)(unsigned long long)number) * pow((double)base, f)), f, 0, exp, lower, base, p);

		if(e)
		{
			p += f;
			*p++ = lower ? 'e' : 'E';

			if(e > 0)
			{
				*p++ = '+';
			}
			else if(e < 0)
			{
				*p++ = '-';
				e = -e;
			}

			ntow(e, 0, 0, exp, lower, base, p);
		}
	}
	else
	{
		*p = '\0';
	}

	n = number;
	p = ((ret[0] == '-') ? ret + i : ret + i - 1);
	for(; i > 0; --i)
	{
		T2 v = (T2)((unsigned long long)n % base);

		if(v < 10)
			*p-- = (T2)('0' + v + det);
		else if(lower)
			*p-- = (T2)('a' + v - 10 + det);
		else
			*p-- = (T2)('A' + v - 10 + det);

		n = n / base;
		det = 0;
	}

	return ret;
}

//wton
template <typename T1, typename T2>
T2 wton(const T1* str, int* ret = NULL, int base = 10)
{
	T2 v = 0;
	T1* c = (*str == '-' ? (T1*)(str + 1) : (T1*)str);

	for(T2 tmp; ; ++c)
	{
		if(*c >= '0' && *c <= '9')
			tmp = (T2)(*c - '0');
		else if(*c >= 'a' && *c <= 'z')
			tmp = (T2)(*c - 'a' + 10);
		else if(*c >= 'A' && *c <= 'Z')
			tmp = (T2)(*c - 'A' + 10);
		else
			break;

		if(tmp >= base)
			break;

		v = (T2)(v * base + tmp);
	}

	if((T2)(0.1) != 0 && c != str)
	{
		if(*c == '.')
		{
			++c;

			T2 vf = 0;
			T2 div = 1;

			for(T2 tmp; ; ++c)
			{
				if(*c >= '0' && *c <= '9')
					tmp = (T2)(*c - '0');
				else if(*c >= 'a' && *c <= 'z')
					tmp = (T2)(*c - 'a' + 10);
				else if(*c >= 'A' && *c <= 'Z')
					tmp = (T2)(*c - 'A' + 10);
				else
					break;

				if(tmp >= base)
					break;

				vf = (T2)(vf * base + tmp);
				div *= base;
			}

			v = v + vf / div;
		}

		if(*c == 'e' || *c == 'E')
		{
			int e = 0;

			++c;
			switch(*c)
			{
			case '-':
				v = (T2)(v * pow((double)base, -wton<typename T1, int>(++c, &e, base)));
				break;

			case '+':
				++c;
			default:
				v = (T2)(v * pow((double)base, wton<typename T1, int>(c, &e, base)));
			}

			c += e;
		}
	}

	if(ret)
		*ret = (int)(c - str);

	return (*str == '-' ? 0 - v : v);
}

#endif
