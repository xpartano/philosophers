/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jballest <jballest@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 05:16:57 by jballest          #+#    #+#             */
/*   Updated: 2021/05/04 14:40:10 by jballest         ###   ########.fr       */
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

int	ft_ndigits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
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

char	*ft_itoa(int n)
{
	char			*num;
	unsigned int	onum;
	int				is_negative;
	int				nsize;

	is_negative = n < 0;
	nsize = ft_ndigits(n) + is_negative;
	num = (char *)malloc((nsize + 1) * sizeof(char));
	if (!num)
		return (0);
	if (is_negative)
		onum = -n;
	else
		onum = n;
	num[nsize] = 0;
	if (is_negative)
		num[0] = '-';
	while (--nsize >= is_negative)
	{
		num[nsize] = onum % 10 + 48;
		onum /= 10;
	}
	return (num);
}
