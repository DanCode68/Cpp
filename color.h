#ifndef COLOR_H
#define COLOR_H

#include <iostream>

unsigned int GetRed(unsigned int c)
{
	return (c & 0x00ff0000) >> 16;
}
unsigned int GetGreen(unsigned int c)
{
	return (c & 0x0000ff00) >> 8;
}
unsigned int GetBlue(unsigned int c)
{
	return c & 0x000000ff;
}

class Color
{
    public:
        Color(int r = 0, int g = 0, int b = 0)
        {
            red = (unsigned char) r;
            green = (unsigned char) g;
            blue = (unsigned char) b;
        }

        #ifdef PARSE_H
            Color(string rgb)
            {
                rgb = rgb.substr(0, 6);
                for (unsigned int i = rgb.length(); i < 6; ++i)
                {
                    rgb += '0';
                }
                red = ParseHex(rgb.substr(0, 2));
                green = ParseHex(rgb.substr(2, 2));
                blue = ParseHex(rgb.substr(4, 2));
            }
        #endif

        int GetRed() { return (int) red; }

        int GetGreen() { return (int) green; }

        int GetBlue() { return (int) blue; }

        void Print()
        {
            std::cout << "(" << GetRed() << ", " << GetGreen() << ", " << GetBlue() << ")";
        } 

        Color& operator++()     // prefix increment
        {
            green++;
            if (green == 0)
            {
                blue++;
                if (blue == 0)
                {
                    red++;
                }
            }
            return *this;
        }

        Color operator++(int)   //postfix increment
        {
            Color temp = *this;
            ++*this;
            return temp;
        }

        Color& operator--()     //prefix decrement
        {
            green--;
            if (green == 255)
            {
                blue--;
                if (blue == 255)
                {
                    red--;
                }
            }
            return *this;
        }

        Color operator--(int)   //postfix decrement
        {
            Color temp = *this;
            --*this;
            return temp;
        }
    
    protected:
        unsigned char red, green, blue;
};

#endif