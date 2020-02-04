/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@1337.MA>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 18:19:02 by abiri             #+#    #+#             */
/*   Updated: 2020/02/03 11:03:25 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max_long(char *str)
{
	if (ft_strlen(str) > 19 ||
		(ft_strlen(str) == 19 && ft_strcmp(str, "9223372036854775807") > 0))
		return ((int)9223372036854775807);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	number;
	int			i;

	i = 0;
	number = ft_max_long((char*)str);
	if (number)
		return (number);
	if ((str[0] >= 9 && str[0] <= 13) || str[0] == ' ')
		return (ft_atoi(++str));
	if (str[0] == '-' && str[1] >= '0' && str[1] <= '9')
	{
		number = ft_atoi(++str);
		return (number * -1);
	}
	if (str[0] == '+' && str[1] >= '0' && str[1] <= '9')
		number = ft_atoi(++str);
	else if (str[0] != '-')
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			number = (number * 10) + (str[i] - '0');
			++i;
		}
	}
	return ((int)number);
}
