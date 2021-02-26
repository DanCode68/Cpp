#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

//https://github.com/nothings/stb
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
//#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb_image_write.h"

#include "../args.h"
#include "../parsenum.h"
#include "../color.h"

typedef unsigned int uint;
typedef unsigned char uchar;
typedef pair<int, int> point;       // 2d coordinate pair
typedef map<point, bool> grid2D;    // 2d space with active/inactive value at each point

enum Direction { UP, RIGHT, DOWN, LEFT };

class Ant
{
    protected:
        int x, y;
        Direction facing;

        void Turn(bool clockwise)
        {
            if (clockwise)
            {
                switch(facing)
                {
                    case Direction::UP:
                        facing = Direction::RIGHT;
                        break;
                    case Direction::RIGHT:
                        facing = Direction::DOWN;
                        break;
                    case Direction::DOWN:
                        facing = Direction::LEFT;
                        break;
                    case Direction::LEFT:
                        facing = Direction::UP;
                        break;
                    default:
                        break;
                }
            }
            else
            {
                switch(facing)
                {
                    case Direction::UP:
                        facing = Direction::LEFT;
                        break;
                    case Direction::RIGHT:
                        facing = Direction::UP;
                        break;
                    case Direction::DOWN:
                        facing = Direction::RIGHT;
                        break;
                    case Direction::LEFT:
                        facing = Direction::DOWN;
                        break;
                    default:
                        break;
                }
            }
            
        }

    public:
        Ant(int x = 0, int y = 0, Direction facing = UP)
        {
            this->x = x;
            this->y = y;
            this->facing = facing;
        }

        void Step(grid2D &grid)
        {
            bool value = grid[point(x, y)];     // get active/inactive state of current point in 2d space
            Turn(!value);                       // turn clockwise on inactive, counterclockwise on active
            grid[point(x, y)] = !value;         // flip active/inactive state of point

            switch(facing)                      // move forward based on facing direction
            {
                case Direction::UP:             // -y is up, +y is down, like pixels in an image
                    --y;
                    break;
                case Direction::RIGHT:          // +x is right, -x is left
                    ++x;
                    break;
                case Direction::DOWN:
                    ++y;
                    break;
                case Direction::LEFT:
                    --x;
                    break;
                default:
                    break;
            }
        }

        point GetPosition()
        {
            return point(x, y);
        }
};

void PrintGrid(grid2D &grid, bool values)
{
    for (grid2D::const_iterator it = grid.begin(); it != grid.end(); ++it)
    {
        cout << "(" << it->first.first << ", " << it->first.second << ")";
        
        if (values)
        {
            cout << " = " << it->second;
        }

        cout << "\n";
    }
}

// remove data for inactive points
// return min and max values of active columns and rows
pair<point, point> ProcessGrid(grid2D &grid, bool target)
{
    if (grid.empty())       // no data, no processing is necessary
    {
        return pair<point, point>(point(0, 0), point(0, 0));
    }

    grid2D::iterator it = grid.begin();
    point min = point(it->first.first, it->first.second);
    point max = point(min.first, min.second);

    while (it != grid.end())
    {
        if (it->second == target)
        {
            it = grid.erase(it);    // erase inactive point data, automatically iterates
        }
        else
        {
            // track min and max for x and y for active points
            if (it->first.first < min.first)
            {
                min.first = it->first.first;
            }
            if (it->first.second < min.second)
            {
                min.second = it->first.second;
            }

            if (it->first.first > max.first)
            {
                max.first = it->first.first;
            }
            if (it->first.second > max.second)
            {
                max.second = it->first.second;
            }

            ++it;       // manually iterate after active points
        }
    }

    return pair<point, point>(min, max);
}

