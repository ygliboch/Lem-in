/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:20:58 by yhliboch          #+#    #+#             */
/*   Updated: 2019/04/11 14:20:59 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lst	*new_link(t_node *node, char *line, int fl)
{
	t_lst	*new;
	t_node	*tmp_node;

	new = ft_memalloc(sizeof(t_lst));
	tmp_node = node;
	if (fl == 0)
		while (tmp_node && ft_strcmp(ft_strchr(line, '-') + 1,
			tmp_node->room->name) != 0)
			tmp_node = tmp_node->next;
	else
		while (tmp_node && ft_strncmp(line, tmp_node->room->name,
						(ft_strchr(line, '-') - line)) != 0)
			tmp_node = tmp_node->next;
	new->room = tmp_node->room;
	return (new);
}

t_node	*new_node(t_lem *lem, char *line)
{
	t_node	*new;
	t_node	*tmp_node;

	new = ft_memalloc(sizeof(t_node));
	new->room = ft_memalloc(sizeof(t_room));
	new->room->name = ft_strndup(line, ft_strchr(line, ' ') - line);
	new->room->x = ft_atoi(line + ft_strlen(new->room->name));
	new->room->y = ft_atoi(line + (ft_strrchr(line, ' ') - line));
	tmp_node = lem->node;
	while (tmp_node)
	{
		if (ft_strcmp(new->room->name, tmp_node->room->name) == 0)
			error("error\n");
		if (new->room->x == tmp_node->room->x &&
		new->room->y == tmp_node->room->y)
			error("error\n");
		tmp_node = tmp_node->next;
	}
	return (new);
}

void	new_room(t_lem *lem, char *line, int fl)
{
	t_node *tmp_node;
	t_node *new;

	if (lem->node == NULL)
	{
		lem->node = new_node(lem, line);
		if (fl == 1)
			lem->start = lem->node->room;
		else if (fl == 2)
			lem->end = lem->node->room;
		return ;
	}
	tmp_node = lem->node;
	while (tmp_node->next)
		tmp_node = tmp_node->next;
	new = new_node(lem, line);
	tmp_node->next = new;
	if (fl == 1)
		lem->start = new->room;
	else if (fl == 2)
		lem->end = new->room;
}

void	make_link(t_node *node, char *line, int fl)
{
	t_node	*tmp_node;
	t_lst	*tmp_link;
	t_lst	*new;

	tmp_node = node;
	if (fl == 0)
		while (tmp_node && ft_strncmp(line, tmp_node->room->name,
					(ft_strchr(line, '-') - line)) != 0)
			tmp_node = tmp_node->next;
	else
		while (tmp_node && ft_strcmp(ft_strchr(line, '-')
						+ 1, tmp_node->room->name) != 0)
			tmp_node = tmp_node->next;
	if (tmp_node->link == NULL)
	{
		tmp_node->link = new_link(node, line, fl);
		return ;
	}
	tmp_link = tmp_node->link;
	while (tmp_link->next)
		tmp_link = tmp_link->next;
	new = new_link(node, line, fl);
	tmp_link->next = new;
}

void	take_check_links(t_lem *lem, char *line)
{
	if (line[0] != '#')
	{
		check_link(lem, line);
		make_link(lem->node, line, 0);
		make_link(lem->node, line, 1);
	}
	add_file(line, lem);
	while (get_next_line(0, &line))
	{
		if (line[0] != '#')
		{
			check_link(lem, line);
			make_link(lem->node, line, 0);
			make_link(lem->node, line, 1);
		}
		add_file(line, lem);
	}
}
