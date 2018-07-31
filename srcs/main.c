/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:03:19 by wdebs             #+#    #+#             */
/*   Updated: 2017/03/02 00:33:52 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exe(t_vars *vars, char ***envp)
{
	check_bins(vars, envp);
	if (vars->check == 0 && ft_strncmp(vars->args[0], "./", 2) != 0 &&
				ft_strncmp(vars->args[0], "~/", 2) != 0 &&
				ft_strncmp(vars->args[0], "../", 3) != 0 &&
				ft_strncmp(vars->args[0], "/", 1) != 0 &&
				vars->path_check == 0)
		check_path(vars);
	else if (vars->check == 0)
		check_arg(vars, envp);
	if (vars->check == 2)
		run(vars, envp);
}

char	**set_path(char ***envp)
{
	char	**path;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while ((*envp)[++i])
		if (ft_strncmp((*envp)[i], "PATH", 4) == 0)
			break ;
	path = ft_strsplit((*envp)[i] + 5, ':');
	while (path[++j])
		path[j] = ft_strjoin(path[j], "/");
	return (path);
}

void	ini_params(t_vars *vars, char ***envp)
{
	int		i;
	char	*buf;
	char	*tmp;

	buf = NULL;
	i = -1;
	vars->old_path = 0;
	while ((*envp)[++i] && ft_strncmp((*envp)[i], "HOME", 4) != 0)
		vars->home = i + 1;
	i = -1;
	while ((*envp)[++i] && ft_strncmp((*envp)[i], "OLDPWD", 6) != 0)
		vars->old_path = i + 1;
	tmp = getcwd(buf, 10024);
	env_chg("PWD", tmp, envp);
	free(tmp);
	free(buf);
	vars->check = 0;
}

int		main(int argc, char **argv, char **envp)
{
	t_vars	*vars;
	char	*tmp;

	vars = (t_vars *)malloc(sizeof(t_vars));
	vars->path_check = 0;
	while (argc && argv)
	{
		ini_params(vars, &envp);
		vars->path_check == 0 ? vars->path = set_path(&envp) : 0;
		ft_putstr("$> ");
		if (grab_line(0, &tmp) < 2)
			continue ;
		vars->args = ft_strsplit(tmp, ' ');
		free(tmp);
		tmp = NULL;
		if (ft_strcmp(vars->args[0], "exit") == 0)
			exit(0);
		else
			run_exe(vars, &envp);
		free(vars->args);
		vars->path_check == 0 ? free(vars->path) : 0;
	}
	free(vars);
	return (0);
}
