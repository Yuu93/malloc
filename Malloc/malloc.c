/*
** myliblock.c for  in /home/messao_y/malloc_projet
**
** Made by youcef messaoudene
** Login   <messao_y@epitech.net>
**
** Started on  Tue Feb 04 14:22:56 2014 youcef messaoudene
** last_block update Tue Feb 04 14:22:56 2014 youcef messaoudene
*/

#include "libmy.h"

t_block *first_block = NULL;

t_block *void_to_block(void *ptr)
{
	ptr = (char *)ptr - BLOCK_SIZE;
	return (ptr);
}

int check_adress(t_block *p)
 {
 	t_block *tmp;

 if (first_block != NULL)
	{
		tmp = first_block;
	while (tmp != NULL)
		{
			if (tmp->ptr == p->ptr)
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

void free_block (t_block *block)
	{
	 if (block != NULL && block->next == NULL) 
	 	 brk(block);
	 }


t_block *fusion(t_block *b)
{
if (b->next && b->next->empty)
{
b->size += BLOCK_SIZE + b->next->size;
 b->next = b->next ->next;
 if (b->next)
 b->next->prev = b;
 }
 return (b);
 }
 
void free(void *p)
 {	
 	t_block *b;
 	int i;

 	if ((i = check_adress(p)) == 1)
 	{	
 		p = void_to_block(p);
 		b = p;
 		b->empty = 1;
 	if(b->prev && b->prev->empty)
 b = fusion(b->prev);
 if (b->next)
 fusion(b);
 else
 {
 if (b->prev)
 b->prev ->next = NULL;
 else
 first_block = NULL;
 		free_block(b); 
}
}
 }

void *realloc(void *ptr, size_t size)
{
	void 	*p;

	if (ptr == NULL)
		return (NULL);
	p = malloc(size);
	size = align64(size);
	p = memcpy(p, ptr, size);
 	free(ptr);
	return(p);
}

 void *calloc(size_t num_elements, size_t size)
	{
		void *block;

		block = malloc(num_elements * size);
		if (block == NULL)
			return (NULL);
		size = align64(size);
		num_elements = align64(num_elements);
		if (block != NULL)
			block = memset(block, 0, size * num_elements);
		return (block);
	}


t_block		*alloc_memory(t_block *last_block, size_t size)
{
	t_block *block;
	size_t 	pagesize;

	pagesize = getpagesize();
	while (pagesize < size)
		pagesize += pagesize;
	block = sbrk(0);
 	if (sbrk(pagesize) == (void*) -1)
 		return (NULL);
 	block->size = size;
 	block->next = NULL;
 	block->empty = 0;
 	if (last_block != NULL)
		last_block->next = block;
	else
		first_block = block;
	return (block);
}

void		*malloc(size_t size)
{
	t_block *block;
 	size_t 	_size;

 _size = align64(size + BLOCK_SIZE);
 block = alloc_memory(first_block, _size);
 if (block == NULL)
	 return(NULL);
return(block->data);
}