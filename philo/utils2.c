/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:32:47 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/08 18:32:48 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if ((c >= 48) && (c <= 57))
		return (1);
	return (0);
}

long	ft_getnbr(char *nptr, int k)
{
	long int	i;

	i = 0;
	while (*nptr == ' ')
		nptr++;
	if (*nptr == '-')
		return (-1);
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		i = i * 10 + (*nptr - 48);
		nptr++;
	}
	if (i > INT32_MAX || i == 0 || *nptr)
		return (-1);
	i = i * k;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
