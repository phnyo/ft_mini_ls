/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 21:28:00 by fsugimot          #+#    #+#             */
/*   Updated: 2020/12/04 16:04:12 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mini_ls.h"

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
			root = init_t_file(root, dirent->d_name, st.st_ctim);
		else
			set_leaf(root, dirent->d_name, st.st_ctim);
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
