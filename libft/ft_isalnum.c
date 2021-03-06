/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinigo <jinigo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:24:11 by jinigo            #+#    #+#             */
/*   Updated: 2020/11/23 15:24:39 by jinigo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int src)
{
	if ((src >= 'a' && src <= 'z') || (src >= 'A' && src <= 'Z')
		|| (src >= '0' && src <= '9'))
		return (1);
	return (0);
}
