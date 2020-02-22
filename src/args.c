/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 09:43:42 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/22 10:44:04 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	st_print_digest_id(t_flags flags, char *id)
{
	if (flags & FLAG_STRING)
		ft_putchar('"');
	ft_putstr(id);
	if (flags & FLAG_STRING)
		ft_putchar('"');
}

static void	st_print_digest(t_digest *digest, t_flags flags, char *name, char *id)
{
	int	i;

	if (!(flags & FLAG_REVERSE) && !(flags & FLAG_QUIET))
	{
		ft_putstr(name);
		ft_putchar('(');
		st_print_digest_id(flags, id);
		ft_putstr(") = ");
	}
	i = -1;
	while (++i < digest->size)
		ft_putnbr_base(digest->data[i], "0123456789abcdef");
	if (flags & FLAG_QUIET)
		return ;
	ft_putchar(' ');
	st_print_digest_id(flags, id);
}

int		fl_parse_args(char *name, int argc, char **argv, t_func_hash func_hash)
{
	t_flags		flags;
	t_digest	digest;
	char		*file;

	flags = 0x0;
	while (**argv == '-')
	{
		(*argv)++;
		if (**argv == 's')
		{
			if ((*argv)[1] == '\0')
			{
				func_hash(*(++argv), &digest);
				argc--;
			}
			else
				func_hash(ft_strdup(*argv + 1), &digest);
			st_print_digest(&digest, flags, name, "");
		}
		else if (**argv == 'p')
			flags |= FLAG_PIPE;
		else if (**argv == 'q')
			flags |= FLAG_QUIET;
		else if (**argv == 'r')
			flags |= FLAG_REVERSE;
		else
			return (1);
		if (ft_strchr("pqrs", (*argv)[1]) != NULL)
		{
			**argv = '-';
			continue;
		}
		argv++;
		argc--;
	}
	while (argc-- > 0)
	{
		if ((file = ft_read_file(*argv)) == NULL)
			return (1);
		func_hash(file, &digest);
		free(file);
		st_print_digest(&digest, flags, name, *argv);
		argv++;
	}
	return (0);
}
