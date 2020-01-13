/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:43:44 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/13 22:41:54 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char    *g_error_strings[] =
{
	"Invalid extenstion :",
	"Invalid filename :",
	"Requires one or more files",
	"Program_name' command already defined",
	"Comment' command already defined",
	"Missing double quotes in command",
	"Program_name' length above PROG_NAME_LENGTH",
	"Comment' command length above COMMENT_LENGTH",
	"Undefined command :",
	"Program should start with commands",
	"Missing command :",
	"Missing argument",
	"Invalid name instruction",
	"Invalid chars in label",
	"Invalid ENDLINE character",
	NULL
};

int ft_raise_exception(int error_code, char *custom)
{
	char    *error_string;

	error_string = g_error_strings[error_code];
	ft_putstr_fd("\e[1m\e[91mERROR :\e[0m ", 2);
	ft_putstr_fd(error_string, 2);
	if (custom)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(custom, 2);
	}
	ft_putchar_fd('\n', 2);
	return (0);
}
