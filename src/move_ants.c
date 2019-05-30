/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:55:04 by yhliboch          #+#    #+#             */
/*   Updated: 2019/04/30 17:55:19 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		sum_steps(t_node *way, t_lem *lem)
{
	int		sum;
	t_node	*tmp_ways;

	tmp_ways = lem->ways;
	sum = 0;
	while (tmp_ways && tmp_ways != way)
	{
		sum += way->lnth - tmp_ways->lnth;
		tmp_ways = tmp_ways->next;
	}
	return (sum);
}

void	one_step(t_node *way, t_lem *lem)
{
	t_lst	*tmp_link;
	t_node	*tmp_way;
	int		i;
	int		rm;

	i = 0;
	tmp_way = lem->ways;
	while (tmp_way != way)
		tmp_way = tmp_way->next;
	rm = tmp_way->ants;
	while (i != rm)
	{
		tmp_link = tmp_way->link;
		while (tmp_link && tmp_link->room->ant == 0)
			tmp_link = tmp_link->next;
		while (tmp_link && tmp_link->next->room->ant != 0)
			tmp_link = tmp_link->next;
		ft_printf("L%d-%s ", tmp_link->room->ant, tmp_link->next->room->name);
		if (tmp_link->next->room == lem->end)
			tmp_way->ants--;
		else
			tmp_link->next->room->ant = tmp_link->room->ant;
		tmp_link->room->ant = 0;
		i++;
	}
}

void	move(t_lem *lem)
{
	t_node	*tmp_way;

	tmp_way = lem->ways;
	while (tmp_way)
	{
		if (tmp_way->ants > 0)
			one_step(tmp_way, lem);
		tmp_way = tmp_way->next;
	}
}

void	move_ants2(t_lem *lem)
{
	int		ant;
	t_node	*way;

	ant = 1;
	while (ant > 0)
	{
		ant = 0;
		way = lem->ways;
		while (way)
		{
			if (way->ants > 0)
			{
				move(lem);
				ft_printf("\n");
				lem->num_lines++;
				ant++;
			}
			way = way->next;
		}
	}
	if (lem->fl == 1)
		ft_printf("number of lines: %d\n", lem->num_lines);
}

void	move_ants(t_lem *lem)
{
	t_node	*way;
	int		ant;

	ant = 1;
	while (lem->ants)
	{
		way = lem->ways;
		if (lem->ways->ants > 0)
			move(lem);
		while (way && lem->ants && lem->ants > way->sum)
		{
			ft_printf("L%d-%s ", ant, way->link->room->name);
			way->link->room->ant = ant;
			if (way->link->room != lem->end)
				way->ants++;
			lem->ants--;
			ant++;
			way = way->next;
		}
		ft_printf("\n");
		lem->num_lines++;
	}
	move_ants2(lem);
}
