#ifndef ASM_H
# define ASM_H

#include "libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define LABEL 0
#define INST 1
#define COMMAND 2

typedef	struct		s_arg
{
	int				type;
	char			*str;
	int				value;
}					t_arg;

typedef struct		s_lexer
{
	int				type;
	char			*name;
	char			*data;
	int				op;
	t_arg			arg[3];
	struct s_lexer	*next;
}					t_lexer;

typedef struct		s_asm
{
	char			*file_name;
	int				cor_fd;
	int				s_fd;
	int				size;
	char			*line;
	t_lexer			*lexer;
}					t_asm;

char	*grab_name(char *s);
t_lexer	*add_list(t_lexer **lexer, char *name, int type, t_asm *env);
#endif
