/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:16:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/11 20:16:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static t_content_type	get_content_type(const char *line);
static int				parse_map_data_router(char *line, t_map *map);
static int				is_preset_complete(t_map *map);

/**
 * @brief Parse the map data in the .cub file
 * @return Return 0 on success, -1 otherwise
 */
int	parse_map_data(int map_fd, t_map *map)
{
	char		*line;

	line = get_next_line(map_fd);
	while (line)
	{
		if (*line != '\n')
			if (parse_map_data_router(line, map) == -1)
				return (free(line), -1);
		free(line);
		if (!is_preset_complete(map))
			line = get_next_line(map_fd);
		else
			line = NULL;
	}
	if (errno)
		return (parser_error(NULL));
	return (0);
}

/**
 * @brief Choose to call parse_wall or parse_horizontal_plane
 * @return Return 0 on success, -1 otherwise
 */
static int	parse_map_data_router(char *line, t_map *map)
{
	t_content_type	content_type;

	content_type = get_content_type(line);
	if (content_type == UNDEFINED_ID)
		return (parser_error("Undefined content\n"));
	else if (content_type == FLOOR_ID || content_type == CEILING_ID)
		return (parse_horizontal_plane(line + 1, content_type, map));
	else
		return (parse_wall(line + 2, content_type, map));
}

/**
 * @return the type of the content, or UNDEFINED if is not a valid content
 */
static t_content_type	get_content_type(const char *line)
{
	int						i;
	int						j;
	const char				*content_id[] = {"NO", "SO", "WE", "EA", "F", "C",
		NULL};
	const t_content_type	content_type[]
		= {NORTH_ID, SOUTH_ID, WEST_ID, EAST_ID, FLOOR_ID, CEILING_ID};

	i = 0;
	while (content_id[i])
	{
		j = 0;
		while (content_id[i][j] && content_id[i][j] == line[j] && line[j])
			j++;
		if (content_id[i][j] == '\0' && line[j] == ' ')
			return (content_type[i]);
		i++;
	}
	return (UNDEFINED_ID);
}

static int	is_preset_complete(t_map *map)
{
	if (map->ceiling_color != -1 && map->floor_color != -1
		&& map->wall.wall[NORTH] && map->wall.wall[SOUTH]
		&& map->wall.wall[EAST] && map->wall.wall[WEST])
		return (1);
	return (0);
}
