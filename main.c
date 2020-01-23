/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:34:08 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/23 00:41:32 by aelouarg         ###   ########.fr       */
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
			initialize_asm(&data, argv[iterator]);
			if (!parse_args(argv[iterator], data))
			{
// free_s_asm(data);
				continue ;
			}
			write_file(data);
// free_s_asm(data);
		}
	else
		ft_raise_exception(2, NULL);
	return (1);
}
