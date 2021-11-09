/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:32:43 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 19:08:09 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	austerity(t_philo *philo)
{
	if (philo->num_eat != -1)
	{
		philo->num_eat--;
		if (philo->num_eat == 0)
			*(philo->well_fed) = '1';
	}
}

void	*living(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->t_last_eating = philo->t_born;
	while (*(philo->status) != '4')
	{
		ft_mutex_lock(philo->take_f);
		pthread_mutex_lock(philo->fork_1);
		note(philo, "has taken a fork\n", NULL);
		pthread_mutex_lock(philo->fork_2);
		note(philo, "has taken a fork\n", "is eating\n");
		austerity(philo);
		my_usleep(philo->time.to_eat, philo->t_last_eating, philo->status);
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(philo->fork_2);
		note(philo, "is sleeping\n", NULL);
		my_usleep(philo->time.to_sleep, philo->t, philo->status);
		note(philo, "is thinking\n", NULL);
	}
	return (NULL);
}

int	init_checker(t_data *data)
{
	pthread_t	table;
	pthread_t	death;

	if (pthread_create(&table, NULL, waiter, (void *)data) != 0)
		return (ft_error("Error creat thread\n"));
	usleep(100);
	if (pthread_create(&death, NULL, grim_reaper, (void *)data) != 0)
		return (ft_error("Error creat thread\n"));
	pthread_join(table, NULL);
	pthread_join(death, NULL);
	return (0);
}

int	init_pthread(t_data *data)
{
	int				i;
	struct timeval	t_born;

	i = 0;
	gettimeofday(&t_born, NULL);
	t_born.tv_usec = t_born.tv_usec / 1000 * 1000;
	while (i < data->total)
	{
		data->philo[i].t_born = t_born;
		if (pthread_create(&data->lives[i], NULL, living, \
		(void *)&(data->philo[i])) != 0)
		{
			ft_exit(data, i);
			return (ft_error("Error creat thread\n"));
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (init_data(argc, argv, &data))
		return (1);
	if (init_pthread(&data))
		return (1);
	if (init_checker(&data))
	{
		ft_exit(&data, data.total);
		return (1);
	}
	ft_unlock(&data);
	ft_join(data.lives, data.total);
	ft_destroy(&data);
	ft_free(&data);
	return (0);
}
