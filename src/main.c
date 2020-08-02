/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:29:33 by cacharle          #+#    #+#             */
/*   Updated: 2020/08/02 11:26:50 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t	g_md5_state[4] = {MD5_A_INIT, MD5_B_INIT, MD5_C_INIT, MD5_D_INIT};

/* static uint32_t	g_sha1_state[5] = {0}; */

t_compression_entry	g_compression_table[] = {
	{"md5", {md5_compression_func, g_md5_state, sizeof(g_md5_state), 64}},
	/* {"sha1", {sha1_compression_func, g_sha1_state, sizeof(g_sha1_state), 64}} */
};

t_message_digest_param	*dispatch_command(char *command)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_compression_table) / sizeof(t_compression_entry))
	{
		if (ft_strcmp(g_compression_table[i].name, command) == 0)
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
	return (parse_args(argc - 2, argv + 2, argv[1], md_param));

	/* printf("%s\n", message_digest(md_param, (uint8_t*)argv[2], ft_strlen(argv[2]))); */
	/* return 0; */
}
