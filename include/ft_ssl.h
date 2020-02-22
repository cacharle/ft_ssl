/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:27:19 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/22 07:20:34 by cacharle         ###   ########.fr       */
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

/*
** error.c
*/

void	fl_error_command(char *command);

#endif
