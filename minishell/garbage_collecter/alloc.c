/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:57:52 by naanapa           #+#    #+#             */
/*   Updated: 2024/09/27 16:57:54 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

t_malloc	*get_garbage_c(void)
{
	static t_malloc	garbage_c = {NULL, NULL};

	return (&garbage_c);
}

void	*gc_malloc(unsigned int size)
{
	void		*ptr;
	t_malloc	*garbage_c;

	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
		ft_exit(strerror(errno));
	ptr = ft_calloc(1, size);
	if (!ptr)
		ft_exit(strerror(errno));
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
	return (ptr);
}

void	add_garbage_c(void *ptr)
{
	t_malloc	*garbage_c;

	if (!ptr)
		ft_exit(strerror(errno));
	garbage_c = get_garbage_c();
	while (garbage_c->next)
		garbage_c = garbage_c->next;
	garbage_c->next = ft_calloc(1, sizeof(t_malloc));
	if (!garbage_c->next)
	{
		free(ptr);
		ft_exit(strerror(errno));
	}
	*garbage_c->next = (t_malloc){.ptr = ptr, .next = NULL};
}
