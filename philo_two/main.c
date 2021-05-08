/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:12:02 by jballest          #+#    #+#             */
/*   Updated: 2021/05/08 03:51:20 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define SEM_FORKS "sem_forks"
#define SEM_PRINT "sem_print"
#define SEM_DEAD "sem_dead"

int	init_philosophers(t_scenario *scen)
{
	int	i;

	i = -1;
	while (++i < scen->philon)
	{
		scen->philos[i].scenario = scen;
		scen->philos[i].id = i;
		scen->philos[i].is_eating = 0;
		scen->philos[i].eat_times = 0;
		scen->philos[i].death_line = 0;
		scen->philos[i].sem_philo_name = ft_itoa(i);
		sem_unlink(scen->philos[i].sem_philo_name);
		scen->philos[i].m_eating = sem_open(scen->philos[i].sem_philo_name,
				O_CREAT, 0644, 1);
	}
	return (0);
}

int	init_pm(t_scenario *scen, int argc, char **argv)
{
	scen->philon = ft_atoi(argv[1]);
	scen->ttdie = ft_atoi(argv[2]);
	scen->tteat = ft_atoi(argv[3]);
	scen->ttsleep = ft_atoi(argv[4]);
	if (argc == 6)
		scen->philo_maxeat = ft_atoi(argv[5]);
	else
		scen->philo_maxeat = 0;
	scen->philos = (t_philo *)malloc(sizeof(t_philo) * scen->philon);
	if (!scen->philos)
		return (-10);
	scen->sem_dead = "sem_dead";
	sem_unlink(scen->sem_dead);
	scen->m_philo_dead = sem_open(scen->sem_dead, O_CREAT, 0644, 0);
	scen->sem_print = "sem_print";
	sem_unlink(scen->sem_print);
	scen->m_philo_print = sem_open(scen->sem_print, O_CREAT, 0644, 1);
	scen->sem_waiter = "sem_waiter";
	sem_unlink(scen->sem_waiter);
	scen->m_waiter = sem_open(scen->sem_waiter, O_CREAT, 0644, 1);
	scen->sem_forks = "sem_forks";
	sem_unlink(scen->sem_forks);
	scen->m_forks = sem_open(scen->sem_forks, O_CREAT, 0644, scen->philon);
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
	sem_wait(scenario.m_philo_dead);
	free_everything(&scenario);
	return (0);
}
