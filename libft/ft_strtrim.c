/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 17:53:00 by wdebs             #+#    #+#             */
/*   Updated: 2017/01/09 21:30:32 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(s);
	j = len;
	while (s[i] == ' ' && s[i] == '\n' && s[i] == '\t' && s[i] != '\0')
		i++;
	while (s[j] == ' ' && s[j] == '\n' && s[j] == '\t' && s[j] != '\0')
		j--;
	if (i == 0 && j == len)
		return (s);
	if ((new = ft_strnew((len - i) - j)) != NULL)
	{
		len = 0;
		while (i <= j)
			new[len++] = s[i++];
		return (new);
	}
	else
		return (NULL);
}
