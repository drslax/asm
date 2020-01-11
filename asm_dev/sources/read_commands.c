/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 22:00:03 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/10 23:53:14 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char	*check_double_quotes(char *cmd)
{
	size_t	length;
	char	*error;

	error = NULL;
	length = ft_strlen(cmd);
	if (length <= 2)
		error = ft_strdup("COMMAND NOT WELL FORMATED");
	else if (!(cmd[length - 1] == '"' && cmd[0] == '"'))
		error = ft_strdup("DOUBLE QUOTES MISSING");
	return (error);
}

void	store_name_cmd(t_asm *data, char *line)
{
	size_t	length;
	char	*first_quotes;
	char	*last_quotes;

	if ((length = ft_strlen(line)) <= PROG_NAME_LENGTH + 2)
	{
		first_quotes = ft_strchr(line, '"') + 1;
		last_quotes = ft_strrchr(line, '"');
		data->cmd_name = ft_strsub(line, first_quotes - line, last_quotes - first_quotes);
	}
	else
		error("PROG NAME LENGTH ABOVE MAX");
}

void	store_comment_cmd(t_asm *data, char *line)
{
	size_t	length;
	char	*first_quotes;
	char	*last_quotes;

	if ((length = ft_strlen(line)) <= COMMENT_LENGTH + 2)
	{
		first_quotes = ft_strchr(line, '"') + 1;
		last_quotes = ft_strrchr(line, '"');
		data->cmd_comment = ft_strsub(line, first_quotes - line, last_quotes - first_quotes);
	}
	else
		error("COMMENT LENGTH ABOVE MAX");
}

void	get_command(char *line, t_asm *data)
{
	char	*error_desc;
	char	*cmd;
	int		name_cmd;
	int		comment_cmd;
	size_t	length;

	name_cmd = 0;
	comment_cmd = 0;
	if ((cmd = ft_strstr(line, NAME_CMD_STRING)) && !(line - cmd))
		name_cmd = 1;
	else if ((cmd = ft_strstr(line, COMMENT_CMD_STRING)) && !(line - cmd))
		comment_cmd = 1;
	else
	{
		if (line && line[0] == '.')
			error("UNDEFINED COMMAND");
		else
			error("PROGRAM SHOULD START WITH COMMANDS");
	}
	if (name_cmd ^ comment_cmd)
	{
		if (!(error_desc = check_double_quotes(line)))
		{
			ft_memdel((void**)&line);
			error(error_desc);
		}
		name_cmd ? store_name_cmd(data, line) : store_comment_cmd(data, line);
	}
}

void	allocate_instruction(t_inst **instructions)
{
	*instructions = (t_inst*)malloc(sizeof(t_inst));
	(*instructions)->label = NULL;
	(*instructions)->name = NULL;
	(*instructions)->args[0] = NULL;
	(*instructions)->args[1] = NULL;
	(*instructions)->args[2] = NULL;
	(*instructions)->next = NULL;
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
		printf("\t%s %s %s %s %s\n", inst->label, inst->name, inst->args[0], inst->args[1], inst->args[2]);
		inst = inst->next;
		i += 1;
	}
}

void	read_file(int filedesc, t_asm *data)
{
	int		command;
	char	*line;
	char	*comment;

	command = -2;
	while (get_next_line(filedesc, &line) >= 0 && command < 0)
	{
		if (line && line[0] != COMMENT_CHAR)
		{
			comment = ft_strchr(line, COMMENT_CHAR);
			command += 1;
			if (comment)
				comment[0] = '\0';
			get_command(line, data);
		}
		ft_memdel((void**)&line);
	}
	allocate_instruction(&data->instructions);
	// get_command(filedesc, data);
	if (!command)
		get_instructions(filedesc, data);
	else
		error("MISSING COMMAND NAME/COMMENT");
	print_data(data);
}
