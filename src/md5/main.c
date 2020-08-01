/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 07:20:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/08/01 19:27:06 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** | bits | bytes |
** |------|-------|
** | 8    | 1     |
** | 16   | 2     |
** | 32   | 4     |
** | 64   | 8     |
** | 128  | 16    |
** | 256  | 32    |
** | 512  | 64    |
**
** | 448  | 56    |
*/

static const int	g_shifts_table[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,   //  0..15
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,   // 16..31
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,   // 32..47
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,   // 48..63
};

static const uint32_t	g_sin_table[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,  //  0.. 3
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,  //  4.. 7
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,  //  8..11
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,  // 12..15
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,  // 16..19
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,  // 20..23
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,  // 24..27
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,  // 28..31
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,  // 32..35
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,  // 36..39
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,  // 40..43
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,  // 44..47
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,  // 48..51
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,  // 52..55
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,  // 56..59
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,  // 60..63
};


void *md5_compression_func(void *v_state, uint8_t *chunk)
{
	int g;
	int	i;

	uint32_t	a, b, c, d, f;
	uint32_t	*state;

	state = v_state;
	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];

	i = -1;
	while (++i < 64)
	{

		if (i < 16)
		{
			f = (b & c) | ((~b) & d);
			g = i;
		}
		else if (i < 32)
		{
			f = (b & d) | (c & (~d));
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			f = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}
		else
		{
			f = c ^ (b | ~d);
			g = (7 * i) % 16;
		}

		f += a + g_sin_table[i] + ((uint32_t*)chunk)[g];
		a = d;
		d = c;
		c = b;
		b += rotate_left(f, g_shifts_table[i]);
	}
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	return (state);
}
