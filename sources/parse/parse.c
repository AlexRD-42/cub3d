/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:19:47 by adeimlin          #+#    #+#             */
/*   Updated: 2026/02/11 11:32:00 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub_structs.h"
#include "cub_utils.h"
#include "cmlx.h"
#include "mlx.h"

// Save max wall width and height
// Validate wall exterior
// Only one N/S/W/E
// Map content has to be last

// Reads a string until it finds a null terminator, space or length > 255
// Returns: >=0) valid fd, -1) fd error, -2) path too long
// TODO: Create a wrapper function for xpm_to_image that removes struct malloc
static
t_img	*stt_read_xpm(t_xvar *mlx, const char **filename_ptr)
{
	int			tmp;
	t_img		*img;
	const char	*filename = *filename_ptr;
	char		path[256];
	size_t		length;

	length = 0;
	while (ft_isspace(filename[length]))
		length++;
	while (filename[length] != 0 && !ft_isspace(filename[length]))
	{
		if (length >= 255)
			return (NULL);	// Path too long, TODO: print
		path[length] = filename[length];
		length++;
	}
	path[length] = 0;
	*filename_ptr = filename;
	img = mlx_xpm_file_to_image(mlx, path, &tmp, &tmp);
	if (img == NULL)
		return (NULL);	// Error opening file, TODO: print
	return (img);
}

// Returns: >0) Ok, -1) Invalid value (P), -2) Two Player Positions (P)
static
ssize_t	stt_parse_line(const char *line, t_map *map)
{
	const char	*oline = line;
	size_t		cols;

	cols = 0;
	while (*line != '\n' && *line != 0)
	{
		if (*line == '0' || *line == '1')
			cols++;
		else if (*line == 'N' || *line == 'E' || *line == 'S' || *line == 'W')
		{
			if (map->player_pos.col == 0)
				return (ft_error("Error\n", "", -2));	// Two player positions
			map->player_pos.row = map->rows;
			map->player_pos.col = cols++;
		}
		else if (!ft_isspace(*line))
			return (ft_error("Error\n", "", -1));	// Not NESW, space or 01
		line++;
	}
	if (cols > map->cols)
		map->cols = cols;
	return ((line - oline) + (*line == '\n'));
}

int	cub_validate_map(const char *str, t_map *map)
{
	ssize_t		offset;
	const char	*ostr = str;

	while (*str != 0)
	{
		offset = stt_parse_line(str, map);
		if (offset <= 0)
			return (offset);
		map->rows++;
	}
	return (0);
}

int	cub_read_texture(const char *filename)
{

}
