/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:32:29 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/09 18:12:10 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_times
{
	long	to_die;
	long	to_eat;
	long	to_sleep;
}	t_times;

typedef struct s_philo
{
	int				name;
	sem_t			*take_f;
	struct timeval	t_born;
	struct timeval	t_last_eating;
	struct timeval	t;
	int				num_eat;
	t_times			time;
	sem_t			*take_2f;
	sem_t			*chronicler;
	sem_t			*well_fed;
	sem_t			*death;
}	t_philo;

typedef struct s_data
{
	int		end_sim;
	int		total;
	t_times	time;
	int		num_eat;
	t_philo	*philo;
	sem_t	*take_f;
	sem_t	*take_2f;
	sem_t	*chronicler;
	sem_t	*well_fed;
	sem_t	*death;
	pid_t	*lives;
}	t_data;

//init.c
int			init_mutex(t_data *data);
int			init_data(int argc, char **argv, t_data *data);
//utils.c
void		note(t_philo *philo, char *s1, char *s2);
void		*grim_reaper(void *data);
void		*check_well_fed(void *dt);
void		open_sem(t_data *data);
void		unlink_sem(void);
//time.c
long long	t_usec(struct timeval t_start, struct timeval *t_end);
long long	t_usec_gr(struct timeval t_start);
void		my_usleep(long t_to_sleep, struct timeval t_start);
//utils2.c
long		ft_getnbr(char *nptr, int k);
int			ft_error(char *str);
void		ft_kill_all(t_data *data, int n);

#endif