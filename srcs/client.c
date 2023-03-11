/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:44:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/10 18:24:58 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int bit_count = 0;

void	send_char(const int pid, char c)
{
	static const int	sig[NB_SIG] = {SIGUSR2, SIGUSR1};
	size_t				i;

	i = 0;
	while (i < CHAR_SIZE)
	{
		send_signal(pid, sig[c & 1]);
		usleep(USECONDS_TO_WAIT);
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
	send_char(pid, END_TRANSMISSION);
	pause();
	ft_printf("NEVER raise this point\n");
}

void	signal_handler(int signum)
{
	(void)signum;
	ft_printf("Message received\n");
	exit(EXIT_SUCCESS);
}

void	set_catcher(void)
{
	signal(SIGUSR1, signal_handler);
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
