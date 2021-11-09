/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:32:43 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 18:12:12 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	austerity(t_philo *philo)
{
	if (philo->num_eat != -1)
	{
		philo->num_eat--;
		if (philo->num_eat == 0)
			sem_post(philo->well_fed);
	}
}

void	living(t_philo *philo)
{
	pthread_t	death;

	philo->t_last_eating = philo->t_born;
	if (pthread_create(&death, NULL, grim_reaper, (void *)philo) < 0)
		exit(2);
	pthread_detach(death);
	while (1)
	{
		sem_wait(philo->take_2f);
		usleep(10);
		sem_wait(philo->take_f);
		note(philo, "has taken a fork\n", NULL);
		sem_wait(philo->take_f);
		note(philo, "has taken a fork\n", "is eating\n");
		austerity(philo);
		my_usleep(philo->time.to_eat, philo->t_last_eating);
		sem_post(philo->take_2f);
		sem_post(philo->take_f);
		sem_post(philo->take_f);
		note(philo, "is sleeping\n", NULL);
		my_usleep(philo->time.to_sleep, philo->t);
		note(philo, "is thinking\n", NULL);
	}
	exit (1);
}

int	init_checker(t_data *data)
{
	pthread_t	asceticism;

	if (pthread_create(&asceticism, NULL, check_well_fed, (void *)data) != 0)
	{
		ft_kill_all(data, data->total);
		unlink_sem();
		exit(1);
	}
	pthread_detach(asceticism);
	return (0);
}

void	init_fork(t_data *data)
{
	int				i;
	struct timeval	t_born;

	i = 0;
	gettimeofday(&t_born, NULL);
	t_born.tv_usec = t_born.tv_usec / 1000 * 1000;
	data->philo->t_born = t_born;
	while (i < data->total)
	{
		data->philo->name = i + 1;
		data->lives[i] = fork();
		if (data->lives[i] < 0)
		{
			unlink_sem();
			ft_kill_all(data, i);
			exit (1);
		}
		else if (data->lives[i] == 0)
			living(data->philo);
		else
			i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;

	data.philo = (t_philo *)malloc(sizeof(t_philo));
	data.lives = (pid_t *)malloc(data.total * sizeof(pid_t));
	if (!data.philo || !data.lives)
		return (ft_error("Memory allocation error\n"));
	if (init_data(argc, argv, &data))
		return (1);
	init_fork(&data);
	if (data.num_eat != -1)
		init_checker(&data);
	sem_wait(data.death);
	if (data.num_eat != -1)
	{
		data.end_sim = 0;
		sem_post(data.well_fed);
	}
	ft_kill_all(&data, data.total);
	unlink_sem();
	return (0);
}
