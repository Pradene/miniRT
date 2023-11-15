/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:23:31 by lpradene          #+#    #+#             */
/*   Updated: 2022/11/11 14:24:54 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*

< Makefile cat | echo "|" | ls > out >> out2
< Makefile cat | echo "|" | ls > out >> out2
{< Makefile cat} | {echo "|"} | {ls > out >> out2}

{[<], [Makefile], [cat]} 
if tab[i] n'est pas une redirection alors c'est la commande et que count est 0
	count++;
else if tab[i] n'est pas une redirection alors c'est un argument
else tab[i] est une redirection et tab[i + 1] est le fichier

< 			redirection
Makefile	fichier
cat			commande

{[echo], ["|"]} 

echo		commande
"|"			est l'argument



> out

> redirection
out	fichier

commande == NULL;

{[ls] [>] [out] [>>] [out2]}

ls	commande
>	redirection
out	fichier
>>	redirection
out fichier

ls | cat
{ls} | {cat}
{[ls]} | {[cat]}

ls
{ls}






*/