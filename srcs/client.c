/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:44:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/10 01:38:14 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(const int pid, char c)
{
	const int	sig[NB_SIG] = {SIGUSR2, SIGUSR1};
	size_t		i;

	i = 0;
	while (i < CHAR_SIZE)
	{
		if (kill(pid, sig[c & 1]) == KILL_FAILURE)
			exit(EXIT_FAILURE);
		usleep(10);
		c >>= 1;
		++i;
	}
}

void	send_str(const int pid, const char *str)
{
	ft_printf("string -> %s; pid -> %d\n", str, pid);
	while (*str != END_CHAR)
	{
		send_char(pid, *str);
		++str;
	}
	send_char(pid, END_CHAR);
}

void	success_send(int pid)
{
	(void)pid;
	ft_printf("Message received\n");
	exit(EXIT_SUCCESS);
}

void	set_catcher(void)
{
	signal(SIGUSR1, success_send);
	signal(SIGUSR2, success_send);
}

int	main(int ac, char **av)
{
	if (ac == EXPECTED_NB_ARG)
	{
		set_catcher();
		send_str(ft_atoi(av[1]), av[2]);
	}
	return (EXIT_SUCCESS);
}
