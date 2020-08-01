/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:27:19 by cacharle          #+#    #+#             */
/*   Updated: 2020/08/01 19:24:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>

# include "libft.h"

typedef void *(*t_compression_func)(void *state, uint8_t *chunk);

typedef struct
{
	t_compression_func	compression_func;
	void				*compression_state;
	size_t				compression_state_size;
	size_t				chunk_size;
	uint8_t				*message;
	uint64_t			size;
}						t_message_digest_param;

void *md5_compression_func(void *v_state, uint8_t *chunk);
char	*message_digest(t_message_digest_param *param);

#define MD5_A_INIT 0x67452301
#define MD5_B_INIT 0xefcdab89
#define MD5_C_INIT 0x98badcfe
#define MD5_D_INIT 0x10325476

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


/*
** utils.c
*/

uint32_t	rotate_left(uint32_t x, int s);
uint32_t	rotate_right(uint32_t x, int s);
char		*bytes_to_str(uint8_t *bytes, size_t size);

/*
** md5
*/

char	*message_digest_md5(uint8_t *msg, size_t size);

#endif
