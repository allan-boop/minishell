/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_factory_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoumer <gdoumer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:33:05 by gdoumer           #+#    #+#             */
/*   Updated: 2024/06/29 14:33:07 by gdoumer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_alloc(int size)
{
	return (malloc_factory(size, NEW, NULL));
}

void	*ft_del_alloc(void *var)
{
	return (malloc_factory(0, DELETE, var));
}

void	*ft_del_all(void)
{
	return (malloc_factory(0, CLEAR, NULL));
}
