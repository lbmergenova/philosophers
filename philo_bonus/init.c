/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:33:11 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 23:15:04 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_data *data)
{
	data->philo->take_f = data->take_f;
	data->philo->take_2f = data->take_2f;
	data->philo->num_eat = data->num_eat;
	data->philo->time = data->time;
	data->philo->chronicler = data->chronicler;
	data->philo->well_fed = data->well_fed;
	data->philo->death = data->death;
}

int	get_data(int argc, char **argv, t_data *data)
{
	data->end_sim = 1;
	if (argc < 5 || argc > 7)
		return (ft_error("Bad arguments\n"));
	data->total = ft_getnbr(argv[1], 1);
	data->time.to_die = ft_getnbr(argv[2], 1000);
	data->time.to_eat = ft_getnbr(argv[3], 1000);
	data->time.to_sleep = ft_getnbr(argv[4], 1000);
	if (data->total == -1 || data->time.to_eat == -1 || \
	data->time.to_sleep == -1 || data->time.to_die == -1)
		return (ft_error("Bad arguments\n"));
	if (argc == 6)
	{
		data->num_eat = ft_getnbr(argv[5], 1);
		if (data->num_eat == -1)
			return (ft_error("Bad arguments\n"));
	}
	else
		data->num_eat = -1;
	return (0);
}

int	init_data(int argc, char **argv, t_data *data)
{
	if (get_data(argc, argv, data))
		return (1);
	open_sem(data);
	init_philos(data);
	return (0);
}
