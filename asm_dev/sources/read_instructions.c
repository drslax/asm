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

void	add_inst(t_inst	**inst)
{
	t_inst	*iter;

	iter = *inst;
	while (iter->next)
		iter = iter->next;
	iter->next = (t_inst*)malloc(sizeof(t_inst));
}

void	manage_label(char *line, t_asm *data)
{
	int		index;
	int		jndex;
	char	*label;

	index = 0;
	jndex = index;
	data->instructions->next = (t_inst*)malloc(sizeof(t_inst));
	//while (line[index])
	//{
		if ((label = ft_strstr(line, ":\t")))
			data->instructions->label = ft_strsub(line, 0, label - line);
		else
			data->instructions->label = NULL;
	printf("line = %s | label = %s | diff = %ld\n", line, data->instructions->label, label? label - line : -1);
	//	index += 1;
	//}
}

void    get_instructions(int filedesc, t_asm *data)
{
	char	*line;
	char	*comment;
	int		EOL;
	int		i = 0;

	while ((EOL = get_next_line(filedesc, &line)) > 0)
	{
		printf("i = %d\n", i++);
		if (line && line[0] != COMMENT_CHAR)
		{
			comment = ft_strchr(line, COMMENT_CHAR);
			if (comment)
				comment[0] = '\0';
			manage_label(line, data);
			//printf("EOL = %d label = %s\n", EOL, data->instructions->label);
		//	manage_instructions(line, data);
		}
		else
			printf("line null\n");
		ft_memdel((void**)&line);
		if (!EOL)
			break ;
	}
}
