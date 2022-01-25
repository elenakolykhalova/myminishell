/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:36:59 by jinigo            #+#    #+#             */
/*   Updated: 2021/04/13 16:14:13 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*output;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	output = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!output)
		return (0);
	while (s1[i] != '\0')
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		output[i] = s2[j];
		i++;
		j++;
	}
	output[i] = '\0';
	return (output);
}
