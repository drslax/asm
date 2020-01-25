/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sou3ada <sou3ada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 04:51:53 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/25 17:05:32 by sou3ada          ###   ########.fr       */
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

int		read_args(char *filename, t_asm *data)
{
	int		filedesc;
	char	*error;

	filedesc = open_file(filename);
	initialize_asm(&data, filename);
	if (!errno)
	{
		if (!read_file(filedesc, data))
		{
			return (0);
		}
		return (1);
	}
	error = strerror(errno);
	ft_raise_exception(19, error);
	ft_memdel((void**)&error);
	return (0);
}

int		parse_args(char *filename, t_asm *data)
{
	errno = 0;
	if (check_extension(filename))
		return (read_args(filename, data));
// free_s_asm(data);
	return (ft_raise_exception(0, filename));
}
