/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:39:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/08 04:07:13 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_string_info;

void	init_data(t_data *data)
{
	data->index_bit = 0;
	data->curr_byte = 0;
	data->final_str = NULL;
}

void	reset_data(t_data *data)
{
	free(data->final_str);
	init_data(data);
}

uint8_t	get_bit(const int nb)
{
	return (nb == SIGUSR2);
}

uint8_t	turn_bit(const uint8_t byte, const size_t index, const uint8_t bit)
{
	int	new_bit;

	new_bit = (bit << index);
	return (byte | new_bit);
}

void	add_char(t_data *str_info)
{
	const char	c = str_info->curr_byte;
	char		new_str[2];

	new_str[0] = c;
	new_str[1] = '\0';
	str_info->final_str = ft_strnjoin(str_info->final_str, new_str, sizeof(char));
}

void	add_byte(const int sig_nb)
{
	static t_data	*str_info = &g_string_info;

	if (str_info->index_bit < 8)
	{
		str_info->curr_byte = turn_bit(str_info->curr_byte, str_info->index_bit, get_bit(sig_nb));
		++(str_info->index_bit);
	}
	if (str_info->index_bit >= 8)
	{
		if (str_info->curr_byte == 0x00)
		{
			ft_printf("final_str -> %s\n", str_info->final_str);
			reset_data(str_info);
		}
		else
		{
			add_char(str_info);
			str_info->curr_byte = 0x00;
			str_info->index_bit = 0;
		}
	}
}

void	server_action(int sig_nb, siginfo_t *siginfo, void *context)
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
	sigaction(SIGUSR1, &sigact, NULL);
	sigaddset(&sigact.sa_mask, SIGUSR2);
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
