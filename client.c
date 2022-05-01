/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhunter <mhunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:01:58 by mhunter           #+#    #+#             */
/*   Updated: 2022/03/07 17:43:01 by mhunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minitalk.h"

void	ft_update_vars(int	*index, char	*output_char, int sig)
{
	if (sig)
		*output_char += *index;
	*index /= 2;
}

void	ft_handler(int sig)
{
	static int	i = 0;
	static int	index = 128;
	static char	output_char = 0;

	if (sig == g_signal)
	{
		g_signal = 1;
		if (sig == SIGUSR1)
			ft_update_vars(&index, &output_char, 1);
		else
			ft_update_vars(&index, &output_char, 0);
		i++;
		if (i == 8)
		{
			if (output_char == '\n')
				ft_putstr_fd("Line delivered\n", 1);
			i = 0;
			index = 128;
			output_char = 0;
		}
	}
	else
		g_signal = 0;
}

int	send_symbol(char c, int pid)
{
	int	index;

	index = 128;
	while (index >= 1)
	{
		if (c & index)
		{
			g_signal = SIGUSR1;
			kill(pid, SIGUSR1);
		}
		else
		{
			g_signal = SIGUSR2;
			kill(pid, SIGUSR2);
		}
		signal(SIGUSR1, ft_handler);
		signal(SIGUSR2, ft_handler);
		usleep(20);
		if (g_signal)
			index /= 2;
		usleep(20);
	}
	return (0);
}

int	main(int argc, char	*argv[])
{
	int	i;
	int	income_pid;

	if (argc == 3)
	{
		income_pid = ft_atoi(argv[1]);
		i = 0;
		while (argv[2][i])
		{
			send_symbol(argv[2][i], income_pid);
			usleep(150);
			i++;
		}
		send_symbol('\n', income_pid);
	}
	else
		ft_putstr_fd("Error\n", 2);
}
