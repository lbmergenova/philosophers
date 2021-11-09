/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfearow <sfearow@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:32:29 by sfearow           #+#    #+#             */
/*   Updated: 2021/11/08 18:32:37 by sfearow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				flag;
}	t_mutex;

typedef struct s_times
{
	long	to_die;
	long	to_eat;
	long	to_sleep;
}	t_times;

typedef struct s_philo
{
	int				name;
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	struct timeval	t_born;
	struct timeval	t_last_eating;
	struct timeval	t;
	int				num_eat;
	t_times			time;
	t_mutex			*take_f;
	pthread_mutex_t	*chronicler;
	pthread_mutex_t	*change_status;
	char			*status;
	char			*well_fed;
}	t_philo;

typedef struct s_data
{
	int				total;
	t_times			time;
	int				num_eat;
	char			*all_well_fed;
	char			*all_status;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	t_mutex			*take_f;
	pthread_mutex_t	chronicler;
	pthread_mutex_t	change_status;
	pthread_t		*lives;
}	t_data;

//init.c
int			init_mutex(t_data *data);
int			init_data(int argc, char **argv, t_data *data);
//checker_lifr.c
void		note(t_philo *philo, char *s1, char *s2);
void		*grim_reaper(void *data);
void		*waiter(void *dt);
//time.c
long long	t_usec(struct timeval t_start, struct timeval *t_end);
long long	t_usec_gr(struct timeval t_start);
void		my_usleep(long t_to_sleep, struct timeval t_start, char *condition);
//utils.c
int			is_full(char *s, char c, int n);
int			any_dead(char *s, int n);
void		ft_mutex_lock(t_mutex *mutex);
void		ft_mutex_unlock(t_mutex *mutex);
void		ft_unlock(t_data *data);
//utils2.c
long		ft_getnbr(char *nptr, int k);
int			ft_error(char *str);
//exit.c
void		ft_join(pthread_t *lives, int n);
void		ft_free(t_data *data);
void		ft_exit(t_data *data, int n);
void		ft_destroy(t_data *data);

#endif