/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 13:16:42 by yhliboch          #+#    #+#             */
/*   Updated: 2019/04/22 13:16:43 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_old_link(t_lem *lem, char *line)
{
	t_node	*nd;
	t_lst	*link;

	nd = lem->node;
	while (nd && ft_strncmp(line, nd->room->name,
			ft_strlen(nd->room->name)))
		nd = nd->next;
	link = nd->link;
	while (link)
	{
		if (ft_strcmp(line + ft_strlen(nd->room->name)
							+ 1, link->room->name) == 0)
			error("error\n");
		link = link->next;
	}
}

void	add_rooms(t_node *tmp_node, t_lst *turn, t_lst *tmp_link)
{
	t_lst	*tmp_turn;

	tmp_turn = turn;
	while (tmp_link)
	{
		if (tmp_link->room->fl == 0)
		{
			tmp_link->room->fl = 1;
			tmp_link->room->way = tmp_node->room;
			while (tmp_turn->next != NULL)
				tmp_turn = tmp_turn->next;
			tmp_turn->next = ft_memalloc(sizeof(t_lst));
			tmp_turn->next->room = tmp_link->room;
			tmp_turn->next->next = NULL;
		}
		tmp_link = tmp_link->next;
	}
}

int		bfs(t_lem *lem)
{
	t_node	*tmp_node;
	t_lst	*tmp_link;
	t_lst	*del_turn;

	while (lem->turn && lem->turn->room != lem->end)
	{
		tmp_node = lem->node;
		while (tmp_node && tmp_node->room != lem->turn->room)
			tmp_node = tmp_node->next;
		tmp_link = tmp_node->link;
		add_rooms(tmp_node, lem->turn, tmp_link);
		del_turn = lem->turn;
		lem->turn = lem->turn->next;
		free(del_turn);
		del_turn = NULL;
	}
	return (lem->end->way == NULL ? 0 : 1);
}
