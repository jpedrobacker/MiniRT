/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:46:46 by jazevedo          #+#    #+#             */
/*   Updated: 2024/09/20 12:41:47 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minirt.h"

int	invalid_ambient(char **split)
{
	double	amblight;

	if (matrixlen(split) != 3)
		return (1);
	if (ft_strcmp(split[0], "A"))
		return (1);
	amblight = ft_atod(split[1]);
	if (amblight < 0 || amblight > 1)
		return (1);
	if (invalid_rgb(split[2]))
		return (1);
	return (0);
}

t_amb	*fill_amb(char **split)
{
	char	**color;
	t_amb	*amb;

	amb = memcard(NULL, DEFAULT, MALLOC, sizeof(t_amb));
	amb->type = A;
	amb->amblight = ft_atod(split[1]);
	color = splitline(split[2], ',');
	amb->rgb[0] = ft_atoi(color[0]);
	amb->rgb[1] = ft_atoi(color[1]);
	amb->rgb[2] = ft_atoi(color[2]);
	return (color = memcard(color, VECTOR, FREE, 0), amb);
}

int	add_ambient(t_map *map, char *line)
{
	char	**split;

	split = splitline(line, '\0');
	if (invalid_ambient(split))
		return (split = memcard(split, VECTOR, FREE, 0), 0);
	map->a = fill_amb(split);
	return (split = memcard(split, VECTOR, FREE, 0), 1);
}
