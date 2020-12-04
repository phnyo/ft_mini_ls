/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:47:02 by fsugimot          #+#    #+#             */
/*   Updated: 2020/12/04 15:47:48 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

int		ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_strdup(char *str)
{
	int		len;
	char	*ret;

	len = ft_strlen(str);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len] = 0;
	len--;
	while (len > -1)
	{
		ret[len] = str[len];
		len--;
	}
	return (ret);
}

char	*ft_strconcat(char *f, char *s)
{
	int		total_len;
	int		f_len;
	int		itr;
	char	*str;

	total_len = ft_strlen(f) + ft_strlen(s);
	if ((str = malloc(total_len + 1)) == NULL)
		return (NULL);
	str[total_len] = 0;
	itr = 0;
	f_len = ft_strlen(f);
	while (f[itr] != 0)
	{
		str[itr] = f[itr];
		itr++;
	}
	while (s[itr - f_len])
	{
		str[itr] = s[itr - f_len];
		itr++;
	}
	return (str);
}
