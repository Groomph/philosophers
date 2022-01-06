/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:22:23 by rsanchez          #+#    #+#             */
/*   Updated: 2021/12/10 15:20:09 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "buffer.h" 

long int	get_timestamp(void)
{
	t_time		time;
	long int	timestamp;

	if (gettimeofday(&time, NULL) != 0)
	{
		error(NULL, FALSE, "get_timestamp:", -1);
		timestamp = -1;
	}
	else
	{
		timestamp = time.tv_sec * 1000;
		timestamp += (time.tv_usec / 1000);
	}
	return (timestamp);
}

//	printf("%ld %d %s\n", ms, philo->id, status[i]);

long int	printer(t_philo *philo, int i, long int ms)
{
	static char	*status[5] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	if (ms < 0)
		ms = get_timestamp();
	if (!*(philo->is_dead) || i == DEAD)
	{
		write_longint_buffer(philo->buff, ms);
		write_char_buffer(philo->buff, ' ', 1);
		write_longint_buffer(philo->buff, philo->id);
		write_char_buffer(philo->buff, ' ', 1);
		write_str_buffer(philo->buff, status[i], -1);
		write_char_buffer(philo->buff, '\n', 1);
	}
	return (ms);
}

long int	display_status(t_philo *philo, int i, long int ms)
{
	pthread_mutex_lock(philo->display);
	ms = printer(philo, i, ms);
	pthread_mutex_unlock(philo->display);
	return (ms);
}
