/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 07:14:45 by cacharle          #+#    #+#             */
/*   Updated: 2020/07/27 16:36:41 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>

# include "libft.h"

char	*message_digest_md5(uint8_t *msg, size_t size);

#endif
