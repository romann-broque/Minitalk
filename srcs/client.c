/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:44:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 13:14:20 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	g_received = false;

void	send_char(const int pid, char c)
{
	static const int	sig[NB_SIG] = {SIGUSR2, SIGUSR1};
	size_t				i;

	i = 0;
	while (i < CHAR_SIZE)
	{
		while (g_received == false)
			send_signal_to_server(pid, sig[c & 1]);
		g_received = false;
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
	g_received = true;
	if (signum == SIGUSR1)
	{
		ft_printf("%s\n", MESSAGE_RECEIVED);
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
