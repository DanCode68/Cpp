#ifndef PIXEL_H
#define PIXEL_H

#include <string>
#include <vector>

class Pixel
{
    public:
        Pixel(int comp = 3)
        {
            if (comp < 1)
            {
                comp = 1;
            }
			else if (comp > 4)
			{
				comp = 4;
			}

            data = std::vector<int> (comp, 0);
        }

        void SetValue(int member, int value)
        {
            if (member >= 0 && member < data.size())
            {
                data[member] = value;
                ClipValue(data[member]);
            }
        }

        int GetValue(int member)
        {
            if (member >= 0 && member < data.size())
            {
                return data[member];
            }
            else
            {
                return -1;
            }
        }

        std::string GetString()
        {
			std::string result = "";
			
            for (int i = 0; i < data.size(); ++i)
			{
				if (data[i] < 10)
				{
					result += "00";
				}
				else if (data[i] < 100)
				{
					result += "0";
				}
				result += std::to_string(data[i]);
				if (i < data.size() - 1)
				{
					result += ",";
				}
			}

			return result;
        }
		
		int GetComponents()
		{
			return data.size();
		}

    private:
        std::vector<int> data;

        void ClipValue(int &value)
        {
            if (value < 0)
            {
                value = 0;
            }
            else if (value > 255)
            {
                value = 255;
            }
        }
};

#endif