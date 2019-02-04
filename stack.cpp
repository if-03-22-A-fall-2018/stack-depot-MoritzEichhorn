#include "stack.h"

typedef struct _node {
  struct _node* next;
  void* data;
} Node;

struct StackImplementation{
  Node* head;
  int count;
};
/**
 * Used to create a stack structure.
 * @return The newly created stack.
 */
Stack create_stack(){
  Stack new_stack = (Stack)smalloc(sizeof(struct StackImplementation));
  new_stack->head = 0;
  new_stack->count = 0;
  return new_stack;
}

/**
 * Used to free all memory the supplied stack allocated.
 * @param stack The stack to be deleted.
 * @note delete structure, including the struct itself, but not the data!
 */
void delete_stack(Stack stack){
  if(stack!= 0){
    Node* crnt_node = stack->head;
    while(crnt_node != 0){
      Node* delete_node = crnt_node;
      crnt_node = crnt_node->next;
      sfree(delete_node);
    }
    sfree(stack);
  }
}

/**
 * Adds a new node with the supplied data to the top of the stack.
 * @param stack The stack onto which data has to be pushed.
 * @param data The data to be pushed.
 */
void push_stack(Stack stack, void *data){
  Node* new_node = (Node*)smalloc(sizeof(Node));
  new_node->next = stack->head;
  new_node->data = data;
  stack->head = new_node;
  stack->count++;
}

/**
 * @param stack The stack which number of elements to be retrieved.
 * @return The number of items currently on the stack.
 */
int get_count(Stack stack){
  return stack->count;
}

/**
 * Removes and returns the topmost item of the stack.
 * @param stack The stack from which to take.
 * @return The element returned from the stack.
 */
void* pop_stack(Stack stack){
  if(stack == 0 || stack->head == 0){
    return 0;
  }
  Node* delete_node = stack->head;
  void* return_data = delete_node->data;
  stack->head = stack->head->next;
  sfree(delete_node);
  stack->count--;
  return return_data;
}

/**
 * Returns the topmost item of the stack without removing it.
 * @param stack The stack from which to take.
 * @return The element returned from the stack.
*/
void* peek_stack(Stack stack){
  if(stack == 0 || stack->head == 0){
    return 0;
  }
  return stack->head->data;
}