int main(int argc, char* argv[])
{
    Args args(argc, argv);
    string param;           // temp variable for arg values

    // can be overwitten by args
    uint count = 11000;
    Direction facing = Direction::LEFT;
    Color colorAnt(255, 0, 0);
    string fileNameIn;
    string fileNameOut = "Langton";

    // internal variables
    Color colorOn(0, 0, 0);
    Color colorOff(255, 255, 255);
    grid2D grid;
    string fileExt = ".png";
    uchar cutoff = 128;
    ifstream inFile;
    int widthIn = 0, heightIn = 0, bitsIn, compIn = 1;
    int x, y;

    // handle custom iteration count from args
    if (args.HasParam("count"))
    {
        param = args.GetParam("count");
        if (IsInt(param))
        {
            count = ParseInt(param);
        }
        else
        {
            cout << "ERROR: invalid iteration count\n";
            return -1;
        }
        
    }

    // abort if iteration count is impossible
    if (count < 1)
    {
        cout << "ERROR: invalid iteration count\n";
        return -1;
    }

    // handle custom seed image from args
    if (args.HasParam("seed"))
    {
        fileNameIn = args.GetParam("seed");

        inFile.open(fileNameIn + fileExt);
        if (inFile.is_open())               // check if file can be successfully opened
        {
            inFile.close();                 // close file, it actually deosn't need to be open

            // read in image data
            uchar* imageIn = stbi_load((fileNameIn + fileExt).c_str(), &widthIn, &heightIn, &bitsIn, compIn);

            x = 0;
            y = 0;
            for(uint i = 0; i < widthIn * heightIn * compIn; i += compIn)
            {
                if (imageIn[i] < cutoff)    // find pixels close enough to black
                {
                    // convert position in array to 2d corrdinates
                    x = i % widthIn;
                    y = i / widthIn;
                    // set 2d point to active
                    grid[point(x, y)] = true;
                }
            }
        }
        else    // seed file specified but cannot be opened
        {
            cout << "ERROR: could not open \"" << (fileNameIn + fileExt) << "\"\n";
            return -1;
        }
    }

    // handle custom output image name from args
    if (args.HasParam("out"))
    {
        fileNameOut = args.GetParam("out");
    }

    // handle custom ant color from args
    if (args.HasParam("ant"))
    {
        param = args.GetParam("ant");
        if (IsHex(param))
        {
            colorAnt = Color(param);
        }
    }

    // handle custom facing direction from args
    if (args.HasParam("face"))
    {
        param = args.GetParam("face");
        if (param == "u" || param == "U")
        {
            facing = Direction::UP;
        }
        else if (param == "r" || param == "R")
        {
            facing = Direction::RIGHT;
        }
        else if (param == "d" || param == "D")
        {
            facing = Direction::DOWN;
        }
        else if (param == "l" || param == "L")
        {
            facing = Direction::LEFT;
        }
        else
        {
            cout << "ERROR: invalid facing direction\nvalid directions: U D R L\n";
            return -1;
        }
        
    }

    // start ant in the middle of the current image, will be (0, 0) if there is no seed
    Ant ant(widthIn / 2, heightIn / 2, facing);
    for (uint i = 0; i < count; ++i)    // repeatedly perform ant operations
    {
        ant.Step(grid);
    }

    pair<point, point> bounds = ProcessGrid(grid, false);   // remove data for inactive points and get min/max x/y values

    // calculate final min and max x and y values, counting ant position if necessary
    point end = ant.GetPosition();
    point min = bounds.first;
    if (end.first < min.first)
    {
        min.first = end.first;
    }
    if (end.second < min.second)
    {
        min.second = end.second;
    }
    point max = bounds.second;
    if (end.first > max.first)
    {
        max.first = end.first;
    }
    if (end.second > max.second)
    {
        max.second = end.second;
    }

    point offset = point(min.first * -1, min.second * -1);      // calculate offsets for coordinate conversion to non-negative space

    // calculate dimensions of output image
    uint widthOut = max.first - min.first + 1;
    uint heightOut = max.second - min.second + 1;

    uint compOut = 3;       // bit depth of output image pixels

    // prepare 1d data array for pixel values
    uchar* imageOut = new uchar[widthOut * heightOut * compOut];
    uint index = 0;

    // initialize all pixel values to match inactive state
    for (uint j = 0; j < heightOut; ++j)
    {
        for (uint i = 0; i < widthOut; ++i)
        {
            // set pixel RGB values, assumes bit depth of 3
            imageOut[index++] = colorOff.GetRed();
            imageOut[index++] = colorOff.GetGreen();
            imageOut[index++] = colorOff.GetBlue();
        }
    }

    // set pixel values to match active state for stored active points
    for (grid2D::const_iterator it = grid.begin(); it != grid.end(); ++it)
    {
        // apply offset and bit depth in generating 2d coordinates
        x = (it->first.first + offset.first) * compOut;
        y = (it->first.second + offset.second) * compOut;

        index = (y * widthOut) + x;     // convert 2d coordinates to 1d index

        // set pixel RGB values, assumes bit depth of 3
        imageOut[index++] = colorOn.GetRed();
        imageOut[index++] = colorOn.GetGreen();
        imageOut[index++] = colorOn.GetBlue();
    }

    // get final coordinates of ant
    x = (end.first + offset.first) * compOut;
    y = (end.second + offset.second) * compOut;

    index = (y * widthOut) + x;     // convert 2d coordinates to 1d index

    // set pixel RGB values for ant, assumes bit depth of 3
    imageOut[index++] = colorAnt.GetRed();
    imageOut[index++] = colorAnt.GetGreen();
    imageOut[index++] = colorAnt.GetBlue();

    // write output image
    stbi_write_png((fileNameOut + fileExt).c_str(), widthOut, heightOut, compOut, imageOut, widthOut * compOut);

	return 0;
}