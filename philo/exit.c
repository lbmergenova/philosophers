/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:33:02 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 19:04:29 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_join(pthread_t *lives, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(lives[i], NULL);
		i++;
	}
}

void	ft_free(t_data *data)
{
	if (!data->all_status)
		free(data->all_status);
	if (!data->all_well_fed)
		free(data->all_well_fed);
	if (!data->lives)
		free(data->lives);
	if (!data->philo)
		free(data->philo);
	if (!data->take_f)
		free(data->take_f);
	if (!data->forks)
		free(data->forks);
}

void	ft_exit(t_data *data, int n)
{
	pthread_mutex_lock(&data->change_status);
	pthread_mutex_lock(&data->chronicler);
	memset(data->all_status, '4', data->total);
	pthread_mutex_unlock(&data->change_status);
	pthread_mutex_unlock(&data->chronicler);
	ft_unlock(data);
	ft_join(data->lives, n);
	ft_destroy(data);
	ft_free(data);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->take_f[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->change_status);
	pthread_mutex_destroy(&data->chronicler);
}
