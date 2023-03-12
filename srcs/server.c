/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:43:21 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 01:11:14 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_env	g_env;

void	add_char(void)
{
	const char	str[2] = {g_env.curr_char, '\0'};

	g_env.final_str = ft_strnjoin(g_env.final_str, str, sizeof(char));
}

void	clear_char(void)
{
	g_env.index = 0;
	g_env.curr_char = '\0';
}

void	init_env(void)
{
	clear_char();
	g_env.client_pid = 0;
	g_env.final_str = NULL;
	g_env.end_of_transmission = false;
}

void	process_byte(void)
{
	if (g_env.curr_char == END_TRANSMISSION)
		g_env.end_of_transmission = true;
	else
		add_char();
	clear_char();
}

void	bit_handler(int sig, siginfo_t *info, __attribute__((unused))void *ucontext)
{
	if (g_env.is_waiting == true)
	{
		g_env.is_waiting = false;
		if (g_env.client_pid != info->si_pid)
		{
			init_env();
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

void end_of_transmission_routine()
{
	ft_printf("%s\n", g_env.final_str);
	usleep(USECONDS_TO_CLOSE);
	send_signal(g_env.client_pid, SIGUSR1);
	listening_loop_laucher();
	while (g_env.end_of_transmission == false)
		;
}

void	loop_hander()
{
	while (g_env.end_of_transmission == false)
	{
		g_env.is_waiting = true;
		pause();
		if (g_env.index == CHAR_SIZE)
		{
			process_byte();
		}
		send_signal(g_env.client_pid, SIGUSR2);
	}
	end_of_transmission_routine();
}

void listening_loop_laucher()
{
	init_env();
	loop_hander();
}

int	main(void)
{
	g_env.is_waiting = true;
	ft_printf("SERVER_PID : %d\n", getpid());
	define_catcher();
	listening_loop_laucher();
	// free
}

// hey

