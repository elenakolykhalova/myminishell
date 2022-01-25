/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:28:19 by jinigo            #+#    #+#             */
/*   Updated: 2020/11/23 15:37:39 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *src, int c, size_t len)
{
	unsigned char	*dst;
	int				j;

	dst = src;
	j = 0;
	while (len-- > 0)
	{
		dst[j] = c;
		j++;
	}
	return (dst);
}
