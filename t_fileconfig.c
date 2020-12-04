/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fileconfig.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 15:48:23 by fsugimot          #+#    #+#             */
/*   Updated: 2020/12/04 15:48:53 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

void	set_t_file(t_file *file, char *filename, unsigned long long ctime)
{
	file->filename = ft_strdup(filename);
	file->time = ctime;
	file->left = NULL;
	file->right = NULL;
}

t_file	*init_t_file(t_file *file, char *filename, unsigned long long ctime)
{
	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	set_t_file(file, filename, ctime);
	return (file);
}

void	traverse_tree(t_file *root)
{
	if (root == NULL)
		return ;
	traverse_tree(root->left);
	write(1, root->filename, ft_strlen(root->filename));
	write(1, "\n", 1);
	traverse_tree(root->right);
	free(root->filename);
	free(root);
}

void	set_leaf(t_file *root, char *filename, long long int ctime)
{
	if (root->time < ctime && root->right)
		set_leaf(root->right, filename, ctime);
	else if (root->time < ctime)
		root->right = init_t_file(root->right, filename, ctime);
	else if (root->time > ctime && root->left)
		set_leaf(root->left, filename, ctime);
	else if (root->time > ctime)
		root->left = init_t_file(root->left, filename, ctime);
	else
		root->right = init_t_file(root->right, filename, ctime);
}

