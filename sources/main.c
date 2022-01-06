/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:27:16 by rsanchez          #+#    #+#             */
/*   Updated: 2021/12/09 23:59:33 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static void	lave_vaisselle(t_fork *fork, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(&(fork[i]));
		i++;
	}
	free(fork);
}

void	clean_program(t_facebook *fb)
{
	if (fb->philos)
		free(fb->philos);
	if (fb->forks)
		lave_vaisselle(fb->forks, fb->nb);
	pthread_mutex_destroy(&(fb->display));
}

int	error(t_facebook *fb, BOOL clean, const char *str, int size)
{
	write(2, "Error\n", 6);
	if (size > -1)
		write(2, str, size);
	else
		perror(str);
	if (clean)
		clean_program(fb);
	return (0);
}

int	main(int ac, char **av)
{
	t_facebook	fb;

	memset(&fb, 0, sizeof(fb));
	if (ac != 5 && ac != 6)
		return (error(&fb, FALSE, "Wrong number of arguments\n", 26));
	if (!parse_args(&fb, &(av[1]), ac))
		return (0);
	init_buffer(&(fb.buff));
	launch_thread(&fb, fb.philos);
	clean_program(&fb);
	return (1);
}
