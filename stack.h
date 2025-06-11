typedef struct{
	int* data;
	int size;
	int top;
} stack;

#define SUCCESS 0
#define ERROR -1
#define STACK_OVERFLOW -2

stack* stack_create(int capacity);
int stack_push(stack* st, int value);
int stack_pop(stack* st, int* res);
int stack_peek(stack* st, int* res);
void stack_free(stack* st);
int stack_is_empty(stack* st);

