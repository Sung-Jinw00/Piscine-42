/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:52:22 by locagnio          #+#    #+#             */
/*   Updated: 2024/11/24 21:48:53 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *s, int *count, int limit)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && i < limit)
	{
		write(1, &s[i], 1);
		*count += 1;
		i++;
	}
}

void	ft_putunbr(unsigned long n, t_struct v)
{
	if (n > 9)
		ft_putunbr(n / 10, v);
	if (!(n == 0 && srch_flag(v.flags, '.') && v.nb2 == 0))
	{
		n = n % 10 + '0';
		write(1, &n, 1);
	}
}

void	ft_putnbr(long n, t_struct v, long base, long print)
{
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	else if (srch_flag(v.flags, '+'))
		write(1, "+", 1);
	else if (srch_flag(v.flags, ' '))
		write(1, " ", 1);
	while (v.zeros-- > 0)
		write(1, "0", 1);
	while (base <= n)
	{
		print = n;
		while (print >= base)
			print /= 10;
		print = print % 10 + '0';
		write(1, &print, 1);
		base *= 10;
	}
	print = n % 10 + '0';
	if (!(n == 0 && srch_flag(v.flags, '.') && v.nb2 == 0))
		write(1, &print, 1);
}

void	ptr_print(size_t nb, t_struct v)
{
	char	*str;
	size_t	nb_cpy;
	size_t	base;

	nb_cpy = nb;
	base = 16;
	str = "0123456789abcdef";
	if (srch_flag(v.flags, '+'))
		write(1, "+", 1);
	else if (srch_flag(v.flags, ' '))
		write(1, " ", 1);
	write(1, "0x", 2);
	while (v.zeros-- > 0)
		write(1, "0", 1);
	while (!(base > nb || base == 0))
	{
		nb_cpy = nb;
		while (nb_cpy >= base)
			nb_cpy /= 16;
		write (1, &str[nb_cpy % 16], 1);
		base *= 16;
	}
	write (1, &str[nb % 16], 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
