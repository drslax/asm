/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sou3ada <sou3ada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:34:30 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/25 16:04:56 by sou3ada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H
# include "op.h"
# include "../libft/libft.h"
# include <errno.h>
# include <stdio.h>
# define MAX_INST 10009

extern int	errno;
extern char	*g_error_strings[];

typedef struct	s_arguments
{
	char	*name;
	int		type;
}				t_arg;

typedef struct	s_instructions
{
	char					*label;
	int						id;
	char					*name;
	int						size;
	int						size_set;
	t_arg					*args[3];
	struct s_instructions	*tail;
	struct s_instructions	*next;
}				t_inst;

typedef struct s_label
{
	int		id;
	char	*name;
	t_inst	*addr;
}				t_label;

typedef struct	s_asm
{
	char	*file_name;
	char	*cmd_name;
	char	*cmd_comment;
	int		size_champ;
	int		remain_labels;
	t_label	*labels;
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

int     check_valid_args(t_inst *inst);
int     str_type_arg(char *arg);

int		update_size_instruction(t_inst *inst);


int 	type_size(int type, int id);
int		write_file(t_asm *data);
void	allocate_label(t_label **label);

#endif
