/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:44:51 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 22:49:44 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_str(const int pid, const char *str)
{
	ft_printf("string -> %s; pid -> %d\n", str, pid);
}

int	main(int ac, char **av)
{
	if (ac > 2)
		send_str(ft_atoi(av[1]), av[2]);
	return (EXIT_SUCCESS);
}
