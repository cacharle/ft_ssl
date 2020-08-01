/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <me@cacharle.xyz>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:00:16 by charles           #+#    #+#             */
/*   Updated: 2020/08/01 19:24:41 by charles          ###   ########.fr       */
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
