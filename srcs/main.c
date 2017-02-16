/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 17:03:19 by wdebs             #+#    #+#             */
/*   Updated: 2017/02/15 20:48:21 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char		**environ

int		main(void)
{
	char	*cmd;

	while (1)
	{
		ft_putstr("$>");
		grab_line(0, &cmd);
		ft_putstr(cmd);
		exit(0);
	}
	return (0);
}
