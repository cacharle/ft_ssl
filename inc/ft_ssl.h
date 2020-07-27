/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:27:19 by cacharle          #+#    #+#             */
/*   Updated: 2020/07/27 21:38:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"

# include "ft_ssl_md5.h"

// # include "ft_ssl_md5.h"
// # include "ft_ssl_sha256.h"

// typedef int		(*t_func_main)(int argc, char **argv);
//
// typedef struct
// {
// 	char		*name;
// 	t_func_hash	func;
// }				t_command;
//
// typedef enum
// {
// 	FLAG_PIPE    = 1 << 0,
// 	FLAG_QUIET   = 1 << 1,
// 	FLAG_REVERSE = 1 << 2,
// }				t_flags;

typedef char	*(*t_func_hash)(char *message);

/*
** error.c
*/

// void	error_command(char *command);

/*
** args.c
*/

// int		parse_args(char *name, int argc, char **argv, t_func_hash func_hash);

#endif
