#include "depot.h"

struct DepotImplementation{
  Stack stacks;
};

Depot create_depot (){
  Depot new_depot = (Depot)smalloc(sizeof(struct DepotImplementation));
  new_depot->stacks = 0;
  return new_depot;
}

void delete_depot (Depot depot){
  while(get_count(depot) > 0){
    Stack d_stack = (Stack)pop_stack(depot->stacks);
    delete_stack(d_stack);
  }
  delete_stack(depot->stacks);
  sfree(depot);
}

void push_depot (Depot depot, Product *product){
  if(depot->stacks == 0){
    depot->stacks = create_stack();
    add_stack(depot,product);
    return;
  }
  Stack last_stack = (Stack)peek_stack(depot->stacks);
  if(get_count(last_stack) == 3){
    add_stack(depot,product);
  }
  else{
    push_stack(last_stack, product);
  }
}

int get_count (Depot depot){
  if(depot->stacks == 0){
    return 0;
  }
  return get_count(depot->stacks);
}

Product * pop_depot (Depot depot){
  Stack last_stack = (Stack)peek_stack(depot->stacks);
  Product* p = (Product*)pop_stack(last_stack);
  if(get_count(last_stack) == 0){
    Stack stack_to_del = (Stack)pop_stack(depot->stacks);
    delete_stack(stack_to_del);
    if(get_count(depot) == 0){
      sfree(depot->stacks);
      depot->stacks = 0;
    }
  }

  return p;
}

void add_stack(Depot depot, Product* product){
  Stack product_stack = create_stack();
  push_stack(product_stack, product);
  push_stack(depot->stacks, product_stack);
}
