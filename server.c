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

int	len = 0;
unsigned char	c = 0;

unsigned char reverse_bits(unsigned char x) {
	unsigned char	y;
	int				i;
	
	y = 0;
	i = -1;
	while (++i < 8)
	{
		y = (y << 1) | (x & 1);
		x >>= 1;
	}
	return (y);
}

void printBinary(unsigned int num) {
	if (num > 1) {
		printBinary(num / 2);
	}
	ft_printf("%d", num % 2);
}

void	global()
{
	if (len == 7)
	{
		ft_printf("%c", reverse_bits(c));
		len = 0;
		c = 0;
	}
}

void	prt() // SIGUSR2 = 1
{
	len++;
	c++;
	// ft_printf("%d\n", c);
	c = c << 1;
	global();
	
	// ft_printf("%d, %d\n", c, len);
}

void	receive() // SIGURS1 = 0
{
	len++;
	c = c << 1;
	global();

	// ft_printf("%d, %d\n", c, len);
}

int	main(void)
{
	ft_printf("PID : %d\n", getpid());
	signal(SIGUSR2, prt);
	signal(SIGUSR1, receive);
	while (1)
		pause();
}