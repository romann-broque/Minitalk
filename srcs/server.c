/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:39:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/05 23:39:29 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum)
{
	ft_printf("Signal incoming: %d\n", signum);
}

int	main(void)
{
	ft_printf("This is server !\n");
	ft_printf("pid -> %d\n", getpid());
	while (true)
	{
		signal(SIGUSR1, sig_handler);
	}
	return (EXIT_SUCCESS);
}
