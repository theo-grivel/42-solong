#include	"sl.h"

static int
	sl_conv(char c)
{
	if (c == 'E')
		return (4);
	if (c == 'C')
		return (3);
	if (c == 'P')
		return (2);
	return (c - '0');
}
	/*
	0 empt
	1 wall
	2 play
	3 coll
	4 exit
	5 MLX
	6 MLX_WIN
	*/

static void
	it_is_the_end(t_info *param)
{
	char	**map;
	void	**img;

	map = param->map;
	while (*map)
	{	
		printf("free(%p) : %s\n", *map, *map);
		free(*(map++));
	}
	img = param->img;
	mlx_destroy_window(img[5], img[6]);
	exit(0);
}

static void
	move_player(int movex, int movey, t_info *param)
{
	printf("coll : %d\n", param->coll);
	if (param->map[param->py + movey][param->px + movex] == '1')
		return ;
	if (param->map[param->py + movey][param->px + movex] == 'E')
	{
		if (!param->coll)
			it_is_the_end(param);
		return ;
	}
	if (param->map[param->py + movey][param->px + movex] == 'C')
		param->coll--;
	param->move++;
	printf("move number : %d\n", param->move);
	param->map[param->py][param->px] = '0';
	param->px += movex;
	param->py += movey;
	param->map[param->py][param->px] = 'P';
	sl_displaymap(param->map, param->img);
}

void
	sl_displaymap(char **map, void **img)
{
	int	x;
	int	y;
	int	xi;
	int	yi;
	int	c;

	x = 0;
	xi = 0;
	y = -1;
	yi = 0;
	while (map[++y])
	{
		x = -1;
		xi = 0;
		while (map[y][++x])
		{
			c = sl_conv(map[y][x]);
			mlx_put_image_to_window(img[5], img[6], img[c], xi, yi);
			xi += SPRITE_SIZE;
		}
		yi += SPRITE_SIZE;
	}
	printf("x %d , y %d\n", xi, yi);
	mlx_string_put(img[5], img[6], 10, yi + 32, 0x00ff0000, "Move :");
	mlx_string_put(img[5], img[6], 10 + 36, yi + 32, 0x00ff0000, "42");
}

int
	deal_key(int key, void *param)
{
	if (key == KEY_LEFT || key == KEY_A)
		move_player(-1, 0, param);
	else if (key == KEY_DOWN || key == KEY_S)
		move_player(0, 1, param);
	else if (key == KEY_RIGHT || key == KEY_D)
		move_player(1, 0, param);
	else if (key == KEY_UP || key == KEY_W)
		move_player(0, -1, param);
	else if (key == KEY_ESC)
		it_is_the_end(param);
	else
		printf("key pressed : %d\n", key);
	return (0);
}
