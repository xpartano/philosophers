/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:12:02 by jballest          #+#    #+#             */
/*   Updated: 2021/05/04 14:28:42 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_philosophers(t_scenario *scen)
{
	int	i;

	i = -1;
	while (++i < scen->philon)
	{
		scen->philos[i].scenario = scen;
		scen->philos[i].id = i;
		scen->philos[i].lfork = i;
		scen->philos[i].rfork = (i + 1) % scen->philon;
		scen->philos[i].is_eating = 0;
		scen->philos[i].eat_times = 0;
		scen->philos[i].death_line = 0;
		if (pthread_mutex_init(&scen->philos[i].m_eating, NULL))
			return (-11);
	}
	return (0);
}

int	init_pm(t_scenario *scen, int argc, char **argv)
{
	int	i;

	scen->philon = ft_atoi(argv[1]);
	scen->ttdie = ft_atoi(argv[2]);
	scen->tteat = ft_atoi(argv[3]);
	scen->ttsleep = ft_atoi(argv[4]);
	if (argc == 6)
		scen->philo_maxeat = ft_atoi(argv[5]);
	scen->philos = (t_philo *)malloc(sizeof(t_philo) * scen->philon);
	if (!scen->philos)
		return (-10);
	if (pthread_mutex_init(&scen->m_philo_print, NULL)
		|| pthread_mutex_init(&scen->m_philo_dead, NULL))
		return (-11);
	scen->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* scen->philon);
	if (!scen->m_forks)
		return (-10);
	i = -1;
	while (++i < scen->philon)
		if (pthread_mutex_init(&scen->m_forks[i], NULL))
			return (-11);
	pthread_mutex_lock(&scen->m_philo_dead);
	return (init_philosophers(scen));
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
	pthread_mutex_unlock(&scenario.m_philo_dead);
	free_everything(&scenario);
	return (0);
}
