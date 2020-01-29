/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   todelete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:47:29 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 06:00:26 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void print_data(t_asm *data, int debug)
{
	t_inst *inst;
	int i;

	if (debug)
	{
		i = 0;
		printf(".filename %s\n", data->file_name);
		printf(".name %s\n", data->cmd_name);
		printf(".cmt %s\n", data->cmd_comment);
		printf("remaining labels %d\n", data->instructions->label_in_arg);
		inst = data->instructions;
		printf("MAGIC DZAB :%s\n", ft_itoa(COREWAR_EXEC_MAGIC));
		while (inst)
		{
			printf("%03d° inst\t%d:", inst->line, inst->size);
			printf("\t%s%c\t%s\t%s[%d]\t%s[%d]\t%s[%d]\n", inst->label ? inst->label : "\t",
				   inst->label ? ':' : ' ',
				   inst->name ? inst->name : "\t",
				   inst->args[0]->name ? inst->args[0]->name : "\t",
				   inst->args[0]->type != 16 ? type_size(inst->args[0]->type, inst->id) : -1,
				   inst->args[1]->name ? inst->args[1]->name : "\t",
				   inst->args[1]->type != 16 ? type_size(inst->args[1]->type, inst->id) : -1,
				   inst->args[2]->name ? inst->args[2]->name : " ",
				   inst->args[2]->type != 16 ? type_size(inst->args[2]->type, inst->id) : -1);
			inst = inst->next;
			i += 1;
		}
	}
	else
	{
			char	*name;
			char	*path;

			name = ft_strsub(data->file_name, 0, ft_strlen(data->file_name) - 2);
			path = ft_strjoin(name, ".cor");
		printf("Writing output program to %s\n", path);
	}
}

void	print_labels(t_label *labels)
{
	int i = 0;

	if (labels)
	{
		while (i < labels->id)
		{
			printf("%d label %s (%p)\n", labels[i].addr->line, labels[i].addr->name, labels[i].addr);
			printf("\t%s\n", labels[i].addr->name ? labels[i].addr->name : labels[i].addr->next->name);
			i += 1;
		}
	}
}



// int		replace(t_inst *inst, t_asm *data, int index)
// {
// 	int		diff_line;
// 	char	*name;
// 	int		error;
// 	int		value;

// 	error = 0;
// 	if (!inst)
// 		return (1);
// 	if (!index)
// 		return (replace(inst->next, data, index));
// 	else
// 	{
// 		name = inst->args[index]->name;
// 		if ((name && name + 1 && *(name + 1) == LABEL_CHAR) ||
// 			(name && *name == LABEL_CHAR))
// 		{
// 			diff_line = get_label_line(data, inst, index, &error);
// 			if (error)
// 				return (0);
// 			value = get_value(data, inst->line, diff_line);
// 			ft_memdel((void**)&(inst->args[index]->name));
// 			replace_by_type(inst, index, value);
// 		}
// 		return (replace(inst, data, index - 1));
// 	}
// }