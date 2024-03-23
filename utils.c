/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqiouami <aqiouami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:12:17 by aqiouami          #+#    #+#             */
/*   Updated: 2023/02/27 08:26:17 by aqiouami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	long long		sec;
	struct timeval	time;

	gettimeofday(&time, NULL);
	sec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (sec);
}

void	ft_sleep(long long ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(100);
}

void	print_stuff(t_thread *pthr, char *str, char *str2)
{
	long long	time;

	time = timestamp() - pthr->common_vars->start_time;
	pthread_mutex_lock(&pthr->common_vars->print);
	pthread_mutex_lock(&pthr->common_vars->death);
	if (pthr->common_vars->state_of_being == DEAD)
		usleep(15000);
	pthread_mutex_unlock(&pthr->common_vars->death);
	printf("%lld %s %d %s\n", time, str, pthr->current_philo + 1, str2);
	pthread_mutex_unlock(&pthr->common_vars->print);
}

void	destroy_mutex(t_thread *pthr)
{
	int	i;

	i = -1;
	while (++i < pthr->common_vars->number_of_philo)
	{
		pthread_mutex_destroy(&pthr[i].fork);
		pthread_mutex_destroy(&pthr->common_vars->print);
		pthread_mutex_destroy(&pthr[i].common_vars->meal_check);
		pthread_mutex_destroy(&pthr[i].common_vars->lock_time);
	}
}
