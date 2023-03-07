/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:17:44 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/07 14:48:37 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
