/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:29:33 by cacharle          #+#    #+#             */
/*   Updated: 2020/07/27 16:27:16 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/* static t_command	g_commands[] = { */
/* 	{"md5", main_md5}, */
/* 	{"sha256", main_sha256} */
/* }; */

/* int	dispatch_command(char *command, int argc, char **argv) */
/* { */
/* 	size_t	i; */
/*  */
/* 	i = 0; */
/* 	while (i < sizeof(g_commands) / sizeof(t_command)) */
/* 	{ */
/* 		if (ft_strcmp(g_commands[i].name, command) == 0) */
/* 			return (g_commands[i].entry(argc, argv)); */
/* 		i++; */
/* 	} */
/* 	error_command(command); */
/* 	return (1); */
/* } */

int main(int argc, char **argv)
{
	/* if (argc == 1) */
	/* { */
	/* 	ft_putstr("usage: "); */
	/* 	ft_putstr(argv[0]); */
	/* 	ft_putendl_fd(" command [command opts] [command args]", STDERR_FILENO); */
	/* 	return (1); */
	/* } */
	/* return (dispatch_command(argv[1], argc - 2, argv + 2)); */
	(void)argc;

	printf("%s\n", message_digest_md5((uint8_t*)argv[1], ft_strlen(argv[1])));
}
