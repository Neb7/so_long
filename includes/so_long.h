/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:30:58 by benpicar          #+#    #+#             */
/*   Updated: 2024/12/17 18:00:30 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/*
	Coin animation : Freekins (freekins.itch.io/)
	Grass : CodeSpree (codespree.itch.io/)
	Tree : simodias (simodias.itch.io/)
	Player animation : cactusturtle (cactusturtle.itch.io/)
	Enemy : Admurin (admurin.itch.io/)
	Doors : Me (Neb7 : github.com/neb7)
*/

# include "../libft/includes/libft.h"
# include "../MLX42/include/MLX42/MLX42.h" 
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define ERR_MALLOC "Allocation fail\n"
# define ERR_OPN "Can't open file\n"
# define ERR_LEN "Lines arn't same length\n"
# define ERR_READ "Can't read file or empty file\n"
# define ERR_OPN_MAP "Map isn't close\n"
# define ERR_NAME "Map name doesn't end with '.ber'\n"
# define ERR_CHA "Unknown character in map\n"
# define ERR_PLY "Different than 1 player found\n"
# define ERR_SOR "Different than 1 exit found\n"
# define ERR_IMP_E "Map impossible to end : can't reach exit\n"
# define ERR_IMP_C "Map impossible to end : can't reach all collectibles\n"
# define ERR_COLL "Less then 1 collectible\n"
# define ERR_BIG "Map too big\n"
# define ERR_HOST "Can't reach ennemy\n"

# define GAME_NAME "Best Game of all time (almost)"

# define FPS 0.042
# define PXL_L 64
# define PXL_H 64
# define SPEED_ENNEMY 0.5

typedef struct s_imgs
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
	struct s_imgs	*next;
}	t_imgs;

typedef struct s_windows
{
	mlx_t	*win;
	t_imgs	*player;
	t_imgs	*sol;
	t_imgs	*wall;
	t_imgs	*coll;
	t_imgs	*exit_f;
	t_imgs	*exit_o;
	t_imgs	*ennemy;
}	t_windows;

typedef struct s_map
{
	char			**map;
	size_t			lenght;
	size_t			height;
	size_t			i_player[2];
	size_t			nb_collectible;
	unsigned int	nb_move;
	t_windows		*win;
	mlx_image_t		*img_win;
	double			time;
	double			time_ennemy;
	t_vector		*index_ennemy;
}	t_map;

/*ft_error*/

void		ft_exit_fail(const char *str);
void		ft_free_map(t_map **map);
void		ft_free_copy(char **copy, size_t max);
void		ft_free_win(t_windows *win);

/*ft_parsing*/

void		ft_this_is_sparsing(char *file_name, t_map **map);

/*ft_parsing_utils*/

void		ft_is_completable(t_map **map);
bool		ft_check_last_line(t_map **map, char *buf);

/*ft_have_good_nb*/

void		ft_have_good_nb(t_map **map);

/*ft_flut_file*/

void		ft_flut_file(t_map **map, char **copy);

/*ft_set_windows*/

void		ft_set_windows(t_map **map);

/*main_loop*/

void		main_loop(void *param);
void		ft_put_img_diff(char c, t_map **map, size_t x, size_t y);
void		ft_put_img(t_map **map, t_imgs **img, size_t x, size_t y);

/*main_loop_utils*/

void		ft_move_enneny(t_map *map);

/*my_keyhook*/

void		my_keyhook(mlx_key_data_t keydata, void *param);

/*ddd*/

void		ft_init_map(t_map **map);
t_windows	*ft_init_win(t_map **map);
void		ft_exit_succes(bool victory);
void		ft_check_nb(t_map **map, int nb_ex);

#endif