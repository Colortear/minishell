/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 16:56:18 by wdebs             #+#    #+#             */
/*   Updated: 2017/02/26 20:00:36 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct	s_vars
{
	char		**path;
	int			home;
	char		**args;
	char		**env;
	int			check;
	int			path_check;
	int			old_path;
	int			pwd;
}				t_vars;

void			check_bins(t_vars *vars, char ***envp);
int				check_path(t_vars *vars);
void			check_arg(t_vars *vars, char ***envp);
void			run_exe(t_vars *vars, char ***envp);
char			**set_path(char ***envp);
void			errors(t_vars *vars, int error);
void			find_home(t_vars *vars);

void			run_echo(t_vars *vars, char ***envp);
void			run_setenv(t_vars *vars, char ***envp);
void			run_cd(t_vars *vars, char ***envp);
void			run_unsetenv(t_vars *vars, char ***envp);
void			run_env(char ***envp);
void			run(t_vars *vars, char ***envp);
void			ini_params(t_vars *vars, char ***envp);
void			env_chg(char *env_name, char *env_val, char ***envp);
void			add_line(char *line, char ***envp);
void			echo_env(char *name, char ***envp);
void			arg_cd(t_vars *vars, char ***envp);

#endif
