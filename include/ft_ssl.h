/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:27:19 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/22 10:10:30 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"

# include "ft_ssl_md5.h"
# include "ft_ssl_sha256.h"

typedef int	(*t_func_main)(int argc, char **argv);
typedef struct
{
	char		*name;
	t_func_main	entry;
}				t_command;

enum
{
	FLAG_PIPE = 1 << 0,
	FLAG_QUIET = 1 << 1,
	FLAG_REVERSE = 1 << 2,
	FLAG_STRING = 1 << 3
};
typedef unsigned char	t_flags;

typedef struct
{
	unsigned char		*data;
	int					size;
}						t_digest;
typedef void			(*t_func_hash)(char *message, t_digest *digest);

/*
** error.c
*/

void	fl_error_command(char *command);

/*
** args.c
*/

int		fl_parse_args(char *name, int argc, char **argv, t_func_hash func_hash);

#endif
