/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_have_good_nb.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:43:50 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/06 16:05:27 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_index_player(t_map **map, size_t x, size_t y);
static void	ft_nb_exit(t_map **map, int *nb_ex);
static void	ft_check_first_last(t_map **map, size_t x, size_t max_y);
static void	ft_check_char(t_map **map, size_t x, size_t y, int *nb_ex);

void	ft_have_good_nb(t_map **map)
{
	size_t	x;
	size_t	y;
	int		nb_ex;

	y = 1;
	nb_ex = 0;
	ft_check_first_last(map, 0, (*map)->height - 1);
	while (y < (*map)->height - 1)
	{
		if ((*map)->map[y][0] != '1')
			return (ft_free_map(map), ft_exit_fail(ERR_OPN_MAP));
		x = 1;
		while (x < (*map)->lenght - 1)
		{
			ft_check_char(map, x, y, &nb_ex);
			x++;
		}
		if ((*map)->map[y][x] != '1')
			return (ft_free_map(map), ft_exit_fail(ERR_OPN_MAP));
		y++;
	}
	if ((*map)->nb_collectible < 1)
		return (ft_free_map(map), ft_exit_fail(ERR_COLL));
	else if ((*map)->i_player[0] == 0)
		return (ft_free_map(map), ft_exit_fail(ERR_PLY));
}

static void	ft_index_player(t_map **map, size_t x, size_t y)
{
	if ((*map)->i_player[0] == 0)
	{
		(*map)->i_player[0] = y;
		(*map)->i_player[1] = x;
	}
	else
		return (ft_free_map(map), ft_exit_fail(ERR_PLY));
}

static void	ft_nb_exit(t_map **map, int *nb_ex)
{
	if (!(*nb_ex))
		(*nb_ex)++;
	else
		return (ft_free_map(map), ft_exit_fail(ERR_SOR));
}

static void	ft_check_first_last(t_map **map, size_t x, size_t max_y)
{
	while (x < (*map)->lenght)
	{
		if ((*map)->map[0][x] != '1')
			return (ft_free_map(map), ft_exit_fail(ERR_OPN_MAP));
		else if ((*map)->map[max_y][x] != '1')
			return (ft_free_map(map), ft_exit_fail(ERR_OPN_MAP));
		x++;
	}
}

static void	ft_check_char(t_map **map, size_t x, size_t y, int *nb_ex)
{
	if ((*map)->map[y][x] == 'P')
		ft_index_player(map, x, y);
	else if ((*map)->map[y][x] == 'E')
		ft_nb_exit(map, nb_ex);
	else if ((*map)->map[y][x] == 'C')
		((*map)->nb_collectible)++;
}
