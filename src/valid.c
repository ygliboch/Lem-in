/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:32:54 by yhliboch          #+#    #+#             */
/*   Updated: 2019/04/08 12:32:56 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_link(t_lem *lem, char *line)
{
	t_node	*tmp_node;
	int		fl;

	fl = 0;
	tmp_node = lem->node;
	if (ft_num_words(line, ' ') != 1)
		error("error\n");
	check_old_link(lem, line);
	while (tmp_node)
	{
		if (ft_strncmp(line, tmp_node->room->name,
			ft_strlen(tmp_node->room->name)) == 0 &&
			ft_strcmp(line + ft_strlen(tmp_node->room->name)
							+ 1, tmp_node->room->name) == 0)
			error("error\n");
		else if (ft_strncmp(line, tmp_node->room->name,
			(ft_strchr(line, '-') - line)) == 0 ||
			ft_strcmp(ft_strchr(line, '-') + 1, tmp_node->room->name) == 0)
			fl++;
		tmp_node = tmp_node->next;
	}
	if (fl != 2)
		error("error\n");
}

int		check_room(char *line)
{
	char *tmp;

	if (line[0] == '#')
		return (1);
	if (ft_num_words(line, ' ') != 3)
		return (0);
	tmp = line;
	tmp += ft_strchr(tmp, ' ') - tmp + 1;
	while (*tmp)
	{
		if (!(ft_isdigit(*tmp)) && *tmp != ' ')
			return (0);
		tmp++;
	}
	return (1);
}

void	take_room(t_lem *lem, char **line, int fl)
{
	int	i;

	i = 1;
	if (fl == 1 && lem->start != NULL)
		error("more then one start\n");
	if (fl == 2 && lem->end != NULL)
		error("more then one end\n");
	while (i > 0 && *(line[0]) == '#')
	{
		add_file(*line, lem);
		i = get_next_line(0, line);
	}
	if (*line == NULL || *(line[0]) == '\0' || i < 1)
		error("error\n");
	if ((fl == 1 || fl == 2) && !check_room(*line))
		error("error\n");
	new_room(lem, *line, fl);
}

char	*take_check_rooms(t_lem *lem)
{
	char	*line;

	while (get_next_line(0, &line) && check_room(line))
	{
		if (ft_strcmp(line, "##start") == 0)
			take_room(lem, &line, 1);
		else if (ft_strcmp(line, "##end") == 0)
			take_room(lem, &line, 2);
		else if (line[0] != '#')
			new_room(lem, line, 0);
		add_file(line, lem);
	}
	if (line == NULL || line[0] == '\0')
		error("No links.\n");
	return (line);
}

void	valid(t_lem *lem)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	i = -1;
	while (line[++i])
		if (!(ft_isdigit(line[i])))
			error("error\n");
	lem->ants = ft_atoi(line);
	if (lem->ants <= 0)
		error("error\n");
	add_file(line, lem);
	line = take_check_rooms(lem);
	if (!lem->node)
		error("error\n");
	take_check_links(lem, line);
	if (lem->start == NULL || lem->end == NULL)
		error("error\n");
}
