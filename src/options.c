/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:21:15 by yhliboch          #+#    #+#             */
/*   Updated: 2019/04/10 13:21:17 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_map(t_lem *lem)
{
	t_file	*file;

	file = lem->file;
	while (file)
	{
		ft_printf("%s\n", file->line);
		file = file->next;
	}
	ft_printf("\n");
}

void	add_file(char *line, t_lem *lem)
{
	t_file	*tmp;

	if (lem->file == NULL)
	{
		lem->file = ft_memalloc(sizeof(t_file));
		lem->file->next = NULL;
		lem->file->line = line;
		return ;
	}
	tmp = lem->file;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_memalloc(sizeof(t_file));
	tmp->next->next = NULL;
	tmp->next->line = line;
}

int		count_lst(t_lst *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	del_links(t_node *tmp_node, t_room *room)
{
	t_lst	*del;
	t_lst	*tmp_link;

	tmp_link = tmp_node->link;
	if (tmp_link->room == room)
	{
		del = tmp_node->link;
		tmp_node->link = tmp_node->link->next;
	}
	else
	{
		while (tmp_link->next->room != room)
			tmp_link = tmp_link->next;
		del = tmp_link->next;
		tmp_link->next = tmp_link->next->next;
	}
	free(del);
}

t_node	*find_node(t_room *room, t_lem *lem)
{
	t_node	*tmp_node;

	tmp_node = lem->node;
	while (tmp_node && tmp_node->room != room)
		tmp_node = tmp_node->next;
	return (tmp_node);
}
