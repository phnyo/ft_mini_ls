/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_ls.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 22:11:17 by fsugimot          #+#    #+#             */
/*   Updated: 2020/12/04 15:40:24 by fsugimot         ###   ########.fr       */
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
	long long		time;
	struct s_file	*left;
	struct s_file	*right;
}					t_file;

#endif
