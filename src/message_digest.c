/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_digest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <me@cacharle.xyz>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:03:39 by charles           #+#    #+#             */
/*   Updated: 2020/08/02 13:56:26 by charles          ###   ########.fr       */
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
	*((uint64_t*)(message + size + padding_size - sizeof(uint64_t))) = size * 8;
	size += padding_size;
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
	ret = bytes_to_str(local_state, param->compression_state_size);
	free(local_state);
	return (ret);
}
