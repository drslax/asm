/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:21:57 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 06:42:13 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_command(int filedesc, char *line, t_asm *data)
{
	int		name_cmd;
	int		comment_cmd;
	char	name_buffer[PROG_NAME_LENGTH + 2];
	char	comment_buffer[COMMENT_LENGTH + 2];

	ft_bzero(name_buffer, PROG_NAME_LENGTH + 2);
	ft_bzero(comment_buffer, COMMENT_LENGTH + 2);
	name_cmd = command_isname(line);
	comment_cmd = command_iscomment(line);
	if (!name_cmd && !comment_cmd)
		return (ft_raise_exception(8, line));
	else if (name_cmd && !comment_cmd)
		return (store_name_command(data, line, filedesc, name_buffer));
	else if (!name_cmd && comment_cmd)
		return (store_comment_command(data, line, filedesc, comment_buffer));
	ft_memdel((void**)&line);
	return (0);
}

int		read_line(int filedesc, t_asm *data, int *code)
{
	int		eol;
	int		skip;
	char	*line;

	while ((eol = get_next_line(filedesc, &line)) >= 0)
	{
		skip = skip_wsp(line);
		if ((line && (line[0] != COMMENT_CHAR && line[0] != COMMENT_CHAR_2))
			&& !ft_strequ(line, ""))
		{
			ft_find_comment(line);
			if (!data->cmd_name || !data->cmd_comment || line[skip] == '.')
			{
				if (!(get_command(filedesc, line + skip, data)))
					return (free_s_asm(&data));
				continue ;
			}
			if (!get_instructions(line + skip, data, code))
				return (free_s_asm(&data));
		}
		ft_memdel((void**)&line);
		if (!eol)
			break ;
	}
	return (!(*code) ? ft_raise_exception(19, "sh had lbssala ?") : 1);
}

int		read_file(int filedesc, t_asm *data)
{
	int		code;

	code = 0;
	if (!read_line(filedesc, data, &code))
		return (0);
	if (!replace_label_value(data->instructions, data))
		return (0);
	print_data(data, 0);
	return (1);
}
