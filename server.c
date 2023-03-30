/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsion <nsion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:33:53 by nsion             #+#    #+#             */
/*   Updated: 2023/03/30 19:29:36 by nsion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void            serveur()
{
  int         pid;
 
  ft_printf("serveur\n");
  pid = getpid();
  ft_printf("getpid%d\n", getpid());
	return (pid);
}

int             main(int ac, char **av)
{
	(void)ac;
	(void)av;
	
	signal(SIGUSR1, serveur);
	ft_printf("main\n");
	while (1);
}