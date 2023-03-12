/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:44:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 13:44:07 by rbroque          ###   ########.fr       */
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
	bool	is_valid_pid;
	int		server_pid;

	if (ac == EXPECTED_NB_ARG)
	{
		set_catcher();
		is_valid_pid = (ft_satoi(av[1], &server_pid) && server_pid != -1);
		if (is_valid_pid == true)
			send_str(server_pid, av[2]);
	}
	return (EXIT_FAILURE);
}
