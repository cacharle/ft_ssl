/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:29:33 by cacharle          #+#    #+#             */
/*   Updated: 2020/08/03 13:46:52 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const uint32_t	g_md5_state[4] = {
	0x67452301,
	0xefcdab89,
	0x98badcfe,
	0x10325476,
};

static const uint32_t	g_sha1_state[5] = {
	0x67452301,
	0xefcdab89,
	0x98badcfe,
	0x10325476,
	0xc3d2e1f0,
};

static const uint32_t	g_sha256_state[8] = {
	0x6a09e667,
	0xbb67ae85,
	0x3c6ef372,
	0xa54ff53a,
	0x510e527f,
	0x9b05688c,
	0x1f83d9ab,
	0x5be0cd19,
};

t_compression_entry	g_compression_table[] = {
	{"md5", {md5_compression_func, g_md5_state, sizeof(g_md5_state), sizeof(uint32_t), 64, false}},
	{"sha1", {sha1_compression_func, g_sha1_state, sizeof(g_sha1_state), sizeof(uint32_t), 64, true}},
	{"sha256", {sha256_compression_func, g_sha256_state, sizeof(g_sha256_state), sizeof(uint32_t), 64, true}},
};

t_message_digest_param	*dispatch_command(char *command)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_compression_table) / sizeof(t_compression_entry))
	{
		if (ft_strcasecmp(g_compression_table[i].name, command) == 0)
			return (&g_compression_table[i].param);
		i++;
	}
	error_command(command);
	return (NULL);
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putendl_fd(" command [command opts] [command args]", STDERR_FILENO);
		return (1);
	}
	t_message_digest_param *md_param = dispatch_command(argv[1]);
	if (md_param == NULL)
		return 1;
	return (parse_args(argc - 2, argv + 2, ft_strtoupper(argv[1]), md_param));
}
