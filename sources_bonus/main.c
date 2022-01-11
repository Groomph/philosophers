/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:27:16 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/11 18:27:40 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>

void	clean_program(t_facebook *fb)
{
	if (fb->philos)
		free(fb->philos);
	sem_unlink("forks_nam_nam");
	sem_unlink("displayer");
	sem_unlink("count_meals");
	sem_unlink("death");
	sem_unlink("start_simulation");
	if (fb->display)
		safe_close(fb->display);
	if (fb->count_meals)
		safe_close(fb->count_meals);
	if (fb->death)
		safe_close(fb->death);
	if (fb->start)
		safe_close(fb->start);
	free(fb->pid);
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

static BOOL	init_sem(t_facebook *fb, int forks)
{
	sem_t	*sem;

	sem_unlink("forks_nam_nam");
	sem_unlink("displayer");
	sem_unlink("count_meals");
	sem_unlink("death");
	sem_unlink("start_simulation");
	if (!safe_create(&sem, "forks_nam_nam", forks) || !safe_close(sem))
		return (FALSE);
	if (!safe_create(&(fb->display), "displayer", 1))
		return (FALSE);
	if (!safe_create(&(fb->count_meals), "count_meals", 0))
		return (FALSE);
	if (!safe_create(&(fb->death), "death", 0))
		return (FALSE);
	if (!safe_create(&(fb->start), "start_simulation", 0))
		return (FALSE);
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_facebook	fb;

	memset(&fb, 0, sizeof(fb));
	if (ac != 5 && ac != 6)
		return (error(&fb, FALSE, "Wrong number of arguments\n", 26));
	if (!parse_args(&fb, &(av[1]), ac))
		return (0);
	if (init_sem(&fb, fb.nb))
		launch_thread(&fb, fb.philos);
	clean_program(&fb);
	return (1);
}