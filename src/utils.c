/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <me@cacharle.xyz>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:00:16 by charles           #+#    #+#             */
/*   Updated: 2020/08/03 12:57:25 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#define HEX_CHARS "0123456789abcdef"

uint32_t	rotate_left(uint32_t x, int s)
{
	return (x << s) | (x >> (32 - s));
}

uint32_t	rotate_right(uint32_t x, int s)
{
	return (x >> s) | (x << (32 - s));
}

char		*bytes_to_str(uint8_t *bytes, size_t size)
{
	char	*ret;
	size_t	i;

	if ((ret = ft_strnew(size * 2)) == NULL)
		return (NULL);

	i = 0;
	while (i < size)
	{
		ret[i * 2 + 0] = HEX_CHARS[(bytes[i] & 0xf0) >> 4];
		ret[i * 2 + 1] = HEX_CHARS[(bytes[i] & 0x0f) >> 0];
		i++;
	}
	return (ret);
}

uint32_t	reverse_bytes32(uint32_t x)
{
	return (
		(x & 0x000000ffu) << 24 |
		(x & 0x0000ff00u) << 8 |
		(x & 0x00ff0000u) >> 8 |
		(x & 0xff000000u) >> 24
	);
}

/*
** from: <byteswap.h>
*/

uint64_t	reverse_bytes64(uint64_t x)
{
	return (
		(x & 0x00000000000000ffull) << 56 |
		(x & 0x000000000000ff00ull) << 40 |
		(x & 0x0000000000ff0000ull) << 24 |
		(x & 0x00000000ff000000ull) << 8 |
		(x & 0x000000ff00000000ull) >> 8 |
		(x & 0x0000ff0000000000ull) >> 24 |
		(x & 0x00ff000000000000ull) >> 40 |
		(x & 0xff00000000000000ull) >> 56
	);
}
