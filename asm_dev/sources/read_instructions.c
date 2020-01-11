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

void	manage_label(char *line, t_inst *inst)
{
	int		index;
	int		jndex;
	char	*label;

	index = 0;
	jndex = index;
	//while (line[index])
	//{
		if ((label = ft_strstr(line, ":\t")))
			inst->label = ft_strsub(line, 0, label - line);
		else
			inst->label = NULL;
	//	printf("line = %s | label = %s | diff = %ld\n", line, inst->label, label? label - line : -1);
	//	index += 1;
	//}
}

void    get_instructions(int filedesc, t_asm *data)
{
	char	*line;
	char	*comment;
	int		EOL;
	int		i = 0;
	t_inst	*new;

	while ((EOL = get_next_line(filedesc, &line)) > 0)
	{
		printf("i = %d ", i++);
		printf("line = %s\n", line);
		if (line && line[0] != COMMENT_CHAR)
		{
			comment = ft_strchr(line, COMMENT_CHAR);
			if (comment)
				comment[0] = '\0';
			allocate_instruction(&new);
			manage_label(line, new);
			//printf("EOL = %d label = %s\n", EOL, data->instructions->label);
			//manage_instructions(line, data);

			//add_instruction(data, new);
		}
		else
			printf("line null\n");
		ft_memdel((void**)&line);
//		if (!EOL)
//			break ;
	}
}
