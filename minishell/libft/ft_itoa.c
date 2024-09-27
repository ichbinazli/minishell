/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:03:39 by naanapa           #+#    #+#             */
/*   Updated: 2024/09/27 17:24:59 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	long	ft_len(int n)
{
	long	size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static	int	ft_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	long	number;
	long	len;
	char	*str;

	number = n;
	len = ft_len(number);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	if (number < 0)
		number = -number;
	while (len >= 0)
	{
		str[len] = (number % 10) + '0';
		len--;
		number = number / 10;
	}
	if (ft_sign(n))
		str[0] = '-';
	return (str);
}
