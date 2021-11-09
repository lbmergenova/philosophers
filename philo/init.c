/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:33:11 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 23:12:26 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	int	i;
	int	i_next;

	i = 0;
	while (i < data->total)
	{
		i_next = i + 1;
		if (i_next == data->total)
			i_next = 0;
		data->philo[i].name = i + 1;
		data->philo[i].take_f = &data->take_f[i];
		data->philo[i].fork_1 = &data->forks[i];
		data->philo[i].fork_2 = &data->forks[i_next];
		data->philo[i].num_eat = data->num_eat;
		data->philo[i].time = data->time;
		data->philo[i].status = &(data->all_status[i]);
		data->philo[i].well_fed = &(data->all_well_fed[i]);
		data->philo[i].chronicler = &(data->chronicler);
		data->philo[i].change_status = &(data->change_status);
		i++;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->total)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0 || \
		pthread_mutex_init(&data->take_f[i].mutex, NULL) != 0)
			return (ft_error("Error init mutex\n"));
		data->take_f[i].flag = 0;
		if (i % 2)
			ft_mutex_lock(&data->take_f[i]);
	}
	if (pthread_mutex_init(&data->chronicler, NULL) != 0 || \
	pthread_mutex_init(&data->change_status, NULL) != 0)
		return (ft_error("Error init mutex\n"));
	return (0);
}

int	init_num_eat(int argc, char **argv, t_data *data)
{
	if (argc == 6)
	{
		data->num_eat = ft_getnbr(argv[5], 1);
		if (data->num_eat == -1)
			return (ft_error("Bad arguments\n"));
		memset(data->all_well_fed, '0', data->total);
	}
	else
	{
		data->num_eat = -1;
		free(data->all_well_fed);
		data->all_well_fed = NULL;
	}
	return (0);
}

int	get_data(int argc, char **argv, t_data *data)
{
	data->time.to_die = ft_getnbr(argv[2], 1000);
	data->time.to_eat = ft_getnbr(argv[3], 1000);
	data->time.to_sleep = ft_getnbr(argv[4], 1000);
	if (data->time.to_eat == -1 || data->time.to_sleep == -1 || \
	data->time.to_die == -1)
		return (ft_error("Bad arguments\n"));
	if (init_num_eat(argc, argv, data))
		return (1);
	memset(data->all_status, '0', data->total);
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 7)
		return (ft_error("Bad arguments\n"));
	data->total = ft_getnbr(argv[1], 1);
	if (data->total == -1)
		return (ft_error("Bad arguments\n"));
	data->philo = (t_philo *)malloc(data->total * sizeof(t_philo));
	data->forks = (pthread_mutex_t *)malloc(data->total \
	* sizeof(pthread_mutex_t));
	data->take_f = (t_mutex *)malloc(data->total * sizeof(t_mutex));
	data->lives = (pthread_t *)malloc(data->total * sizeof(pthread_t));
	data->all_status = (char *)malloc(data->total * sizeof(char));
	data->all_well_fed = (char *)malloc(data->total * sizeof(char));
	if (!data->philo || !data->forks || !data->take_f || !data->lives || \
	!data->all_status || !data->all_well_fed)
	{
		ft_free(data);
		return (ft_error("Memory allocation error\n"));
	}
	if (get_data(argc, argv, data) || init_mutex(data))
	{
		ft_free(data);
		return (1);
	}
	init_philos(data);
	return (0);
}
