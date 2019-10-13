#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "../args.h"
#include "../parsenum.h"
#include "../split.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<string> args = GetArgs(argc, argv);
    bool wideCharMode = find(args.begin(), args.end(), "-s") == args.end() && find(args.begin(), args.end(), "-slim") == args.end();
	
	int pixelBreakpoints[] = {51, 102, 153, 204, 255};
	int pixelChars[] = {32, 176, 177, 178, 219};

    vector<vector<int>> matrix;

    string imageName = "image.txt";

    string text;
    vector<string> pixelsInRow, componentsInPixel;
    string delimPixel = " ", delimComponent = ",";
    int found, value;
    vector<int> row;
    char printChar;
    bool printInConsole = true;

    cout << "Printing in Windows console may not work as expected if the image is too wide.\nIt is recommended to set the console to full-screen mode and use an image with a width of 100 pixels or less.\nThis program can also be run with the parameter \"-slim\" or \"-s\" to display an image horizontally-compressed.\n\nEnter file name: ";
    cin >> imageName;
    cout << "\n";

    ifstream file;
    file.open(imageName);
    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, text);
            pixelsInRow.clear();
            SplitString(text, delimPixel, pixelsInRow);

            for(int i = 0; i < pixelsInRow.size(); ++i)
            {
                componentsInPixel.clear();
                SplitString(pixelsInRow[i], delimComponent, componentsInPixel);

                if (componentsInPixel.size() != 1)
                {
                    printInConsole = false;
                    break;
                }
                else
                {
                    row.push_back(ParseInt(componentsInPixel[0]));
                }
                
            }

            if (printInConsole)
            {
                matrix.push_back(row);
                row.clear();
            }
            else
            {
                break;
            }
            
        }

        file.close();

        if (printInConsole)
        {
            for (int i = 0; i < matrix.size(); ++i)
            {
                for (int j = 0; j < matrix[i].size(); ++j)
                {
                    value = matrix[i][j];
                    if (value <= pixelBreakpoints[0])
                    {
                        printChar = pixelChars[0];
                    }
                    else if (value <= pixelBreakpoints[1])
                    {
                        printChar = pixelChars[1];
                    }
                    else if (value <= pixelBreakpoints[2])
                    {
                        printChar = pixelChars[2];
                    }
                    else if (value <= pixelBreakpoints[3])
                    {
                        printChar = pixelChars[3];
                    }
                    else if (value <= pixelBreakpoints[4])
                    {
                        printChar = pixelChars[4];
                    }

                    cout << printChar;

                    if (wideCharMode)
                    {
                        cout << printChar;
                    }
                }
                cout << "\n";
            }
        }
        else
        {
            cout << "Error: could not display pixels from \'" << imageName << "\' in console\n";
        }
        
    }
    else
    {
        cout << "Error: could not open \'" << imageName << "\'\n";
    }
    

    return 0;
}