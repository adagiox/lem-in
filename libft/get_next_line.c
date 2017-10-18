/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erintala <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:39:59 by erintala          #+#    #+#             */
/*   Updated: 2017/05/08 13:40:11 by erintala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/get_next_line.h"

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*head;
	t_gnl			*node;

	if (!line)
		return (-1);
	if (head == NULL)
		head = gnl_init(fd, head);
	node = gnl_init(fd, head);
	if (contains_newline(node, NULL, line) == 1)
		return (1);
	return (read_line(node, line));
}

int		read_line(t_gnl *node, char **line)
{
	char			*temp;
	char			*holder;
	int				ret;

	temp = ft_strnew(BUFF_SIZE);
	holder = ft_strjoin(node->buf, temp);
	free(temp);
	temp = holder;
	while ((ret = read(node->fd, node->buf, BUFF_SIZE)) > 0)
	{
		holder = ft_strjoin(temp, node->buf);
		free(temp);
		temp = holder;
		if ((contains_newline(node, temp, line)) == 1)
			return (1);
		ft_bzero(node->buf, BUFF_SIZE);
	}
	if (ret == 0 && *temp != 0 && *(node->buf) == 0)
	{
		*line = temp;
		return (1);
	}
	return (ret);
}

char	*get_line(char *buf, char *temp)
{
	int		size;
	char	*line;
	char	*holder;

	size = 0;
	if (temp == NULL)
	{
		while (buf[size] != '\n')
			size++;
		holder = ft_strsub(buf, 0, size);
		line = holder;
		buf = ft_strncpy(buf, &buf[size + 1], BUFF_SIZE);
		return (line);
	}
	while (temp[size] != '\n')
		size++;
	holder = ft_strsub(temp, 0, size);
	line = holder;
	free(temp);
	size = 0;
	while (buf[size] != '\n')
		size++;
	buf = ft_strncpy(buf, &buf[size + 1], BUFF_SIZE);
	return (line);
}

int		contains_newline(t_gnl *node, char *temp, char **line)
{
	char *nl;

	nl = ft_strchr(node->buf, '\n');
	if (nl == NULL)
		return (0);
	if (*nl == '\n')
	{
		*line = get_line(node->buf, temp);
		return (1);
	}
	return (0);
}

t_gnl	*gnl_init(int fd, t_gnl *head)
{
	t_gnl *temp;

	if (head == NULL)
	{
		temp = (t_gnl *)malloc(sizeof(t_gnl));
		temp->fd = fd;
		ft_bzero(temp->buf, BUFF_SIZE + 1);
		temp->next = NULL;
		return (temp);
	}
	while (head->fd != fd && head->next != NULL)
		head = head->next;
	if (head->fd == fd)
		return (head);
	temp = (t_gnl *)malloc(sizeof(t_gnl));
	temp->fd = fd;
	ft_bzero(temp->buf, BUFF_SIZE + 1);
	temp->next = NULL;
	head->next = temp;
	return (temp);
}
