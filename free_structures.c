/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 20:24:16 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 05:54:43 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	free_s_instructions(t_inst **inst)
{
	t_inst	*tmp;

	if (inst && *inst)
	{
		while (*inst)
		{
			tmp = *inst;
			*inst = (*inst)->next;
			ft_memdel((void**)&tmp->label);
			ft_memdel((void**)&tmp->name);
			ft_memdel((void**)&tmp->args[0]);
			ft_memdel((void**)&tmp->args[1]);
			ft_memdel((void**)&tmp->args[2]);
			ft_memdel((void**)&tmp);
		}
	}
}

int		free_s_asm_node(t_asm **data)
{
	ft_memdel((void**)data);
	return (0);
}

int		free_s_asm(t_asm **data)
{
	if (data && *data)
	{
		ft_memdel((void**)&(*data)->cmd_comment);
		ft_memdel((void**)&(*data)->cmd_name);
		free_s_instructions(&(*data)->instructions);
	}
	return (0);
}

int		force_quit(char *line, t_asm *data, t_inst *inst)
{
	line ? ft_memdel((void**)&line) : 0;
	data ? free_s_asm(&data) : 0;
	(void)inst;
	return (0);
}
