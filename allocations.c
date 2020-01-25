/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sou3ada <sou3ada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:13:08 by sou3ada           #+#    #+#             */
/*   Updated: 2020/01/25 17:24:58 by sou3ada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void    allocate_asm(t_asm **data)
{
    if (!(*data = (t_asm *)malloc(sizeof(t_asm))))
		exit(-1);
}

void	initialize_asm(t_asm **data, char *arg)
{
	(*data)->file_name = arg;
	(*data)->cmd_comment = NULL;
	(*data)->cmd_name = NULL;
	(*data)->size_champ = 0;
	(*data)->remain_labels = 0;
	(*data)->instructions = NULL;
    (*data)->labels = NULL;
	// allocate_label(&(*data)->labels);
	// allocate_instruction(&(*data)->instructions);
}

void	allocate_argument(t_arg *argument[3])
{
	argument[0] = (t_arg*)malloc(sizeof(t_arg));
	argument[1] = (t_arg*)malloc(sizeof(t_arg));
	argument[2] = (t_arg*)malloc(sizeof(t_arg));
	argument[0]->name = NULL;
	argument[0]->type = 16;
	argument[1]->name = NULL;
	argument[1]->type = 16;
	argument[2]->name = NULL;
	argument[2]->type = 16;
}

void    initialize_instruction(t_inst **instructions)
{
    (*instructions)->label = NULL;
	(*instructions)->id = 16;
	(*instructions)->name = NULL;
	(*instructions)->size = 0;
	(*instructions)->size_set = 0;
	allocate_argument((*instructions)->args);
    (*instructions)->tail = NULL;
	(*instructions)->next = NULL;
}

void	allocate_instruction(t_inst **instructions)
{
	if (!(*instructions = (t_inst*)malloc(sizeof(t_inst))))
        exit (-1);
    // *instructions = NULL;
}
