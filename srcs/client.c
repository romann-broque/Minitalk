/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:17:44 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/07 14:43:36 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_received(int signal_number, siginfo_t *siginfo, void *context)
{
	const pid_t	server_pid = siginfo->si_pid;
	const int	server_data = siginfo->si_value.sival_int;

	// check if the incoming sig is from server
	ft_printf("Received signal %d from server %d with data %d\n", signal_number, server_pid, server_data);
	(void)context;
}

void	waiting_for_signal(const int signum)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, signum);
	sigact.sa_sigaction = signal_received;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(signum, &sigact, NULL);
	pause();
}

void	send_signal(const int pid, const int sig, const char *sig_name)
{
	ft_printf("Send %s\n", sig_name);
	kill(pid, sig);
	waiting_for_signal(sig);
}

void	send_char(const int pid, const char c)
{
	size_t	i;
	int		sig;

	i = 0;
	sig = c;
	while (i < 8 * sizeof(char))
	{
		if (sig & 1)
			send_signal(pid, SIGUSR2, "SIGUSR2");
		else
			send_signal(pid, SIGUSR1, "SIGUSR1");
		sig = (sig >> 1);
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
	if (ac > 2)
	{
		pid = ft_atoi(av[1]);
		send_str(pid, av[2]);
	}
	return (EXIT_SUCCESS);
}
