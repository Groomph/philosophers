/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:19:25 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/11 18:31:57 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "buffer.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>

# define BOOL int
# define TRUE 1
# define FALSE 0

typedef pthread_mutex_t	t_fork;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
typedef struct s_philo	t_philo;

enum	e_status
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
};

typedef struct s_facebook
{
	int			nb;
	int			die;
	int			eat;
	int			sleep;
	int			meals;
	t_philo		*philos;
	sem_t		*display;
	sem_t		*count_meals;
	sem_t		*death;
	sem_t		*start;
	pid_t		*pid;
	BOOL		end;
}			t_facebook;

typedef struct s_philo
{
	int			id;
	long int	last_meal;
	int			meals;
	BOOL		is_dead;
	sem_t		*forks;
	sem_t		*display;
	sem_t		*count_meals;
	sem_t		*death;
	sem_t		*start;
	t_facebook	*fb;
	int			(*sleep)(unsigned int ms);
}			t_philo;

void			clean_program(t_facebook *fb);
int				error(t_facebook *fb, BOOL clean, const char *str, int size);
long int		display_status(t_philo *philo, int i, long int ms);
long int		printer(t_philo *philo, int i, long int ms);
long int		get_timestamp(void);
int				optimized_msleep(unsigned int ms);

BOOL			parse_args(t_facebook *fb, char **av, int ac);
BOOL			launch_thread(t_facebook *fb, t_philo *philo);
void			launch_child(t_facebook *fb, t_philo *philo);
void			philo_routine(t_facebook *fb, t_philo *philos);

BOOL			safe_create(sem_t **sem, char *name, int value);
BOOL			safe_open(sem_t **sem, char *name);
BOOL			safe_close(sem_t *sem);

BOOL			safe_thr_create(pthread_t *thread,
					void *(f)(void *), void *data);
BOOL			safe_thr_wait(pthread_t thread);

#endif
