/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minholee <minholee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:04:43 by minholee          #+#    #+#             */
/*   Updated: 2022/02/21 18:47:23 by minholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_fd(int fd, char *s)
{
	char	*tmp;
	int		count;

	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	count = 1;
	while (!ft_strchr(s, '\n') && count)//카운트가 양수이면서 s에 엔터가 없면 진행
	{
		count = read(fd, tmp, BUFFER_SIZE);//리드 함수 읽은 것만큼 숫자 세고 나감
		if (count == -1)//못 읽었을때
		{
			free(tmp);
			return (NULL);
		}
		tmp[count] = 0;//읽어드릴 버퍼 끝에 널문자 넣기
		s = ft_strjoin(s, tmp);
	}
	free(tmp);
	return (s);
}

static char	*dup_str(char *s)
{
	char	*dest;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s[0])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	len = i + 1;
	if (s[i] == '\n')
		len++;
	dest = (char *)malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

static char	*next_save(char *s)
{
	char	*save;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	len = ft_strlen(s + i + 1);
	save = (char *)malloc(sizeof(char) * (len + 1));
	if (!save)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		save[j++] = s[i++];
	save[j] = '\0';
	free(s);
	return (save);
}

char	*get_next_line(int	fd)//함수 시작
{
	static char	*save;//스태틱 변수 설정(함수가 끝나도 사라지지 않고 처음만 0으로 초기화)
	char		*r;//gnl에서 리턴 하는 값

	if (fd < 0 || BUFFER_SIZE <= 0)//버퍼가 0이하 이거나 파일 디렉션이 음수일경우 예외처리
		return (NULL);
	save = read_fd(fd, save);//리드한후 파일 디렉션에 엔터 까지 복사 그리고 원래있던 스태틱 변수에 붙여넣음
	if (!save)
		return (NULL);
	r = dup_str(save);//복사해서 리턴할 곳에 넣음
	save = next_save(save);//짤린것 세이브
	return (r);
}
