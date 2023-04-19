#include "mini_paint.h"

int ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return(i);
}

int ft_error(char *msg)
{
	write(1, msg, ft_strlen(msg));
	return(1);
}

int check_pos(float x, float y, float center_x, float center_y, float radius)
{
	float distance = sqrtf((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));
	if (distance <= radius)
	{
		if ((distance - radius) < 1.0000000)
			return(1);
		return(2);
	}
	return(0);
}

int main(int argc, char **argv)
{
	int x, y, pos, read, b_width, b_height;
	float radius, center_x, center_y;
	char background, id, color;
	char *canvas;
	FILE *file;

	if (argc != 2)
		return(ft_error("Error: argument"));
	if(!(file = fopen(argv[1], "r")) ||
			(fscanf(file, "%d %d %c\n", &b_width, &b_height, &background) != 3) ||
			(!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300)) ||
			(!(canvas = (char *)malloc(sizeof(char) * (b_width * b_height)))))
		return(ft_error("Error: Operation file corrupted"));
	memset(canvas, background, b_width * b_height);
	while((read = fscanf(file, "%c %f %f %f %c\n", &id, &center_x, &center_y, &radius, &color)) == 6)
	{
		if (!(radius > 0) || !(id == 'c' || id == 'C'))
			break ;
		y = -1;
		while(++y < b_height)
			{
				x = -1;
				while(++x < b_width)
				{
					pos = check_pos((float) x, (float)y, center_x, center_y, radius);
					if (pos == 1 || (pos == 2 && id == 'C'))
						canvas[y * b_width + x] = color;
				}
			}
	}
	if(read != -1)
	{
		free(canvas);
		return(ft_error("Error: Operation file corrupted"));
	}
	y = -1;
	while(++y < b_height)
	{
		write(1, canvas + y * b_width, b_width);
		write(1, "\n", 1);
	}
	free(canvas);
	fclose(file);
	return(0);
}
