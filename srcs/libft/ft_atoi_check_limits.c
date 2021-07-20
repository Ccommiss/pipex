/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check_limits.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 10:31:33 by ccommiss          #+#    #+#             */
/*   Updated: 2021/06/23 10:38:24 by ccommiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_check_limits(char *nptr)
{
	long int	nbr;
	int			neg;

	nbr = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\r' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\n')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			neg = 1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		nbr = nbr * 10;
		nbr = nbr + (*nptr - 48);
		nptr++;
	}
	if (neg == 1)
		nbr = nbr * -1;
	if (nbr > INT_MAX || nbr < INT_MIN)
		return (0);
	return (1);
}
