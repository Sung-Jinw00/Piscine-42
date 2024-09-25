/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:43:52 by locagnio          #+#    #+#             */
/*   Updated: 2024/09/18 12:08:44 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ABS_H
# define FT_ABS_H

# define ABS(Value)			\
({							\
	int	abs = Value;		\
							\
 	if (abs < 0)			\
		(abs = -abs);		\
	else					\
		(abs = abs);		\
		abs;				\
 })
#endif