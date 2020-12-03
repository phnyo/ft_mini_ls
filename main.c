/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:28:00 by fsugimot          #+#    #+#             */
/*   Updated: 2020/12/04 00:57:19 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

/*int		is_later(struct timespec *f_time, struct timespec *s_time)
{
	f_time->tv_sec - s_time->tv_sec
}*/
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

	ret = malloc((len = ft_strlen(str)) + 1);
	if (!ret)
		return (NULL);
	ret[len--] = 0;
	while (len > -1)
		ret[len--] = str[len];
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
		str[itr++] = f[itr];
	while (s[itr - f_len])
		str[itr++] = s[itr - f_len];
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
	file = malloc(sizeof(t_file *));
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
		if (!root)
			root = init_t_file(root, dirent->d_name, st.st_ctime);
		set_leaf(root, dirent->d_name, st.st_ctime);	
		free(filename);
		filename = NULL;
	}
	traverse_tree(root);
}

void	ft_mini_ls()
{
	DIR				*dir;
	
	if ((dir = opendir(".")) == NULL)
		return ;
	output_filename(dir);
	closedir(dir);
}

int		main()
{
	ft_mini_ls();
}
