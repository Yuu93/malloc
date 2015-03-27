/*
** libmy.h for  in /home/messao_y/malloc_projet
**
** Made by youcef messaoudene
** Login   <messao_y@epitech.net>
**
** Started on  Tue Feb  04 17:20:29 2014 youcef messaoudene
** Last update Tue Feb  04 17:20:29 2014 youcef messaoudene
*/

#ifndef  _LIBMY_H_
#define _LIBMY_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define  BLOCK_SIZE (align64(33))
#define align64(x) (((((x)-1)/8)*8)+8)

void	*malloc(size_t size);

typedef struct s_block
{
	size_t size;
	struct s_block *next;
	struct s_block *prev;
	bool empty;
	void *ptr;
	char data[1];
} t_block;

#endif