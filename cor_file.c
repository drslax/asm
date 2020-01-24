/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zbi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelouarg <aelouarg@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:19:51 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/23 04:44:52 by aelouarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"


void	ft_write_int(int filedesc, int value)
{
	value = ((value & 0xFF000000) >> 24) |
		((value & 0x00FF0000) >> 8) | ((value & 0x0000FF00) << 8) |
		((value & 0x000000FF) << 24);
	write(filedesc, &value, sizeof(int));
}

void	ft_write_short(int filedesc, short value)
{
	value = ((value & 0xFF00) >> 8) | ((value & 0xFF) << 8);
	write(filedesc, &value, sizeof(short));
}

void	ft_write_bytes(int filedesc, unsigned char *bytes, size_t size)
{
	write(filedesc, bytes, size);
}

void	write_exec_magic(int filedesc)
{
	int				magic;

	magic = COREWAR_EXEC_MAGIC;
	ft_write_int(filedesc, magic);
}

void	write_command_name(int filedesc, t_asm *data)
{
	char	name_bytes[PROG_NAME_LENGTH];

	ft_bzero(name_bytes, PROG_NAME_LENGTH);
	ft_strcpy(name_bytes, data->cmd_name);
	ft_write_bytes(filedesc, (unsigned char*)name_bytes, PROG_NAME_LENGTH);
	ft_write_int(filedesc, 0);
}

void	write_command_comment(int filedesc, t_asm *data)
{
	char	comment_bytes[COMMENT_LENGTH];

	ft_bzero(comment_bytes, COMMENT_LENGTH);
	ft_strcpy(comment_bytes, data->cmd_comment);
	ft_write_bytes(filedesc, (unsigned char*)comment_bytes, COMMENT_LENGTH);
	ft_write_int(filedesc, 0);
}

int	create_file(t_asm *data)
{
	int	filedesc;

	(void)data;
	if ((filedesc= open("cor.cor", O_WRONLY | O_APPEND | O_CREAT, 0777)) < 0)
		return (-1);
	return (filedesc);
}

void write_champ_exec_code(int fildesc, t_asm *data)
{
	ft_write_int(fildesc, data->size_champ);
}

int	write_file(t_asm *data)
{
	int		filedesc;

	if ((filedesc = create_file(data)) < 0)
		return (0);
	write_exec_magic(filedesc);
	write_command_name(filedesc, data);
	write_champ_exec_code(filedesc, data);
	write_command_comment(filedesc, data);
	return (1);
}
