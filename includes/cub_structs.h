/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeimlin <adeimlin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 13:14:34 by adeimlin          #+#    #+#             */
/*   Updated: 2026/02/10 16:27:54 by adeimlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_STRUCTS_H
# define CUB_STRUCTS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct s_game
{
	const char	*cwd;
}	t_game;

typedef struct s_vec2
{
	uint32_t	col;
	uint32_t	row;
}	t_vec2;

typedef struct s_map
{
	char	*ptr;
	size_t	cols;
	size_t	rows;
	t_vec2	player_pos;
}	t_map;

#endif
