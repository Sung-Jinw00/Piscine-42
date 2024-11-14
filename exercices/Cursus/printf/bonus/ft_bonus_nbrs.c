/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: locagnio <locagnio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:50:36 by locagnio          #+#    #+#             */
/*   Updated: 2024/11/14 17:45:25 by locagnio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*  . gerer n'importe quelle combinaison des flags (-0.) et la taille minimale des convertion */
/* 		- sans "-" : %(nombre)(suffixe) (nombre) determine la largeur du champ 
			d'espaces en incluant ce que contient le suffixe a la fin; */

void	ft_string3(int i, int nb, t_struct v, va_list args)
{
	if (v.str[i] == 'p')//si je dois ecrire un pointeur
	{
		v.arg = va_arg(args, void *);
		if (!v.arg)//si j'ai un pointeur null
		{
			nb -= ft_strlen("(nil)");//j'enleve la longueur de (nil)
			while (nb-- > 0)
				write(1, " ", 1);
			write(1, "(nil)", 5);//j'ecris l'erreur
			return ;
		}
		v.arg = print_ptr((size_t)v.arg, -1);//sinon, je converti mon pointeur en hexa
		nb -= ft_strlen((const char *)v.arg);//j'enleve la len de la chaine
		while (nb-- > 0)
			write(1, " ", 1);
		ft_putstr_fd((char *)v.arg, 1);//j'ecris mon pointeur
	}
}

void	ft_string2(int i, int nb, t_struct v, va_list args)
{
	int	k;

	k = 0;
	if (v.str[i] == 's')//si c'est une chaine de characteres
	{
		v.arg = va_arg(args, char *);
		if (!v.arg)//si j'ai une chaine vide
		{
			nb -= ft_strlen("(null)");//j'enleve la longueur de (null)
			while (nb-- > 0)
				write(1, " ", 1);
			write(1, "(null)", 6);//j'ecris l'erreur
			return ;
		}
		nb -= ft_strlen((const char *)v.arg);//sinon jenleve la len de la chaine
		while (nb-- > 0)
			write(1, " ", 1);
		while (((char *)v.arg)[k])//et je l'ecris
			write (1, &((char *)v.arg)[k++], 1);
	}
	else
		ft_string3(i, nb, v, args);
}


void	ft_string(int i, int nb, t_struct v, va_list args)
{
	int	k;
	long long value;

	value = 0;
	k = 0;
	if (v.str[i] == 'X' || v.str[i] == 'x')//si je veux un nombre en hexadecimal
	{
		value = va_arg(args, int);
		if (v.str[i] == 'X')//j'e choisis comment je vais ecrire en hexadecimal
			v.arg = ft_itoa_base(value, "0123456789ABCDEF");
		else
			v.arg = ft_itoa_base(value, "0123456789abcdef");
		nb -= ft_strlen((const char *)v.arg);//j'enleve la longueur de la chaine
		while (nb-- > 0)
			write(1, " ", 1);
		while (((char *)v.arg)[k])//j'ecris la chaine
			write (1, &((char *)v.arg)[k++], 1);
	}
	else
		ft_string2(i, nb, v, args);
}

void	field_width2(int i, int nb, t_struct v, va_list args)
{
	long value;

	value = 0;
	if (v.str[i] == 'u')//si c'est un entier non signé
	{
		value = va_arg(args, int);
		if (value < 0)//j'e choisi le nombre que je vais ecrire
			*(unsigned long *)v.arg = (unsigned long)(value + (long)INT_MAX * 2 + 2);
		else
			*(unsigned long *)v.arg = (unsigned long)value;
		nb -= ft_digits(*(int *)v.arg);//j'enleve la longueur du nombre
		while (nb-- > 0)
			write(1, " ", 1);
		ft_putunbr_fd(-1, *(unsigned long *)v.arg, 1);//j'ecris le nombre
	}
	else if (v.str[i] == 'p' || v.str[i] == 'x' || v.str[i] == 'X' || v.str[i] == 's')//si c'est une chaine de characteres (en puissance)
		ft_string(i, nb, v, args);
}

