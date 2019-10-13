#ifndef SPLITSTR_H
#define SPLITSTR_H

#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> SplitString(std::string s, std::string &delim)
{
	std::vector<std::string> result;
	
	for (int i = s.find(delim); i != std::string::npos; i = s.find(delim))
	{
		result.push_back(s.substr(0, i));
		s = s.substr(i + 1);
	}
	result.push_back(s);
	
	return result;
}

void SplitString(std::string s, std::string &delim, std::vector<std::string> &v)
{
	for (int i = s.find(delim); i != std::string::npos; i = s.find(delim))
	{
		v.push_back(s.substr(0, i));
		s = s.substr(i + 1);
	}
	v.push_back(s);
}

#endif