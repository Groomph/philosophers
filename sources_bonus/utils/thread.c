/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsanchez <rsanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:18:05 by rsanchez          #+#    #+#             */
/*   Updated: 2022/01/11 18:26:09 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

BOOL	safe_thr_create(pthread_t *thread, void *(f)(void *), void *data)
{
	if (pthread_create(thread, NULL, f, data) != 0)
		return (error(NULL, FALSE, "pthread_create", -1));
	return (TRUE);
}

BOOL	safe_thr_wait(pthread_t thread)
{
	if (pthread_join(thread, NULL) != 0)
		return (error(NULL, FALSE, "pthread_join", -1));
	return (TRUE);
}
