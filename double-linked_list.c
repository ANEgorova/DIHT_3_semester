#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct __listnode{
	int data;
	struct __listnode *prev;
	struct __listnode *next;
};

#define listnode struct __listnode

typedef struct __list{
	struct __listnode* head;
	struct __listnode* tail;
	size_t size;
} list;

list*	new_list() {
	return (list*)calloc(1, sizeof(list));
}

bool	remove_from_list_by_ptr(list* ls, listnode* node) {
	if (!ls->head || !ls->tail || !node)
		return false;

	if (ls->head == node)
	{
		ls->head = node->next;
		if (node->next)
			node->next->prev = NULL;
	}

	else {
		node->prev->next = node->next;
	}

	if (ls->tail == node) {
		ls->tail = node->prev;
		if (node->prev)
			node->prev->next = NULL;
	}
	else{
		node->next->prev = node->prev;
	}
	free(node);
	ls->size--;
	return true;
}

bool	remove_list(list* ls){
	while (ls->tail){
		remove_from_list_by_ptr(ls, ls->tail);
	}
	free(ls);
	return true;
}

bool	push(list* ls, int data){
	listnode *node = (listnode*)calloc(1, sizeof(listnode));
	node->data = data;
	if (!ls->head) {
		ls->head = node;
		ls->head->next = NULL;
		ls->head->prev = NULL;

	}
	if (ls->tail)
		ls->tail->next = node;
	node->prev = ls->tail;
	ls->tail = node;
	ls->tail->next = NULL;
	ls->size++;
	return true;
}

bool unshift(list* ls, int data){
	listnode *node = (listnode*)calloc(1, sizeof(listnode));
	node->data = data;
	ls->head->prev = node;
	node->next = ls->head;
	ls->head = node;
	ls->head->prev = NULL;
	ls->size++;
	return true;
}

bool pop(list* ls, int* x){
	if (!ls->head)
		return false;
	*x = ls->tail->data;
	ls->tail = ls->tail->prev;
	free(ls->tail->next);
	ls->tail->next = NULL;
	ls->size--;
	return true;
}

bool shift(list* ls, int* x){
	if (!ls->head)
		return false;
	*x = ls->head->data;
	ls->head = ls->head->next;
	free(ls->head->prev);
	ls->head->prev = NULL;
	ls->size--;
	return true;
}

bool reverse(list* ls){
	if (!ls->head)
		return false;
	if (ls->size == 1)
		return true;
	listnode **node = (listnode**)calloc(1, sizeof(listnode*));
	listnode *tmp = (listnode*)calloc(1, sizeof(listnode));
	node = ls->head;
	ls->head->prev = ls->head->next;
	ls->head->next = NULL;
	ls->head = ls->head->prev;
	for (int i = 1; i < ls->size; i++){
		tmp->next = ls->head->next;
		tmp->prev = ls->head->prev;
		ls->head->prev = tmp->next;
		ls->head->next = tmp->prev;
		ls->head = ls->head->prev;
	}
	ls->tail = node;
	free(tmp);
	return true;
}

int main(){
	list* ls = new_list();
	push(ls, 574874);
	//printf("%d\n", ls->head->data);
	push(ls, 245);
	int x;
	shift(ls, &x);
	//printf("%i\n", ls->size);
	unshift(ls, 2323);
	push(ls, 864);
	push(ls, 97);
	//printf("%i\n", x);
	printf("%d\n", ls->size);
	reverse(ls);
	printf("%d\n", ls->head->data);
	system("pause");
	return 0;
}