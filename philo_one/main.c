/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:12:02 by jballest          #+#    #+#             */
/*   Updated: 2021/05/02 01:31:32 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	// pthread_mutex_init(&scenario.m_philo_dead, NULL);
	// pthread_mutex_lock(&scenario.m_philo_dead);
	// printf("PRINT THIS LINE\n");
	// // pthread_mutex_lock(&scenario.m_philo_dead);
	// // printf("CANT PRINT THIS LINE\n");
	// // pthread_mutex_unlock(&scenario.m_philo_dead);
	// // pthread_mutex_unlock(&scenario.m_philo_dead);

	// (void)status;
	// (void)argc;
	// (void)argv;
	// free(scenario.m_forks);
	// free(scenario.philos);
	return (0);
}
