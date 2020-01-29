/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 04:27:24 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/29 05:00:06 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int	ft_isint(char *str)
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

int	type_size(int type, int id)
{
	if (type == T_REG)
		return (1);
	if (type == T_IND)
		return (IND_SIZE);
	if (type == T_DIR)
		return (DIR_SIZE - (g_op_tab[id].label_size ? 2 : 0));
	return (0);
}

/*
**  LABELS are automatically defined as T_IND
*/

int	str_type_arg(char *arg)
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