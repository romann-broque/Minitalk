/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:39:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 10:49:59 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_string_info;

void	add_byte(const int sig_nb)
{
	t_data *const	str = &g_string_info;

	if (str->index_bit < 8)
	{
		str->curr_byte |= (get_bit(sig_nb) << str->index_bit);
		++(str->index_bit);
	}
	if (str->index_bit >= 8)
	{
		if (str->curr_byte == 0x00)
		{
			ft_printf("%s\n", str->final_str);
			reset_data(str);
		}
		else
		{
			add_char(str);
			str->curr_byte = 0x00;
			str->index_bit = 0;
		}
	}
}
void	server_action(int sig_nb, siginfo_t *siginfo, void *context)
{
	send_ping_to_client(sig_nb, siginfo);
	add_byte(sig_nb);
	(void)context;
}

void	init_sigact(void)
{
	struct sigaction	sigact;

	sigact.sa_sigaction = server_action;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
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
