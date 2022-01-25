/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:12:00 by jinigo            #+#    #+#             */
/*   Updated: 2020/11/21 14:13:02 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*last_occ;

	last_occ = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			last_occ = (char *)&str[i];
		i++;
	}
	if (str[i] == c)
		return ((char *)&str[i]);
	return (last_occ);
}
