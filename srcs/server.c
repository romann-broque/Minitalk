/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:39:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/05 23:12:00 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum)
{
	ft_printf("Signal : %d\n", signum);
}

int	main(void)
{
	ft_printf("pid -> %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	ft_printf("hello !");
	return (EXIT_SUCCESS);
}
