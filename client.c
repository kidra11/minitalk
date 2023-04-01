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

//'c' = 0110 0011

void printBinary(unsigned int num, int pid) {
    if (num > 1) {
        printBinary(num / 2, pid);
    }
    if (num % 2 == 1)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	usleep(500);
}

void	client(int pid, char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		c = 128;
		// c = str[i];
		printBinary(c, pid);
	}
}
 
int	main(int ac, char **av)
{	
	if (ac != 3)
		return (ft_printf("client usage : ./client [PID] [message]"));
	if (ft_atoi(av[1]) > 0)
		client(ft_atoi(av[1]), av[2]);
}

// int i = 0;

// 0000 0000
// i += 1;
// 0000 0001
// i = i << 1;
// 1000 0010
// i = i << 8