/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_digest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <me@cacharle.xyz>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:03:39 by charles           #+#    #+#             */
/*   Updated: 2020/08/03 12:56:52 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*message_digest(t_message_digest_param *param, uint8_t *message_origin, uint64_t size)
{
	size_t		i;
	uint64_t	padding_size;
	uint8_t		*message;
	void		*local_state;
	char		*ret;

	local_state = ft_memdup(param->compression_state_init, param->compression_state_size);
	if (local_state == NULL)
		return (NULL);
	padding_size = (param->chunk_size - (size + sizeof(uint64_t)) % param->chunk_size) + sizeof(uint64_t);
	if ((message = malloc(size + padding_size)) == NULL)
	{
		free(local_state);
		return (NULL);
	}
	ft_memcpy(message, message_origin, size);
	ft_memset(message + size, 0x0, padding_size);
	message[size] |= 1 << 7;
	*((uint64_t*)(message + size + padding_size - sizeof(uint64_t))) =
		param->big_endian ? reverse_bytes64(size * 8) : (size * 8);
	size += padding_size;

	for (size_t j = 0; j < size; j++)
	{
		if (j % 8 == 0)
			printf("\n");
		printf("%02x ", message[j]);
	}
			printf("\n");

	i = 0;
	while (i < size)
	{
		local_state = param->compression_func(local_state, message + i);
		if (local_state == NULL)
		{
			free(message);
			free(local_state);
			return (NULL);
		}
		i += param->chunk_size;
	}
	free(message);
	if (param->big_endian)
	{
		for (i = 0; i < param->compression_state_size / param->compression_state_stride; i++)
			((uint32_t*)local_state)[i] =
				param->compression_state_stride == sizeof(uint32_t)
					? reverse_bytes32(((uint32_t*)local_state)[i])
					: reverse_bytes64(((uint64_t*)local_state)[i]);
	}
	ret = bytes_to_str(local_state, param->compression_state_size);
	free(local_state);
	return (ret);
}
