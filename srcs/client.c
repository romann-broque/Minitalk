/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 23:17:44 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/05 23:26:33 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int ac, char **av)
{
	ft_printf("This is client !\n");
	if (ac > 1)
	{
		kill(ft_atoi(av[1]), SIGUSR1);
	}
	return (EXIT_SUCCESS);
}
