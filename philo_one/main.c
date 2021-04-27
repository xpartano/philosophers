/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:12:02 by jballest          #+#    #+#             */
/*   Updated: 2021/04/27 17:16:44 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	ft_get_time(void)
{
	unsigned long			res;
	static struct timeval	time;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000;
	res += time.tv_usec / 1000;
	return (res);
}

int	finish_philo_meals(int max, t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		if (philos[i]->eat_times < max)
			return (0);
		i++;
	}
	return (1);
}

void	*meal_count(t_scenario *scenario)
{
	while (1)
	{
		if (finish_philo_meals(scenario->philo_maxeat, &scenario->philos))
		{
			printf("\e[1;32m ALL PHILOSOPHERS HAVE SURVIVED! \e[0m");
			pthread_mutex_unlock(&scenario->m_philo_dead);
		}
		usleep(1000);
	}
}

void	*check_death(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->scenario->m_philo_print);
		printf("DIECYCLE\n");
		pthread_mutex_unlock(&philo->scenario->m_philo_print);
		usleep(1000000);
	}
	(void)philo;
}

void	lifecycle(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->scenario->m_philo_print);
		printf("LIFECYCLE\n");
		pthread_mutex_unlock(&philo->scenario->m_philo_print);
		usleep(1000000);
	}
	(void)philo;
}

void	*start_philo_thread(t_philo *philo)
{
	pthread_t	dead_thread;

	philo->last_eat = ft_get_time();
	philo->death_line = philo->death_line + philo->scenario->ttdie;
	pthread_create(&dead_thread, NULL, (void *)&check_death, philo);
	pthread_detach(dead_thread);
	while (1)
		lifecycle(philo);
}

int	philo_threads(t_scenario *scen)
{
	int			i;
	pthread_t	philo_thread;

	scen->init_time = ft_get_time();
	if (scen->philo_maxeat > 0)
	{
		pthread_create(&philo_thread, NULL, (void *)&meal_count, (void *)&scen);
		pthread_detach(philo_thread);
	}
	i = -1;
	while (++i < scen->philon)
	{
		pthread_create(&philo_thread, NULL,
			(void *)&start_philo_thread, (void *)&scen->philos[i]);
		pthread_detach(philo_thread);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_scenario	scenario;
	int			status;

	status = check_arg_errors(argc, argv);
	if (status != 0)
		return (error_return("Program will not start...", status));
	status = init_pm(&scenario, argc, argv);
	if (status != 0)
		return (error_return("Program will not start...", status));
	
	philo_threads(&scenario);
	pthread_mutex_lock(&scenario.m_philo_dead);
	return (0);
}
