/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:39:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/07 14:18:08 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_answer(int signal_number, siginfo_t *siginfo, void *context)
{
	const pid_t	client_pid = siginfo->si_pid;
	const int	client_data = siginfo->si_value.sival_int;

	ft_printf("Received signal %d from client %d with data %d\n", signal_number, client_pid, client_data);
	kill(client_pid, signal_number);
	(void)context;
}

int	main(void)
{
	struct sigaction	sigact;

	ft_printf("This is server !\n");
	ft_printf("pid -> %d\n", getpid());

	sigact.sa_sigaction = signal_answer;
	sigact.sa_flags = SA_SIGINFO;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (true)
		continue ;
	return (EXIT_SUCCESS);
}

// int	main(void)
// {
// 	struct sigaction	sigact;

// 	sigemptyset(&sigact.sa_mask);
// 	sigaddset(&sigact.sa_mask, SIGUSR1);
// 	sigaddset(&sigact.sa_mask, SIGUSR2);
// 	sigact.sa_handler = sig_handler;
// 	sigaction(SIGUSR1, &sigact, NULL);
// 	sigaction(SIGUSR2, &sigact, NULL);
// 	ft_printf("This is server !\n");
// 	ft_printf("pid -> %d\n", getpid());
// 	while (true)
// 		continue ;
// 	return (EXIT_SUCCESS);
// }
