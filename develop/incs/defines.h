/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykuo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:25:23 by ykuo              #+#    #+#             */
/*   Updated: 2023/02/18 00:25:26 by ykuo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define READ	0
# define WRITE	1
# define CHILD	0

enum	e_token_type
{
	EMPTY = 0,
	CMD = 1,
	ARG = 2,
	ENV_DEF = 3,
	ENV_VAL = 4,
	OPTN = 5,
	INPUT = 6, // <
	OUTPUT = 7, // >
	DELIM = 8, // <<
	APPEN = 9, // >>
	PIPE = 10
};

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 4,
	DUPERR = 5,
	FORKERR = 6,
	PIPERR = 7,
	MEM = 8,
	IS_DIR = 9,
	NOT_DIR = 11,
	OP_NS = 12,
	SYNERR = 13,
	TM_ARGS = 14,
};

#endif
