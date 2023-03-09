/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:17:44 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 15:06:07 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	g_is_waiting;

static void	signal_received(int signal_number, siginfo_t *siginfo, void *context)
{
	const pid_t		server_pid = siginfo->si_pid;
	static pid_t	last_pid = -1;

	(void)signal_number;
	(void)context;
	if (last_pid == -1)
		last_pid = server_pid;
	if (last_pid == server_pid && signal_number == SIGUSR1)
		g_is_waiting = false;
}

void	send_signal(const int pid, const int sig, const char *sig_name)
{
	ft_printf("Send %s\n", sig_name);
	g_is_waiting = true;
	if (kill(pid, sig) != 0)
		exit(EXIT_FAILURE);
	while (g_is_waiting == true)
		usleep(10);
}

void	send_char(const int pid, const char c)
{
	size_t	i;
	uint8_t	byte;

	i = 0;
	byte = c;
	while (i < 8 * sizeof(char))
	{
		if (byte & 1)
			send_signal(pid, SIGUSR2, "SIGUSR2");
		else
			send_signal(pid, SIGUSR1, "SIGUSR1");
		byte >>= 1;
		++i;
	}
}

void	send_str(const int pid, const char *str)
{
	while (*str != '\0')
	{
		send_char(pid, *str);
		++str;
	}
	send_char(pid, *str);
}

int	main(int ac, char **av)
{
	int	pid;

	ft_printf("This is client !\n");
	ft_printf("pid -> %d\n", getpid());
	init_sigact(signal_received);
	if (ac > 2)
	{
		pid = ft_atoi(av[1]);
		if (pid > -1)
			send_str(pid, av[2]);
	}
	return (EXIT_SUCCESS);
}
