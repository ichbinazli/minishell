/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naanapa <naanapa@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:07:29 by naanapa           #+#    #+#             */
/*   Updated: 2024/09/27 17:07:30 by naanapa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int signal_state(int set_signal)
{
    static int signal = 0;
    if (set_signal != NOT_SET)
        signal = set_signal;
    return (signal);
}
