/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhunter <mhunter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:35:49 by mhunter           #+#    #+#             */
/*   Updated: 2022/03/07 19:18:46 by mhunter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	s_handler(int signal, siginfo_t *info, void *context)
{
	static int	i = 0;
	static int	index = 128;
	static char	output_char = 0;

	(void)context;
	if (signal == SIGUSR1)
	{
		output_char += index;
		index /= 2;
		i++;
	}
	else
	{
		index /= 2;
		i++;
	}
	if (i == 8)
	{
		write(1, &output_char, 1);
		i = 0;
		index = 128;
		output_char = 0;
	}
	kill(info->si_pid, signal);
}

int	main(void)
{
	int					pid;
	struct sigaction	action;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	ft_memset(&action, 0, sizeof(action));
	action.sa_sigaction = s_handler;
	while (1)
	{
		sigaction(SIGUSR1, &action, 0);
		sigaction(SIGUSR2, &action, 0);
		pause();
		usleep(1);
	}
	return (0);
}
