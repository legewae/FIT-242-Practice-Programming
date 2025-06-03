typedef struct{
	int* data;
	int size;
	int top;
} stack;

#define DEFAULT_SIZE 10
#define PLUS_SIZE 5

#define SUCCESS 1
#define ERROR -1

stack* stack_create();
int stack_push(stack* st, int value);
int stack_pop(stack* st);
int stack_peek(stack* st);
int stack_increase(stack* st);
void stack_free(stack* st);
int stack_is_empty(stack* st);