/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:34:08 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/17 23:13:48 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_extension(char *filename)
{
	size_t	length;

	length = ft_strlen(filename);
	if (length >= 2)
	{
		if (!(filename[length - 1] == 's' && filename[length - 2] == '.'))
			return (0);
		return (1);
	}
	return (0);
}

int		open_file(char *filename)
{
	int	filedesc;

	errno = 0;
	filedesc = open(filename, O_RDONLY);
	if (errno)
		return (-1);
	return (filedesc);
}

int		parse_args(char *filename, t_asm *data)
{
	int		filedesc;
	char	*error;

	errno = 0;
	if (check_extension(filename))
	{
		filedesc = open_file(filename);
		if (!errno)
		{
			if (!read_file(filedesc, data))
			{
				free_s_asm(data);
				return (0);
			}
		}
		else
		{
			free_s_asm(data);
			error = strerror(errno);
			ft_raise_exception(17, error);
			ft_memdel((void**)&error);
			return (0);
		}
	}
	else
	{
		free_s_asm(data);
		return (ft_raise_exception(0, filename));
	}
	return (1);
}

void	initialize_asm(t_asm **data, char *arg)
{
	if (!(*data = (t_asm *)malloc(sizeof(t_asm))))
		exit(-1);
	(*data)->file_name = arg;
	(*data)->cmd_comment = NULL;
	(*data)->cmd_name = NULL;
	allocate_instruction(&(*data)->instructions);

	// (*data)->instructions = NULL;
}

int		main(int argc, char **argv)
{
	t_asm	*data;
	int		iterator;

	iterator = 0;
	if (argc > 1)
		while (++iterator < argc)
		{
			initialize_asm(&data, argv[iterator]);
			if (!parse_args(argv[iterator], data))
				continue ;
			free_s_asm(data);
		}
	else
		ft_raise_exception(2, NULL);
	return (1);
}
