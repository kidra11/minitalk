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

int	main(int ac, char **av)
{
	  int pid;
  int i;
  int j;
  char c;

  if (ac != 3)
	{
	  write(1, "Usage: ./client [PID] [message]\n", 32);
	  return (0);
	}
  pid = ft_atoi(av[1]);
  i = 0;
  while (av[2][i])
	{
	  j = 0;
	  c = av[2][i];
	  while (j < 8)
		{
		  if (c & 1)
			kill(pid, SIGUSR1);
		  else
			kill(pid, SIGUSR2);
		  c = c >> 1;
		  j++;
		  usleep(100);
		}
	  i++;
	}
  return (0);
}