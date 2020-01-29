/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 22:21:57 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 08:53:34 by slyazid          ###   ########.fr       */
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
	ft_memdel((void**)&line);
	return (!(*code) ? ft_raise_exception(19, "sh had lbssala ?") : 1);
}

void	write_valid_output(char *file_name)
{
	char	*name;
	char	*path;

	name = ft_strsub(file_name, 0, ft_strlen(file_name) - 2);
	path = ft_strjoin(name, ".cor");
	ft_memdel((void**)&name);
	printf("Writing output program to %s\n", path);
	ft_memdel((void**)&path);
}

int		read_file(int filedesc, t_asm *data)
{
	int		code;


	code = 0;
	if (!read_line(filedesc, data, &code))
		return (0);
	if (!replace_label_value(data->instructions, data))
		return (0);
	write_valid_output(data->file_name);
	return (1);
}
