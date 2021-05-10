/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:17:33 by jballest          #+#    #+#             */
/*   Updated: 2021/05/08 17:48:22 by jballest         ###   ########.fr       */
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

void	print_philo_message(char *col, t_philo *philo, char *message, int ret)
{
	int		t;
	char	*timestamp;
	char	*philoid;

	t = ft_get_time() - philo->scenario->init_time;
	timestamp = ft_itoa(t);
	philoid = ft_itoa(philo->id);
	sem_wait(philo->scenario->m_philo_print);
	write(1, col, ft_strlen(col));
	write(1, timestamp, ft_strlen(timestamp));
	write(1, " Philo ", ft_strlen(" Philo "));
	write(1, philoid, ft_strlen(philoid));
	write(1, message, ft_strlen(message));
	write(1, WHITE, ft_strlen(WHITE));
	write(1, "\n", 1);
	free(timestamp);
	free(philoid);
	if (ret != 1)
		sem_post(philo->scenario->m_philo_print);
}

void	print_simple_message(char *col, t_scenario *scenario, char *message)
{
	sem_wait(scenario->m_philo_print);
	printf("%s", col);
	printf("%s\n", message);
	printf("%s", WHITE);
	sem_post(scenario->m_philo_print);
}

void	free_everything(t_scenario *scen)
{
	int		i;

	i = -1;
	if (scen->m_forks)
	{
		while (++i < scen->philon)
		{
			free(scen->philos[i].sem_philo_name);
			pthread_join(scen->philos[i].philo_thread, NULL);
			pthread_join(scen->philos[i].dead_thread, NULL);
			usleep (10);
		}
	}
	i = 0;
	if (scen->philos)
		free(scen->philos);
	sem_post(scen->m_philo_dead);
}
