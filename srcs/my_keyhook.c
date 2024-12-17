/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:16:11 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/11 16:42:06 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	ft_pressed(char *c, t_map *map);
static void	ft_die(t_map *map);

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		return (ft_free_map(&map), exit(EXIT_SUCCESS));
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (ft_pressed(&map->map[map->i_player[0] - 1][map->i_player[1]], map))
			map->i_player[0] -= 1;
	}
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (ft_pressed(&map->map[map->i_player[0] + 1][map->i_player[1]], map))
			map->i_player[0] += 1;
	}
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		if (ft_pressed(&map->map[map->i_player[0]][map->i_player[1] - 1], map))
			map->i_player[1] -= 1;
	}
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (ft_pressed(&map->map[map->i_player[0]][map->i_player[1] + 1], map))
			map->i_player[1] += 1;
	}
}

static bool	ft_pressed(char *c, t_map *map)
{
	if (*c != '1' && *c != 'H')
	{
		map->nb_move++;
		ft_fprintf(1, "Number of movements : %u\n", map->nb_move);
		if (*c == 'C')
		{
			*c = '0';
			map->nb_collectible--;
			write(1, "\033[3;93m*Cling*\033[0m\n", 19);
			if (map->nb_collectible < 1)
				write(1, "\033[3;92m*Criiic... klaac*\033[0m\n", 29);
		}
		else if (*c == 'E' && map->nb_collectible < 1)
			return (ft_free_map(&map), ft_exit_succes(true), true);
		else if (*c == 'E' && map->nb_collectible > 0)
		{
			write(1, "\033[3;91m*Clac-clac-clac*\033[0m Let me in. ", 39);
			write (1, "LET ME IIIIIIIIIIIIIIN !!!\n", 28);
		}
		return (true);
	}
	else if (*c == 'H')
		return (ft_die(map), true);
	return (false);
}

static void	ft_die(t_map *map)
{
	ft_free_map(&map);
	ft_exit_succes(false);
}
