/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 02:55:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/12 02:55:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int init_wall_sprite(void **sprite, char *sprite_path);

/**
 * @brief Get the path associated with a wall texture and add it to map struct
 * @return 0 on success, -1 otherwise
 */
int	parse_wall(char *line, t_content_type type, t_map *map)
{
	char	*sprite_path;

	while (*line && *line == ' ')
		line++;
	if (*line == '\0')
		return (parser_error("File name is missing\n"));
	sprite_path = ft_strdup(line);
	if (sprite_path == NULL)
		return (parser_error(NULL));
	if (type == NORTH)
		return (init_wall_sprite(&map->wall.sprite_no, sprite_path));
	else if (type == SOUTH)
		return (init_wall_sprite(&map->wall.sprite_so, sprite_path));
	else if (type == WEST)
		return (init_wall_sprite(&map->wall.sprite_we, sprite_path));
	else if (type == EAST)
		return (init_wall_sprite(&map->wall.sprite_ea, sprite_path));
	return (0);
}

/**
 * @brief Init a t_wall sprite, free sprite_path if an error occurred
 * @return 0 on success, -1 otherwise
 */
static int	init_wall_sprite(void **sprite, char *sprite_path)
{
	if (*sprite != NULL)
	{
		free(sprite_path);
		return (parser_error("Duplicate entry detected"));
	}
	*sprite = sprite_path;
	return (0);
}
