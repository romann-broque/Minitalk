/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:39:01 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 15:07:52 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_string_info;

void	add_char(t_data *str_info)
{
	const char	c = str_info->curr_byte;
	char		new_str[2];

	new_str[0] = c;
	new_str[1] = '\0';
	str_info->final_str = ft_strnjoin(str_info->final_str, new_str, sizeof(char));
}

void	send_ping_to_client(siginfo_t *siginfo)
{
	// static pid_t	last_pid = -1;
	const pid_t		client_pid = siginfo->si_pid;

	// if (last_pid != client_pid)
	// 	reset_data(&g_string_info);
	kill(client_pid, SIGUSR1);
}

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
	send_ping_to_client(siginfo);
	add_byte(sig_nb);
	(void)context;
}

int	main(void)
{
	ft_printf("This is server !\n");
	ft_printf("pid -> %d\n", getpid());

	init_data(&g_string_info);
	init_sigact(server_action);
	while (true)
		continue ;
	return (EXIT_SUCCESS);
}
