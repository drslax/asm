/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:35:36 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/25 22:08:21 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

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

void	store_label(t_label **labels, t_inst *list)
{
	int	id;

	if (!*labels)
	{
		allocate_label(labels);
		(*labels)->id = 1;
		(*labels)[0].addr = list->tail;
	}
	else
	{
		id = (*labels)->id;
		(*labels)->id += 1;
		(*labels) = (t_label *)realloc(*labels, (*labels)->id * sizeof(t_label));
		(*labels)[id].addr = list->tail;
	}
}

void	add_instruction(t_inst **list, t_inst *new, t_label **labels)
{
	if (!*list)
	{
		(*list) = new;
		(*list)->tail = (*list);
		(*list)->tail->next = NULL;
	}
	else
	{
		(*list)->tail->next = new;
		(*list)->tail = (*list)->tail->next;
		(*list)->tail->next = NULL;
	}
	if (new->label)
		store_label(labels, *list);
	// if (new->label)
	// 	store_label(*data);
}

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
		printf("remaining labels %d\n", data->remain_labels);
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
		printf("Writing output program to %s\n", data->file_name);
}

/*
void	print_data(t_asm *data, int debug)
{
	t_inst	*inst;
	int		i;

	if (debug)
	{
		i = 0;
		printf(".filename %s\n", data->file_name);
		printf(".name %s\n", data->cmd_name);
		printf(".cmt %s\n", data->cmd_comment);
		printf("remaining labels %d\n", data->remain_labels);
		inst = data->instructions;
		printf("MAGIC DZAB :%s\n", ft_itoa(COREWAR_EXEC_MAGIC));
		while (inst)
		{
			printf("%02d° inst\t%d:", i + 1, inst->size);
			printf("\t%s%c\t%s\t%s[%d]\t%s[%d]\t%s[%d]\n", inst->label ? inst->label : "\t",
				inst->label ? ':' : ' ',
				inst->name ? inst->name : "\t",
				inst->args[0]->name ? inst->args[0]->name : "\t",
				inst->args[0]->type != 16 ? inst->args[0]->type : -1,
				inst->args[1]->name ? inst->args[1]->name : "\t",
				inst->args[1]->type != 16 ? inst->args[1]->type : -1,
				inst->args[2]->name ? inst->args[2]->name : " ",
				inst->args[2]->type != 16 ? inst->args[2]->type : -1);
			inst = inst->next;
			i += 1;
		}
	}
	else
		printf("Writing output program to %s\n", data->file_name);
}
*/
int		last_arg(char *last)
{
	int	len;

	len = 0;
	while (*(last + len) && !ft_ischarin(WHITESPACES, *(last + len)))
		len += 1;
	return (len);
}

int		single_or_less_argument(char *line, t_inst *new)
{
	int	arg_length;
	int	endline;

	arg_length = skip_not_wsp(line);
	new->args[0]->name = ft_strsub(line, 0, arg_length);
	new->args[0]->type = str_type_arg(new->args[0]->name);
	endline = skip_wsp(line + arg_length);
	if (!*(line + arg_length + endline))
		return (1);
	else
		return (ft_raise_exception(14, line + arg_length + endline));
}

int		store_arg_and_skip(char *line, char *separator, t_inst *new, int index)
{
	int		arg_length;
	char	*tmp;

	tmp = separator ? ft_strsub(line, 0, separator - line) : line;
	arg_length = skip_not_wsp(tmp);
	new->args[index]->name = ft_strsub(line, 0, arg_length);
	new->args[index]->type = str_type_arg(new->args[index]->name);
	separator ? ft_memdel((void**)&tmp) : 0;
	arg_length += skip_wsp(line + arg_length);
	return (arg_length);
}

int		check_3rd_arg(char *line, int index, int arg_length, t_inst *new)
{
	line = line + index + arg_length;
	if (*line == SEPARATOR_CHAR)
	{
		line += 1;
		index = skip_wsp(line);
		arg_length = skip_not_wsp(line + index);
		new->args[2]->name = ft_strsub(line + index, 0, arg_length);
		new->args[2]->type = str_type_arg(new->args[2]->name);
		if (arg_length &&
			!*(line + index + arg_length + skip_wsp(line + index + arg_length)))
			return (1);
		else
			return (ft_raise_exception(14, line));
	}
	else if (!*line)
		return (1);
	return (2);
}

