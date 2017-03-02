/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 23:25:45 by wdebs             #+#    #+#             */
/*   Updated: 2017/02/28 17:49:15 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_chg(char *env_name, char *env_val, char ***envp)
{
	char	*line;
	char	*env;
	int		i;

	i = -1;
	line = ft_strjoin(env_name, "=");
	env = line;
	line = ft_strjoin(line, env_val);
	free(env);
	while (*envp && (*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], env_name, ft_strlen(env_name)))
		{
			env = (*envp)[i];
			(*envp)[i] = line;
			return ;
		}
	}
	add_line(line, envp);
}

void	add_line(char *line, char ***envp)
{
	int		len;
	char	**new;

	len = 0;
	while (*envp && (*envp)[len])
		len++;
	new = (char **)ft_memalloc(sizeof(char *) * (len + 2));
	len = -1;
	while ((*envp)[++len])
		new[len] = (*envp)[len];
	new[len] = line;
	new[len + 1] = 0;
	*envp = new;
}

void	echo_env(char *name, char ***envp)
{
	int		i;

	i = -1;
	while ((*envp)[++i])
	{
		if (ft_strncmp((*envp)[i], &(name[1]), (ft_strlen(name) - 1)) == 0)
		{
			ft_putstr((*envp)[i] + ft_strlen(name));
			break ;
		}
	}
}

void	arg_cd(t_vars *vars, char ***envp)
{
	char *tmp;

	tmp = ft_strdup(vars->args[1]);
	if (vars->args[1][0] == '~')
	{
		tmp = ft_strjoin((*envp)[vars->home], tmp + 1);
		chdir(tmp + 5);
	}
	else
		chdir(tmp);
	free(tmp);
	tmp = NULL;
}
