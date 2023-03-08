/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:51:05 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/08 18:14:13 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	g_received;

static void	signal_received(int signal_number, siginfo_t *siginfo, void *context)
{
	// const pid_t	server_pid = siginfo->si_pid;
	// const int	server_data = siginfo->si_value.sival_int;

	// check if the incoming sig is from server
	// ft_printf("Received signal %d from server %d with data %d\n", signal_number, server_pid, server_data);
	(void)signal_number;
	(void)siginfo;
	(void)context;
	if (signal_number == SIGUSR1)
		g_received = true;
}

static void	waiting_for_signal(void)
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_sigaction = signal_received;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	pause();
}

void	send_signal(const int pid, const int sig, const char *sig_name)
{
	ft_printf("Send %s\n", sig_name);
	g_received = false;
	kill(pid, sig);
	waiting_for_signal();
}

void	signal_answer(int sig_nb, siginfo_t *siginfo)
{
	const pid_t	client_pid = siginfo->si_pid;
	// const int	client_data = siginfo->si_value.sival_int;
	(void)sig_nb;
	// ft_printf("Received signal %d from client %d with data %d\n", sig_nb, client_pid, client_data);
	kill(client_pid, SIGUSR1);
}
