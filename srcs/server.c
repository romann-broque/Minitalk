/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:39:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/07 20:57:57 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

uint8_t	get_bit(const int nb)
{
	return (nb == SIGUSR2);
}

void	add_byte(const int sig_nb)
{
	static t_data	*str_info = &g_string_info;

	if (str_info->index_bit < 8)
		str_info->curr_byte >> str_info->index_bit = get_bit(sig_nb);
}

void	server_action(int sig_nb, siginfo_t *siginfo, void *content)
{
	signal_answer(sig_nb, siginfo);
	add_byte(sig_nb);
	(void)context;
}

void	init_sigact(void)
{
	struct sigaction	sigact;

	sigact.sa_sigaction = server_action;
	sigact.sa_flags = SA_SIGINFO;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
}

void	init_data(t_data *data)
{
	data->index_bit = 0;
	data->curr_byte = 0;
	data->final_str = NULL;
}

int	main(void)
{
	ft_printf("This is server !\n");
	ft_printf("pid -> %d\n", getpid());

	init_data(&g_string_info);
	init_sigact();
	while (true)
		continue ;
	return (EXIT_SUCCESS);
}
