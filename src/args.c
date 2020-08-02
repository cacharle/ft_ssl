/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 09:43:42 by cacharle          #+#    #+#             */
/*   Updated: 2020/08/02 14:17:15 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	st_print_digest_input(t_flags flags, char *input)
{
	if (flags & FLAG_STRING)
		ft_putchar('"');
	ft_putstr(input);
	if (flags & FLAG_STRING)
		ft_putchar('"');
}

static void	st_print_digest(t_flags flags, char *command, char *input, char *digest_str)
{
	if (!(flags & FLAG_REVERSE) && !(flags & FLAG_QUIET))
	{
		ft_putstr(command); //toupper
		ft_putstr(" (");
		st_print_digest_input(flags, input);
		ft_putstr(") = ");
	}
	ft_putstr(digest_str);
	if (flags & FLAG_QUIET)
	{
		ft_putchar('\n');
		return ;
	}
	if (flags & FLAG_REVERSE)
	{
		ft_putchar(' ');
		st_print_digest_input(flags, input);
	}
	ft_putchar('\n');
}

int		parse_args(int argc, char **argv, char *command, t_message_digest_param *md_param)
{
	t_flags		flags;
	t_ftmem		file;

	char *digest_str;
	int i;

	flags = 0;
	i = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			break ;
		if (ft_strcmp(argv[i], "-s") == 0)
		{
			i++;
			if (i >= argc) // no string
				return (1);
			digest_str = message_digest(md_param, (uint8_t*)argv[i], ft_strlen(argv[i]));
			if (digest_str == NULL)
				return (1);
			st_print_digest(flags | FLAG_STRING, command, argv[i], digest_str);
			free(digest_str);
		}
		else if (ft_strcmp(argv[i], "-p") == 0)
		{
			if (ft_getfile_fd(STDIN_FILENO, &file) < 0)
				return (1);
			digest_str = message_digest(md_param, file.data, file.size);
			if (digest_str == NULL)
				return (1);
			write(STDOUT_FILENO, file.data, file.size);
			ft_putendl(digest_str);
		}
		else if (ft_strcmp(argv[i], "-q") == 0)
			flags |= FLAG_QUIET;
		else if (ft_strcmp(argv[i], "-r") == 0)
			flags |= FLAG_REVERSE;
		else
		{
			ft_putstr_fd("ft_ssl: invalid option -- '", STDERR_FILENO);
			ft_putstr_fd(argv[i] + 1, STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	while (i < argc)
	{
		if (ft_getfile(argv[i], &file) < 0)
		{
			ft_putstr_fd("ft_ssl: ", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			i++;
			continue ;
		}
		digest_str = message_digest(md_param, file.data, file.size);
		if (digest_str == NULL)
			return 1;
		st_print_digest(flags, command, argv[i], digest_str);
		free(digest_str);
		free(file.data);
		i++;
	}
	return (0);
}
