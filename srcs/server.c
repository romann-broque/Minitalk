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

void 	clear_char(void)
{
	g_env.index = 0;
	g_env.curr_char = '\0';
}

void	init_env(void)
{
	clear_char();
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

void end_of_transmission_routine()
{
	ft_printf("%s\n", g_env.final_str);
	// reset_buffer
	send_signal(g_env.client_pid, SIGUSR1);
	listening_loop_laucher();
}

void	loop_hander()
{
	while (g_env.end_of_transmission == false)
	{
		pause();
		if (g_env.index == CHAR_SIZE)
			process_byte();
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
	ft_printf("SERVER_PID : %d\n", getpid());
	define_catcher();
	listening_loop_laucher();
	// free
}

// hey

