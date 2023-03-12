/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:44:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 00:48:30 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool received = false;

void	send_char(const int pid, char c)
{
	static const int	sig[NB_SIG] = {SIGUSR2, SIGUSR1};
	size_t				i;

	i = 0;
	while (i < CHAR_SIZE)
	{
		while (received == false)
		{
			send_signal(pid, sig[c & 1]);
		}
		received = false;
		c >>= 1;
		++i;
	}
}

void	send_str(const int pid, const char *str)
{
	while (*str != END_CHAR)
	{
		send_char(pid, *str);
		++str;
	}
	send_char(pid, END_TRANSMISSION);
	pause();
}

void	signal_handler(int signum)
{
	received = true;
	if (signum == SIGUSR1)
	{
		ft_printf("Message received\n");
		exit(EXIT_SUCCESS);
	}
}

void	set_catcher(void)
{
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
}

int	main(int ac, char **av)
{
	if (ac == EXPECTED_NB_ARG)
	{
		set_catcher();
		send_str(ft_atoi(av[1]), av[2]);
	}
	return (EXIT_FAILURE);
}
