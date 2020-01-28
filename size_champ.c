/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_champ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 03:14:11 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/28 04:59:23 by slyazid          ###   ########.fr       */
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
			inst->size += type_size(inst->args[index]->type, inst->id);
			if (inst->args[index]->type != T_REG)
			{
				name = inst->args[index]->name;
				if ((name && *(name + 1) == LABEL_CHAR) || (name && *name == LABEL_CHAR))
					inst->label_in_arg = 1;
			}
			index += 1;
		}
		inst->size += (g_op_tab[inst->id].octet_codage ? 1 : 0);
	}
	return (0);
}

t_inst	*iter_in_instructions(t_inst *instructions, int iter_number)
{
	while (iter_number && instructions)
	{
		instructions = instructions->next;
		iter_number -= 1;
	}
	if (iter_number && !instructions)
		return (NULL);
	return (instructions);
}

int		get_value(t_asm *data, int current_line, int position)
{
	int		index;
	int		result;
	t_inst	*current_inst;

	index = 0;
	result = 0;
	if (position > 0)
	{
		current_inst = iter_in_instructions(data->instructions, current_line);
		while (position && current_inst)
		{
			result += current_inst->size;
			current_inst = current_inst->next;
			position -= 1;
		}
		return (result);
	}
	current_inst = iter_in_instructions(data->instructions,
		position + current_line);
	// printf("initial position = %d | %s\n", current_inst->line, current_inst->label);
	while (position < 0 && current_inst)
	{
		while (!current_inst->name)
		{
			position += 1;
			current_inst = current_inst->next;
		}
		if (!position)
			break ;
		// {
			// printf("\t%d: %d line added.\n",current_inst->line, current_inst->size);
			result += current_inst->size;
			current_inst = current_inst->next;
			position += 1;
		// }
		// else
		// {
		// }
		
	}
	return (-result);
}

int		get_label_line(t_asm *data, t_inst *inst, int id)
{
	int		index;
	t_label	*label;

	label = data->labels;
	index = 0;
	while (index < label->id)
	{
		if (ft_strequ(label[index].addr->label,
			*(inst->args[id]->name) == LABEL_CHAR ?
				inst->args[id]->name + 1: inst->args[id]->name + 2))
			return (label[index].addr->line - inst->line);
		index += 1;
	}
	return (ft_raise_exception(18, inst->args[id]->name + 2));
}

void	get_label_value(t_inst *inst, t_asm *data)
{
	int		diff_line;
	int		index;
	char	*name;
	char	tab[2];
	int		value;

	while (inst)
	{
		if (inst->label_in_arg)
		{
			index = 0;
			while (index < 3)
			{
				// printf(">> %s | type = %d\n", inst->args[index]->name, inst->args[index]->type);
				if (inst->args[index]->type != T_REG)
				{
					name = inst->args[index]->name;
					if ((name && name + 1 && *(name + 1) == LABEL_CHAR )|| (name && *name == LABEL_CHAR))
					{
						if ((diff_line = get_label_line(data, inst, index)) != 0)
						{
							// printf("this label = %d\n", inst->line);
							value = get_value(data, inst->line, diff_line);
							// printf("label = %s => %d\n", inst->args[index]->name, value);
							ft_memdel((void**)&(inst->args[index]->name));
							// printf("type = %d\n", inst->args[index]->type);
							if (inst->args[index]->type == T_DIR)
							{
								tab[0] = DIRECT_CHAR;
								tab[1] = '\0';
								inst->args[index]->name = ft_strjoin(tab, ft_itoa(value));
							}
							else
							{
								inst->args[index]->name = ft_itoa(value);
								// printf("value = %s\n",ft_itoa(value));
							}
						}
					}
				}
				index += 1;
			}
		}
		inst = inst->next;
	}
}