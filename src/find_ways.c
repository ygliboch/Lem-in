/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:19:29 by yhliboch          #+#    #+#             */
/*   Updated: 2019/04/30 15:19:31 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	hide_the_way(t_lem *lem)
{
	t_node	*tmp_ways;
	t_node	*tmp_node;
	t_lst	*tmp_link;
	t_lst	*link;

	tmp_ways = lem->ways;
	while (tmp_ways->next)
		tmp_ways = tmp_ways->next;
	tmp_link = tmp_ways->link;
	while (tmp_link && tmp_link->room != lem->end)
	{
		tmp_node = find_node(tmp_link->room, lem);
		link = tmp_node->link;
		while (link)
		{
			del_links(tmp_node, link->room);
			del_links(find_node(link->room, lem), tmp_node->room);
			link = tmp_node->link;
		}
		tmp_link = tmp_link->next;
	}
}

t_node	*new_way(t_node *new, t_lem *lem)
{
	t_room	*tmp_room;
	t_room	*tmp_end;
	t_lst	*tmp_link;

	new->next = NULL;
	new->room = lem->start;
	new->link = ft_memalloc(sizeof(t_lst));
	tmp_end = lem->end;
	tmp_room = lem->start;
	while (tmp_end->way != tmp_room)
		tmp_end = tmp_end->way;
	tmp_room = tmp_end;
	new->link->room = tmp_end;
	tmp_link = new->link;
	while (tmp_room != lem->end)
	{
		tmp_end = lem->end;
		while (tmp_end->way != tmp_room)
			tmp_end = tmp_end->way;
		tmp_room = tmp_end;
		tmp_link->next = ft_memalloc(sizeof(t_lst));
		tmp_link->next->room = tmp_end;
		tmp_link = tmp_link->next;
	}
	return (new);
}

void	remember_way(t_lem *lem)
{
	t_node	*tmp_ways;

	if (lem->ways == NULL)
	{
		lem->ways = ft_memalloc(sizeof(t_node));
		new_way(lem->ways, lem);
		lem->ways->lnth = count_lst(lem->ways->link);
		lem->ways->sum = 0;
		lem->ways->ants = 0;
	}
	else
	{
		tmp_ways = lem->ways;
		while (tmp_ways->next)
			tmp_ways = tmp_ways->next;
		tmp_ways->next = ft_memalloc(sizeof(t_node));
		new_way(tmp_ways->next, lem);
		tmp_ways->next->lnth = count_lst(tmp_ways->next->link);
		tmp_ways->next->sum = sum_steps(tmp_ways->next, lem);
		lem->ways->next->ants = 0;
	}
}

void	init_turn(t_lem *lem)
{
	t_lst	*del_turn;
	t_node	*tmp_node;

	tmp_node = lem->node;
	while (lem->turn)
	{
		del_turn = lem->turn;
		lem->turn = lem->turn->next;
		free(del_turn);
		del_turn = NULL;
	}
	while (tmp_node)
	{
		tmp_node->room->fl = 0;
		tmp_node->room->way = NULL;
		tmp_node = tmp_node->next;
	}
	lem->start->fl = 1;
	lem->turn = ft_memalloc(sizeof(t_lem));
	lem->turn->room = lem->start;
	lem->turn->next = NULL;
}

void	find_ways(t_lem *lem)
{
	t_node	*tmp_end;

	tmp_end = lem->node;
	while (tmp_end && tmp_end->room != lem->end)
		tmp_end = tmp_end->next;
	while (tmp_end->link)
	{
		init_turn(lem);
		if (!(bfs(lem)))
			return ;
		remember_way(lem);
		if (lem->ways->lnth == 1)
			return ;
		hide_the_way(lem);
	}
}
