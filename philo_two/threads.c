/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:26:04 by jballest          #+#    #+#             */
/*   Updated: 2021/05/07 01:24:31 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*meal_count(t_scenario *scenario)
{
	while (1)
	{
		if (finish_philo_meals(scenario->philo_maxeat, scenario))
		{
			sem_wait(scenario->m_philo_print);
			write(1, GREEN, ft_strlen(GREEN));
			write(1, "ALL PHILOSOPHERS SURVIVED!\n",
				ft_strlen("ALL PHILOSOPHERS SURVIVED!\n"));
			write(1, WHITE, ft_strlen(WHITE));
			sem_post(scenario->m_philo_dead);
			return (NULL);
		}
		usleep(10);
	}
}

void	*check_death(t_philo *philo)
{
	while (1)
	{
		if (!philo->is_eating && ft_get_time() > philo->death_line)
		{
			print_philo_message(RED, philo, " has died... :(", 1);
			sem_post(philo->scenario->m_philo_dead);
			break ;
		}
		usleep(10);
	}
	return (NULL);
}

void	*start_philo_thread(t_philo *philo)
{
	philo->last_eat = ft_get_time();
	philo->death_line = philo->last_eat + philo->scenario->ttdie;
	pthread_create(&philo->dead_thread, NULL,
		(void *)&check_death, philo);
	pthread_detach(philo->dead_thread);
	while (1)
		lifecycle(philo);
}

int	philo_threads(t_scenario *scen)
{
	int			i;

	scen->init_time = ft_get_time();
	if (scen->philo_maxeat > 0)
	{
		pthread_create(&scen->meals_thread, NULL,
			(void *)&meal_count, scen);
		pthread_detach(scen->meals_thread);
	}
	i = -1;
	while (++i < scen->philon)
	{
		pthread_create(&scen->philos[i].philo_thread, NULL,
			(void *)&start_philo_thread, (void *)&scen->philos[i]);
		pthread_detach(scen->philos[i].philo_thread);
		usleep(10);
	}
	return (1);
}
