/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 03:14:11 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/29 08:16:11 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_label_line(t_asm *data, t_inst *inst, int id, int *error)
{
	int		index;
	t_label	*label;

	label = data->labels;
	index = 0;
	while (index < label->id)
	{
		if (ft_strequ(label[index].addr->label,
			*(inst->args[id]->name) == LABEL_CHAR ?
				inst->args[id]->name + 1 : inst->args[id]->name + 2))
			return (label[index].addr->line - inst->line);
		index += 1;
	}
	*error = 1;
	return (ft_raise_exception(7, ft_itoa(inst->line)));
}

void	replace_by_type(t_inst *inst, int index, int value)
{
	char	tab[2];
	char	*itoa_value;

	itoa_value = NULL;
	ft_memdel((void**)&(inst->args[index]->name));
	if (inst->args[index]->type == T_DIR)
	{
		tab[0] = DIRECT_CHAR;
		tab[1] = '\0';
		itoa_value = ft_itoa(value);
		inst->args[index]->name = ft_strjoin(tab, itoa_value);
		ft_memdel((void**)&(itoa_value));
	}
	else
		inst->args[index]->name = ft_itoa(value);
}

int		replace_label_value(t_inst *inst, t_asm *data)
{
	int		diff_line;
	int		index;
	char	*name;
	int		error;
	int		value;

	error = 0;
	while (inst)
	{
		if (inst->label_in_arg)
		{
			index = -1;
			while (++index < 3)
			{
				name = inst->args[index]->name;
				if ((name && name + 1 && *(name + 1) == LABEL_CHAR) ||
					(name && *name == LABEL_CHAR))
				{
					diff_line = get_label_line(data, inst, index, &error);
					if (error)
						return (0);
					value = get_value(data, inst->line, diff_line);
					replace_by_type(inst, index, value);
				}
			}
		}
		inst = inst->next;
	}
	return (1);
}
