/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_windows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:59:28 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 17:57:08 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void		ft_init_img(t_map **map);
static t_imgs	*ft_init_textur(char *path, t_windows *win, size_t len, int nb);
static char		*ft_set_path(char *path, int nb, size_t len, char **true_path);
static t_imgs	*ft_img_next(char *path, t_windows *win, int nb, \
t_imgs **start);

void	ft_set_windows(t_map **map)
{
	(*map)->win->win = mlx_init((*map)->lenght * PXL_L, (*map)->height * \
	PXL_H, GAME_NAME, true);
	if (!(*map)->win)
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	ft_init_img(map);
	(*map)->map[(*map)->i_player[0]][(*map)->i_player[1]] = '0';
	(*map)->img_win = mlx_new_image((*map)->win->win, (*map)->lenght * \
	PXL_L, (*map)->height * PXL_H);
	if (!((*map)->img_win))
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
}

static void	ft_init_img(t_map **map)
{
	(*map)->win->coll = ft_init_textur("./img/c", (*map)->win, 7, 0);
	if (!((*map)->win->coll))
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	(*map)->win->exit_f = ft_init_textur("img/door_close", (*map)->win, 14, 0);
	if (!((*map)->win->exit_f))
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	(*map)->win->exit_o = ft_init_textur("img/door_open", (*map)->win, 13, 0);
	if (!((*map)->win->exit_o))
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	(*map)->win->player = ft_init_textur("img/p", (*map)->win, 5, 0);
	if (!((*map)->win->player))
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	(*map)->win->sol = ft_init_textur("img/sol", (*map)->win, 7, 0);
	if (!((*map)->win->sol))
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	(*map)->win->wall = ft_init_textur("img/wall", (*map)->win, 8, 0);
	if (!((*map)->win->wall))
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	(*map)->win->ennemy = ft_init_textur("img/e", (*map)->win, 5, 0);
	if (!((*map)->win->ennemy))
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
}

static t_imgs	*ft_init_textur(char *path, t_windows *win, size_t len, int nb)
{
	t_imgs	*new;
	char	*true_path;

	true_path = NULL;
	if (!ft_set_path(path, nb, len, &true_path))
		return (NULL);
	new = (t_imgs *)malloc(sizeof(t_imgs));
	if (!new)
		return (free(true_path), NULL);
	new->texture = mlx_load_png(true_path);
	if (!new->texture)
		return (free(new), free(true_path), NULL);
	new->img = mlx_texture_to_image(win->win, new->texture);
	if (!new->img)
		return (mlx_delete_texture(new->texture), free(new), NULL);
	new->next = ft_img_next(path, win, nb + 1, &new);
	if (!new->next)
		return (mlx_delete_image(win->win, new->img), \
		mlx_delete_texture(new->texture), free(new), NULL);
	return (free(true_path), new);
}

static char	*ft_set_path(char *path, int nb, size_t len, char **true_path)
{
	char	c;
	char	*d;

	d = (char *)malloc(sizeof(char) * (len + 6));
	if (!d)
		return (NULL);
	ft_memcpy(d, path, len);
	c = nb + 'a';
	ft_memcpy(&d[len], &c, 1);
	ft_memcpy(&d[len + 1], ".png", 4);
	d[len + 5] = 0;
	*true_path = d;
	return (*true_path);
}

static t_imgs	*ft_img_next(char *path, t_windows *win, int nb, t_imgs **start)
{
	t_imgs	*new;
	char	*true_path;
	int		fd;

	true_path = NULL;
	if (!ft_set_path(path, nb, ft_strlen(path), &true_path))
		return (NULL);
	fd = open(true_path, O_RDONLY);
	if (fd < 0)
		return (free(true_path), *start);
	close(fd);
	new = (t_imgs *)malloc(sizeof(t_imgs));
	if (!new)
		return (free(true_path), NULL);
	new->texture = mlx_load_png(true_path);
	if (!new->texture)
		return (free(new), free(true_path), NULL);
	new->img = mlx_texture_to_image(win->win, new->texture);
	if (!new->img)
		return (mlx_delete_texture(new->texture), free(new), NULL);
	new->next = ft_img_next(path, win, nb + 1, start);
	if (!new->next)
		return (mlx_delete_image(win->win, new->img), \
		mlx_delete_texture(new->texture), free(new), NULL);
	return (free(true_path), new);
}
