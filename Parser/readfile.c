/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:11:43 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/14 11:44:57 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

t_map	*start_map(void)
{
	t_map	*map;

	map = memcard(NULL, DEFAULT, MALLOC, sizeof(t_map));
	if (!map)
		return (NULL);
	map->a = NULL;
	map->c = NULL;
	map->l = NULL;
	map->pl = NULL;
	map->sp = NULL;
	map->cy = NULL;
	return (map);
}

int	add_map(t_map *map, char *line)
{
	int	valid;

	valid = 0;
	if (!ft_strncmp(line, "A ", 2))
		valid = add_ambient(map, line);
	else if (!ft_strncmp(line, "C ", 2))
		valid = add_camera(map, line);
	else if (!ft_strncmp(line, "L ", 2))
		valid = add_light(map, line);
	else if (!ft_strncmp(line, "pl ", 3))
		valid = add_plane(map, line);
	else if (!ft_strncmp(line, "sp ", 3))
		valid = add_sphere(map, line);
	else if (!ft_strncmp(line, "cy ", 3))
		valid = add_cylinder(map, line);
	if (valid)
		return (1);
	err(RED, INVALID_VARIABLE, RESET);
	memcard(NULL, 0, FREEALL, 0);
	return (0);
}

t_map	*readfile(char *file)
{
	int		fd;
	char	*line;
	t_map	*map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = start_map();
	line = get_next_line(fd);
	while (line)
	{
		skip_spaces(&line);
		if (line[0])
			if (!add_map(map, line))
				return (NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}