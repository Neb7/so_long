/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:53:46 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 18:00:13 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

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
	(*map)->time_ennemy = 0;
	(*map)->index_ennemy = ft_new_vector(sizeof(size_t));
	if (!(*map)->index_ennemy)
		return (ft_free_map(map), ft_exit_fail(ERR_MALLOC));
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
	new->ennemy = NULL;
	return (new);
}

void	ft_exit_succes(bool victory)
{
	if (victory)
	{
		write(1, "\033[5m", 4);
		write(1, "\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n░░░░█▀▀▀░█▀▀▀░░█▀▀░▀", 149);
		write(1, "▀█░░█░░░░\n░░░░█░▀█░█░▀█░░█▀▀░▄▀░░░▀░░░░\n░░░░▀▀▀▀░▀▀", 149);
		write(1, "▀▀░░▀▀▀░▀▀▀░░▀░░░░\n░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n", 143);
		write(1, "\033[0m", 4);
	}
	else
		write(1, "\033[3;91mYOU DIED\033[0m\n", 20);
	write(1, "Credits :\n\nCoin animation : Freekins (freekins.itch.io/)", 56);
	write(1, "\nGrass : CodeSpree (codespree.itch.io/)\nTree : simodias (", 57);
	write(1, "simodias.itch.io/)\nPlayer animation : cactusturtle (cactu", 57);
	write(1, "sturtle.itch.io/)\nEnemy : Admurin (admurin.itch.io/)\nDoo", 56);
	write(1, "rs : Me (Neb7 : github.com/neb7)\n", 33);
	exit(EXIT_SUCCESS);
}

void	ft_check_nb(t_map **map, int nb_ex)
{
	if ((*map)->nb_collectible < 1)
		return (ft_free_map(map), ft_exit_fail(ERR_COLL));
	else if ((*map)->i_player[0] == 0)
		return (ft_free_map(map), ft_exit_fail(ERR_PLY));
	else if (nb_ex != 1)
		return (ft_free_map(map), ft_exit_fail(ERR_SOR));
}
