/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:19:51 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/27 04:52:05 by slyazid          ###   ########.fr       */
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
	int		filedesc;
	char	*name;
	char	*path;

	name = ft_strsub(data->file_name, 0, ft_strlen(data->file_name) - 2);
	path = ft_strjoin(name, ".cor");
	ft_memdel((void**)&name);
	if ((filedesc= open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777)) < 0)
	{
		ft_memdel((void**)&path);
		return (-1);
	}
	ft_memdel((void**)&path);
	return (filedesc);
}

void write_champ_exec_code(int fildesc, t_asm *data)
{
	ft_write_int(fildesc, data->size_champ);
}

void	write_atc(int filedesc, t_inst *inst)
{
	char	value;
	int		index;

	index = 0;
	value = 0;
	while (index < 3)
	{
		if (inst->args[index]->name)
			value |= (inst->args[index]->type & 0xFF) << (6 - 2 * index);
		index += 1;
	}
	ft_write_bytes(filedesc, (unsigned char*)&value, 1);
}

void	write_arguments(int filedesc, t_inst *inst)
{
	int	index;
	int	value;

	index = 0;
	while (index < 3)
	{
		if (inst->args[index]->name)
		{
			if (inst->args[index]->type == T_REG)
			{
				value = ft_atoi(inst->args[index]->name + 1);
				ft_write_bytes(filedesc, (unsigned char*)&value, 1);
			}
			else
			{
				printf("type of %s = %d\n", inst->args[index]->name, type_size(inst->args[index]->type, index));
				if (inst->args[index]->type == T_DIR && type_size(inst->args[index]->type, inst->id) == 2)
					ft_write_short(filedesc, ft_atoi(inst->args[index]->name + 1));
				else
					ft_write_int(filedesc, ft_atoi(inst->args[index]->name + 1));
			}
		}
		index += 1;
	}
}

// void	write_arguments(int filedesc, t_arg *argument[3])
// {
// 	int	index;

// 	index = 0;
// 	while (index < 3)
// 	{
// 		if (argument[index]->name)
// 		{
// 			if (argument[index]->type == T_REG)
// 				ft_write_bytes(filedesc, (unsigned char *)ft_atoi(argument[index]->name + 1)), 1);
// 			else
// 				ft_write_short(filedesc, ft_atoi(argument[index]->name + 1));
// 		}
// 		index += 1;
// 	}

void	write_instructions(int filedesc, t_inst *inst)
{
	while (inst)
	{
		if (inst->name)
		{
			ft_write_bytes(filedesc, (unsigned char*)&(g_op_tab[inst->id].op_code), 1);
			if (g_op_tab[inst->id].octet_codage)
				write_atc(filedesc, inst);
			write_arguments(filedesc, inst);
		}
		inst = inst->next;
	}
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
	write_instructions(filedesc, data->instructions);
	return (1);
}
