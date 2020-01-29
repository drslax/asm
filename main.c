/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:34:08 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 06:49:09 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		main(int argc, char **argv)
{
	t_asm	*data;
	int		iterator;

	iterator = 0;
	data = NULL;
	if (argc > 1)
		while (++iterator < argc)
		{
			allocate_asm(&data);
			if (!parse_args(argv[iterator], data))
			{
				continue ;
			}
			write_file(data);
		}
	else
		ft_raise_exception(2, NULL);
	return (1);
}

/*
**	free before contnue and after write;
*/
