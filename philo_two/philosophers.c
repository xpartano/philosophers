/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:39:04 by jballest          #+#    #+#             */
/*   Updated: 2021/05/05 21:54:33 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	finish_philo_meals(int max, t_scenario *scen)
{
	int	i;

	i = 0;
	while (i < scen->philon)
	{
		if (scen->philos[i].eat_times < max)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->scenario->m_forks);
	print_philo_message(WHITE, philo, " has taken a fork...", 0);
	sem_wait(philo->scenario->m_forks);
	print_philo_message(WHITE, philo, " has taken another fork...", 0);
}

void	philo_drop_forks(t_philo *philo)
{
	sem_post(philo->scenario->m_forks);
	print_philo_message(WHITE, philo, " dropped a fork...", 0);
	sem_post(philo->scenario->m_forks);
	print_philo_message(WHITE, philo, " dropped another fork...", 0);
}

void	lifecycle(t_philo *philo)
{
	philo_take_forks(philo);
	sem_wait(philo->m_eating);
	print_philo_message(GREEN, philo, " is eating... Yummy, yummy!", 0);
	philo->is_eating = 1;
	usleep(philo->scenario->tteat * 1000);
	philo->last_eat = ft_get_time();
	philo->death_line = philo->last_eat + philo->scenario->ttdie;
	philo->is_eating = 0;
	philo->eat_times++;
	sem_post(philo->m_eating);
	philo_drop_forks(philo);
	print_philo_message(WHITE, philo, " is sleeping... Shhh...", 0);
	usleep(philo->scenario->ttsleep * 1000);
	print_philo_message(WHITE, philo, " is thinking...", 0);
}
