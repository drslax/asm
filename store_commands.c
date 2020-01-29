/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:41:52 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 06:32:06 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		store_command(int fd, char *line, char *buffer, size_t buffsize)
{
	char	*newline;
	int		inquote;
	int		index;
	size_t	buffer_index;

	index = 0;
	inquote = 0;
	newline = 0;
	buffer_index = ft_strlen(buffer);
	if (buffer_index)
		inquote = 1;
	while (line[index])
	{
		if (line[index] == '"')
			inquote ^= 1;
		else if (inquote)
		{
			if (buffer_index >= buffsize)
			{
				ft_memdel((void**)&newline);
				return (ft_raise_exception(6, ft_itoa(buffsize)));
			}
			buffer[buffer_index] = line[index];
			buffer_index++;
		}
		else
		{
			ft_memdel((void**)&newline);
			return (ft_raise_exception(19, &line[index]));
		}
		index++;
	}
	if (inquote)
	{
		buffer[buffer_index] = '\n';
		if (get_next_line(fd, &newline) < 1)
			return (0);
		inquote = store_command(fd, newline, buffer, buffsize);
		ft_memdel((void**)&newline);
		return (inquote);
	}
	if (buffer_index > buffsize)
	{
		ft_memdel((void**)&newline);
		return (ft_raise_exception(6, ft_itoa(buffsize)));
	}
	return (1);
}

int		store_name_command(t_asm *data, char *line,
		int filedesc, char *command_buffer)
{
	char	*command;

	command = line + ft_strlen(NAME_CMD_STRING)
			+ skip_wsp(line + ft_strlen(NAME_CMD_STRING));
	if (!store_command(filedesc, command, command_buffer, PROG_NAME_LENGTH))
		return (0);
	data->cmd_name = ft_strdup(command_buffer);
	return (1);
}

int		store_comment_command(t_asm *data, char *line,
		int filedesc, char *command_buffer)
{
	char *command;

	command = line + ft_strlen(COMMENT_CMD_STRING)
			+ skip_wsp(line + ft_strlen(COMMENT_CMD_STRING));
	if (!store_command(filedesc, command, command_buffer, COMMENT_LENGTH))
		return (0);
	data->cmd_comment = ft_strdup(command_buffer);
	return (1);
}
