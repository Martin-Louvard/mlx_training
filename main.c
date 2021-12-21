#include "mlx_linux/mlx.h"
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

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
	//left click == 1; right click == 3; middle click == 2;
	//draw_line(mlx, mlx_win, 500, 500, 0, 0, 0xFFFFFF);
	ft_putchar('k');
	ft_putnbr(key);
	ft_putchar('\n');
	ft_putchar('x');
	ft_putnbr(x);
	ft_putchar('\n');
	ft_putchar('y');
	ft_putnbr(y);
	ft_putchar('\n');
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	int 	i = 0;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	mlx_mouse_hook(mlx_win, deal_mouse, 0);
	/*while (i++ < 100)
	  {
	  mlx_pixel_put(mlx, mlx_win, 200 + i, 250, 0x00FF00);
	  mlx_pixel_put(mlx, mlx_win, 200, 250 + i, 0x0000FF);
	  mlx_pixel_put(mlx, mlx_win, 200 + i, 350, 0xFF0000);
	  mlx_pixel_put(mlx, mlx_win, 300, 250 + i, 0x00FFF0);
	  }*/
	//mlx_string_put(mlx, mlx_win, 250, 250, 0XFF0000, "Hello world");
	mlx_key_hook(mlx_win, deal_key, 0);
	mlx_loop(mlx);
}
