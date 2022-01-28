/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:19:25 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/28 15:27:26 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "buffer.h"
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

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
	t_fork		*forks;
	long int	start;
	BOOL		is_end;
	t_buff		buff;
	t_mutex		display;
	t_mutex		checkend;
	pthread_t	thread;

}			t_facebook;

typedef struct s_philo
{
	int			id;
	long int	last_meal;
	int			meals;
	t_fork		*fork1;
	t_fork		*fork2;
	BOOL		*is_dead;
	pthread_t	thread;
	t_facebook	*fb;
	t_buff		*buff;
	t_mutex		*display;
	t_mutex		*checkend;
	t_mutex		getmeals;
	t_mutex		gettimer;
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
void			*even_routine(t_philo *philos);
void			*odd_routine(t_philo *philos);

int				get_meals(t_philo *philo);
void			increment_meals(t_philo *philo);
long int		get_mealtimer(t_philo *philo);
void			set_mealtimer(t_philo *philo, long int timer);
void			set_philoend(t_philo *philo, BOOL end);
BOOL			get_philoend(t_philo *philo);
void			set_fbend(t_facebook *fb, BOOL end);
BOOL			get_fbend(t_facebook *fb);

#endif
