/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:34:30 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/13 21:01:27 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H
# include "op.h"
# include "libft.h"
# include <errno.h>
# include <stdio.h>

extern int	errno;
extern char	*g_error_strings[];

typedef struct	s_instructions
{
	char					*label;
	char					*name;
	char					*args[3];
	struct s_instructions	*next;
}				t_inst;

typedef struct	s_asm
{
	char	*cmd_name;
	char	*cmd_comment;
	t_inst	*instructions;
}				t_asm;


void	free_s_asm(t_asm *data);
int		ft_raise_exception(int error_code, char *custom);
#endif
