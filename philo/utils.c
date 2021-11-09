/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:32:54 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/08 18:32:55 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(char *s, char c, int n)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (i < n)
	{
		if (*(s + i) != c)
			return (0);
		i++;
	}
	return (1);
}

int	any_dead(char *s, int n)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (i < n)
	{
		if (*(s + i) == '4')
			return (1);
		i++;
	}
	return (0);
}

void	ft_mutex_lock(t_mutex *mutex)
{
	pthread_mutex_lock(&(mutex->mutex));
	mutex->flag = 1;
}

void	ft_mutex_unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(&(mutex->mutex));
	mutex->flag = 0;
}

void	ft_unlock(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total)
	{
		if (data->take_f[i].flag)
			ft_mutex_unlock(&data->take_f[i]);
		i++;
	}
}
