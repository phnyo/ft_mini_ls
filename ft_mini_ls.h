/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:11:17 by fsugimot          #+#    #+#             */
/*   Updated: 2020/12/04 16:22:12 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINI_LS_H
# define FT_MINI_LS_H

# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <time.h>
# include <sys/stat.h>

typedef struct		s_file
{
	char			*filename;
	struct timespec	time;
	struct s_file	*left;
	struct s_file	*right;
}					t_file;

int					ft_strlen(char *str);
char				*ft_strdup(char *str);
char				*ft_strconcat(char *f, char *s);
void				set_t_file(t_file *file, char *filename, \
					struct timespec ctime);
t_file				*init_t_file(t_file *file, char *filename, \
					struct timespec ctime);
void				traverse_tree(t_file *root);
void				set_leaf(t_file *root, char *filename, \
					struct timespec ctime);

#endif
