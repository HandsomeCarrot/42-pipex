/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:15:43 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/08 21:45:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies a function to each element of a list and creates a new list
 *        resulting from the successive applications of the function.
 * 
 * @param lst The address of a pointer to an element.
 * @param f The address of the function used to iterate on the list.
 * @param del The address of the function used to delete the content of
 *  an element if needed.
 * 
 * @return The new list. NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	result = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&result, del);
			ft_lstdelone(new_node, del);
			return (NULL);
		}
		ft_lstadd_back(&result, new_node);
		lst = lst->next;
	}
	return (result);
}

/*#include <stdio.h>
void printContent(void *content)
{
	//int *c = (int *)content;
	//ft_putnbr_fd(*c, 2);
	char *c = (char *)content;
	ft_putstr_fd(c, 2);
	ft_putchar_fd(' ', 2);
}

void *printCopy(void *content)
{
	return (content);
}

void delete(void *content)
{
	free(content);
}

int main(void)
{
	char c[] = "hello";
	char cc[] = "2.2";
	t_list *one = ft_lstnew(&c);
	t_list *two = ft_lstnew(&cc);
	ft_lstadd_back(&one, two);
	printf("first: \n");
	ft_lstiter(one, printContent);
	printf("\nsecond: \n");
	ft_lstiter(two, printContent);
	printf("\nchanged second: \n");
	two = ft_lstmap(one, printCopy, delete);
	ft_lstiter(two, printContent);
}*/