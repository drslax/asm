/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 22:56:38 by aelouarg          #+#    #+#             */
/*   Updated: 2020/01/28 06:40:44 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int 	ft_isint(char *str)
{
	int	i;

	if (str[0] == '-')
		i = 0;
	else
		i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

/*
 **  LABELS are automatically defined as T_IND
 */

int     str_type_arg(char *arg)
{
	if (arg && *arg == DIRECT_CHAR)
		return (T_DIR);
	if (arg && *arg == REGISTER_CHAR)
		return (T_REG);
	if (arg && ft_isint(arg))
		return (T_IND);
	if (arg && *arg == LABEL_CHAR)
		return (T_IND);
	return (0);
}

int     args_number(t_arg *args[3])
{
	int number;

	number = 0;
	while (args[number] && args[number]->name)
		number += 1;
	return (number);
}

int     is_valid_reg(t_arg *reg)
{
	if (reg->type == T_REG)
	{
		if (!ft_isint(reg->name + 1) ||
				ft_atoi(reg->name + 1) < 0 || ft_atoi(reg->name + 1) > REG_NUMBER)
			return (ft_raise_exception(18, reg->name));
	}
	//if (reg->type == T_DIR)
	return (1);
}

int     is_valid_dir(t_arg *dir)
{
	if (dir->type == T_DIR)
	{
		if (!ft_isint(dir->name + 1) && (dir->name && dir->name + 1 && *(dir->name + 1) != LABEL_CHAR))
			return (ft_raise_exception(18, dir->name));
	}
	return (1);
}

int     is_valid_ind(t_arg *ind)
{
	if (ind->type == T_IND)
	{
		if (!ft_isint(ind->name + 1) && (ind->name && *ind->name != LABEL_CHAR))
			return (ft_raise_exception(18, ind->name));
	}
	return (1);
}

int     check_valid_args(t_inst *inst)
{
	int index;
	int max_arg;

	max_arg = args_number(inst->args);
	if (g_op_tab[inst->id].args_number == max_arg)
	{
		index = 0;
		while (index < max_arg)
		{
			// printf("%s | type = %d\n%d\n", inst->args[index]->name, str_type_arg(inst->args[index]->name),
			// !(str_type_arg(inst->args[index]->name) & g_op_tab[inst->id].args_type[index]));
			if (!(str_type_arg(inst->args[index]->name) & g_op_tab[inst->id].args_type[index]))
				return (ft_raise_exception(17, inst->args[index]->name));
			if (!is_valid_reg(inst->args[index]))
				return (0);
			if (!is_valid_dir(inst->args[index]))
				return (0);
			if (!is_valid_ind(inst->args[index]))
				return (0);
			index += 1;
		}
	}
	else
		return (ft_raise_exception(16, NULL));
	// inst->size = add_inst_size(inst); 
	return (1);
}
