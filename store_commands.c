/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 03:41:52 by slyazid           #+#    #+#             */
/*   Updated: 2020/02/01 03:44:30 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

/*
** // ft_memdel((void**)newline);
**	after if;
*/

int		check_buffer_size(int buffsize, int buffer_index)
{
	char *value;

	value = NULL;
	if (buffer_index > buffsize)
	{
		value = ft_itoa(buffsize);
		ft_raise_exception(6, value);
		ft_memdel((void**)&value);
		return (0);
	}
	return (1);
}

char	*initialize_variables(char *buffer, int *inquote,
		int *index, size_t *buffer_index)
{
	*index = -1;
	*inquote = 0;
	*buffer_index = ft_strlen(buffer);
	return (NULL);
}

void	replace_newline(char *line)
{
	if (*(line + ft_strlen(line) - 1) == '\n')
		*(line + ft_strlen(line) - 1) = '\0';
}

int		get_inquote(char *line, int *inquote, char *buffer, size_t buffsize)
{
	char	*newline;

	newline = NULL;
	if (*line == '"')
		*inquote ^= 1;
	else if (*inquote)
	{
		if (ft_strlen(buffer) >= buffsize)
		{
			ft_memdel((void**)&newline);
			newline = ft_itoa(buffsize);
			ft_raise_exception(6, newline);
			ft_memdel((void**)&newline);
			return (0);
		}
		buffer[ft_strlen(buffer)] = *line;
		return (1);
	}
	else if (!ft_strrchr(WHITESPACES, *line))
	{
		ft_memdel((void**)&newline);
		return (ft_raise_exception(8, line));
	}
	return (2);
}

int		multi_line_content(int inquote, int filedesc,
		int buffsize, char *buffer)
{
	char *newline;

	*buffer = '\n';
	if (get_next_line(filedesc, &newline) < 1)
		return (-1);
	if (*(newline + ft_strlen(newline) - 1) == '\n')
		*(newline + ft_strlen(newline) - 1) = '\0';
	inquote = store_command(filedesc, newline, buffer, buffsize);
	ft_memdel((void**)&newline);
	return (inquote);
}

int		get_multi_line(int fd, int inquote, char *buffer, size_t buffsize)
{
	char *newline;

	newline = NULL;
	if (get_next_line(fd, &newline) < 1)
		return (-1);
	replace_newline(newline);
	inquote = store_command(fd, newline, buffer, buffsize);
	ft_memdel((void**)&newline);
	return (inquote);
}

int		store_command(int fd, char *line, char *buffer, size_t buffsize)
{
	int		inquote;
	int		index;
	size_t	buffer_index;
	int		f;

	initialize_variables(buffer, &inquote, &index, &buffer_index);
	buffer_index ? inquote = 1 : 0;
	replace_newline(line);
	while (line[++index])
	{
		if (!inquote &&
			(line[index] == COMMENT_CHAR || line[index] == COMMENT_CHAR_2))
			return (2);
		if (!(f = get_inquote(line + index, &inquote, buffer, buffsize)))
			return (0);
		if (f == 1)
			buffer_index += 1;
	}
	if (inquote)
	{
		buffer[buffer_index] = '\n';
		return (get_multi_line(fd, inquote, buffer, buffsize));
	}
	return (check_buffer_size(buffsize, buffer_index));
}

int		store_name_command(t_asm *data, char *line,
		int filedesc, char *command_buffer)
{
	char	*command;

	if (data->cmd_name)
		return (ft_raise_exception(3, NULL));
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
	char	*command;
	int		store;

	store = 0;
	if (data->cmd_comment)
		return (ft_raise_exception(4, NULL));
	command = line + ft_strlen(COMMENT_CMD_STRING)
			+ skip_wsp(line + ft_strlen(COMMENT_CMD_STRING));
	if (!(store = store_command(filedesc, command, command_buffer,
		COMMENT_LENGTH)))
		return (0);
	else if (store == -1)
		return (ft_raise_exception(5, NULL));
	data->cmd_comment = ft_strdup(command_buffer);
	return (1);
}