void	field_width(int i, int nb, t_struct v, va_list args)
{
	if (v.str[i] == 'c' || v.str[i] == '%')//si c'est un caractere
	{
		nb -= 1;//j'enleve un espace
		while (nb-- > 0)
			write(1, " ", 1);
		if (v.str[i] == 'c')//j'e choisis ce que je vais ecrire
			*(char *)v.arg = (char)va_arg(args, int);
		else
			*(char *)v.arg = '%';
		write (1, &*(char *)v.arg, 1);//j'ajoute le caractere
	}
	else if (v.str[i] == 'd' || v.str[i] == 'i')//si c'est des entiers
	{
		*(int *)v.arg = va_arg(args, int);
		nb -= ft_digits(*(int *)v.arg);//j'enleve la longueur de mon chiffre
		while (nb-- > 0)
			write(1, " ", 1);
		ft_putnbr_fd(-1, *(int *)v.arg, 1);//j'ecris mon chiffre
	}
	else
		field_width2(i, nb, v, args);
}

/* si j'ai des chiffres entre 0 et 9 et que le premier est pas 0 */
int	ft_bonus_nbrs(int i, int *count, t_struct v, va_list args)
{
	int i;
	int nb;

	i = i;
	nb = ft_atoi(v.str + i);//je prends la valeur du nombre
	*count += nb;//j'ajoute le nombre de caracteres que je vais ecrire au compteur
	while (v.str[i] >= '0' && v.str[i] <= '9')
		i++;
	field_width(i, nb, v, args);//j'ecris et compte en fonction du type
	return (i + 1);
}
//ex : printf("|%10d|\n", 42)     =     "|        42|"

/*		- avec "-" : %-(nombre)(suffixe) (nombre) determine la largeur du champ 
			d'espaces en incluant ce que contient le suffixe au debut;
		- je peux faire des combinaisons avec ".", cf ci-dessous;
		
		- avec "0" : %0(nombre)(suffixe) affiche (nombre) de zeros en incluant ce que
			contient le suffixe a la fin, si jai un nombre negatif ou que jutilise
			un flag +, le signe est au debut de la suite, les zeros sont remplaces par des
			espaces pour %s, %c et %p;
		
		- avec "." : %.(nombre)(e/g/suffixe) affiche (nombre) de chiffres apres la
			virgule (a besoin d'un nombre apres pour fonctionner);
			* si jai un 'e', je dois ecrire en notation scientifique avec (nombre)
				de chiffres apres la virgule (float, double, long double)
			* si jai un 'g', je dois afficher (nombre) significatifs (pas les zeros) apres
				la virgule (float, double, long double)
			* si jai une chaine de characteres, (nombre) determine le nombre de caracteres
			a afficher;
			*si jessai avec des entiers, le numero affiche des zeros supplementaires si la
			taille donne par (nombre) n'est pas remplie (fonctionne comme '0');


	. gerer tous les flags (# +)
		- avec "+" : %+(nombre)(suffixe) affiche explicitement le signe d'un nombre (signés);
		
		- avec " " : % (nombre)(suffixe) affiche un espace devant un nombre (signé) positif
			sans signe '+' ou '-';
		
		- avec "#" : %#(nombre)(e/g/suffixe)
			* si jai un 'o', je dois rajouter un 0 devant mon chiffre pour specifier la
			base octale
			* si jai un 'x' ou un 'X', je dois rajouter un 0x ou 0X devant mon chiffre
			pour specifier la base hexadecimale.
			* si jai un 'e', un 'g', ou un 'f', je dois garantir d'afficher au moins 1
				nombre apres la virgule (float, double, long double);
			* n'a pas d'effets sur %d, %i, %c et %s;*/