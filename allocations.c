/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slyazid <slyazid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 16:13:08 by sou3ada           #+#    #+#             */
/*   Updated: 2020/01/26 01:02:52 by slyazid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void    allocate_asm(t_asm **data)
{
    if (!(*data = (t_asm *)malloc(sizeof(t_asm))))
		exit(-1);
}

void    allocate_label(t_label **label)
{
    if (!(*label = (t_label *)malloc(sizeof(t_label))))
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
	(*instructions)->line = -1;
    (*instructions)->label = NULL;
	(*instructions)->id = 16;
	(*instructions)->name = NULL;
	(*instructions)->size = 0;
	(*instructions)->label_in_arg = 0;
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
