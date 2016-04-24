#include <string>
#include <algorithm>

using namespace std;
//take two strings compare distance apart
//returns number of transformations needed to change one word to the other
int stringDistance(string a, string b)//a is start word b is end word
{
	int d = 0;
	if(b.size() >= a.size())//perform adds
	{
		int longSubStr = 0;
		int longPos = 0;
		for(unsigned int i = 0; i < a.size();i++)//find longest substring which occurs in both
		{
			int subStr = 0;
			int pos = 0;
			if(a.at(i) == b.at(i))
			{
				if(subStr == 0)
				{
					pos = a.at(i);
				}
				subStr++;
			}
			else if((a.at(i) != b.at(i)) && subStr == 0)
			{
				if(subStr > longSubStr)
				{
					longSubStr = subStr;
					longPos = pos;//replace
				}
				subStr = 0;
			}
	}
		int deltaX = b.size() - a.size();
		if(longPos == 0)//matching prefix
		{
			a.insert(a.size(), a.size() - deltaX,'.');
		}
		else //matching somewhere else
		{
			if(deltaX > longSubStr)
			{
				a.insert(0, longPos, '.');
				a.insert(longPos + longSubStr, (deltaX - longSubStr) + (longPos + longSubStr),'.');
			}
			else
			{
				a.insert(0,deltaX,'.');
			}
		}
		d += deltaX;
	}
	if(a.size() >= b.size())//perform removes
	{
		int longSubStr = 0;
		int longPos = 0;
		for(unsigned int i = 0; i < b.size();i++)//find longest substring which occurs in both
		{
			int subStr = 0;
			int pos = 0;
			if(a.at(i) == b.at(i))
			{
				if(subStr == 0)
				{
					pos = a.at(i);
				}
				subStr++;
			}
			else if((a.at(i) != b.at(i)) && subStr == 0)
			{
				if(subStr > longSubStr)
				{
					longSubStr = subStr;
					longPos = pos;//replace
				}
				subStr = 0;
			}
		}
		int deltaX = a.size() - b.size();
		if(longPos == 0)//matching prefix
		{
			a.erase(a.size(), a.size() - deltaX);
		}
		else //matching somewhere else
		{
			if(deltaX > longSubStr)
			{
				a.erase(0, longPos);
				a.erase(longPos + longSubStr, (deltaX - longSubStr) + (longPos + longSubStr));
			}
			else
			{
				a.erase(0, deltaX);
			}
		}
		d += deltaX;
	}
	for(unsigned int i = 0; i < a.size(); i++)//perform subs always check
	{
		if(a.at(i) != b.at(i))
		{
			d++;
		}
	}
	return d;
}
