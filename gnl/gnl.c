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
1112
