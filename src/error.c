/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 07:02:59 by cacharle          #+#    #+#             */
/*   Updated: 2020/08/02 09:23:37 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// use in error message
/* extern t_compression_entry	g_compression_table[]; */

void	error_command(char *command)
{
	// argv[0]?
	ft_putstr_fd("ft_ssl: Error: '", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd("' is an invalid command.", STDERR_FILENO);
	ft_putstr_fd("\nStandard commands:\n"
		"\nMessage Digest commands:\n"
		"md5\n"
		"sha256\n"
		"\nCipher commands:\n",
		STDERR_FILENO
	);
}
