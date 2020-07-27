/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 07:20:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/07/27 17:04:37 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

const int	g_shifts[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,   //  0..15
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,   // 16..31
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,   // 32..47
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,   // 48..63
};

const uint32_t	g_K[64] = {
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

#define A_INIT 0x67452301
#define B_INIT 0xefcdab89
#define C_INIT 0x98badcfe
#define D_INIT 0x10325476

uint32_t	leftrotate(uint32_t x, int s)
{
	return (x << s) | (x >> (32 - s));
}

char	*message_digest_md5(uint8_t *msg, size_t size)
{
	// padding on 512 bit (64 bytes)
	// format:
	// 1 bit
	// fill with zero start -> (end - 64 bit)
	// 64 bit repr of the original len modulo 2^64 (ULONG_MAX)


	uint8_t	*tmp;

	tmp = msg;


	size_t	pad_size = 32 - size % 32;

	/* printf("%lu\n", size % 32); */
	/* printf("%lu\n", 32 - size % 32); */
	/* printf("%lu\n", pad_size); */

	msg = malloc(size + pad_size);

	ft_memcpy(msg, tmp, size);
	ft_memset(msg + size, 0x0, pad_size);

	msg[size] |= 1 << 7;


	/* printf("%lu\n", size + pad_size - sizeof(uint64_t)); */
	*((uint64_t*)(msg + size + pad_size - sizeof(uint64_t))) = (uint64_t)size;
	size += pad_size;
	/* printf("%lu: %s\n", size, msg); */
	/* printf("|%02x%02x%02x%02x|\n", msg[24], msg[25], msg[26], msg[27]); */

	uint32_t	a, b, c, d;

	// state initialized to predefined constants

	// block of 512 bit
	// 128 bit state (a, b, c, d)
	// 4 rounds on each block (128 * 4 = 512)

	uint32_t	f;
	int	g;
	int	i;


	size_t chunk_i;

	chunk_i = 0;
	while (chunk_i < size)
	{

		i = -1;
		while (++i < 64)
		{
			if (i < 16)
			{
				f = (b & c) | ~(b & d);
				g = i;
			}
			else if (i < 32)
			{
				f = (b & c) | (c & ~d);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				f = b ^ c ^ d;
				g = (3 * i + 1) % 16;
			}
			else
			{
				f = c ^ (b | ~d);
				g = (7 * i + 1) % 16;
			}

			f += a + g_K[i] + ((uint32_t*)(msg + chunk_i))[g];
			a = d;
			d = c;
			c = b;
			b += leftrotate(f, g_shifts[i]);
		}

		chunk_i += 32;
	}

	char *ret = malloc(33 * sizeof(char));
	ret[32] = '\0';

	sprintf(ret, "%08x%08x%08x%08x", a, b, c, d);

	return (ret);
}
