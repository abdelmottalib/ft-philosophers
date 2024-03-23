/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_life_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqiouami <aqiouami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:22:46 by aqiouami          #+#    #+#             */
/*   Updated: 2023/02/27 08:26:17 by aqiouami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(t_thread *pthr)
{
	t_thread	*offs;

	if (pthr->current_philo == pthr->common_vars->number_of_philo - 1)
		offs = pthr - pthr->current_philo;
	else
		offs = pthr + 1;
	pthread_mutex_lock(&pthr->fork);
	print_stuff(pthr, "Philosopher", "picked a fork");
	pthread_mutex_lock(&offs->fork);
	print_stuff(pthr, "Philosopher", "picked a fork");
	pthread_mutex_lock(&pthr->common_vars->lock_time);
	print_stuff(pthr, "Philosopher", "is eating");
	pthr->last_meal = timestamp();
	pthr->number_of_meals++;
	pthread_mutex_unlock(&pthr->common_vars->lock_time);
	ft_sleep(pthr->common_vars->time_to_eat);
	pthread_mutex_unlock(&pthr->fork);
	pthread_mutex_unlock(&offs->fork);
}

void	*philosopher(void *ptr)
{
	t_thread	*pthr;

	pthr = (t_thread *)ptr;
	if (pthr->current_philo % 2 != 0)
		ft_sleep(10);
	while (true)
	{
		do_eat(ptr);
		print_stuff(pthr, "Philosopher", "is sleeping");
		ft_sleep(pthr->common_vars->time_to_sleep);
		print_stuff(pthr, "Philosopher", "is thinking");
	}
	return (NULL);
}

void	death(t_thread *pthr)
{
	int	i;

	pthread_mutex_lock(&pthr->common_vars->check_lock);
	while (true)
	{
		pthread_mutex_unlock(&pthr->common_vars->check_lock);
		i = -1;
		while (++i < pthr->common_vars->number_of_philo)
		{
			pthread_mutex_lock(&pthr[i].common_vars->lock_time);
			if ((timestamp() - pthr[i].last_meal > \
			(pthr->common_vars->time_to_die)))
			{
				pthread_mutex_lock(&pthr->common_vars->death);
				pthr->common_vars->state_of_being = DEAD;
				pthread_mutex_unlock(&pthr->common_vars->death);
				print_stuff(&pthr[i], "Philosopher", "has died");
				return ;
			}
			pthread_mutex_unlock(&pthr[i].common_vars->lock_time);
		}
		if (philo_hunger_state(pthr) == true)
			break ;
	}
}

int	count_philo_eaten(t_thread *pthr)
{
	int	i;

	i = 0;
	while (pthr->common_vars->meals != -1)
	{
		if (i < pthr->common_vars->number_of_philo
			&& pthr[i].number_of_meals >= pthr->common_vars->meals)
			i++;
		else
			break ;
	}
	return (i);
}

bool	philo_hunger_state(t_thread *pthr)
{
	int	count;

	count = count_philo_eaten(pthr);
	if (count == pthr->common_vars->number_of_philo)
	{
		pthread_mutex_lock(&pthr->common_vars->check_lock);
		pthr->common_vars->state_of_hunger = FULL;
		pthread_mutex_unlock(&pthr->common_vars->check_lock);
		return (true);
	}
	return (false);
}
