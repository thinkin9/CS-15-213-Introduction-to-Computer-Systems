#include <stdio.h>
#include "queue.h"
int main() {
	queue_t* queue = q_new();
	for (int i = 0; i < 10; i++) {
		q_insert_tail(queue, i);
	}
	printf("%i\n", q_size(queue));
	q_reverse(queue);
	for (int i = q_size(queue); i > 0; i--) {
		printf("%i: ", 10-i);
		int a = 0;
		q_remove_head(queue, &a);
		printf("%i\n", a);
	}
	return 0;
}