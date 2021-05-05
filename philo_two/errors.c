/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:13:48 by jballest          #+#    #+#             */
/*   Updated: 2021/05/04 12:31:46 by jballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_return(char *txt, int ret)
{
	write(1, RED, ft_strlen(RED));
	write(1, txt, ft_strlen(txt));
	write(1, WHITE, ft_strlen(WHITE));
	return (ret);
}

int	check_arg_errors(int argc, char **argv)
{
	if (argc == 1)
		return (error_return("Dude, I can't do magic...", -100));
	if (argc < 5 || argc > 6)
		return (error_return("Error: Wrong number of arguments...", -1));
	if ((ft_atoi(argv[1]) < MIN_PHILO || ft_atoi(argv[1]) > MAX_PHILO
			|| ft_atoi(argv[2]) < MIN_TTDIE
			|| ft_atoi(argv[3]) < MIN_TTEAT
			|| ft_atoi(argv[4]) < MIN_TTSLEEP))
		return (error_return("Error: Invalid init parameters...", -2));
	if (argc == 6)
		if (ft_atoi(argv[5]) < MIN_EATCOUNT)
			return (error_return("Error: Wrong 5th argument...", -3));
	return (0);
}
