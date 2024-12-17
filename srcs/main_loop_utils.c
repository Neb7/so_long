/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:10:09 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/11 16:46:41 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_random_move(t_map *map, size_t x, size_t y, size_t *index);
static bool	ft_put_index(size_t *index, size_t move, bool add, char b);
static void	ft_swap_char(char *a, char *b, bool f);

void	ft_move_enneny(t_map *map)
{
	size_t	i;

	i = 0;
	if (mlx_get_time() - map->time_ennemy > SPEED_ENNEMY)
	{
		while (i < map->index_ennemy->index)
		{
			ft_random_move(map, ((size_t *)map->index_ennemy->buf)[i] % \
			map->lenght, ((size_t *)map->index_ennemy->buf)[i] / map->lenght, \
			&((size_t *)map->index_ennemy->buf)[i]);
			if (map->i_player[0] == ((size_t *)map->index_ennemy->buf)[i] / \
			map->lenght && map->i_player[1] == \
			((size_t *)map->index_ennemy->buf)[i] % map->lenght)
				return (ft_free_map(&map), ft_exit_succes(false));
			i++;
		}
		map->time_ennemy = mlx_get_time();
	}
	while (mlx_get_time() - map->time < FPS && map->time != 0)
		;
}

static void	ft_random_move(t_map *map, size_t x, size_t y, size_t *index)
{
	int	len;
	int	mod;

	len = (int)(mlx_get_time() * 100) + ft_valabs((int)(x - map->i_player[1])) \
	+ ft_valabs((int)(y - map->i_player[0]));
	mod = len % 4;
	if (mod == 0)
		ft_swap_char(&map->map[y][x], &map->map[y][x + 1], \
		ft_put_index(index, 1, true, map->map[y][x + 1]));
	else if (mod == 1)
		ft_swap_char(&map->map[y][x], &map->map[y][x - 1], \
		ft_put_index(index, 1, false, map->map[y][x - 1]));
	else if (mod == 2)
		ft_swap_char(&map->map[y][x], &map->map[y + 1][x], \
		ft_put_index(index, map->lenght, true, map->map[y + 1][x]));
	else
		ft_swap_char(&map->map[y][x], &map->map[y - 1][x], \
		ft_put_index(index, map->lenght, false, map->map[y - 1][x]));
}

static bool	ft_put_index(size_t *index, size_t move, bool add, char b)
{
	if (b != '1' && b != 'C' && b != 'E')
	{
		if (add)
			*index += move;
		else
			*index -= move;
	}
	return (true);
}

static void	ft_swap_char(char *a, char *b, bool f)
{
	char	c;

	if (*b != '1' && *b != 'C' && *b != 'E')
	{
		c = *a;
		*a = *b;
		*b = c;
		f = true;
	}
}
