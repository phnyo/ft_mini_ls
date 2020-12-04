/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:28:00 by fsugimot          #+#    #+#             */
/*   Updated: 2020/12/04 15:45:13 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

int		ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		len++;
	return (len);
}

char	*ft_strdup(char *str)
{
	int		len;
	char	*ret;

	len = ft_strlen(str);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[len] = 0;
	len--;
	while (len > -1)
	{
		ret[len] = str[len];
		len--;
	}
	return (ret);
}

char	*ft_strconcat(char *f, char *s)
{
	int		total_len;
	int		f_len;
	int		itr;
	char	*str;

	total_len = ft_strlen(f) + ft_strlen(s);
	if ((str = malloc(total_len + 1)) == NULL)
		return (NULL);
	str[total_len] = 0;
	itr = 0;
	f_len = ft_strlen(f);
	while (f[itr] != 0)
	{
		str[itr] = f[itr];
		itr++;
	}
	while (s[itr - f_len])
	{
		str[itr] = s[itr - f_len];
		itr++;
	}
	return (str);
}

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

void	output_filename(DIR *dir)
{
	struct dirent	*dirent;
	t_file			*root;
	struct stat		st;
	char			*filename;

	root = NULL;
	while ((dirent = readdir(dir)) != NULL)
	{
		if (dirent->d_name[0] == '.')
			continue;
		lstat((filename = ft_strconcat("./", dirent->d_name)), &st);
		if (filename == NULL)
			break ;
		if (!root)
			root = init_t_file(root, dirent->d_name, st.st_ctime);
		else
			set_leaf(root, dirent->d_name, st.st_ctime);
		free(filename);
	}
	traverse_tree(root);
}

void	ft_mini_ls(void)
{
	DIR				*dir;

	if ((dir = opendir(".")) == NULL)
		return ;
	output_filename(dir);
	closedir(dir);
}

int		main(int argc, char **argv)
{
	if (argc != 1 && argv[0])
		write(2, "Do not execute with commandline arguments.", 42);
	ft_mini_ls();
}

