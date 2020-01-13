/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:24:16 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/13 22:05:26 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	free_s_instructions(t_inst *inst)
{
	t_inst	*tmp;

	while (inst)
	{
		tmp = inst;
		inst = inst->next;
		ft_memdel((void**)&tmp->label);
		ft_memdel((void**)&tmp->name);
		ft_memdel((void**)&tmp->args[0]);
		ft_memdel((void**)&tmp->args[1]);
		ft_memdel((void**)&tmp->args[2]);
//		ft_memdel((void**)tmp->args);
		ft_memdel((void**)&tmp);
	}
}

void	free_s_asm(t_asm *data)
{
	ft_memdel((void**)&data->cmd_comment);
	ft_memdel((void**)&data->cmd_name);
	free_s_instructions(data->instructions);
	ft_memdel((void**)&data);
}
