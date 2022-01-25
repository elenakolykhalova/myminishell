/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:00:38 by jinigo            #+#    #+#             */
/*   Updated: 2020/11/26 15:00:06 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned char	*src;
	unsigned char	sym;
	size_t			i;

	src = (unsigned char *)s;
	sym = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		if (src[i] == sym)
		{
			return (src + i);
		}
		i++;
	}
	return (NULL);
}
