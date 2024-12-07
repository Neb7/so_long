/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:11:08 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/06 17:39:17 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_destroy_img(mlx_t *mlx, t_imgs **imgs);

void	ft_exit_fail(const char *str)
{
	ft_fprintf(2, "Error\n%s", str);
	exit(EXIT_FAILURE);
}

void	ft_free_map(t_map **map)
{
	ssize_t	i;

	i = -1;
	if ((*map)->map)
		while (++i < (ssize_t)(*map)->height)
			free((*map)->map[i]);
	free((*map)->map);
	if ((*map)->win)
		ft_free_win((*map)->win);
	free((*map));
}

void	ft_free_copy(char **copy, size_t max)
{
	size_t	i;

	i = 0;
	while (i < max)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

void	ft_free_win(t_windows *win)
{
	if (win->exit_f)
		ft_destroy_img(win->win, &win->exit_f);
	if (win->exit_o)
		ft_destroy_img(win->win, &win->exit_o);
	if (win->player)
		ft_destroy_img(win->win, &win->player);
	if (win->sol)
		ft_destroy_img(win->win, &win->sol);
	if (win->coll)
		ft_destroy_img(win->win, &win->coll);
	if (win->wall)
		ft_destroy_img(win->win, &win->wall);
	mlx_terminate(win->win);
	free(win);
}

static void	ft_destroy_img(mlx_t *mlx, t_imgs **start)
{
	t_imgs	*tmp;
	t_imgs	*tmp2;

	tmp = *start;
	tmp2 = tmp;
	mlx_delete_image(mlx, tmp->img);
	mlx_delete_texture(tmp->texture);
	tmp = tmp->next;
	free(tmp2);
	while (tmp != *start)
	{
		tmp2 = tmp;
		mlx_delete_image(mlx, tmp->img);
		mlx_delete_texture(tmp->texture);
		tmp = tmp->next;
		free(tmp2);
	}
}
