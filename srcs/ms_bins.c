/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_bins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:59:50 by wdebs             #+#    #+#             */
/*   Updated: 2017/02/28 18:07:52 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_env(char ***envp)
{
	int		i;

	i = -1;
	while ((*envp)[++i])
		ft_putendl((*envp)[i]);
}

void	run_echo(t_vars *vars, char ***envp)
{
	int		i;
	int		end;
	char	*tmp;

	i = 0;
	end = 0;
	while (vars->args[++i])
	{
		tmp = ft_strtrim(vars->args[i]);
		if (vars->args[i][0] == '$')
			echo_env(vars->args[i], envp);
		else
			ft_putstr(tmp);
		write(1, " ", 1);
		free(tmp);
		tmp = NULL;
	}
	write(1, "\n", 1);
}

void	run_cd(t_vars *vars, char ***envp)
{
	int		check;
	char	*buf;
	char	*tmp;

	check = 0;
	buf = NULL;
	tmp = getcwd(buf, 10024);
	while (vars->args[check] != NULL)
		check++;
	if (vars->args[1] && vars->args[1][0] == '-' && vars->args[1][1] == '\0')
		chdir((*envp)[vars->old_path] + 7);
	else if (check == 1)
	{
		if (chdir((*envp)[vars->home] + 5) < 0)
			ft_putendl("cd: no such file or directory");
	}
	else if (check > 2)
		ft_putendl("cd: Too many arguments");
	else
		arg_cd(vars, envp);
	env_chg("OLDPWD", tmp, envp);
	free(tmp);
	free(buf);
}

void	run_setenv(t_vars *vars, char ***envp)
{
	char *tmp;

	tmp = NULL;
	if (ft_strcmp(vars->args[1], "PATH") == 0)
		vars->path_check = 0;
	if (vars->args[1] && vars->args[2] && !(vars->args[3]))
	{
		tmp = ft_strtrim(vars->args[2]);
		env_chg(vars->args[1], tmp, envp);
		free(tmp);
	}
	else
		ft_putendl("setenv: incorrect arguments");
}

void	run_unsetenv(t_vars *vars, char ***envp)
{
	char	**copy;
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = -1;
	len = 0;
	j = 0;
	temp = ft_strtrim(vars->args[1]);
	if (ft_strcmp(temp, "PATH") == 0)
		vars->path_check = 1;
	while (*envp && (*envp)[len])
		len++;
	copy = (char **)ft_memalloc(sizeof(char *) * (len + 2));
	while ((*envp)[++i])
		if (ft_strncmp((*envp)[i], temp, ft_strlen(temp)))
			copy[j++] = (*envp)[i];
	*envp = copy;
}
