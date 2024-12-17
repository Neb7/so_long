/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:39:52 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/09 16:22:52 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_read_map(t_map **map, char **buf, int fd, t_vector **vec);
static int	ft_verify_line(char *buf, t_map **map);
static void	ft_creat_map(t_map **map, t_vector **vec);
static void	ft_end_gnl(int fd, char **buf);

void	ft_this_is_sparsing(char *file_name, t_map **map)
{
	int			fd;
	char		*buf;
	t_vector	*vec;

	vec = ft_new_vector(sizeof(char));
	if (!vec)
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	if (ft_strncmp(&file_name[ft_strlen(file_name) - 4], ".ber", 4))
		return (ft_free_map(map), ft_free_vector(&vec), ft_exit_fail(ERR_NAME));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_free_map(map), ft_free_vector(&vec), ft_exit_fail(ERR_OPN));
	buf = get_next_line(fd);
	if (!buf)
		return (ft_free_map(map), ft_free_vector(&vec), ft_exit_fail(ERR_READ));
	(*map)->lenght = ft_strlen(buf) - 1;
	if ((*map)->lenght > UINT_MAX)
		return (ft_free_map(map), ft_free_vector(&vec), ft_exit_fail(ERR_BIG));
	ft_read_map(map, &buf, fd, &vec);
	close(fd);
	free(buf);
	ft_creat_map(map, &vec);
	ft_free_vector(&vec);
	ft_is_completable(map);
}

static void	ft_read_map(t_map **map, char **buf, int fd, t_vector **vec)
{
	while (*buf != NULL)
	{
		((*map)->height)++;
		if ((*map)->height > UINT_MAX)
			return (ft_free_map(map), ft_free_vector(vec), free(*buf), \
			ft_exit_fail(ERR_BIG));
		if (ft_strlen (*buf) - 1 != (*map)->lenght)
			if (ft_check_last_line(map, *buf))
				return (ft_end_gnl(fd, buf), ft_free_map(map), \
				ft_free_vector(vec), free(*buf), ft_exit_fail(ERR_LEN));
		if (ft_verify_line(*buf, map))
		{
			ft_end_gnl(fd, buf);
			return (ft_free_map(map), ft_free_vector(vec), free(*buf), \
			ft_exit_fail(ERR_CHA));
		}
		if (!ft_add_char_vector(*buf, *vec, (*map)->lenght + 1, sizeof(char)))
		{
			ft_end_gnl(fd, buf);
			return (ft_free_map(map), ft_free_vector(vec), free(*buf), \
			ft_exit_fail(ERR_MALLOC));
		}
		free(*buf);
		*buf = get_next_line(fd);
	}
}

static int	ft_verify_line(char *buf, t_map **map)
{
	size_t	i;

	i = 0;
	while (i < (*map)->lenght)
	{
		if (buf[i] != '1' && buf[i] != '0' && buf[i] != 'C' && \
		buf[i] != 'E' && buf[i] != 'P' && buf[i] != 'H')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_creat_map(t_map **map, t_vector **vec)
{
	char	*tmp;

	tmp = ft_vtos(*vec);
	(*map)->map = ft_split(tmp, '\n');
	if (!((*map)->map))
		return (ft_free_map(map), ft_free_vector(vec), free(tmp), \
		ft_exit_fail(ERR_MALLOC));
	free(tmp);
}

static void	ft_end_gnl(int fd, char **buf)
{
	close(fd);
	while (*buf != NULL)
	{
		free(*buf);
		*buf = get_next_line(fd);
	}
}
