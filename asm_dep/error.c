/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:43:44 by slyazid           #+#    #+#             */
/*   Updated: 2020/01/16 02:50:44 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char    *g_error_strings[] =
{
	"Invalid extenstion :", //0
	"Invalid filename :", //1
	"Requires one or more files",//2
	"Program_name' command already defined", //3
	"Comment' command already defined",//4
	"Command not well formated",//5
	"Program_name' length above PROG_NAME_LENGTH",//6
	"Comment' command length above COMMENT_LENGTH",//7
	"Undefined command :",//8
	"Program should start with commands",//9
	"Missing command :",//10
	"Missing argument",//11
	"Invalid name instruction",//12
	"Invalid chars in label",//13
	"Invalid ENDLINE character",//14
	"",//15
	"",//16
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
