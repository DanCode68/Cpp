#ifndef CASE_H
#define CASE_H
#include <string>
/*
	ToLower() and ToUpper() functions for individual chars and whole strings
*/
char ToLower(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c - ('A' - 'a');
	}
	else
	{
		return c;
	}
}
std::string ToLower(std::string s)
{
	std::string result = "";
	for (int i = 0; i < s.length(); i++)
	{
		result += ToLower(s[i]);
	}
	return result;
}
char ToUpper(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return c - ('A' - 'a');
	}
	else
	{
		return c;
	}
}
std::string ToUpper(std::string s)
{
	std::string result = "";
	for (int i = 0; i < s.length(); i++)
	{
		result += ToUpper(s[i]);
	}
	return result;
}
#endif