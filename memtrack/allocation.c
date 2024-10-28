/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:57:52 by naanapa           #+#    #+#             */
/*   Updated: 2024/10/16 14:01:39 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

t_malloc	*get_memtrack(void)
{
	static t_malloc	memtrack = {NULL, NULL};

	return (&memtrack);
}

void	*memtrack_alloc(unsigned int size)
{
	void		*ptr;
	t_malloc	*memtrack;

	memtrack = get_memtrack();
	while (memtrack->next)
		memtrack = memtrack->next;
	memtrack->next = ft_calloc(1, sizeof(t_malloc));
	if (!memtrack->next)
		ft_exit(strerror(errno));
	ptr = ft_calloc(1, size);
	if (!ptr)
		ft_exit(strerror(errno));
	*memtrack->next = (t_malloc){.ptr = ptr, .next = NULL};
	return (ptr);
}

void	add_to_memtrack(void *ptr)
{
	t_malloc	*memtrack;

	if (!ptr)
		ft_exit(strerror(errno));
	memtrack = get_memtrack();
	while (memtrack->next)
		memtrack = memtrack->next;
	memtrack->next = ft_calloc(1, sizeof(t_malloc));
	if (!memtrack->next)
	{
		free(ptr);
		ft_exit(strerror(errno));
	}
	*memtrack->next = (t_malloc){.ptr = ptr, .next = NULL};
}
