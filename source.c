// datoteka postfix in
// izbaci rezultat na ekran
// postfix shit? javi sintaks error invalid expression
// trazi ime datoteke

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX (32)

typedef struct _Node* Position;
typedef struct _Node {
	int num;
	Position next;
} Node;

char* readFile(char[MAX]);
Position createNode();
int pop(Position);
int push(Position, Position);

int racunaj(Position, char*);

int main() {
	Node stack;
	stack.next = NULL;
	char row[MAX];
	char* postfix;

	printf("\nMolim vas, unesite ime datoteke: ");
	scanf("%s", row);

	postfix = readFile(row);


	racunaj(&stack, postfix);

	printf("\n\t%d\n", stack.next->num);

	return 0;
}

int racunaj(Position stack, char* row) {
	int n = 0;
	char* c = malloc(sizeof(char));
	Position node;
	int a = 0, b = 0;

	while (strlen(row) > 0) {
		sscanf(row, "%c %n", c, &n);
		row += n;

		if (strcmp(c, '+') == 0 || strcmp(c, '*') == 0 || strcmp(c, '-') == 0) {
			a = pop(stack);
			b = pop(stack);
			printf("\n\t%d %d\n", a, b);
			if (strcmp(c, "+") == 0) a += b;
			else if (strcmp(c, "-") == 0) a -= b;
			else a =a * b;

			node = createNode();
			node->num = a;
			push(stack, node);
		}
		else {
			node = createNode();
			node->num = c - '0';
			printf("%d ", node->num);
			push(stack, node);
		}
	}

	return 0;
}








// cita, pop, push, alokacija

char* readFile(char row[MAX]) {
	FILE* ulz;
	strcat(row, ".txt");
	ulz = fopen(row, "r");

	char* postfix = (char*)malloc(MAX * sizeof(char));
	fgets(postfix, MAX, ulz);

	/*while (!feof(ulz)) {
		fgets();
	}*/

	fclose(ulz);
	return postfix;
}

int push(Position stack, Position current) {
	current->next = stack->next;
	stack->next = current;

	return 0;
}

int pop(Position stack) {
	int number = 0;
	number = stack->next->num;

	Position temp;
	temp = stack->next;
	stack->next = stack->next->next;
	free(temp);

	return number;
}

Position createNode() {
	Position temp = malloc(sizeof(Node));
	if (temp == NULL) return NULL;
	else {
		temp->next = NULL;
		return temp;
	}
}
