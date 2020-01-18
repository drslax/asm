/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:21:57 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/18 06:31:22 by slyazid          ###   ########.fr       */
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
	while (len >= 0 && ft_ischarin(WHITESPACES, *(line + len - 1)))
	{
		sp += 1;
		len -= 1;
	}
	return (sp);
}

int		skip_not_wsp(char *line)
{
	int	not_sp;

	not_sp = 0;
	while (line && *(line + not_sp) &&
			!ft_ischarin(WHITESPACES, *(line + not_sp)))
		not_sp += 1;
	return (not_sp);
}

char	*check_double_quotes(char *cmd, int cmd_len)
{
	char	*start;
	char	*content;
	char	*tmp;

	start = (cmd + cmd_len) + skip_wsp(cmd + cmd_len);
	content = ft_strsub(start, 0, ft_strlen(start) - ignore_wsp(start));
	if (content && content[0] == '"')
	{
		if (!(tmp = ft_strchr(content + 1, '"')) || ft_strlen(tmp) != 1)
		{
			ft_memdel((void**)&content);
			ft_raise_exception(5, cmd);
			return (NULL);
		}
		else if (tmp && ft_strlen(tmp) == 1)
			return (content);
	}
	ft_memdel((void**)&content);
	ft_raise_exception(5, cmd);
	return (NULL);
}

int		store_name_cmd(t_asm *data, char *line)
{
	size_t	length;
	char	*content;

	if (data->cmd_name)
		return (ft_raise_exception(3, NULL));
	if ((content = check_double_quotes(line, ft_strlen(NAME_CMD_STRING))))
	{
		if (!((length = ft_strlen(content)) < PROG_NAME_LENGTH))
			return (ft_raise_exception(6, ft_itoa(PROG_NAME_LENGTH)));
		else
		{
			data->cmd_name = content;
			return (1);
		}
	}
	return (0);
}

int		store_comment_cmd(t_asm *data, char *line)
{
	size_t	length;
	char	*content;

	if (data->cmd_comment)
		return (ft_raise_exception(4, NULL));
	if ((content = check_double_quotes(line, ft_strlen(COMMENT_CMD_STRING))))
	{
		if (!((length = ft_strlen(content)) < COMMENT_LENGTH))
			return (ft_raise_exception(6, ft_itoa(COMMENT_LENGTH)));
		else
		{
			data->cmd_comment = content;
			return (1);
		}
	}
	return (0);
}

int		command_isname(char *line)
{
	char	*cmd;

	if ((cmd = ft_strstr(line, NAME_CMD_STRING)) && !(line - cmd))
		return (1);
	return (0);
}

int		command_iscomment(char *line)
{
	char	*cmd;

	if ((cmd = ft_strstr(line, COMMENT_CMD_STRING)) && !(line - cmd))
		return (1);
	return (0);
}

int		get_command(char *line, t_asm *data)
{
	int		name_cmd;
	int		comment_cmd;

	name_cmd = command_isname(line);
	comment_cmd = command_iscomment(line);
	if (!name_cmd && !comment_cmd)
		return (ft_raise_exception(8, line));
	else if (name_cmd && !comment_cmd)
		return (store_name_cmd(data, line));
	else if (!name_cmd && comment_cmd)
		return (store_comment_cmd(data, line));
	return (0);
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
		if (line && line[0] != COMMENT_CHAR && !ft_strequ(line, ""))
		{
			if ((comment = ft_strchr(line, COMMENT_CHAR)))
				comment[0] = '\0';
			if (!data->cmd_name || !data->cmd_comment || line[skipped] == '.')
			{
				if (!(get_command(line + skipped, data)))
					return (0);
			}
			else
			{
				if (!get_instructions(line + skipped, data))
				{
// free_s_asm(data);
// ft_memdel((void**)&line);
					return (0);
				}
			}
		}
		ft_memdel((void**)&line);
		if (!eol)
			break ;
	}
	print_data(data);
	printf("eol");
	return (1);
}
