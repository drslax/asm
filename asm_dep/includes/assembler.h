/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:34:30 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/16 23:36:39 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H
# include "op.h"
# include "../libft/libft.h"
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
	char	*file_name;
	char	*cmd_name;
	char	*cmd_comment;
	t_inst	*instructions;
}				t_asm;


void	free_s_asm(t_asm *data);
int		ft_raise_exception(int error_code, char *custom);
int		read_file(int filedesc, t_asm *data);
void	allocate_instruction(t_inst **instructions);
int		get_instructions(char *line, t_asm *data);
void	print_data(t_asm *data);

int		skip_wsp(char *line);
int		skip_not_wsp(char *line);
int		ignore_wsp(char *line);


#endif
