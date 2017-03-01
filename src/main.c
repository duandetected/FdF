//
// Created by Anton Lushenko on 2/17/17.
//

#include "FdF.h"

void    print_mlx(t_pixel *pixel)
{
    t_pixel *x;
    t_pixel *y;

    y = pixel;
    while (y->down)
    {
        x = y;
        while (x->right)
        {
            printf("%-15f", x->x);
            x = x->right;
        }
        printf("\n");
        y = y->down;
    }
    printf("\n");
    y = pixel;
    while (y->down)
    {
        x = y;
        while (x->right)
        {
            printf("%-15f", x->y);
            x = x->right;
        }
        printf("\n");
        y = y->down;
    }
    printf("\n");
    y = pixel;
    while (y->down)
    {
        x = y;
        while (x->right)
        {
            printf("%-15f", x->z);
            x = x->right;
        }
        printf("\n");
        y = y->down;
    }
    printf("\n");
}

static void    struct_init(t_map **mlx)
{
    if (*mlx == NULL)
        *mlx = (t_map*)malloc(sizeof(t_map));
    (*mlx)->init = NULL;
    (*mlx)->window = NULL;
    (*mlx)->image = NULL;
    (*mlx)->center_x = 0;
    (*mlx)->center_y = 0;
    (*mlx)->center_z = 0;
    (*mlx)->cols = 0;
    (*mlx)->rows = 0;

}

int exit_button()
{
    exit(0);
}

int main(int argc, char **argv)
{
    t_map *mlx;
	int		fd;

    if (argc == 2)
    {
        struct_init(&mlx);
		fd = open(argv[1], O_RDONLY);
        parse_file(mlx, fd);
		close(fd);
        mlx->init = mlx_init();
        mlx->window = mlx_new_window(mlx->init, WINDOW_SIZE_X, WINDOW_SIZE_Y, argv[1]);
        draw(mlx);
        mlx_hook(mlx->window, 2, 5, key_hook, mlx);
        mlx_hook(mlx->window, 17, 0L, exit_button, 0);
        mlx_loop(mlx->init);
    }
    else
        printf("arguments needed");
    return (0);

}