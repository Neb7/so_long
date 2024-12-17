/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flut_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:39:12 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/09 11:46:55 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_add_in_tmp(t_vector *tmp, unsigned int i, t_map **map, \
char **copy);
static void	ft_add_index(t_vector *tmp, unsigned int i, t_map **map, \
char **copy);

void	ft_flut_file(t_map **map, char **copy)
{
	unsigned int	i;
	t_vector		*tmp;

	tmp = ft_new_vector(sizeof(unsigned int));
	if (!tmp)
		return ;
	i = ((*map)->i_player[0] * (*map)->lenght) + (*map)->i_player[1];
	ft_add_in_tmp(tmp, i, map, copy);
	while (tmp->index > 0)
	{
		(tmp->index)--;
		ft_add_in_tmp(tmp, ((unsigned int *)tmp->buf)[tmp->index], map, copy);
	}
	ft_free_vector(&tmp);
}

static void	ft_add_in_tmp(t_vector *tmp, unsigned int i, t_map **map, \
char **copy)
{
	if (ft_memchar("0CEH", copy[(i + 1) / (*map)->lenght][(i + 1) % \
	(*map)->lenght], 4) != -1)
		ft_add_index(tmp, i + 1, map, copy);
	if (ft_memchar("0CEH", copy[(i - 1) / (*map)->lenght][(i - 1) % \
	(*map)->lenght], 4) != -1)
		ft_add_index(tmp, i - 1, map, copy);
	if (ft_memchar("0CEH", copy[(i + (*map)->lenght) / \
	(*map)->lenght][(i + (*map)->lenght) % (*map)->lenght], 4) != -1)
		ft_add_index(tmp, i + (*map)->lenght, map, copy);
	if (ft_memchar("0CEH", copy[(i - (*map)->lenght) / \
	(*map)->lenght][(i - (*map)->lenght) % (*map)->lenght], 4) != -1)
		ft_add_index(tmp, i - (*map)->lenght, map, copy);
}

static void	ft_add_index(t_vector *tmp, unsigned int i, t_map **map, \
char **copy)
{
	copy[i / (*map)->lenght][i % (*map)->lenght] = '2';
	if (!ft_add_char_vector(&i, tmp, 1, sizeof(unsigned int)))
		return (ft_free_vector(&tmp), ft_free_map(map), \
		ft_free_copy(copy, (*map)->height), ft_exit_fail(ERR_MALLOC));
}

/*
else if ((*map)->map[i / (*map)->lenght][i % (*map)->lenght] == 'C')
		copy[i / (*map)->lenght][i % (*map)->lenght] = '3';
	else
		copy[i / (*map)->lenght][i % (*map)->lenght] = '4';
*/
