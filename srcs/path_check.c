/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 22:43:35 by wdebs             #+#    #+#             */
/*   Updated: 2017/02/28 18:32:36 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_bins(t_vars *vars, char ***envp)
{
	if (ft_strcmp(vars->args[0], "echo") == 0 && (vars->check = 1))
		run_echo(vars, envp);
	else if (ft_strcmp(vars->args[0], "setenv") == 0 && (vars->check = 1))
		run_setenv(vars, envp);
	else if (ft_strcmp(vars->args[0], "cd") == 0 && (vars->check = 1))
		run_cd(vars, envp);
	else if (ft_strcmp(vars->args[0], "unsetenv") == 0 && (vars->check = 1))
		run_unsetenv(vars, envp);
	else if (ft_strcmp(vars->args[0], "env") == 0 && (vars->check = 1))
		run_env(envp);
}

int		check_path(t_vars *vars)
{
	char		*tmp;
	int			i;
	struct stat	test;

	i = 0;
	tmp = NULL;
	while (vars->path[i])
	{
		tmp = ft_strjoin(vars->path[i], vars->args[0]);
		if (stat(tmp, &test) > -1)
		{
			free(vars->args[0]);
			vars->args[0] = ft_strdup(tmp);
			vars->check = 2;
			free(tmp);
			tmp = NULL;
			return (1);
		}
		free(tmp);
		tmp = NULL;
		i++;
	}
	errors(vars, 1);
	return (0);
}

void	check_arg(t_vars *vars, char ***envp)
{
	struct stat	test;
	char		*tmp;

	tmp = NULL;
	if (ft_strncmp(vars->args[0], "~/", 2) == 0)
	{
		tmp = vars->args[0];
		free(vars->args[0]);
		vars->args[0] = NULL;
		vars->args[0] = ft_strjoin((*envp)[vars->home] + 5,
				tmp + 1);
	}
	if (stat(vars->args[0], &test) > -1)
		vars->check = 2;
	else
		errors(vars, 0);
}

void	errors(t_vars *vars, int error)
{
	if (error == 0)
	{
		ft_putstr("minishell: no such file or directory: ");
		ft_putstr(vars->args[0]);
		write(1, "\n", 1);
	}
	else if (error == 1)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(vars->args[0]);
		write(1, "\n", 1);
	}
}

void	run(t_vars *vars, char ***envp)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!access(vars->args[0], R_OK || X_OK))
	{
		pid = fork();
		if (pid)
			waitpid(-1, &status, 0);
		else
			execve(vars->args[0], vars->args, *(envp));
	}
	else
	{
		ft_putstr("minishell: Permission denied: ");
		ft_putendl(vars->args[0]);
	}
}
