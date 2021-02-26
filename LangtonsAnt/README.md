# Langton

An implementation of [Langton's Ant] (https://en.wikipedia.org/wiki/Langton%27s_ant)

Requires the public-domain header files "stb_image.h" and "stb_image_write.h" from https://github.com/nothings/stb

## Parameters:
Enter command-line parameters in the form "-name=value" (i.e. -count=1000)

*param*		*default*		*description*
count		11000			number of times the ant should perform its "turn, change color, move forward" process
seed					name of .png file to use as the starting configuration of white/black spaces
out		Langton			name of .png file to store the resulting configuration of white/black spaces and ant position
ant		ff0000			6-digit hex string for the color of the ant in the final image
face		L			direction the ant should face at the start of the process
