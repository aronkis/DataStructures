#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List {
	void* element;

	struct List* next;
	struct List* prev;
};

struct List* list_add_to_end(struct List *head, void* elem) {
	struct List* new_element = malloc(sizeof(struct List));
	new_element->next = NULL;
	new_element->prev = NULL;
	new_element->element = elem;
	
	if (head == NULL) {
		return new_element;
	}

	struct List* original_head = head;

	while (head->next != NULL) {
		head = head->next;
	}

	head->next = new_element;
	new_element->prev = head;

	return original_head;
}

struct List* list_delete_at_end(struct List* head, void ** out_elem) {
	if (out_elem)
		*out_elem = NULL;
	if (head == NULL) {
		return  NULL;
	}

	struct List* original_head = head;

	while (head->next != NULL) {
		head = head->next;
	}

	if (out_elem)
		*out_elem = head->prev->element;
	head->prev->next = NULL;
	head->prev = NULL;
	free(head);

	return original_head;
}

struct List * list_add_to_beginning(struct List* head, void* elem) {
	struct List* new_element = malloc(sizeof(struct List));
	new_element->element = elem;
	new_element->prev = NULL;
	new_element->next = NULL;
	
	if (head == NULL) {
		return new_element;
	}

	head->prev = new_element;
	new_element->next = head;

	return new_element;
}

struct List* list_delete_at_beginning(struct List* head, void** out_elem) {
	if (out_elem)
		*out_elem = NULL;

	if (head == NULL) {
		return NULL;
	}

	struct List* new_head = head->next;
	free(head);

	if (new_head)
		new_head->prev = NULL;

	if (out_elem)
		*out_elem = head->element;

	return new_head;
}

struct List* list_add_at_index(struct List* head, void* elem, int index) {
	if (index == 0)
		return list_add_to_beginning(head, elem);
	
	if (head == NULL)
		return NULL;

	struct List* new_element = malloc(sizeof(struct List));
	new_element->element = elem;
	new_element->next = NULL;
	new_element->prev = NULL;
	
	struct List* original_head = head;

	while (index-- && head->next) {
		head = head->next;
	}

	if (index > 0) {
		return NULL;
	}

	head->next = new_element;
	new_element->prev = head;

	return original_head;
}

struct List* list_delete_at_index(struct List* head, void** out_elem, int index) {
	if (out_elem)
		*out_elem = NULL;
	if (index == 0)
		return list_delete_at_beginning(head, out_elem, index);

	if (head == NULL)
		return NULL;

	struct List* original_head = head;

	while (index-- && head->next) {
		head = head->next;
	}

	if (index > 0) {
		return NULL;
	}

	head->prev->next = head->next;
	head->next->prev = head->prev;
	
	if (out_elem)
		*out_elem = head->element;
	
	free(head);
	return original_head;
}

void* list_get_at_index(struct List* head, int index) {
	while (index-- && head->next) {
		head = head->next;
	}
	
	if (index > 0) {
		return NULL;
	}

	return head->element;
}

void list_free(struct List* head) {
	while (head)
		head = list_delete_at_beginning(head, NULL);
}

typedef (*format_elem)(void* elem, char* buf, int buf_size);

void list_print(struct List* head, format_elem formatter, int buf_size) {
	char *buf = malloc(buf_size);
	while (head) {
		formatter(head->element, buf, buf_size);
		printf("[%s] ", buf);
		head = head->next;
	}
	printf("\n");
	free(buf);
}

void format_int(void* elem, char* buf, int buf_size) {
	if (elem == NULL)
		return;
	
	int* p = (int*)elem;
	snprintf(buf, buf_size, "%d", *p);
}

int main() {
	int x = 3;
	int y = 4;
	int z = 7;
	int q = 8;
	struct List* head = list_add_to_beginning(NULL, &q);
	head = list_add_to_beginning(head, &y);
	head = list_add_to_beginning(head, &x);
	head = list_add_to_beginning(head, &x);
	head = list_add_to_end(head, &z);
	list_print(head, format_int, 100);

	void* third = list_get_at_index(head, 3);
	if (third == NULL) {
		printf("no third element\n");
	}
	else {
		printf("third element: %d\n", *(int*)third);
	}

	head = list_delete_at_index(head, NULL, 3);
	list_print(head, format_int, 100);
	head = list_delete_at_beginning(head, NULL);
	head = list_delete_at_end(head, NULL);
	list_print(head, format_int, 100);
	list_free(head);
}
