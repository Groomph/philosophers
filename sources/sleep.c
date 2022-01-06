/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:45:14 by rsanchez          #+#    #+#             */
/*   Updated: 2021/12/13 18:55:47 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

int	optimized_msleep(unsigned int ms)
{
	long int	current;
	long int	end;

	end = get_timestamp();
	if (end < 0)
		return (-1);
	end += ms;
	while (1)
	{
		current = get_timestamp();
		if (current < 0)
			return (-1);
		else if (current >= end)
			return (0);
		usleep(100);
		current = get_timestamp();
		if (current < 0)
			return (-1);
		else if (current >= end)
			return (0);
		usleep(100);
	}
	return (0);
}
