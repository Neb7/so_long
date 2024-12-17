/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:27:25 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 16:49:23 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_print_move(t_map *map, char *nb, char *join);
static void	ft_next(t_map **map);

void	main_loop(void *param)
{
	t_map			*map;
	ssize_t			x;
	ssize_t			y;

	map = (t_map *)param;
	ft_move_enneny(map);
	y = -1;
	while (++y < (ssize_t)map->height)
	{
		x = -1;
		while (++x < (ssize_t)map->lenght)
		{
			if (y == (ssize_t)map->i_player[0] && x == \
			(ssize_t)map->i_player[1])
				ft_put_img(&map, &map->win->player, x, y);
			else
				ft_put_img_diff(map->map[y][x], &map, x, y);
		}
	}
	ft_print_move(map, ft_itoa((int)map->nb_move), NULL);
	if (mlx_image_to_window(map->win->win, map->img_win, 0, 0) < 0)
		return (ft_free_map(&map), ft_exit_fail(mlx_strerror(mlx_errno)));
	ft_next(&map);
	map->time = mlx_get_time();
}

void	ft_put_img_diff(char c, t_map **map, size_t x, size_t y)
{
	if (c == '1')
		ft_put_img(map, &(*map)->win->wall, x, y);
	else if (c == '0')
		ft_put_img(map, &(*map)->win->sol, x, y);
	else if (c == 'C')
		ft_put_img(map, &(*map)->win->coll, x, y);
	else if (c == 'E' && (*map)->nb_collectible > 0)
		ft_put_img(map, &(*map)->win->exit_f, x, y);
	else if (c == 'E' && (*map)->nb_collectible < 1)
		ft_put_img(map, &(*map)->win->exit_o, x, y);
	else if (c == 'H')
		ft_put_img(map, &(*map)->win->ennemy, x, y);
}

void	ft_put_img(t_map **map, t_imgs **img, size_t x, size_t y)
{
	int	i;

	i = -1;
	while (++i < PXL_H)
	{
		ft_memcpy((*map)->img_win->pixels + ((((y * PXL_L) + i) * \
		(*map)->img_win->width * sizeof(int32_t)) + (x * PXL_H * \
		sizeof(int32_t))), (*img)->img->pixels + (i * PXL_L * \
		sizeof(int32_t)), PXL_L * sizeof(int32_t));
	}
}

static void	ft_print_move(t_map *map, char *nb, char *join)
{
	static mlx_image_t	*img = NULL;
	int					i;

	i = -1;
	if (!nb)
		return (ft_free_map(&map), ft_exit_fail(ERR_MALLOC));
	join = ft_strjoin("Number of movements : ", nb);
	if (!join)
		return (free(nb), ft_free_map(&map), ft_exit_fail(ERR_MALLOC));
	img = mlx_put_string(map->win->win, join, 32, 32);
	while (++i < (int)img->height)
	{
		ft_memcpy(map->img_win->pixels + (((32 + i) * map->img_win->width * \
		sizeof(int32_t)) + (32 * sizeof(int32_t))), img->pixels + (i * \
		img->width * sizeof(int32_t)), img->width * sizeof(int32_t));
	}
	free(nb);
	free(join);
	mlx_delete_image(map->win->win, img);
}

static void	ft_next(t_map **map)
{
	(*map)->win->coll = (*map)->win->coll->next;
	(*map)->win->exit_f = (*map)->win->exit_f->next;
	(*map)->win->exit_o = (*map)->win->exit_o->next;
	(*map)->win->player = (*map)->win->player->next;
	(*map)->win->sol = (*map)->win->sol->next;
	(*map)->win->wall = (*map)->win->wall->next;
	(*map)->win->ennemy = (*map)->win->ennemy->next;
}
