/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarry <mcarry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 15:50:48 by mcarry            #+#    #+#             */
/*   Updated: 2021/07/21 21:44:23 by mcarry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shlvl(t_shell *g_mini)
{
	int		i;
	int		nbr;
	char	*tmp;
	char	*tmp2;

	i = -1;
	while (g_mini->str_env[++i])
	{
		if (!(ft_strncmp(g_mini->str_env[i], "SHLVL=", 6)))
		{
			tmp = ft_substr(g_mini->str_env[i], 6,
					ft_strlen(g_mini->str_env[i]) - 6);
			nbr = ft_atoi(tmp) + 1;
			free(tmp);
			tmp2 = ft_itoa(nbr);
			tmp = ft_strjoin("SHLVL=", tmp2);
			free(tmp2);
			free(g_mini->str_env[i]);
			g_mini->str_env[i] = ft_strdup(tmp);
			free(tmp);
			return ;
		}
	}
}

void	init_flags(t_shell *g_mini)
{
	g_mini->flag_rd = 0;
	g_mini->flag_rd2 = 0;
	g_mini->flag_rd3 = 0;
	g_mini->type_rd = 0;
	g_mini->type_rd_arg = 0;
	g_mini->pip = 0;
	g_mini->flag_q = 0;
	g_mini->flag_q1 = 0;
	g_mini->ft_errno = 0;
	g_mini->flag_new = 0;
	g_mini->flag_new2 = 0;
	g_mini->global_var = 0;
	g_mini->flag_pipe1 = 0;
	g_mini->flag_pipe2 = 0;
	g_mini->flag_dol_q = 0;
}

void	init_array(char **envp, t_shell *g_mini)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_mini->str_env = (char **)malloc(sizeof(char *) * (i + 1));
	g_mini->str_exp = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		g_mini->str_env[i] = ft_strdup(envp[i]);
		g_mini->str_exp[i] = ft_strdup(envp[i]);
	}
	g_mini->str_env[i] = NULL;
	g_mini->str_exp[i] = NULL;
	init_shlvl(g_mini);
	init_flags(g_mini);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
