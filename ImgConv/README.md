# ImgConv

Converts an image to a text file containing a matrix of pixel information

Pixel info format:

\#		= grayvalue

#,#		= grayvalue,alpha

#,#,#	= red,green,blue

#,#,#,# = red,green,blue,alpha

Requires the public-domain header file "stb_image.h" from https://github.com/nothings/stb

Currently tested with .jpg and .png files, should be compatible with all the same formats as "stb_image.h"

# ImgPrint

Prints ASCII characters to the Windows console representing a grayscale image saved as a text file by ImgConv
