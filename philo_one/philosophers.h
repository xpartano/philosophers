/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:13:00 by jballest          #+#    #+#             */
/*   Updated: 2021/05/04 13:42:15 by jballest         ###   ########.fr       */
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
# define BLACK "\e[1;30m"
# define RED "\e[1;31m"
# define GREEN "\e[1;32m"
# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define MAGENTA "\e[1;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[0;37m"

typedef struct s_philo
{
	pthread_t			philo_thread;
	pthread_t			dead_thread;

	int					id;
	int					is_eating;
	int					eat_times;
	int					lfork;
	int					rfork;

	unsigned long		death_line;
	unsigned long		last_eat;

	struct s_scenario	*scenario;

	pthread_mutex_t		m_eating;
}t_philo;

typedef struct s_scenario
{
	pthread_t		meals_thread;

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

//	Utils

int				ft_atoi(char *str);
int				ft_strlen(char *str);
char			*ft_itoa(int n);

//	Errors

int				check_arg_errors(int argc, char **argv);
int				error_return(char *txt, int ret);

//	Threads

int				philo_threads(t_scenario *scen);

//	Philosophers utils

unsigned long	ft_get_time(void);
void			print_philo_message(char *col, t_philo *philo,
					char *message, int ret);
void			print_simple_message(char *col, t_scenario *scenario,
					char *message);

//	Philosophers

int				finish_philo_meals(int max, t_scenario *scen);
void			lifecycle(t_philo *philo);
void			free_everything(t_scenario *scen);

#endif