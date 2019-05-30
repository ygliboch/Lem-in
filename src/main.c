/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 11:50:30 by yhliboch          #+#    #+#             */
/*   Updated: 2019/04/08 11:50:32 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(char *str)
{
	ft_printf("%s", str);
	exit(0);
}

int		main(int argc, char **argv)
{
	t_lem lem;

	lem.node = NULL;
	lem.turn = NULL;
	lem.start = NULL;
	lem.end = NULL;
	lem.ways = NULL;
	lem.file = NULL;
	lem.num_lines = 0;
	lem.fl = 0;
	if (argc == 2 && ft_strcmp(argv[1], "-f") == 0)
		lem.fl = 1;
	else if ((argc == 2 && ft_strcmp(argv[1], "-f")) || argc > 2)
		error("error\n");
	valid(&lem);
	find_ways(&lem);
	if (!lem.ways)
		error("error\n");
	print_map(&lem);
	move_ants(&lem);
	return (0);
}
