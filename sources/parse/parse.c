/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 11:19:47 by adeimlin          #+#    #+#             */
/*   Updated: 2026/02/10 16:27:50 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub_structs.h"
#include "cub_utils.h"

// Save max wall width and height
// Validate wall exterior
// Only one N/S/W/E
// Map content has to be last

// Reads a string until it finds a null terminator, space or length > 255
// Copies what is read into a buffer and returns the fd of what was read
// Returns: >=0) valid fd, -1) fd error, -2) path too long (P)
static
int	stt_read_path(const char **filename_ptr)
{
	int			fd;
	const char	*filename = *filename_ptr;
	char		path[256];
	size_t		length;

	length = 0;
	while (ft_isspace(filename[length]))
		length++;
	while (filename[length] != 0 && !ft_isspace(filename[length]))
	{
		if (length >= 255)
			return (ft_error("Error\n", "", -2));	// Path too long
		path[length] = filename[length];
		length++;
	}
	path[length] = 0;
	*filename_ptr = filename;
	fd = open(path, O_RDONLY);
	return (fd);
}

// Returns: 0) Ok, -1) Invalid value (P), -2) Two Player Positions (P)
static
int	stt_parse_line(const char **line_ptr, t_map *map)
{
	const char	*line = *line_ptr;
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
	*line_ptr = line + (*line == '\n');
	return (0);
}

int	cub_validate_map(const char *str, t_map *map)
{
	int			rvalue;
	const char	*ostr = str;

	while (*str != 0)
	{
		rvalue = stt_parse_line(&str, map);
		if (rvalue != 0)
			return (rvalue);
		map->rows++;
	}
	return (0);
}

int	cub_read_texture(const char *filename)
{

}
