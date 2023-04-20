/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <nsion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:34:01 by nsion             #+#    #+#             */
/*   Updated: 2023/03/30 19:18:07 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_conf = 1;

void	check(int signal)
{
	if (signal == SIGUSR1)
		g_conf = 1;
	else if (signal == SIGUSR2)
		g_conf = 2;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	send(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_conf = 0;
		if (c & (1 << bit))
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(ft_printf("Error while sending"));
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(ft_printf("Error while sending"));
		}
		bit++;
		while (1)
		{
			if (g_conf == 1)
				break ;
			else if (g_conf == 2)
				exit(ft_printf("Message send!\n"));
		}
	}
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ac != 3)
	{
		exit(ft_printf("Usage: ./client [PID] [message]\n"));
	}
	if (ft_atoi(av[1]) <= 0)
		exit(ft_printf("Wrong PID\n"));
	pid = ft_atoi(av[1]);
	signal(SIGUSR1, check);
	signal(SIGUSR2, check);
	i = 0;
	while (av[2][i])
	{
		send(pid, av[2][i]);
		i++;
	}
	send(pid, '\n');
	send(pid, '\0');
	return (0);
}
