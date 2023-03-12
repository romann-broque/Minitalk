/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:43:21 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 03:01:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_env	g_env;

void	bit_handler(int sig, siginfo_t *info, __attribute__((unused))void *ucontext)
{
	if (g_env.is_waiting == true)
	{
		g_env.is_waiting = false;
		if (g_env.client_pid != info->si_pid)
		{
			init_env(&g_env);
			g_env.client_pid = info->si_pid;
		}
		if (sig == SIGUSR1)
			g_env.curr_char |= (0x01 << g_env.index);
		++g_env.index;
	}
}

void	define_catcher(void)
{
	struct sigaction	sigact;

	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = bit_handler;
	sigemptyset(&sigact.sa_mask);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
}

int	main(void)
{
	ft_printf("SERVER_PID : %d\n", getpid());
	define_catcher();
	listening_loop_launcher(&g_env);
	// free
}
