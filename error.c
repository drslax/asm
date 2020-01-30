/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:43:44 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/30 08:17:01 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char	*g_error_strings[] =
{
	"Invalid extenstion :",
	"Invalid filename :",
	"Requires one or more files",
	"Program_name' command already defined",
	"Comment' command already defined",
	"Command not well formated",
	"Command length above ",
	"Undefined label line",
	"Undefined command :",
	"Program should start with commands",
	"Missing command :",
	"Missing argument",
	"Invalid name instruction",
	"Invalid chars in label",
	"Invalid ENDLINE",
	"Syntax Error",
	"Invalid number of arguments",
	"Invalid type of argument",
	"Argument not well formated",
	NULL
};

int		ft_raise_exception(int error_code, char *custom)
{
	char	*error_string;

	error_string = g_error_strings[error_code];
	ft_putstr_fd("\e[1m\e[91mERROR :\e[0m ", 2);
	ft_putstr_fd(error_string, 2);
	if (custom)
	{
		ft_putstr_fd(" [", 2);
		ft_putstr_fd(custom, 2);
		ft_putstr_fd("]", 2);
	}
	ft_putchar_fd('\n', 2);
	return (0);
}
