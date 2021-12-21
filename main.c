#include "mlx_linux/mlx.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

typedef struct s_params {
    void    *mlx;
    void    *win;
    int     beginX;
    int     beginY;
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

int	deal_key(int key, void *param)
{	
	//keys are letters in ascii
	if (key == 65307)
		exit(1);
	ft_putnbr(key);
	return (0);
}

int	deal_mouse(int key,int x, int y, void *params)
{
    t_params *args = (t_params *)params;
	//left click == 1; right click == 3; middle click == 2;
    
    if (key == 1 && !args->beginX && !args->beginY)
    {
        args->beginX = x;
        args->beginY = y;
    }
    else if (key == 1)
	    draw_line(args->mlx, args->win, args->beginX, args->beginY, x, y, 0xFFFFFF);
    if (key == 3)
    {
        args->beginX = 0;
        args->beginY = 0;
    }

	return (0);
}

int	main(void)
{
    t_params    *params;
    params = malloc(sizeof(t_params *));
    //int 	i = 0;

	params->mlx = mlx_init();
	params->win = mlx_new_window(params->mlx, 500, 500, "Hello world!");
	params->beginX = 0;
    params->beginY = 0;

    mlx_mouse_hook(params->win, deal_mouse, params);
	//mlx_string_put(params->mlx, params->win, 250, 250, 0XFF0000, "Hello world");
	mlx_key_hook(params->win, deal_key, (void *)params);
	mlx_loop(params->mlx);
}
