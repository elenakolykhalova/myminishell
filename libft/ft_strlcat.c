/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:11:47 by jinigo            #+#    #+#             */
/*   Updated: 2021/04/13 16:14:38 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;
	int				a;
	unsigned int	k;
	int				b;

	i = ft_strlen(dst);
	b = i;
	j = ft_strlen(src);
	if (dstsize <= i)
		return (dstsize + j);
	a = dstsize - i - 1;
	k = 0;
	while (src[k] && a--)
	{
		dst[i] = src[k];
		k++;
		i++;
	}
	dst[i] = '\0';
	if (dstsize == 0 || i + j > dstsize)
		return (b + j);
	return (i);
}
