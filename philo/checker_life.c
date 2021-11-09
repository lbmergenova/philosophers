/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_life.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:32:51 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 19:16:05 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	note(t_philo *philo, char *s1, char *s2)
{
	long long	t;

	pthread_mutex_lock(philo->chronicler);
	if (*philo->status != '4')
	{
		t = t_usec(philo->t_born, &(philo->t)) / 1000;
		printf("%lld %d %s", t, philo->name, s1);
		if (s2)
		{
			philo->t_last_eating = philo->t;
			printf("%lld %d %s", t, philo->name, s2);
			*(philo->status) = '2';
		}
	}
	pthread_mutex_unlock(philo->chronicler);
}

int	register_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->chronicler);
	if (t_usec_gr(data->philo[i].t_last_eating) > \
	data->time.to_die)
	{
		pthread_mutex_lock(&data->change_status);
		memset(data->all_status, '4', data->total);
		printf("%lld %d died\n", \
		t_usec_gr(data->philo[i].t_born) / 1000, data->philo[i].name);
		pthread_mutex_unlock(&data->change_status);
		pthread_mutex_unlock(&data->chronicler);
		if (data->total == 1)
			pthread_mutex_unlock(data->philo[0].fork_1);
		return (1);
	}
	pthread_mutex_unlock(&data->chronicler);
	return (0);
}

int	register_full_fed(t_data *data)
{
	if (is_full(data->all_well_fed, '1', data->total))
	{
		pthread_mutex_lock(&data->chronicler);
		pthread_mutex_lock(&data->change_status);
		memset(data->all_status, '4', data->total);
		pthread_mutex_unlock(&data->change_status);
		pthread_mutex_unlock(&data->chronicler);
		return (1);
	}
	return (0);
}

void	*grim_reaper(void *dt)
{
	int		i;
	t_data	*data;

	data = (t_data *)dt;
	i = 0;
	while (1)
	{
		if (t_usec_gr(data->philo[i].t_last_eating) > data->time.to_die)
		{
			if (register_death(data, i))
				break ;
		}
		if (register_full_fed(data))
			break ;
		usleep(100);
		if (++i == data->total)
			i = 0;
	}
	return (NULL);
}

void	*waiter(void *dt)
{
	t_data	*data;
	int		i;
	int		i_next;

	data = (t_data *)dt;
	i = 0;
	while (!any_dead(data->all_status, data->total))
	{
		i_next = i + 1;
		if (i_next == data->total)
			i_next = 0;
		if (*(data->philo[i].status) == '2')
		{
			pthread_mutex_lock(&data->change_status);
			ft_mutex_unlock(data->philo[i_next].take_f);
			if (*(data->philo[i].status) != '4')
				*(data->philo[i].status) = '1';
			pthread_mutex_unlock(&data->change_status);
			i = i_next;
		}
		if (++i == data->total)
			i = 0;
	}
	return (NULL);
}
