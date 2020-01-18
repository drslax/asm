/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:35:36 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/18 06:15:59 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	add_instruction(t_asm **data, t_inst *new)
{
	t_inst	*current;

	current = (*data)->instructions;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	print_data(t_asm *data)
{
	t_inst	*inst;
	int		i;

	i = 0;
	printf("\n*************printing data***********\n");
	printf(".filename %s\n", data->file_name);
	printf(".name %s\n", data->cmd_name);
	printf(".cmt %s\n", data->cmd_comment);
	inst = data->instructions;
	while (inst)
	{
		printf("%02d° inst:", i + 1);
		printf("\t%s%c\t%s\t%s\t%s\t%s\n",
			inst->label ? inst->label : "\t",
			inst->label ? ':' : ' ',
			inst->name ? inst->name : "\t",
			inst->args[0] ? inst->args[0] : "\t",
			inst->args[1] ? inst->args[1] : "\t",
			inst->args[2] ? inst->args[2] : " ");
		inst = inst->next;
		i += 1;
	}
}

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
	new->args[0] = ft_strsub(line, 0, arg_length);
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
	new->args[index] = ft_strsub(line, 0, arg_length);
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
		new->args[2] = ft_strsub(line + index, 0, arg_length);
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
	return (1);
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
			args = ft_strlen(new->name) + skip_wsp(line + ft_strlen(new->name));
		}
	}
	if (new->name)
		return (args);
	return (ft_raise_exception(12, NULL));
}

int		manage_label(char *line, t_inst *inst)
{
	int		index;
	char	*label;

	index = 0;
	if ((label = ft_strchr(line, LABEL_CHAR)))
	{
		if (ft_ischarin(LABEL_CHARS, *(label - 1)))
		{
			inst->label = ft_strsub(line, 0, label - line);
			while (inst->label[index])
			{
				if (!ft_ischarin(LABEL_CHARS, inst->label[index]))
				{
					ft_memdel((void**)&inst->label);
					ft_raise_exception(13, NULL);
				}
				index += 1;
			}
		}
		else
		{
			inst->label = NULL;
			return (0);
		}
	}
	else
	{
		inst->label = NULL;
		return (0);
	}
	if (!inst->label)
		return (0);
	index += 1;
	while (ft_ischarin(WHITESPACES, *(line + index)))
		index += 1;
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
		add_instruction(&data, new);
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
	int		cursor;
	t_inst	*new;

	allocate_instruction(&new);
	if (!*line)
		return (1);
	cursor = manage_label(line, new);
	if (!*(line + cursor))
		return (label_simple_line(line, cursor, data, new));
	cursor += manage_inst_name(line + cursor, new);
	if (!cursor)
		return (0);
	if (!*(line + cursor))
		return (ft_raise_exception(14, NULL));
	if (!(manage_arguments(line + cursor, new)))
		return (0);
	add_instruction(&data, new);
	return (1);
}
