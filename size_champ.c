/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 03:14:11 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/26 01:07:11 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"


int		type_size(int type, int id)
{
	if (type == T_REG)
		return (1);
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_DIR)
		return (DIR_SIZE - (g_op_tab[id].label_size ? 2 : 0));
	return (0);
}

int		update_size_instruction(t_inst *inst)
{
	int		index;
	char	*name;

	if (inst)
	{
		inst->size = 1;
		index = 0;
		while (index < 3)
		{
			// if (inst->args[index]->type == T_REG)
			// else
				inst->size += type_size(inst->args[index]->type, inst->id);
				if (inst->args[index]->type != T_REG)
			{
				name = inst->args[index]->name;
				if (name && *(name + 1) == LABEL_CHAR)
				{
					inst->label_in_arg = 1;
					// return (1);
				}
			}
			index += 1;
		}
		inst->size += (g_op_tab[inst->id].octet_codage ? 1 : 0);
	}
	return (0);
}

int		get_size_label(t_asm *data, t_inst *inst, int direction, int index)
{
	int		result;
	int		i;
	t_inst	*iterator;

	result = -1;
	if (direction < 0)
	{
		result = 0;
		i = 0;
		iterator = data->instructions;
		while (i++ < inst->line + direction) //label + 0;
			iterator = iterator->next;
		if (!iterator->name)
			iterator = iterator->next; //1st inst after label
		while (iterator != inst)
		{
			result += iterator->size;
			iterator = iterator->next;
		}
		// if (iterator == inst)
		// 		{
		// 			printf("result = %d\n", result);
		// 			print_data(data, 1);
		// 			exit(0);
		// 		}	 
	}
	else if (direction > 0)
	{
		
	}
	return (result);
	// printf(">>>>>>>>%d,%d\n", i, inst->line + direction);
	// if (direction < 0)
	// {
	// 	while (i < inst->line + direction - 1)
	// 	{
	// 		printf("line = %d\n", i);
	// 		i += 1;
	// 	}
	// 	printf("stored[] = %d", data->labels[inst->])
	// 	exit(0);
	// }
	(void)index;
}

int		get_label_line(t_asm *data, t_inst *inst, int id)
{
	int		index;
	t_label	*label;

	label = data->labels;
	index = 0;
	while (index < label->id)
	{
		if (ft_strequ(label[index].addr->label, inst->args[id]->name + 2))
		{
			printf("stored = %d | current = %d\n", label[index].addr->line, inst->line);
			return (label[index].addr->line - inst->line);
		}
		index += 1;
	}
	return (ft_raise_exception(18, inst->args[id]->name + 2));
}

void	fix_label_size(t_inst *inst, t_asm *data)
{
	int		diff_line;
	int		index;
	char	*name;

	while (inst)
	{
		if (inst->size < 0)
		{
			inst->size = 0; // reset size not to add 1 later
			index = 0;
			while (index < 3)
			{
				if (inst->args[index]->type == T_REG)
					inst->size += type_size(inst->args[index]->type, inst->id);
				else
				{
					name = inst->args[index]->name;
					if (name && name + 1 && *(name + 1) != LABEL_CHAR)
						inst->size += type_size(inst->args[index]->type, inst->id);
					else if (name && *(name + 1) == LABEL_CHAR)
					{
						if ((diff_line = get_label_line(data, inst, index)) < 0)
							inst->size += get_size_label(data, inst, diff_line, index);
							// printf("diff_line = %d\n", diff_line);
							// inst->size += get_size_label(data, inst, diff_line, index);
						// else
						// {
						// 	zero_yawjeh_zero();
						// }
					}
				}
				index += 1;
			}
		}
		inst = inst->next;
	}
}

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
