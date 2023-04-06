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

int	ft_atoi(const char *str)
{
  int i;
  int sign;
  int res;

  i = 0;
  sign = 1;
  res = 0;
  while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
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

void	send_char(char *str, int pid)
{
	int 	i;
	char	c;

	while (str)
	{
		i = 0;
		c = *str;
		while (i < 8)
		{
			if ((c >> i) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			i++;
			usleep(500);
		}
		str++;
	}
}

void	receive_true(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		ft_printf("Message received\n");
}

int	main(int ac, char **av)
{
	struct sigaction sa;

	sa.sa_sigaction = &receive_true;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (ac != 3)
		return (ft_printf("client usage : ./client [PID] [message]"));
	if (ft_atoi(av[1]) > 0)
		send_char(av[2], ft_atoi(av[1]));
}