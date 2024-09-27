/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:16:14 by naanapa           #+#    #+#             */
/*   Updated: 2024/09/27 17:28:32 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen(s + start))
		len = (unsigned int)ft_strlen(s + start);
	cpy = (char *)malloc(sizeof(char) * len + 1);
	if (cpy == NULL || !s)
		return (NULL);
	while (s[i])
	{
		if (j < len && i >= start)
		{
			cpy[j] = s[i];
			j++;
		}
		i++;
	}
	cpy[j] = '\0';
	return (cpy);
}
