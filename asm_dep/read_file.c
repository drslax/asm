/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:21:57 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/14 00:53:13 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"


int		skip_wsp(char *line)
{
	int	sp;

	sp = 0;
	while (line && ft_ischarin(WHITESPACES, *(line + sp)))
		sp += 1;
	return (sp);
}

int		ignore_wsp(char *line)
{
	int		sp;
	int		len;

	sp = 0;
	len = ft_strlen(line);
	printf("line = [%s]", line + len);
	while (len >= 0 && ft_ischarin(WHITESPACES, *(line + len)))
	{
		sp += 1;
		len -= 1;
	}
	return (sp);
}

int		check_double_quotes(char *cmd)
{
	size_t  length;
	int		trimmed;

	trimmed = skip_wsp(cmd);
	length = ft_strlen(cmd) - trimmed;
	if (length <= 2)
		return (ft_raise_exception(8, "Not well formated."));
	printf("[%c] [%c]\n", cmd[trimmed + length - 1], cmd[trimmed + 8]);
	 if (!(cmd[trimmed + length - 1] == '"' && cmd[trimmed] == '"'))
		return (ft_raise_exception(5, NULL));
	return (1);
}

void	error(char *str)
{
	ft_putendl(str);
}

int		store_name_cmd(t_asm *data, char *line)
{
	size_t	length;
	char	*first_quotes;
	char	*last_quotes;

	if (data->cmd_name)
		return (ft_raise_exception(3, NULL));
	if ((length = ft_strlen(line)) <= PROG_NAME_LENGTH + 2)
	{
		first_quotes = ft_strchr(line, '"') + 1;
		last_quotes = ft_strrchr(line, '"');
		data->cmd_name = ft_strsub(line, first_quotes - line, last_quotes - first_quotes);
	}
	else
		error("PROG NAME LENGTH ABOVE MAX");
	return (1);
}

int		store_comment_cmd(t_asm *data, char *line)
{
	if (data->cmd_comment)
		return (ft_raise_exception(4, NULL));
	printf("line + 8 = [%s]\n", line + 8);
	exit(0);
}

/*
 * trimmed = line + skip_wsp(line + 8) + 8;
 *     length = ft_strlen(trimmed) - skip_wsp(line) - ignore_wsp(trimmed);
 *         printf("len = %zu | trimmed = %s\n", length, trimmed);;
 *             if (!trimmed || trimmed[0] != '"' )
 *                     return (ft_raise_exception(5, NULL));
 *                         if ((length = ft_strlen(trimmed)) <= COMMENT_LENGTH + 2)
 *                             {
 *                                     first_quotes = ft_strchr(trimmed, '"') + 1;
 *                                             last_quotes = ft_strrchr(trimmed, '"');
 *                                                     data->cmd_comment = ft_strsub(line, first_quotes - line, last_quotes - first_quotes);
 *                                                         }
 *                                                             else
 *                                                                     error("COMMENT LENGTH ABOVE MAX");
 *                                                                         printf("%s\n", data->cmd_comment);
 *                                                                             exit(0);
 */
int		get_command(char *line, t_asm *data)
{
	char	*cmd;
	int		name_cmd;
	int		comment_cmd;

	name_cmd = 0;
	comment_cmd = 0;
	if ((cmd = ft_strstr(line, NAME_CMD_STRING)) && !(line- cmd))
		name_cmd = 1;
	else if ((cmd = ft_strstr(line, COMMENT_CMD_STRING)) && !(line - cmd))
		comment_cmd = 1;
	else
		return (ft_raise_exception(8, line));
	if (name_cmd ^ comment_cmd)
	{
		if (!(check_double_quotes(line)))
			return (0);
		else if (name_cmd)
			return(store_name_cmd(data, line));
		else if (comment_cmd)
			return(store_comment_cmd(data, line));
	}
	else
		return (ft_raise_exception(5, line));
	return (1);
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

int		read_file(int filedesc, t_asm *data)
{
	int		eol;
	int		skipped;
	char	*line;
	char	*comment;

	while ((eol = get_next_line(filedesc, &line)) >= 0)
	{
		skipped = skip_wsp(line);
		if (line && line[0] != COMMENT_CHAR)
		{
			if ((comment = ft_strchr(line, COMMENT_CHAR)))
				comment[0] = '\0';
			if (line[skipped] == '.')
			{
				if (!(get_command(line + skipped, data)))
					return (0);
			}
			else
			{
				allocate_instruction(&data->instructions);
				//if (!get_instructions(filedesc, data))
				//		return (0);
			}
		}
		ft_memdel((void**)&line);
		if (!eol)
			break ;
	}
	return (1);
}
