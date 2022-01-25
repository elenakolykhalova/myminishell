/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:34:38 by jinigo            #+#    #+#             */
/*   Updated: 2020/11/21 13:17:34 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t len)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (len-- > 0)
	{
		*d = *s;
		if (*s == (unsigned char)c)
		{
			return ((void *)d + 1);
		}
		d++;
		s++;
	}
	return (NULL);
}
