/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_digest.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <me@cacharle.xyz>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:03:39 by charles           #+#    #+#             */
/*   Updated: 2020/08/01 19:25:07 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*message_digest(t_message_digest_param *param)
{
	size_t		i;
	uint64_t	padding_size;
	uint8_t		*message;

	padding_size = (64 - (param->size + 8) % 64) + 8;

	message = malloc(param->size + padding_size);
	if (message == NULL)
		return (NULL);
	ft_memcpy(message, param->message, param->size);
	ft_memset(message + param->size, 0x0, padding_size);

	message[param->size] |= 1 << 7;
	*((uint64_t*)(message + param->size + padding_size - sizeof(uint64_t))) =
		(uint64_t)param->size * 8;
	param->size += padding_size;

	i = 0;
	while (i < param->size)
	{
		param->compression_state = param->compression_func(param->compression_state, message + i);
		if (param->compression_state == NULL)
		{
			free(message);
			return (NULL);
		}
		i += param->chunk_size;
	}

	return (bytes_to_str(param->compression_state, param->compression_state_size));
}
