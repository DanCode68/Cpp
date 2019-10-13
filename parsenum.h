#ifndef PARSE_H
#define PARSE_H
#include <string>
#include <math.h>
bool IsDigit(char c) {return (c >= '0' && c <= '9');}
bool IsPlus(char c) {return (c == '+');}
bool IsMinus(char c) {return (c == '-');}
bool IsSign(char c) {return (IsPlus(c) || IsMinus(c));}
bool IsDot(char c) {return (c == '.');}
bool IsInt(std::string s)
{
	if (!IsDigit(s[0]) && !IsSign(s[0])) {return false;}
	for (int i = 1; i < s.length(); i++)
	{
		if (!IsDigit(s[i])) {return false;}
	}
	return true;
}
bool IsInt(int i)
{
	return true;
}
bool IsInt(float f)
{
	return (f - floor(f) == 0);
}
bool IsInt(double d)
{
	return (d - floor(d) == 0);
}
bool IsNumber(std::string s)
{
	int points = 0;
	if (!IsDigit(s[0]) && !IsSign(s[0]) && !IsDot(s[0])) {return false;}
	for (int i = 1; i < s.length(); i++)
	{
		if (IsDot(s[i])) {points++;}
		if (!IsDigit(s[i]) && !IsDot(s[i])) {return false;}
	}
	return (points <= 1);
}
bool IsNumber(int i)
{
	return true;
}
bool IsNumber(float f)
{
	return true;
}
bool IsNumber(double d)
{
	return true;
}
int ParseInt(char c)
{
	if (IsDigit(c)) {return (c - 48);}
	else {return 0;}
}
int ParseInt(std::string s)
{
	if (!IsInt(s)) {throw "Not an integer";}
	int result = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (IsDigit(s[i])) {result *= 10; result += ParseInt(s[i]);}
	}
	if (IsMinus(s[0])) {result *= -1;}
	return result;
}
int ParseInt(int i)
{
	return i;
}
int ParseInt(float f)
{
	return static_cast<int>(floor(f));
}
int ParseInt(double d)
{
	return static_cast<int>(floor(d));
}
float ParseFloat(std::string s)
{
	if (!IsNumber(s)) {throw "Not a float";}
	float result = 0, factor = 1;
	bool fraction = false;
	for (int i = 0; i < s.length(); i++)
	{
		if (IsDot(s[i])) {fraction = true; continue;}
		if (!fraction && IsDigit(s[i])) {result *= 10; result += ParseInt(s[i]);}
		else if (fraction) {factor *= 0.1; result += ParseInt(s[i]) * factor;}
	}
	if (IsMinus(s[0]) && result > 0) {result *= (-1 * IsMinus(s[0]));}
	return result;
}
float ParseFloat(int i)
{
	return static_cast<float>(i);
}
float ParseFloat(float f)
{
	return f;
}
float ParseFloat(double d)
{
	return static_cast<float>(d);
}
double ParseDouble(std::string s)
{
	if (!IsNumber(s)) {throw "Not a double";}
	double result = 0, factor = 1;
	bool fraction = false;
	for (int i = 0; i < s.length(); i++)
	{
		if (IsDot(s[i])) {fraction = true; continue;}
		if (!fraction && IsDigit(s[i])) {result *= 10; result += ParseInt(s[i]);}
		else if (fraction) {factor *= 0.1; result += ParseInt(s[i]) * factor;}
	}
	if (IsMinus(s[0]) && result > 0) {result *= (-1 * IsMinus(s[0]));}
	return result;
}
double ParseDouble(int i)
{
	return static_cast<double>(i);
}
double ParseDouble(float f)
{
	return static_cast<double>(f);
}
double ParseDouble(double d)
{
	return d;
}
#endif