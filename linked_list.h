typedef struct node
{
	double value;
	struct node* next;
} node;

node *list_create(double value);
node *list_get(node* list, int index);

int list_length(node* list);

void list_add_at(node** list, int index, double value);
void list_add_start(node** list, double value);
void list_add_end(node** list, double value);
void list_add_middle(node** list, double value);
void list_delete_at(node** list, int index);
void list_free(node* list);
