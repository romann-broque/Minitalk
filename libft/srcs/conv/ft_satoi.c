/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_satoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbroque <rbroque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:35:19 by rbroque           #+#    #+#             */
/*   Updated: 2023/03/12 13:37:41 by rbroque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_whitespace(const char c)
{
	return (c == SPACE || (FIRST_WHITESPACE <= c && c <= LAST_WHITESPACE));
}

bool	ft_satoi(const char *nptr, int *dest_nb)
{
	long	nb;
	size_t	i;

	nb = 0;
	while (is_whitespace(*nptr) == true)
		++nptr;
	i = 0;
	if (nptr[0] == '-' || nptr[0] == '+')
		++i;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		++i;
	}
	if (nptr[0] == '-')
		nb *= -1;
	if (nb >= INT_MIN && nb <= INT_MAX)
		*dest_nb = nb;
	return (*dest_nb == nb);
}
