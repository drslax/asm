/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 20:05:34 by abiri             #+#    #+#             */
/*   Updated: 2020/01/10 23:04:11 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H
# include "libft.h"
# include "op.h"
# include <errno.h>
# include <stdio.h>

extern int  errno;

typedef struct	s_instructions
{
	char	*label;
	char	*name;
	char	args[3];
	// char	*comments;
}				t_inst;


typedef struct	s_asm
{
	char	*cmd_name;
	char	*cmd_comment;
	t_inst	instructions;
}				t_asm;

void    error(char *str);

#endif
