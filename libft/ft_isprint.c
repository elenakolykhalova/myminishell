/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 14:00:53 by jinigo            #+#    #+#             */
/*   Updated: 2020/11/23 15:31:14 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int src)
{
	if (src >= 32 && src <= 126)
		return (1);
	return (0);
}