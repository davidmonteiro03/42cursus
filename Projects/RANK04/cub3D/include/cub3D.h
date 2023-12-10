/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:28:50 by dcaetano          #+#    #+#             */
/*   Updated: 2023/12/10 14:54:01 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

// ERRORS
# define ERROR_INPUT "Invalid input"
# define ERROR_EXTENSION "Invalid extension"
# define ERROR_LENGTH "Invalid length in given argument"
# define ERROR_EMPTY "Empty file"
# define ERROR_CONFIG "Invalid configuration"
# define ERROR_MAP "Invalid map"
# define ERROR_ORDER "Map must be after configuration"

typedef struct s_util
{
	int	pos;
	int	count;
}t_util;

typedef struct s_paths
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}t_paths;

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	unsigned long	color;
}t_color;

typedef struct s_coord
{
	int	x;
	int	y;
}t_coord;

typedef struct s_data
{
	char	*filename;
	char	**file_content;
	char	***data;
}t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}t_mlx;

typedef struct s_config
{
	t_data	data;
	t_color	floor;
	t_color	ceiling;
}t_config;

typedef struct s_cub
{
	t_config	config;
	t_mlx		mlx;
}t_cub;

/* ************************************************************************** */
/*                                     MLX                                    */
/* ************************************************************************** */

// draw
void			cub_draw_square(t_cub *cub, t_coord coord, int size, int color);

// key_handler
int				cub_key_handler(int key, t_cub *cub);

/* ************************************************************************** */
/*                                    EXIT                                    */
/* ************************************************************************** */

// cub exit
int				cub_exit(t_cub *cub);

/* ************************************************************************** */
/*                                   ERRORS                                   */
/* ************************************************************************** */

// simple error
void			cub_error(char *error, bool perror_flag);

// error parsing
void			cub_error_parsing(t_cub *cub, char *error);

// error parsing 1
void			cub_clear_error1(t_cub *cub, char *error);
void			cub_clear_error2(t_cub *cub, char *error);

/* ************************************************************************** */
/*                                   PARSER                                   */
/* ************************************************************************** */

// check colors
void			cub_check_color(t_cub *cub, char **strs, int i);

// get data
char			*cub_get_config(char *str, int i);
char			*cub_get_map(char *str, int i);

// parse file
void			cub_check_file_content(char *filename, t_cub *cub);

// parse input
char			*cub_check_extension(t_cub *cub, char *arg, char *extension);
void			cub_check_input(t_cub *cub, int argc, char **argv);

// check config
bool			cub_check_each_config(char *str);
bool			cub_check_color_range(char *red, char *green, char *blue);
void			cub_check_config(t_cub *cub, char **strs, int i);
void			cub_set_config_util(t_cub *cub, char **strs, int i, int count);
void			cub_check_data(t_cub *cub, char ***data, int i);

// set config
void			cub_set_config_util(t_cub *cub, char **strs, int i, int count);
void			cub_set_color(t_cub *cub, char **strs, char *type, int i);
void			cub_set_config(t_cub *cub, char ***data, int i);

// struct
t_color			cub_get_color(char **tmp);
t_coord			cub_coord(int x, int y);

/* ************************************************************************** */
/*                                    UTILS                                   */
/* ************************************************************************** */

// atol
long int		cub_atol(const char *nptr);

// build free
char			*cub_buildfree(char *s1, char *s2, \
	char *(*f)(const char *, const char *));

// display file content
void			cub_display_strs(char **file_content, int i);

// get num
int				cub_get_num_chars(char *str, char c);
int				cub_strs_size(char **strs);

// multiple free
void			multiple_free(const char *format, ...);

// rgb to hex
unsigned long	cub_rgb_to_hex(int red, int green, int blue);

// strcmp
int				cub_strcmp(const char *s1, const char *s2);

#endif
