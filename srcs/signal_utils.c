/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 02:00:53 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 13:06:31 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal_to_server(const int pid, const int signal)
{
	if (kill(pid, signal) == KILL_FAILURE)
		exit(EXIT_FAILURE);
	usleep(USECONDS_TO_WAIT);
}

void	send_signal_to_client(const int pid, const int signal, t_env *env)
{
	if (kill(pid, signal) == KILL_FAILURE)
	{
		free(env->final_str);
		exit(EXIT_FAILURE);
	}
	usleep(USECONDS_TO_WAIT);
}
