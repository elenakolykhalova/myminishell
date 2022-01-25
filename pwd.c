/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:51:00 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/19 17:40:19 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *g_mini)
{
	char	*str;
	char	*buf;

	buf = NULL;
	str = getcwd(buf, 4096);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	g_mini->ft_errno = 0;
	free(str);
	return (0);
}
