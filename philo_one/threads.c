/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:26:04 by jballest          #+#    #+#             */
/*   Updated: 2021/05/02 01:43:02 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*meal_count(t_scenario *scenario)
{
	while (1)
	{
		if (finish_philo_meals(scenario->philo_maxeat, scenario))
		{
			error_return("SURVIVED", 1);
			//print_simple_message(scenario, "ALL PHILOSOPHERS HAVE SURVIVED");
			pthread_mutex_unlock(&scenario->m_philo_dead);
			return (NULL);
		}
		usleep(1000);
	}

}

void	*check_death(t_philo *philo)
{
	while (1)
	{
		if (!philo->is_eating && ft_get_time() > philo->death_line)
		{
			print_philo_message(philo, " has died... :(", 1);
			pthread_mutex_unlock(&philo->scenario->m_philo_dead);
		}
		usleep(10);
	}
	(void) philo;
}

void	*start_philo_thread(t_philo *philo)
{
	pthread_t	dead_thread;

	philo->last_eat = ft_get_time();
	philo->death_line = philo->last_eat + philo->scenario->ttdie;
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
		pthread_create(&philo_thread, NULL, (void *)&meal_count, scen);
		pthread_detach(philo_thread);
	}
	i = -1;
	while (++i < scen->philon)
	{
		pthread_create(&philo_thread, NULL,
			(void *)&start_philo_thread, (void *)&scen->philos[i]);
		pthread_detach(philo_thread);
		usleep(1000);
	}
	return (1);
}
