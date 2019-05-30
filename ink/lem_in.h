/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:51:58 by yhliboch          #+#    #+#             */
/*   Updated: 2019/05/06 16:54:21 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# define INT_MAX 2147483647

typedef struct		s_room
{
	char			*name;
	struct s_room	*way;
	int				x;
	int				y;
	int				fl;
	int				ant;
}					t_room;

typedef struct		s_lst
{
	t_room			*room;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_file
{
	char			*line;
	struct s_file	*next;
}					t_file;

typedef struct		s_node
{
	t_room			*room;
	t_lst			*link;
	int				lnth;
	int				sum;
	struct s_node	*next;
	int				ants;
}					t_node;

typedef struct		s_lem
{
	int				ants;
	t_file			*file;
	t_node			*node;
	t_lst			*turn;
	t_node			*ways;
	t_room			*start;
	t_room			*end;
	int				fl;
	int				num_lines;
}					t_lem;

void				valid(t_lem *lem);
void				error(char *str);
void				take_check_links(t_lem *lem, char *line);
void				new_room(t_lem *lem, char *line, int fl);
void				check_link(t_lem *lem, char *line);
void				find_ways(t_lem *lem);
int					count_lst(t_lst	*lst);
void				del_links(t_node *tmp_node, t_room *room);
int					bfs(t_lem *lem);
void				find_ways(t_lem *lem);
t_node				*find_node(t_room *room, t_lem *lem);
int					sum_steps(t_node *way, t_lem *lem);
void				move_ants(t_lem *lem);
void				add_file(char *line, t_lem *lem);
void				print_map(t_lem *lem);
void				check_old_link(t_lem *lem, char *line);

#endif
