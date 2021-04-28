/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:39:04 by jballest          #+#    #+#             */
/*   Updated: 2021/04/29 01:46:17 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	philo_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->scenario->m_forks[philo->lfork]);
		print_philo_message(philo, " has taken left fork...", 0);
		pthread_mutex_lock(&philo->scenario->m_forks[philo->rfork]);
		print_philo_message(philo, " has taken right fork...", 0);
	}
	else
	{
		pthread_mutex_lock(&philo->scenario->m_forks[philo->rfork]);
		print_philo_message(philo, " has taken right fork...", 0);
		pthread_mutex_lock(&philo->scenario->m_forks[philo->lfork]);
		print_philo_message(philo, " has taken left fork...", 0);
	}
}

void	philo_drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->scenario->m_forks[philo->lfork]);
		print_philo_message(philo, " dropped left fork...", 0);
		pthread_mutex_unlock(&philo->scenario->m_forks[philo->rfork]);
		print_philo_message(philo, " dropped right fork...", 0);
	}
	else
	{
		pthread_mutex_unlock(&philo->scenario->m_forks[philo->rfork]);
		print_philo_message(philo, " dropped right fork...", 0);
		pthread_mutex_unlock(&philo->scenario->m_forks[philo->lfork]);
		print_philo_message(philo, " dropped left fork...", 0);
	}
}

void	lifecycle(t_philo *philo)
{
	philo_take_forks(philo);
	pthread_mutex_lock(&philo->m_eating);
	print_philo_message(philo, " is eating... Yummy, yummy!", 0);
	philo->eat_times++;
	philo->is_eating = 1;
	usleep(philo->scenario->tteat * 1000);
	philo->last_eat = ft_get_time();
	philo->death_line = philo->last_eat + philo->scenario->ttdie;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->m_eating);
	philo_drop_forks(philo);
	print_philo_message(philo, " is sleeping... Shhh...", 0);
	usleep(philo->scenario->ttsleep * 1000);
	print_philo_message(philo, " is thiniking...", 0);
}

