/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:32:33 by dcaetano          #+#    #+#             */
/*   Updated: 2024/09/23 08:15:36 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	updatevar(t_vars *node, t_exp exp)
{
	if (node == NULL || exp.key == NULL || exp.op == NULL)
		return ;
	if (utils_strcmp(exp.op, "=") == 0)
	{
		if (node->value != NULL)
			free(node->value);
		node->value = ft_strdup(exp.value);
		return ;
	}
	if (node->value == NULL)
	{
		node->value = ft_strdup(exp.value);
		return ;
	}
	node->value = utils_joinfree(node->value, ft_strdup(exp.value));
}

void	vars_export(t_vars **vars, t_exp const exp)
{
	t_vars	*iter;
	t_vars	*node;

	if (vars == NULL || exp.key == NULL)
		return ;
	iter = vars_first(*vars);
	while (iter != NULL)
	{
		if (utils_strcmp(iter->key, exp.key) == 0)
		{
			updatevar(iter, exp);
			return ;
		}
		iter = iter->next;
	}
	node = vars_new2(exp);
	if (node == NULL)
		return ;
	vars_pushback(vars, node);
}
