#include "mlx_linux/mlx.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_params {
    void    *mlx;
    void    *win;
    int     beginX;
    int     beginY;
    int     winX;
    int     winY;
} t_params;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	char c;

	if (n < 0)
		return ;
	if (n < 10)
	{
		c = n + 48;
		ft_putchar(c);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
        double deltaX = endX - beginX;
        double deltaY = endY - beginY;
        int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
        deltaX /= pixels;
        deltaY /= pixels;

        double pixelX = beginX;
        double pixelY = beginY;
        while (pixels)
        {
                mlx_pixel_put(mlx, win, pixelX, pixelY, color);
                pixelX += deltaX;
                pixelY += deltaY;
                --pixels;
        }
}

//keys are letters in ascii
int	deal_key(int key, void *param)
{	
	if (key == 65307)
		exit(1);
	ft_putnbr(key);
	return (0);
}

//left click == 1; right click == 3; middle click == 2;
int	deal_mouse(int key,int x, int y, void *params)
{
    t_params *args = (t_params *)params;
    
    printf("x: %d\n", x);
    printf("y: %d\n", y);
    if (key == 1 && !args->beginX && !args->beginY)
    {
        args->beginX = x;
        args->beginY = y;
    }
    else if (key == 1)
	    draw_line(args->mlx, args->win, args->beginX, args->beginY, x, y, 0x00FF00);
    if (key == 3)
    {
        args->beginX = 0;
        args->beginY = 0;
    }

	return (0);
}

int draw_map(int lines, int col, void *params)
{
    t_params *args = (t_params *)params;
    int beginX;
    int beginY;
    int endX;
    int endY;
    int isoBeginX;
    int isoBeginY;
    int isoEndX;
    int isoEndY;
    int init_lines = lines;
    int init_col = col;

    while (lines >= 0)
    {
        beginX = 400 ;
        endX =  400 + col * 100;
        beginY = 100 + lines * 80;
        endY = beginY;
        isoBeginX = (init_lines * 100) / 2 - (lines / 2);
        isoEndX =  (init_lines * 100) - (lines / 2);
        isoBeginY =  beginY / 2;
        isoEndY = endY / 2;
        //draw_line(args->mlx, args->win, beginX, beginY, endX, endY, 0x00FF00);
        draw_line(args->mlx, args->win, isoBeginX, isoBeginY, isoEndX, isoEndY, 0x00FF00);
        lines--;
    }
    while (col >= 0)
    {
        beginX = 400 + col * 100;
        endX = beginX;
        beginY = 100 + init_lines * 80;
        endY = 100;
        isoBeginX = 400 + init_col / 2 - (col / 2);
        isoEndX = init_col - (col / 2);
        isoBeginY = 100 + beginY / 2;
        isoEndY = endY / 2;
        //draw_line(args->mlx, args->win, beginX, beginY, endX, endY, 0x00FF00);
        //draw_line(args->mlx, args->win, isoBeginX, isoBeginY, isoEndX, isoEndY, 0x00FF00);
        col--;
    }
}

int	main(void)
{
    t_params    *params;
    params = malloc(sizeof(t_params *));
	    
    params->mlx = mlx_init();
	params->beginX = 0;
    params->beginY = 0;
    params->winX = 1920;
    params->winY = 1080;
	params->win = mlx_new_window(params->mlx, 1920, 1080, "Training");

    mlx_pixel_put(params->mlx, params->win, params->winX /2, params->winY /2, 0XFF0000);
    //draw_map(4, 4, params);
    mlx_mouse_hook(params->win, deal_mouse, params);
	//mlx_string_put(params->mlx, params->win, 250, 250, 0XFF0000, "Hello world");
	mlx_key_hook(params->win, deal_key, (void *)params);
	mlx_loop(params->mlx);
}
