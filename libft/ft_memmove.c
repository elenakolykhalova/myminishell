/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:33:12 by jinigo            #+#    #+#             */
/*   Updated: 2020/11/23 17:00:06 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	const char	*lasts;
	char		*lastd;

	d = dst;
	s = src;
	if (!dst && !src)
		return (NULL);
	if (d < s)
	{
		while (len-- > 0)
			*d++ = *s++;
	}
	else
	{
		lasts = s + (len - 1);
		lastd = d + (len - 1);
		while (len-- > 0)
			*lastd-- = *lasts--;
	}
	return (dst);
}
