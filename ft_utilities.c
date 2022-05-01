/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhunter <mhunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:19:47 by mhunter           #+#    #+#             */
/*   Updated: 2022/03/07 16:39:20 by mhunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	int long	num;

	num = n;
	if (num < 0)
	{
		num = num * (-1);
		write(fd, "-", 1);
	}
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	c = num % 10 + '0';
	write(fd, &c, 1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!b)
		return (NULL);
	str = b;
	while (i < len)
	{
		str[i] = (char)c;
		i++;
	}
	return (b);
}

int	ft_atoi(const char *str)
{
	int	output;
	int	sign;

	output = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{	
		if (*str == '-')
		{
			sign *= -1;
		}
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		output = output * 10 + (*str - '0');
		str++;
	}
	return (output * sign);
}
