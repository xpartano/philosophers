/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:13:00 by jballest          #+#    #+#             */
/*   Updated: 2021/04/26 15:29:41 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# define MIN_PHILO 2
# define MAX_PHILO 200
# define MIN_TTDIE 60
# define MIN_TTEAT 60
# define MIN_TTSLEEP 60
# define MIN_EATCOUNT 1

typedef struct s_philo
{
	int					id;
	int					is_eating;
	int					eat_times;
	int					lfork;
	int					rfork;

	unsigned long		death_line;
	unsigned long		last_eat;

	struct s_scenario	*scenario;

	pthread_mutex_t		m_eating;
	pthread_mutex_t		m_alive;
}t_philo;

typedef struct s_scenario
{
	int				philon;
	unsigned long	ttdie;
	unsigned long	tteat;
	unsigned long	ttsleep;
	int				philo_maxeat;

	unsigned long	init_time;

	t_philo			*philos;

	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_philo_print;
	pthread_mutex_t	m_philo_dead;
}t_scenario;

//	Initializers

int	init_pm(t_scenario *scen, int argc, char **argv);

//	Utils

int	ft_atoi(char *str);
int	ft_strlen(char *str);

//	Errors

int	check_arg_errors(int argc, char **argv);
int	error_return(char *txt, int ret);

#endif