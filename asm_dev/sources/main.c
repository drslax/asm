/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 20:05:59 by abiri             #+#    #+#             */
/*   Updated: 2020/01/13 18:32:29 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	check_extension(char *filename)
{
	size_t	length;

	length = ft_strlen(filename);
	if (length >= 2)
	{
		if (!(filename[length - 1] == 's' && filename[length - 2] == '.'))
			error("INVALID EXTENSTION [.s]");
	}
	else
		error("INVALID FILENAME");	
}

int		open_file(char *filename)
{
	int	filedesc;

	errno = 0;
	filedesc = open(filename, O_RDONLY);
	if (errno)
	{
		perror(filename);
		return (-1);
	}
	return (filedesc);
}

void	tts_parse_args(char *filename, t_asm *data)
{
	int	filedesc;

	check_extension(filename);
	if ((filedesc = open_file(filename)) < 0)
		error(NULL);
	else
		read_file(filedesc, data);
}

void	initialize_asm(t_asm **data)
{
	*data = (t_asm *)malloc(sizeof(t_asm));
	(*data)->cmd_comment = NULL;
	(*data)->cmd_name = NULL;
	(*data)->instructions = NULL;
/*	data->instructions.label = NULL;
	data->instructions.name = NULL;
	data->instructions.args[0] = NULL;
	data->instructions.args[1] = NULL;
	data->instructions.args[2] = NULL;
	data->next = NULL;*/
}

int main(int argc, char **argv)
{
	int		iterator;
	t_asm	*data;

	iterator = 0;
	initialize_asm(&data);
	if (argc > 1)
		while (++iterator < argc)
			tts_parse_args(argv[iterator], data);
	else
		error("REQUIRES FILE OR MORE");
	
	return (-1);
}
