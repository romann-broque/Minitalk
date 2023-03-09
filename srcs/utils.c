/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:48:00 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/09 10:50:02 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	add_char(t_data *str_info)
{
	const char	c = str_info->curr_byte;
	char		new_str[2];

	new_str[0] = c;
	new_str[1] = '\0';
	str_info->final_str = ft_strnjoin(str_info->final_str, new_str, sizeof(char));
}
