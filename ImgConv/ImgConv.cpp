#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "../args.h"
#include "../pixel.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

using namespace std;

int main(int argc, char* argv[])
{
	vector<string> args = GetArgs(argc, argv);

	int width, height, bpp, comp, compDefault = 1;

	uint8_t* image;
	vector<vector<Pixel>> matrix;

	string imageName = "image.png";
	string newName = "image.txt";
	
	cout << "Original file:\n>> ";
	getline(cin, imageName);
	cout << "\nNew file:\n>> ";
	getline(cin, newName);
	cout << "\nPixel components (1 for B/W, 3, for RGB, 4 for RGBA):\n>> ";
	try
	{
		cin >> comp;
	}
	catch(...)
	{
		cout << "Error: invalid component value; using default value of " << compDefault << "\n";
		comp = compDefault;
	}

	if (comp != 1 && comp != 3 && comp != 4)
	{
		cout << "Error: invalid component value; using default value of " << compDefault << "\n";
		comp = compDefault;
	}
	
	ifstream file;
	file.open(imageName);
	if (file.is_open())
	{
		file.close();
		image = stbi_load(imageName.c_str(), &width, &height, &bpp, comp);
		
		matrix = vector<vector<Pixel>> (height, vector<Pixel> (width, Pixel(comp)));

		int x = 0, y = 0;
		for (int i = 0; i < width * height * comp; i += comp)
		{
			if (x >= width)
			{
				x = 0;
				++y;
			}
			for (int j = 0; j < comp; ++j)
			{
				matrix[y][x].SetValue(j, image[i + j]);
			}
			x++;
		}
		
		stbi_image_free(image);

		ofstream newFile;
		
		if (newName.compare(imageName) != 0)
		{
			newFile.open(newName);
			if (newFile.is_open())
			{
				for (int i = 0; i < matrix.size(); ++i)
				{
					for (int j = 0; j < matrix[i].size(); ++j)
					{
						newFile << matrix[i][j].GetString();

						if (j < matrix[i].size() - 1)
						{
							newFile << " ";
						}
					}

					if (i < matrix.size() - 1)
					{
						newFile << "\n";
					}
				}
			}
			else
			{
				cout << "Error: could not write \'" << newName << "\'\n";
			}
		}

		file.close();
	}
	else
	{
		cout << "Error: could not open \'" << imageName << "\'\n";
	}
	
	return 0;
}