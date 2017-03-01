//
// Created by Anton Lushenko on 2/17/17.
//

#ifndef FDF_FDF_H
#define FDF_FDF_H

# include <math.h>
# include <mlx.h>
//# include <X11/X.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../externals/get_next_line/get_next_line.h"
# include "../externals/libft/libft.h"

# define WINDOW_SIZE_X 2000
# define WINDOW_SIZE_Y 1250

# define RAD (3.14 / 180)
# define STEP_MOVE 20
# define STEP_ROTATE 2
# define STEP_ZOOM_INCREASE 1.5
# define STEP_ZOOM_DECREASE 0.5

#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_SCALE_INCREASE 69
#define KEY_SCALE_DECREASE 78
#define KEY_EXIT 53

#define KEY_ROTATE_X_RIGHT 91
#define KEY_ROTATE_X_LEFT 84
#define KEY_ROTATE_Y_RIGHT 88
#define KEY_ROTATE_Y_LEFT 86
#define KEY_ROTATE_Z_RIGHT 85
#define KEY_ROTATE_Z_LEFT 83

typedef struct      s_pixel
{
    double  x;
    double  y;
    double  z;
    int     color;
    struct s_pixel  *right;
    struct s_pixel  *down;
}                   t_pixel;

typedef struct      s_limits
{
	double	max_x;
	double	max_y;
	double	max_z;
	double	min_x;
	double	min_y;
	double	min_z;
}                   t_limits;

typedef struct      s_struct
{
    int cols;
    int rows;

    double center_x;
    double center_y;
    double center_z;

    t_pixel *pixel;

    void    *init;
    void    *window;
    void    *image;
    int     endian;
    char    *image_data;
    int     bits_per_pixel;
    int     line_size;
}                   t_map;

/*
** array.c
*/
void		parse_file(t_map *mlx, int fd);
/*
** draw.c
*/
void    draw(t_map *mlx);
/*
** events.c
*/
int    key_hook(int key, t_map *mlx);
/*
** matrix.c
*/
void		prepare_matrix(t_map *mlx);
void    move_matrix(t_pixel *pixel, double move, int combination);
void    zoom_matrix(t_pixel *pixel, double multiplier);
/*
** centrate_matrix.c
*/
void			find_centre(t_map *mlx);
/*
** rotate.c
*/
void    rotate(t_pixel *pixel, double angle, int combination);


#endif //FDF_FDF_H
