/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:43:21 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/10 18:24:06 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_env	g_env;

void	add_char(void)
{
	char	str[2];

	str[0] = g_env.curr_char;
	str[1] = '\0';
	//ft_printf("char --> %c\n", str[0]);
	g_env.final_str = ft_strnjoin(g_env.final_str, str, sizeof(char));
}

void	init_env(void)
{
	g_env.index = 0;
	g_env.curr_char = '\0';
	g_env.final_str = NULL;
}

void	process_byte(void)
{
	if (g_env.curr_char == END_TRANSMISSION)
	{
		ft_printf("%s\n", g_env.final_str);
		// reset_buffer
		init_env();
		send_signal(g_env.client_pid, SIGUSR1);
	}
	else
	{
		add_char();
	}
	g_env.curr_char = '\0';
	g_env.index = 0;
}

void	bit_handler(int sig, siginfo_t *info, void *ucontext)
{
	g_env.client_pid = info->si_pid;
	if (sig == SIGUSR1)
		g_env.curr_char |= (0x01 << g_env.index);
	//ft_putchar_fd(sig == SIGUSR1 ? '1' : '0', 1);
	++g_env.index;
	(void)ucontext;
}

void	define_catcher(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = bit_handler;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
}

void	loop_hander()
{
	while (true)
	{
		pause();
		send_signal(g_env.client_pid, SIGUSR2);
		if (g_env.index == CHAR_SIZE)
			process_byte();
	}
}

int	main(void)
{
	ft_printf("SERVER_PID : %d\n", getpid());
	init_env();
	define_catcher();
	loop_hander();
	// free
}

// hey

