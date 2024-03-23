/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqiouami <aqiouami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:14:40 by aqiouami          #+#    #+#             */
/*   Updated: 2023/02/27 08:26:17 by aqiouami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_thread *pthr, t_common_var *temp)
{
	int	i;

	i = 0;
	while (i < temp->number_of_philo)
	{
		if (pthread_mutex_init(&pthr[i].fork, NULL))
			return (0);
		pthr[i].common_vars = temp;
		pthr[i].last_meal = -1;
		pthr[i].number_of_meals = 0;
		i++;
	}
	return (1);
}

t_common_var	*init_commn_vars(char **av)
{
	t_common_var	*temp;

	temp = malloc(sizeof(t_common_var));
	temp->number_of_philo = ft_atoi(av[1]);
	temp->time_to_die = ft_atoi(av[2]);
	temp->time_to_eat = ft_atoi(av[3]);
	temp->time_to_sleep = ft_atoi(av[4]);
	temp->start_time = timestamp();
	if (pthread_mutex_init(&temp->print, NULL))
		return (NULL);
	if (pthread_mutex_init(&temp->check_lock, NULL))
		return (NULL);
	if (pthread_mutex_init(&temp->lock_time, NULL))
		return (NULL);
	if (pthread_mutex_init(&temp->meal_check, NULL))
		return (NULL);
	if (pthread_mutex_init(&temp->death, NULL))
		return (NULL);
	if (av[5])
		temp->meals = ft_atoi(av[5]);
	else
		temp->meals = -1;
	temp->state_of_hunger = HUNGRY;
	temp->state_of_being = ALIVE;
	return (temp);
}

int	init_philo(t_thread *pthr)
{
	int	i;

	i = 0;
	while (i < pthr->common_vars->number_of_philo)
	{
		pthr[i].current_philo = i;
		pthr[i].last_meal = timestamp();
		if (pthread_create(&pthr[i].th, NULL, &philosopher, &pthr[i]))
			return (0);
		if (pthread_detach(pthr[i].th))
			return (0);
		i++;
	}
	return (1);
}

void	make_thread_mutex(t_thread **thread, char **av)
{
	int	nums;

	nums = ft_atoi(av[1]);
	(*thread) = malloc(sizeof(t_thread) * (nums));
}
