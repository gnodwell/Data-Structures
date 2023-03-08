struct Node 
{
    void *data;
    struct Node *next;
};

typedef struct Node Node;
 
struct Performance
{
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
};


struct Performance *newPerformance();

void push(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);

void readHead(struct Performance *performance, Node **list_ptr, void *dest, unsigned int width);

void pop(struct Performance *performance, Node **list_ptr, void *dest, unsigned int width);

Node **next(struct Performance *performance, Node **list_ptr);

int isEmpty(struct Performance *performance, Node **list_ptr);

void freeList(struct Performance *performance, Node **list_ptr);

void readItem(struct Performance *performance, Node **list_ptr, unsigned int index, void *dest, unsigned int width);

void appendItem(struct Performance *performance, Node **list_ptr, void *src, unsigned int width);

void insertItem(struct Performance *performance, Node **list_ptr, unsigned int index, void *src, unsigned int width);

void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);

void deleteItem(struct Performance *performance, struct Node **list_ptr, unsigned int index );

int cmp(const void *v1, const void *v2);

int findItem( struct Performance *performance, struct Node **list_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width);

int findSize (struct Performance *performance, Node **list_ptr);


