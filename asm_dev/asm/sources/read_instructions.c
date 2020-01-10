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

void	manage_label(char	*line, t_asm *data)
{
	int	index;
	int	jndex;

	index = 0;
	jndex = index;
	while (line[index])
	{
		
	}
}

void    get_instructions(int filedesc, t_asm *data)
{
	char	*line;
	char	*comment;
	int		EOL;

	while ((EOL = get_next_line(filedesc, &line)) >= 0)
	{
		if (line && line[0] != COMMENT_CHAR)
		{
			comment = ft_strchr(line, COMMENT_CHAR);
			if (comment)
				comment[0] = '\0';
			manage_label(line, data);
			manage_instructions(line, data);
		}
		ft_memdel((void**)&line);
		if (!EOL)
			break ;
	}
}