int		multiple_args(char *line, t_inst *new, char *separator)
{
	int		arg_length;
	int		res;
	int		index;

	arg_length = store_arg_and_skip(line, separator, new, 0);
	if (line + arg_length == separator)
	{
		arg_length += skip_wsp(line + arg_length + 1) + 1;
		index = arg_length;
		if ((separator = ft_strchr(line + index, SEPARATOR_CHAR)))
		{
			arg_length = store_arg_and_skip(line + index, separator, new, 1);
			if ((res = check_3rd_arg(line, index, arg_length, new)) < 2)
				return (res);
			return (1);
		}
		else
		{
			if (!*(line + index))
				return (ft_raise_exception(11, NULL));
			arg_length = store_arg_and_skip(line + index, separator, new, 1);
			if (!*(line + index + arg_length))
				return (1);
			return (ft_raise_exception(14, line + index + arg_length));
		}
	}
	return (ft_raise_exception(15, line));
}

int		manage_arguments(char *line, t_inst *new)
{
	char	*separator;

	separator = NULL;
	if ((separator = ft_strchr(line, SEPARATOR_CHAR)))
	{
		if (!(multiple_args(line, new, separator)))
			return (0);
	}
	else
	{
		if (!(single_or_less_argument(line, new)))
			return (0);
	}
	return (check_valid_args(new));
}

int		manage_inst_name(char *line, t_inst *new)
{
	char	*name;
	int		index;
	int		args;

	index = -1;
	while (g_op_tab[++index].name)
	{
		if ((name = ft_strstr(line, g_op_tab[index].name)) && !(name - line))
		{
			new->name = ft_strdup(g_op_tab[index].name);
			new->id = index;
			args = ft_strlen(new->name) + skip_wsp(line + ft_strlen(new->name));
		}
	}
	if (new->name)
		return (args);
	return (ft_raise_exception(12, NULL));
}

int		valid_label(char *line, char *label, t_inst *inst)
{
	int index;

	index = 0;
	if (ft_ischarin(LABEL_CHARS, *(label - 1)))
	{
		inst->label = ft_strsub(line, 0, label - line);
		while (inst->label[index])
		{
			if (!ft_ischarin(LABEL_CHARS, inst->label[index]))
			{
				ft_raise_exception(13, NULL);
				return (-1);
			}
			index += 1;
		}
	}
	else
		return (0);
	return (index);
}

/*
**	this function check if there's a label separator, otherwise it returns 0
**	else it checks if the label is valid or not;
*/

int		manage_label(char *line, t_inst *inst)
{
	int		index;
	char	*label;

	index = 0;
	if ((label = ft_strchr(line, LABEL_CHAR)))
	{
		if ((index = valid_label(line, label, inst)) < 1)
			return (index);
	}
	else
		return (0);
	if (!inst->label)
		return (0);
	index += 1;
	index += skip_wsp(line + index);
	return (index);
}

int		emptylines(char *line)
{
	while (ft_ischarin(WHITESPACES, *line))
		line += 1;
	if (!*line)
		return (1);
	return (0);
}

/*
**	label_simple_line :
**	(!simple_line)	A) if a line contains label + inst, spaces will be != 0
**		=>			B) if a line contains only a label, spaces will be != 0
**		=>			C) if the line contain a word != label ===> spaces == 0
**	examples :	A)	labelname: live %1	|	spaces = 11 !*(line + spaces) = 'l'
**				B)	labelbame:\t \t		|	spaces = 13 !*(line + spaces) = '\0'
**				C)	notalabel			|	spaces = 0	!*(line + spaces) = '\0'
*/

int		label_simple_line(char *line, int cursor, t_asm *data, t_inst *new)
{
	if (cursor)
	{
		add_instruction(&data->instructions, new, &data->labels);
		return (1);
	}
	return (ft_raise_exception(12, line));
}

/*
**	if (!cursor)			== there are no instructions.
**	if (!*(line + cursor))	== valid instructions with invalid endofline.
*/

int		get_instructions(char *line, t_asm *data)
{
	int			cursor;
	t_inst		*new;
	static int	num;

	allocate_instruction(&new);
	initialize_instruction(&new);
	new->line = num++;
	if (!*line)
		return (1);
	if ((cursor = manage_label(line, new)) == -1)
		return (force_quit(NULL, NULL, new));
	if (!*(line + cursor))
		return (label_simple_line(line, cursor, data, new));
	cursor += manage_inst_name(line + cursor, new);
	if (!cursor)
		return (0);
	if (!*(line + cursor))
		return (ft_raise_exception(14, NULL));
	if (!(manage_arguments(line + cursor, new)))
		return (0);
	if (update_size_instruction(new))
		data->remain_labels = 1;
	add_instruction(&data->instructions, new, &data->labels);
	data->size_champ += new->size;
	return (1);
}

// void	store_labels(t_inst *addr, char *label)
// {
	
// }
