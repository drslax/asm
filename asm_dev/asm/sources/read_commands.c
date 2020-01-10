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
	if (cmd <= 2)
		error = ft_strdup("COMMAND NOT WELL FORMATED");
	else if (!(cmd[length - 1] == '"' && cmd[0] == '"'))
		error = ft_strdup("DOUBLE QUOTES MISSING");
	return (error);
}

void	store_name_command(t_asm *data, char *line)
{
	size_t	length;

	if ((length = ft_strlen(line)) <= PROG_NAME_LENGTH + 2)
		data->cmd_name = ft_strsub(line, 1, length - 1);
	else
		error("PROG NAME LENGTH ABOVE MAX");
}

void	store_comment_command(t_asm *data, char *line)
{
	size_t	length;

	if ((length = ft_strlen(line)) <= COMMENT_LENGTH + 2)
		data->cmd_name = ft_strsub(line, 1, length - 1);
	else
		error("COMMENT LENGTH ABOVE MAX");
}

void	get_command(char *line, t_asm *data)
{
	char	*error_desc;
	int		name_cmd;
	int		comment_cmd;
	size_t	length;

	name_cmd = 0;
	comment_cmd = 0;
	if (ft_strequ(line, NAME_CMD_STRING))
		name_cmd = 1;
	else if (ft_strequ(line, COMMENT_CMD_STRING))
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
	ft_memdel((void**)&line);
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
	// get_command(filedesc, data);
	if (data->cmd_comment && data->cmd_name)
		get_instructions(filedesc, data);
	else
		error("MISSING COMMAND NAME/COMMENT");
	
}
