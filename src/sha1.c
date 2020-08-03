/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <me@cacharle.xyz>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 14:20:39 by charles           #+#    #+#             */
/*   Updated: 2020/08/03 12:10:55 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	*sha1_compression_func(void *v_state, uint8_t *chunk)
{
	uint32_t	buf[80] = {0};
	size_t		i;
	uint32_t	a, b, c, d, e, f, k, tmp;
	uint32_t	*state;

	for (i = 0; i < 16; i++)
		buf[i] = reverse_bytes32(((uint32_t*)chunk)[i]);
	i = 16;
	while (i < 80)
	{
		buf[i] = rotate_left(buf[i - 3] ^ buf[i - 8] ^ buf[i - 14] ^ buf[i - 16], 1);
		i++;
	}
	state = v_state;
	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];
	e = state[4];

	i = 0;
	while (i < 80)
	{
		if (i < 20)
		{
			f = (b & c) | ((~b) & d);
			k = 0x5a827999;
		}
		else if (i < 40)
		{
			f = b ^ c ^ d;
			k = 0x6ed9eba1;
		}
		else if (i < 60)
		{
			f = (b & c) | (b & d) | (c & d);
			k = 0x8f1bbcdc;
		}
		else
		{
			f = b ^ c ^ d;
			k = 0xca62c1d6;
		}
		tmp = rotate_left(a, 5) + f + e + k + buf[i];
		e = d;
		d = c;
		c = rotate_left(b, 30);
		b = a;
		a = tmp;
		i++;
	}
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	state[4] += e;
	return (state);
}
