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

int ft_atoi(const char *str)
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

void            client(int pid, char *str)
{
  int           i;
 
  i = 0;
  while (kill(pid, SIGUSR1))
    {
      while (str[i])
        {
          ft_printf("%c", str[i]);
          i++;
          usleep(15000);
        }
    }
}
 
int             main(int ac, char **av)
{	
	if (ac != 3)
		return (ft_printf("client usage : ./client [PID] [message]"));
	client(ft_atoi(av[1]), av[2]);
}