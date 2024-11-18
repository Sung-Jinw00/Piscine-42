/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:05:16 by locagnio          #+#    #+#             */
/*   Updated: 2024/11/18 01:27:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*new_string;
	size_t		len;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	len = ft_bstrlen(s1) + ft_bstrlen(s2) + 1;
	new_string = malloc(len);
	if (!new_string)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		new_string[i++] = s2[j++];
	new_string[i] = '\0';
	return (new_string);
}

void	print_char(t_struct v, int len_field)
{
	int	j;

	j = 0;
	if (!ft_strchr(v.flag_order, '-') || ft_strchr(v.flag_order, '0'))
	{
		while (j + 1 < len_field)
		{
			write(1, " ", 1);
			j++;
		}
		write(1, &(*(char *)v.arg), 1);
	}
	else if (ft_strchr(v.flag_order, '-'))
	{
		write(1, &(*(char *)v.arg), 1);
		while (++j < len_field)
			write(1, " ", 1);
	}
}

void	print_string(t_struct v, int len_field, int i, int trigger)
{
	int	j;
	int	limit;

	j = 0;
	limit = len_field - (int)ft_bstrlen((const char *)v.arg);
	if (special_cases(v, i))
		limit -= v.zerosnb;
	if (len_field == (int)ft_bstrlen((const char *)v.arg) && !special_cases(v, i))
		ft_bputstr_fd((char *)v.arg, 1);
	else if (!ft_strchr(v.flag_order, '-') || ft_strchr(v.flag_order, '0'))
	{
		print_string2(j, limit, v, i);
		if(special_cases(v, i))
			v.nb2 = printfzeronb(v.zerosnb);
		ft_bputstr_fd((char *)v.arg, 1);
	}
	else if (ft_strchr(v.flag_order, '-'))
	{
		j = (int)ft_bstrlen((const char *)v.arg) + v.zerosnb;
		if(special_cases(v, i))
			v.nb2 = printfzeronb(v.zerosnb);
		ft_bputstr_fd((char *)v.arg, 1);
		while (j++ < len_field)
			write(1, " ", 1);
	}
	if (trigger == 1)
		free(v.arg);
}

static void	print_nb2(t_struct v, int len_field, int len_nb, int i)
{
	int	limit_filling;
	int	count;
	int	j;

	j = 0;
	count = 0;
	limit_filling = 0;
	if (ft_strchr(v.flag_order, '0') && !ft_strchr(v.flag_order, '.')
		&& *(long long *)v.arg < 0)
	{
		write(1, "-", 1);
		*(long long *)v.arg = -*(long long *)v.arg;
	}
	if (!ft_strchr(v.flag_order, '-') || ft_strchr(v.flag_order, '0'))
	{
		limit_filling = len_field - len_nb;
		if (ft_strchr(v.flag_order, '.'))
			limit_filling -= v.zerosnb;
		while (j < limit_filling)
		{
			if (ft_strchr(v.flag_order, '0') && !ft_strchr(v.flag_order, '.'))
				write(1, "0", 1);
			else if (ft_strchr(v.flag_order, '0') && ft_strchr(v.flag_order, '.'))
				write(1, " ", 1);
			else if (!(limit_filling == 1 && (ft_strchr(v.flag_order, ' ')
						|| ft_strchr(v.flag_order, '+'))))
				write(1, " ", 1);
			j++;
		}
		if_plus_or_space(v);
		if (!(ft_strchr(v.flag_order, '.') && v.nb2 == 0
			&& *(long long *)v.arg == 0))
			ft_bputnbr_fd(&count, *(long long *)v.arg, 1, v.zerosnb);
		else if (!special_cases(v, i))
			write(1, " ", 1);
	}
}

void	print_nb(t_struct v, int len_field, int i)
{
	int	j;
	int	count;
	int	len_nb;

	j = 0;
	count = 0;
	v = ft_preprint_nb(v);
	len_nb = ft_digits(*(long long *)v.arg);
	if (len_field == len_nb)
		ft_bputnbr_fd(&count, *(long long *)v.arg, 1, v.zerosnb);
	else if (!ft_strchr(v.flag_order, '-') || ft_strchr(v.flag_order, '0'))
		print_nb2(v, len_field, len_nb, i);
	else if (ft_strchr(v.flag_order, '-'))
	{
		if_plus_or_space(v);
		j += v.zerosnb;
		if (!(ft_strchr(v.flag_order, '.') && v.nb2 == 0
			&& *(long long *)v.arg == 0))
			ft_bputnbr_fd(&count, *(long long *)v.arg, 1, v.zerosnb);
		else if (!special_cases(v, i))
			write(1, " ", 1);
		j += len_nb;
		while (j++ < len_field)
			write(1, " ", 1);
	}
}
