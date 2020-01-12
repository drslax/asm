/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 23:13:25 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/11 00:08:27 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
** if (ft_ischarin(WHITESPACES, line[index]))
*/

void	add_instruction(t_asm **data, t_inst *new)
{
	t_inst	*current;

	current =  (*data)->instructions;
	while (current->next)
		current = current->next;
	current->next = new;
}

int		last_arg(char *last)
{
	int	len;

	len = 0;
	while (*(last + len) && !ft_ischarin(WHITESPACES, *(last + len)))
		len += 1;
	return (len);
}

void	manage_arguments(char *line, t_inst *new)
{
	char	*comma;
	char	*tmp;
	int		index;

	index = 0;
	while (ft_ischarin(WHITESPACES, *line))
		line += 1;
	if ((comma = ft_strchr(line, ',')))
	{
		new->args[0] = ft_strsub(line, 0, comma - line);
		line = comma + 1;
		if ((comma = ft_strchr(line, ',')))
		{
			while (ft_ischarin(WHITESPACES, *line))
				line += 1;
			new->args[1] = ft_strsub(line, 0, comma - line);
			if (comma && comma + 1)
			{
				while (ft_ischarin(WHITESPACES, *comma))
					comma += 1;
				new->args[2] = ft_strsub(comma + 1, 0, last_arg(comma + 1));
			}
		}
		else if (comma && comma + 1)
		{
			while (ft_ischarin(WHITESPACES, *(comma)))
				comma += 1;
			new->args[1] = ft_strsub(comma + 1, 0, last_arg(comma + 1));
		}
	}
	else
		new->args[0] = ft_strsub(line, 0, last_arg(line));
}

int		manage_inst_name(char *line, t_inst *new)
{
	char	*name;
	char	*start;
	int		index;
	int		args;

	index = -1;
	start = line + 1 + (new->label ? ft_strlen(new->label) : 0);
	while (ft_ischarin(WHITESPACES, *start))
		start += 1;
	while (g_op_tab[++index].name)
	{
		if ((name = ft_strstr(start, g_op_tab[index].name)) && name + 1
				&& !(name - start))
		{
			new->name = ft_strdup(g_op_tab[index].name);
			args = name - line + ft_strlen(new->name);
		}
	}
	if (new->name)
		return (args);
	error("INVALID NAME INSTRUCTION");
}

void	manage_label(char *line, t_inst *inst)
{
	int		index;
	int		jndex;
	char	*label;

	if (((label = ft_strchr(line, ':')) &&
				label + 1 && ft_ischarin(WHITESPACES, *(label + 1))))
	{
		index = 0;
		inst->label = ft_strsub(line, 0, label - line);
		while (inst->label[index])
		{
			if (!ft_ischarin(LABEL_CHARS, inst->label[index]))
			{
				ft_memdel((void**)&inst->label);
				error("INVALID CHARS IN LABEL");
			}
			index += 1;
		}
	}
	else
		inst->label = NULL;
}

int		emptylines(char *line)
{
	while (ft_ischarin(WHITESPACES, *line))
		line += 1;
	if (!*line)
		return (1);
	return (0);
}

void    get_instructions(int filedesc, t_asm *data)
{
	char	*line;
	char	*comment;
	int		EOL;
	int		args;
	t_inst	*new;
	// int		i;

	// i = 2;
	while ((EOL = get_next_line(filedesc, &line)) >= 0)
	{
		// printf("line %i %s\n", i + 1, line);
		if (line && line[0] != COMMENT_CHAR)
		{
			comment = ft_strchr(line, COMMENT_CHAR);
			if (comment)
				comment[0] = '\0';
			if (emptylines(line))
				continue ;
			allocate_instruction(&new);
			manage_label(line, new);
			args = manage_inst_name(line, new);
		// printf("easy\n");
			// printf("%d\n",			args);
			manage_arguments(line + args, new);
			add_instruction(&data, new);
		}
		ft_memdel((void**)&line);
		if (!EOL)
			break ;
	}
}
