/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:13:16 by naanapa           #+#    #+#             */
/*   Updated: 2024/09/27 17:28:24 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

static int	ft_checkset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	a;
	size_t	b;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	a = 0;
	b = ft_strlen(s1);
	while ((s1[a] != '\0') && (ft_checkset(s1[a], set) == 1))
		a++;
	while ((b > a) && (ft_checkset(s1[b - 1], set) == 1))
		b--;
	str = (char *)malloc(sizeof(char) * (b - a) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (a < b)
		str[i++] = s1[a++];
	str[i] = '\0';
	return (str);
}
