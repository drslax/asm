/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 04:35:36 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/17 01:36:57 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	add_instruction(t_asm **data, t_inst *new)
{
	t_inst	*current;

	current =  (*data)->instructions;
	// if (*data)
	while (current->next)
		current = current->next;
	current->next = new;
	// print_data(*	data);
}

void	print_data(t_asm *data)
{
	t_inst	*inst;
	int		i = 0;

	printf("\n*************printing data***********\n");
	printf(".name %s\n", data->cmd_name);
	printf(".cmt %s\n", data->cmd_comment);
	inst = data->instructions;
	while (inst)
	{
		printf("%d° inst:\n", i + 1);
		printf("\t%s [%s] [%s] [%s] [%s]\n", inst->label, inst->name,
			inst->args[0], inst->args[1], inst->args[2]);
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

// int	manage_arguments(char *line, t_inst *new)
// {
// 	char	*comma;
// 	int		index;

// 	index = 0;
// 	if ((comma = ft_strchr(line, SEPARATOR_CHAR)))
// 	{
// 		new->args[0] = ft_strsub(line, 0, comma - line);
// 		line = comma + 1;
// 		if ((comma = ft_strchr(line, SEPARATOR_CHAR)))
// 		{
// 			while (ft_ischarin(WHITESPACES, *line))
// 				line += 1;
// 			new->args[1] = ft_strsub(line, 0, comma - line);
// 			if (comma && comma + 1)
// 			{
// 				while (ft_ischarin(WHITESPACES, *comma))
// 					comma += 1;
// 				new->args[2] = ft_strsub(comma + 1, 0, last_arg(comma + 1));
// 			}
// 		}
// 		else if (!comma && line)
// 		{
// 			while (line && ft_ischarin(WHITESPACES, *(line)))
// 				line += 1;
// 			if (!line)
//                 ft_raise_exception(11, NULL);
// 			new->args[1] = ft_strsub(line, 0, last_arg(line));
// 		}
// 	}
// 	else
// 		new->args[0] = ft_strsub(line, 0, last_arg(line));
// 	return (1);
// }


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

int		multiple_args(char *line, t_inst *new, char *separator)
{
	int	arg_length;
	int	index;
	char	*tmp;
	int	mem_index;

	printf("line = [%s]\n", line);
	arg_length = skip_not_wsp(line);
	printf("line + arg_len = %d [%s]\n", arg_length, line + arg_length);
	new->args[0] = ft_strsub(line, 0, arg_length);
	arg_length += skip_wsp(line + arg_length);
	printf("line + arg_len = [%s]\n", line + arg_length);
	if (line + arg_length == separator)
	{
		arg_length += skip_wsp(line + arg_length + 1) + 1;
		index = arg_length;
		mem_index = index;
		if ((separator = ft_strchr(line + index, SEPARATOR_CHAR)))
		{
			arg_length = skip_not_wsp(line + index);
			new->args[1] = ft_strsub(line + index, 0, arg_length);
			index += skip_wsp(line + index + arg_length);
			tmp = line + index + arg_length;
			// printf("line + index = [%s]\n", line + index + arg_length);
			if (*(line + index + arg_length) == SEPARATOR_CHAR)
			{
				tmp += 1;
				index = skip_wsp(tmp);
				arg_length = skip_not_wsp(tmp + index);
				new->args[2] = ft_strsub(tmp + index, 0, arg_length);
				if (!*(tmp + index + arg_length + skip_wsp(tmp + index + arg_length)))
					return (1);
				else
					return (ft_raise_exception(14, NULL));
			}
			else if (!*(line + index + arg_length))
				return (1);
			else
				return(ft_raise_exception(14, line + index + arg_length));
			// else
			// 	return (ft_raise_exception(15, NULL));
		}
		else
		{
			arg_length = skip_not_wsp(line + index);
			new->args[1] = ft_strsub(line + index, 0, arg_length);
			index += skip_wsp(line + index + arg_length);
			if (!*(line + index + arg_length))
				return (1);
			else
				return(ft_raise_exception(14, line + index + arg_length));
		}

	}
	else
		return (ft_raise_exception(15, line));
	return (1);
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

int 	manage_label(char *line, t_inst *inst)
{
	int		index;
	char	*label;

    index = 0;
	if ((label = ft_strchr(line, LABEL_CHAR)))
	{
		inst->label = ft_strsub(line, 0, label - line);
		while (inst->label[index])
		{
			if (!ft_ischarin(LABEL_CHARS, inst->label[index]))
			{
				ft_memdel((void**)&inst->label);
                ft_raise_exception(13, NULL);
				// error("INVALID CHARS IN LABEL");
			}
			index += 1;
		}
	}
	else
		inst->label = NULL;
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

int    get_instructions(char *line, t_asm *data)
{
	int		spaces;
    t_inst  *new;

    allocate_instruction(&new);
    //needs add inst to list;
    if (!line)
        return (ft_raise_exception(17, NULL));
    spaces = manage_label(line, new); // later will be new, add before return;
	// printf("line + label + spaces = [%s]\n", line + spaces);
    if (!*(line + spaces))
        return (1);
    spaces += manage_inst_name(line + spaces, new);
	// printf("line + label + spaces + inst + spaces= [%s]\n", line + spaces);

    // free before return (0);
    if (!*(line + spaces))
        return (ft_raise_exception(14, NULL));
	// printf("line + label + spaces + inst + spaces + args= [%s]\n", line + spaces);
    if (!(manage_arguments(line + spaces, new)))
		return (0);
    // if (line + spaces && *(line + spaces))
    //     return (ft_raise_exception(14, line + spaces));
	// printf("good\n");
    add_instruction(&data, new);
    // printf("[%s]\n", line + spaces);
    // (void)data;
    return (1);
}
