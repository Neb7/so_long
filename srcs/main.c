/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:53:46 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/06 18:21:20 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

/*void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		puts("Hello ");

	// If we RELEASE the 'K' key, print "World".
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		puts("World");

	// If we HOLD the 'L' key, print "!".
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("!");
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(0);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		mlx_image_to_window(mlx, img, 100, 0);
	(void)param;
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->height, mlx->height);
}*/

int	main(int ac, char **av)
{
	t_map		*map;

	if (ac != 2)
	{
		write(2, "Error: Wrong format\nTry: ./so_long [MAP]\n", 41);
		return (EXIT_SUCCESS);
	}
	map = (t_map *)malloc(sizeof(t_map));
	ft_init_map(&map);
	if (!map)
		return (ft_exit_fail(ERR_MALLOC), EXIT_FAILURE);
	ft_this_is_sparsing(av[1], &map);
	map->win = ft_init_win(&map);
	ft_set_windows(&map);
	mlx_key_hook(map->win->win, &my_keyhook, map);
	mlx_loop_hook(map->win->win, &main_loop, map);
	mlx_loop(map->win->win);
	ft_free_map(&map);
	return (EXIT_SUCCESS);
}

void	ft_init_map(t_map **map)
{
	(*map)->i_player[0] = 0;
	(*map)->i_player[1] = 0;
	(*map)->lenght = 0;
	(*map)->map = NULL;
	(*map)->nb_collectible = 0;
	(*map)->height = 0;
	(*map)->win = NULL;
	(*map)->nb_move = 0;
	(*map)->img_win = NULL;
	(*map)->time = 0;
}

t_windows	*ft_init_win(t_map **map)
{
	t_windows	*new;

	new = (t_windows *)malloc(sizeof(t_windows));
	if (!new)
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC), NULL);
	new->win = NULL;
	new->coll = NULL;
	new->exit_f = NULL;
	new->exit_o = NULL;
	new->player = NULL;
	new->sol = NULL;
	new->wall = NULL;
	return (new);
}

void	ft_exit_succes(void)
{
	write(1, "\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n░░░░█▀▀▀░█▀▀▀░░█▀▀░▀▀█░░█", 164);
	write(1, "░░░░\n░░░░█░▀█░█░▀█░░█▀▀░▄▀░░░▀░░░░\n░░░░▀▀▀▀░▀▀▀▀░░▀▀▀░▀▀", 164);
	write(1, "▀░░▀░░░░\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n", 113);
	exit(EXIT_SUCCESS);
}
