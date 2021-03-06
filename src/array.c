/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 21:03:11 by alushenk          #+#    #+#             */
/*   Updated: 2017/02/28 21:04:50 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_header.h"

static t_pixel	*new_pixel(void)
{
	t_pixel		*result;

	result = (t_pixel *)malloc(sizeof(t_pixel));
	result->x = 0;
	result->y = 0;
	result->z = 0;
	result->color = 16777215;
	result->right = NULL;
	result->down = NULL;
	return (result);
}

int				hex_to_int(char **hex)
{
	size_t		result;
	char		byte;

	result = 0;
	while (**hex != ' ' && **hex)
	{
		byte = **hex;
		(*hex)++;
		if (ft_isdigit(byte))
			byte -= '0';
		else if (ft_islower(byte))
			byte = (char)(byte - 'a' + 10);
		else if (ft_isupper(byte))
			byte = (char)(byte - 'A' + 10);
		result = (result << 4) | (byte & 0xF);
	}
	return ((int)result);
}

static void		assign_pixel(char **str, t_pixel **prev_row, t_pixel **pixel)
{
	if (ft_strncmp(*str, ",0x", 3) == 0)
	{
		(*str) += 3;
		(*pixel)->color = hex_to_int(str);
	}
	if ((*prev_row) && (*prev_row)->right)
	{
		(*prev_row) = (*prev_row)->right;
		(*pixel)->right = (*prev_row)->down;
		if ((*pixel)->right == NULL)
			(*pixel)->right = new_pixel();
	}
	else
		(*pixel)->right = new_pixel();
	(*pixel)->down = new_pixel();
	(*pixel) = (*pixel)->right;
	while (**str && !ft_isdigit(**str) && **str != '-' && **str != '+')
		(*str)++;
}

static int		get_row(char *str, t_pixel *pixel, t_pixel *prev_row, int y)
{
	int			result;

	result = 0;
	if (str == NULL)
		return (0);
	while (*str)
	{
		while (*str == ' ')
			str++;
		pixel->x = result;
		pixel->y = y;
		if (ft_isdigit(*str) ||
				((*str == '-' || *str == '+') && ft_isdigit(*(str + 1))))
		{
			result++;
			pixel->z = atoi_skip(&str);
		}
		else
			str++;
		assign_pixel(&str, &prev_row, &pixel);
		if (prev_row && prev_row->right == NULL)
			return (result);
	}
	return (result);
}

void			parse_file(t_map *mlx, int fd)
{
	char		*line;
	t_pixel		*pixel;
	t_pixel		*prev_row;
	int			len;

	mlx->pixel = new_pixel();
	pixel = mlx->pixel;
	prev_row = NULL;
	while (get_next_line(fd, &line))
	{
		len = get_row(line, pixel, prev_row, mlx->rows);
		if (mlx->cols == 0)
			mlx->cols = len;
		if (len < mlx->cols)
			error_parse();
		free(line);
		mlx->rows++;
		prev_row = pixel;
		pixel = pixel->down;
	}
	if (mlx->cols == 0 || mlx->rows == 0)
		error_data();
}
