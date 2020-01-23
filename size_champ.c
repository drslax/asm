/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 03:14:11 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/23 06:19:00 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"


int		type_size(int type, int id)
{
	if (type == T_REG)
		return (REG_SIZE);
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_DIR)
		return (DIR_SIZE - (g_op_tab[id].label_size ? 2 : 4));
	return (-1);
}

int		update_size_instruction(t_inst *inst)
{
	int		index;
	char	*name;

	if (inst)
	{
		inst->size = 1;
		index = 0;
		while (inst->args[index])
		{
			if (inst->args[index]->type == T_REG)
				inst->size += type_size(inst->args[index]->type, inst->id);
			else
			{
				name = inst->args[index]->name;
				if (name && *(name + 1) != LABEL_CHAR)
					inst->size += type_size(inst->args[index]->type, inst->id);
				else if (name)
				{
					inst->size = 0;
					return (1);
				}
			}
			index += 1;
		}
		inst->size += 1;
	}
	return (0);
}

// void	fix_label_size(t_inst *inst)
// {
	
// }

// int		manage_label_size(t_asm *data, t_arg *arg, t_inst *current)
// {
// 	t_inst	*search;
// 	int		current_pos;

// 	current_pos = 0;
// 	search = data->instructions;
// 	if (*(arg->name + 1) != LABEL_CHAR)
// 	{
// 		if (arg->type == T_IND)
// 			return (IND_SIZE);
// 		if (arg->type == T_DIR)
// 			return (DIR_SIZE - (g_op_tab[current->id].label_size ? 2 : 4));
// 	}
// 	else
// 	{
// 		while (search)
// 		{
// 			if (search == current)
// 				current_pos = 1;
// 			if (search->label)
// 				if (ft_strequ(search->label, arg->name + 1) && !found)
// 				{

// 				}
// 			search = search->next;
// 		}
// 	}
	
// }

// int		get_inst_size(t_asm *data)
// {
// 	int		index;
// 	t_inst	*inst;

// 	index = 0;
// 	inst = data->instructions;
// 	inst->size = 1;
// 	while (inst->args[index])
// 	{
// 		if (inst->args[index]->type == T_REG)
// 		{
// 			inst->size += REG_SIZE;
// 			inst->size_set = 1;
// 			return ;
// 		}
// 		// inst->size += manage_label_size(data, inst->args[index], inst);
// 		index += 1;
// 	}
// }

// void	get_size_champ(t_asm *data)
// {
// 	t_inst	*inst;

// 	inst = data->instructions;
// 	while (inst)
// 	{
// 		data->size_champ += get_inst_size(data);
// 		inst = inst->next;
// 	}
// }