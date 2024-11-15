/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:53:23 by locagnio          #+#    #+#             */
/*   Updated: 2024/11/15 20:32:12 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*print_ptr(size_t adr, int *count, char *hexa)
{
	char	*ptr;
	int		i;
	size_t	adr_copy;

	ptr = malloc(18);
	i = 2;
	adr_copy = adr;
	while (adr_copy > 0)
	{
		adr_copy /= 16;
		i++;
	}
	ptr[i--] = '\0';
	*count += i + 1;
	while (adr > 0)
	{
		ptr[i] = hexa[adr % 16];
		adr /= 16;
		i--;
	}
	ptr[i] = 'x';
	i--;
	ptr[i] = '0';
	return(ptr);
}

void	ft_putunbr_fd(int *count, unsigned long n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		*count += 1;
		n = -n;
	}
	if (n > 9)
		ft_putunbr_fd(count, n / 10, fd);
	n = n % 10 + '0';
	*count += 1;
	write(fd, &n, 1);
}

void	ft_putnbr_fd(int *count, long long n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		*count += 1;
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(count, n / 10, fd);
	n = n % 10 + '0';
	*count += 1;
	write(fd, &n, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
