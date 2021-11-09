/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 21:53:27 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 17:03:15 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	t_usec_gr(struct timeval t_start)
{
	struct timeval	t_end;

	gettimeofday(&t_end, NULL);
	t_end.tv_sec -= t_start.tv_sec;
	t_end.tv_usec -= t_start.tv_usec;
	if (t_end.tv_usec < 0)
	{
		t_end.tv_sec--;
		t_end.tv_usec += 1000000;
	}
	if (t_end.tv_sec < 0)
		return (0);
	return (t_end.tv_sec * 1000000 + t_end.tv_usec);
}

long long	t_usec(struct timeval t_start, struct timeval *t_end)
{
	struct timeval	temp;

	gettimeofday(t_end, NULL);
	t_end->tv_usec = t_end->tv_usec / 1000 * 1000;
	temp = *t_end;
	temp.tv_sec -= t_start.tv_sec;
	temp.tv_usec -= t_start.tv_usec;
	if (temp.tv_usec < 0)
	{
		temp.tv_sec--;
		temp.tv_usec += 1000000;
	}
	return (temp.tv_sec * 1000000 + temp.tv_usec);
}

void	my_usleep(long t_to_sleep, struct timeval t_start)
{
	struct timeval	t_current;

	while (t_usec(t_start, &t_current) < t_to_sleep)
		usleep(100);
}
