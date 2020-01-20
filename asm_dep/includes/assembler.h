/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:34:30 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/19 20:55:16 by slyazid          ###   ########.fr       */
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
	int						id;
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

void	initialize_asm(t_asm **data, char *arg);
int		parse_args(char *filename, t_asm *data);


int		read_file(int filedesc, t_asm *data);
void	allocate_instruction(t_inst **instructions);
int		get_instructions(char *line, t_asm *data);
void	print_data(t_asm *data, int debug);

int		skip_wsp(char *line);
int		skip_not_wsp(char *line);
int		ignore_wsp(char *line);

void	free_s_instructions(t_inst *inst);
int		force_quit(char *line, t_asm *data, t_inst *inst);

#endif
