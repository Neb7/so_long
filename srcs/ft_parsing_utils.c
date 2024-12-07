/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:04:44 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/06 11:29:26 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**ft_make_copy(t_map **map);
static void	ft_can_we_reach(char **copy, t_map **map);

void	ft_is_completable(t_map **map)
{
	char	**copy;

	ft_have_good_nb(map);
	copy = ft_make_copy(map);
	if (!copy)
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
	ft_flut_file(map, copy);
	ft_can_we_reach(copy, map);
	ft_free_copy(copy, (*map)->height);
}

static char	**ft_make_copy(t_map **map)
{
	size_t	i;
	char	**d;

	i = 0;
	d = (char **)malloc(sizeof(char *) * ((*map)->height + 1));
	if (!d)
		return (NULL);
	while (i < (*map)->height)
	{
		d[i] = (char *)malloc(sizeof(char) * ((*map)->lenght + 1));
		if (!d[i])
			return (ft_free_copy(d, i), NULL);
		ft_memcpy(d[i], (*map)->map[i], (*map)->lenght + 1);
		i++;
	}
	d[i] = NULL;
	return (d);
}

static void	ft_can_we_reach(char **copy, t_map **map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (++y < (*map)->height - 1)
	{
		x = 0;
		while (++x < (*map)->lenght - 1)
		{
			if (copy[y][x] == 'E')
				return (ft_free_copy(copy, (*map)->height), ft_free_map(map), \
				ft_exit_fail(ERR_IMP_E));
			else if (copy[y][x] == 'C')
				return (ft_free_copy(copy, (*map)->height), ft_free_map(map), \
				ft_exit_fail(ERR_IMP_C));
		}
	}
}
