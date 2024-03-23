/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_h.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqiouami <aqiouami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:10:15 by aqiouami          #+#    #+#             */
/*   Updated: 2023/02/27 08:25:27 by aqiouami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_thread		*pthr;
	t_common_var	*temp;

	if (ac != 1 && ac <= 6 && ac >= 5)
	{
		if (!check_validity(av))
			return (0);
		make_thread_mutex(&pthr, av);
		temp = init_commn_vars(av);
		if (!temp)
			return (0);
		if (!init(pthr, temp))
			return (0);
		if (!init_philo(pthr))
			return (0);
		death(pthr);
		destroy_mutex(pthr);
	}
	return (0);
}
