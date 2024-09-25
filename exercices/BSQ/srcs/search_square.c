/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:38:46 by locagnio          #+#    #+#             */
/*   Updated: 2024/09/24 22:05:41 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"
/* je jegarde si un carre plus grannd existe */
int	*find_another_square(int *coords, char **map, t_coords *save)
{
	while (map[save[0].line] && map[save[0].line][save[0].col])//tant que je suis pas arrive a la fin de ma map
	{
		if (map[save[0].line][save[0].col] == save[0].obstacle)
			save[0].col = ft_skip_obst(map, save);//je skip les obstacles
		if (map[save[0].line][save[0].col] == save[0].empty
			&& map[save[0].line][save[0].col - 1] == save[0].obstacle)
			save[0].col_backup = save[0].col;
		while (map[save[0].line][save[0].col] != save[0].obstacle
			&& map[save[0].line][save[0].col] != '\0')//tant que mon tableau existe ou que j'ai pas d'obstacles
			save[0].col++;
		save[0].backup_obst = save[0].col;
		save[0].col = save[0].col_backup;
		solver(map, save);//je trouve le carre que je peux avoir
		if (coords[2] < save[1].size)//si la taille du nouveau carre est plus grande
			assign_new_coords(coords, save);			
		if (map[save[0].line][save[0].col + 1] == '\0')//si je suis a la fin de ma ligne
		{
			save[0].col = -1;
			save[0].backup_obst = 0;
			save[0].col_backup = 0;
			save[0].line += 1;
		}
		save[0].col++;
	}
	return (coords);
}

int	*search_square(char **tab, char *buffer, t_coords *save)
{
	int			*coords;

	coords = (int *)malloc(sizeof(int) * 3);
	save[0].empty = buffer[0];
	save[0].obstacle = buffer[1];
	save[0].full = buffer[2];
	// 1ere coordonnee = position x
	// 2eme coordonnee = position y
	// 3eme coordonnee = longueur du carre
	find_first_square(coords, tab, save);//trouve les coords et la longueur du 1er carre
	coords = find_another_square(coords, tab, save);
	return (coords);
}