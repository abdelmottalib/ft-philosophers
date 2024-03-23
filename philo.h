/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqiouami <aqiouami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:24:40 by aqiouami          #+#    #+#             */
/*   Updated: 2023/02/27 08:39:22 by aqiouami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state {
	DEAD,
	ALIVE,
	HUNGRY,
	FULL
}t_state;

typedef struct s_common_var
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time;
	int				meals;
	t_state			state_of_hunger;
	t_state			state_of_being;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	lock_time;
	pthread_mutex_t	check_lock;
	pthread_mutex_t	death;
}t_common_var;

typedef struct s_thread
{
	pthread_t		th;
	pthread_mutex_t	fork;
	t_common_var	*common_vars;
	int				current_philo;
	int				number_of_meals;
	long long		last_meal;
}t_thread;

int				init(t_thread *pthr, t_common_var *temp);
t_common_var	*init_commn_vars(char **av);
int				init_philo(t_thread *pthr);
void			make_thread_mutex(t_thread **thread, char **av);
void			do_eat(t_thread *pthr);
void			*philosopher(void *ptr);
void			death(t_thread *pthr);
long long		timestamp(void);
void			ft_sleep(long long microscondes);
void			print_stuff(t_thread *pthr, char *str, char *str2);
void			destroy_mutex(t_thread *pthr);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
int				count_philo_eaten(t_thread *pthr);
bool			philo_hunger_state(t_thread *pthr);
int				check_validity(char **av);

#endif
