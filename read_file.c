/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:21:57 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/26 00:38:27 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char	*check_double_quotes(char *cmd, int cmd_len)
{
	char	*start;
	char	*line;
	char	*content;
	char	*tmp;

	start = (cmd + cmd_len) + skip_wsp(cmd + cmd_len);
	line = ft_strsub(start, 0, ft_strlen(start) - ignore_wsp(start));
	if (line && line[0] == '"')
	{
		if (!(tmp = ft_strchr(line + 1, '"')) || ft_strlen(tmp) != 1)
		{
			ft_memdel((void**)&line);
			ft_raise_exception(5, cmd);
			return (NULL);
		}
		else if (tmp && ft_strlen(tmp) == 1)
		{
			content = ft_strsub(line, 1, ft_strlen(line) - 2);
			ft_memdel((void**)&line);
			return (content);
		}
	}
	ft_memdel((void**)&line);
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

// void	allocate_label(t_label **label)
// {
// 		*label = (t_label*)malloc(sizeof(t_label));
// 		(*label)->id = -1;
// 		(*label)->name = NULL;
// 		(*label)->addr = NULL;
// }

int		force_quit(char *line, t_asm *data, t_inst *inst)
{
	line ? ft_memdel((void**)&line) : 0;
	data ? free_s_asm(data) : 0;
	(void)inst;
	inst ? free_s_instructions(inst) : 0;
	return (0);
}

// void	print_labels(t_label *lab)
// {
// 	int i = 0;

// 	while (lab)
// 	{
// 		printf("lab %d = %s\n", i, lab->name);
// 		lab = lab->next;
// 		i += 1;
// 	}
// }

/*
** force quit in return (0)
*/

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
					return (0);
			}
		}
		ft_memdel((void**)&line);
		if (!eol)
			break ;
	}
	//print_labels(data->labels);
	// if (data->remain_labels)
	// 	fix_label_size(data->instructions, data);
	printf("\e[1m\e[42m√\e[0m:\n");
	// print_labels(data->labels);
	print_data(data, 1);
	return (1);
}
