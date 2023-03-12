/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_transmission.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:43:21 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 13:12:19 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	end_of_transmission_routine(t_env *env)
{
	if (env->final_str != NULL)
		ft_printf("%s", env->final_str);
	ft_printf("\n");
	usleep(USECONDS_TO_CLOSE);
	send_signal_to_client(env->client_pid, SIGUSR1, env);
	free(env->final_str);
	listening_loop_launcher(env);
}

void	loop_handler(t_env *env)
{
	while (env->end_of_transmission == false)
	{
		env->is_waiting = true;
		pause();
		if (env->index == CHAR_SIZE)
			process_byte(env);
		send_signal_to_client(env->client_pid, SIGUSR2, env);
	}
	end_of_transmission_routine(env);
}

void	listening_loop_launcher(t_env *env)
{
	env->is_waiting = true;
	init_env(env);
	loop_handler(env);
}
