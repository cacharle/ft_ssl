/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 07:20:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/08/01 13:50:41 by charles          ###   ########.fr       */
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

char	*message_digest_md5(uint8_t *msg, uint64_t size)
{
	// padding on 512 bit (64 bytes)
	// format:
	// 1 bit
	// fill with zero start -> (end - 64 bit)
	// 64 bit repr of the original len modulo 2^64 (ULONG_MAX)


	// at least 1 byte for 1 bit + 8 bytes for 64bit size
	uint64_t	pad_size = (64 - (size + 8) % 64) + 8;

	/* printf("%lu\n", size % 64); */
	/* printf("%lu\n", 64 - size % 64); */
	printf("%lu + %lu = %lu byte\n", size, pad_size, size + pad_size);

	uint8_t	*tmp;
	tmp = msg;
	msg = malloc(size + pad_size); // add ft_memdup

	ft_memcpy(msg, tmp, size);
	ft_memset(msg + size, 0x0, pad_size);                           // fill end with 0

	msg[size] |= 1 << 7;                                            // add 1 bit at padding start

	*((uint64_t*)(msg + size + pad_size - sizeof(uint64_t))) = (uint64_t)size * 8; // add
	size += pad_size;

	for (uint64_t i = 0; i < size; i++)
	{
		if (i % 8 == 0)
			printf("\n");
		printf("%02x ", msg[i]);
	}
	printf("\n\n");
	/* printf("\n%lu: %s\n", size, msg); */
	/* printf("|%lu|\n", *((uint64_t*)(msg + size - 8))); */

	// state initialized to predefined constants

	// block of 512 bit
	// 128 bit state (a, b, c, d)
	// 4 rounds on each block (128 * 4 = 512)


	uint32_t	f;
	int	g;
	int	i;


	size_t chunk_i;

	uint32_t	a, b, c, d;

	uint32_t a0 = A_INIT;
	uint32_t b0 = B_INIT;
	uint32_t c0 = C_INIT;
	uint32_t d0 = D_INIT;

	chunk_i = 0;
	while (chunk_i < size)
	{
		a = a0;
		b = b0;
		c = c0;
		d = d0;

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

			f += a + g_K[i] + ((uint32_t*)(msg + chunk_i))[g];
			a = d;
			d = c;
			c = b;
			b += leftrotate(f, g_shifts[i]);
		}
		a0 += a;
		b0 += b;
		c0 += c;
		d0 += d;

		chunk_i += 64;
	}

	uint8_t buf[16];
	buf[0] = (a0 & 0xff000000) >> 24;
	buf[1] = (a0 & 0x00ff0000) >> 16;
	buf[2] = (a0 & 0x0000ff00) >> 8;
	buf[3] = a0 & 0x000000ff;

	buf[4] = (b0 & 0xff000000) >> 24;
	buf[5] = (b0 & 0x00ff0000) >> 16;
	buf[6] = (b0 & 0x0000ff00) >> 8;
	buf[7] = b0 & 0x000000ff;

	buf[8] = (c0 & 0xff000000) >> 24;
	buf[9] = (c0 & 0x00ff0000) >> 16;
	buf[10] = (c0 & 0x0000ff00) >> 8;
	buf[11] = c0 & 0x000000ff;

	buf[12] = (d0 & 0xff000000) >> 24;
	buf[13] = (d0 & 0x00ff0000) >> 16;
	buf[14] = (d0 & 0x0000ff00) >> 8;
	buf[15] = d0 & 0x000000ff;


	char *ret = malloc(33 * sizeof(char));
	ret[32] = '\0';

	sprintf(ret, "%08x%08x%08x%08x", ((uint32_t*)buf)[0], ((uint32_t*)buf)[1],
			((uint32_t*)buf)[2], ((uint32_t*)buf)[3]);

	return (ret);
}
