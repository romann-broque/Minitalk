/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:51:05 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/07 20:05:19 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_received(int signal_number, siginfo_t *siginfo, void *context)
{
	const pid_t	server_pid = siginfo->si_pid;
	const int	server_data = siginfo->si_value.sival_int;

	// check if the incoming sig is from server
	ft_printf("Received signal %d from server %d with data %d\n", signal_number, server_pid, server_data);
	(void)context;
}

static void	waiting_for_signal(const int signum)
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

void	signal_answer(int sig_nb, siginfo_t *siginfo)
{
	const pid_t	client_pid = siginfo->si_pid;
	const int	client_data = siginfo->si_value.sival_int;

	ft_printf("Received signal %d from client %d with data %d\n", sig_nb, client_pid, client_data);
	kill(client_pid, sig_nb);
}
