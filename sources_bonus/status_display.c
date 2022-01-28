/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 16:22:23 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/28 12:18:31 by rsanchez         ###   ########.fr       */
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
	[FORK] = " has taken a fork\n",
	[EAT] = " is eating\n",
	[SLEEP] = " is sleeping\n",
	[THINK] = " is thinking\n",
	[DEAD] = " died\n"
	};
	t_buff		buff;

	if (ms < 0)
		ms = get_timestamp();
	init_buffer(&buff);
	write_longint_buffer(&buff, ms - philo->start_sim);
	write_char_buffer(&buff, ' ', 1);
	write_longint_buffer(&buff, philo->id);
	write_str_buffer(&buff, status[i], -1);
	print_buffer(&buff, 1);
	return (ms);
}

long int	display_status(t_philo *philo, int i, long int ms)
{
	sem_wait(philo->display);
	ms = printer(philo, i, ms);
	sem_post(philo->display);
	return (ms);
}
