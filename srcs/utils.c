/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:06:48 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 15:07:25 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	init_sigact(void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sigact;

	sigemptyset(&sigact.sa_mask);
	sigact.sa_sigaction = handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
}

void	init_data(t_data *data)
{
	data->index_bit = 0;
	data->curr_byte = 0x00;
	data->final_str = NULL;
}

void	reset_data(t_data *data)
{
	// free(data->final_str);
	init_data(data);
}

uint8_t	get_bit(const int nb)
{
	return (nb == SIGUSR2);
}
