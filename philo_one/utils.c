/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 05:16:57 by jballest          #+#    #+#             */
/*   Updated: 2021/04/29 01:01:56 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		 i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int	i;
	int	ncnt;
	int	nb;

	i = 0;
	ncnt = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			ncnt++;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if ((ncnt % 2) != 0)
		nb = nb * (-1);
	return (nb);
}

unsigned long	ft_get_time(void)
{
	unsigned long			res;
	static struct timeval	time;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000;
	res += time.tv_usec / 1000;
	return (res);
}

void	print_philo_message(t_philo *philo, char *message, int ret)
{
	long long	t;

	t = ft_get_time() - philo->scenario->init_time;
	pthread_mutex_lock(&philo->scenario->m_philo_print);
	printf("%llu Philo %d %s \n", t, philo->id, message);
	if (ret != 1)
		pthread_mutex_unlock(&philo->scenario->m_philo_print);
}
