/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:32:51 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 23:14:24 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	note(t_philo *philo, char *s1, char *s2)
{
	long long	t;

	sem_wait(philo->chronicler);
	t = t_usec(philo->t_born, &(philo->t)) / 1000;
	printf("%lld %d %s", t, philo->name, s1);
	if (s2)
	{
		philo->t_last_eating = philo->t;
		printf("%lld %d %s", t, philo->name, s2);
	}
	sem_post(philo->chronicler);
}

void	*grim_reaper(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while (1)
	{
		if (t_usec_gr(philo->t_last_eating) > philo->time.to_die)
		{
			sem_wait(philo->chronicler);
			if (t_usec_gr(philo->t_last_eating) > philo->time.to_die)
			{
				printf("%lld %d died\n", \
				t_usec_gr(philo->t_born) / 1000, philo->name);
				sem_post(philo->death);
				break ;
			}
			sem_post(philo->chronicler);
		}
		usleep(100);
	}
	return (NULL);
}

void	*check_well_fed(void *dt)
{
	t_data	*data;
	int		n;

	data = (t_data *)dt;
	n = data->total;
	while (n && data->end_sim)
	{
		sem_wait(data->well_fed);
		n--;
	}
	sem_post(data->death);
	return (NULL);
}

void	open_sem(t_data *data)
{
	unlink_sem();
	data->take_2f = sem_open("take_2_forks", O_CREAT | O_EXCL, 0666, \
	data->total / 2 + data->total % 2);
	data->take_f = sem_open("take_fork", O_CREAT | O_EXCL, 0666, data->total);
	data->chronicler = sem_open("chronicler", O_CREAT | O_EXCL, 0666, 1);
	data->well_fed = sem_open("well_fed", O_CREAT | O_EXCL, 0666, 0);
	data->death = sem_open("death", O_CREAT | O_EXCL, 0666, 0);
	if (!data->take_2f || !data->take_f || !data->chronicler \
	|| !data->well_fed || !data->death)
	{
		unlink_sem();
		ft_error("Error open semaphore\n");
		exit (1);
	}
}

void	unlink_sem(void)
{
	sem_unlink("take_2_forks");
	sem_unlink("take_fork");
	sem_unlink("chronicler");
	sem_unlink("well_fed");
	sem_unlink("death");
}
