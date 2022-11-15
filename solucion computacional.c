//Scheduled Project 2
//Jefferson Sanabria Brenes-2022111213,Carlos Alonso Hernandez Corrales 2022291616, Janys

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20


typedef struct record{
	int id;
	char route[75];
	char description[400];
	char type[60];
}Record;

typedef struct leaf{
	Record data;
	struct leaf *left;
	struct leaf *right;
}Leaf;


typedef struct tree{
	Leaf *root;
}Tree;


typedef struct Chores{
	int id;
	int vertex;
	char description[400];
	char type[40];
	int difficulty;
	int time;
	char leader[100];
	
	Tree *Tree;
}Chores;

typedef struct resource{
	int code;
	char name[60];
	char type[60];
	char size[10];
	int load;
	char leader[50];
		
}Resource;



typedef struct node{
	Chores data;
	Resource resource;
	struct node*next;
}Node;



typedef struct list{
	
int range;
Node *start;

}List;

List *newList();
Tree *newTree();
Node *newChores(Chores data);
Node *newResource(Resource item);
void nMatrix(int matrix[][20]);
Node *searchChores(List *list, int id);
int currentChores(List *list,int choresId);
void addModChoresMenu(List *list);
void resourceMenu(List *list1);
void addChoresMenu(List *list);
void addChores(List *list, Chores item);
void addRecord(Tree *tree, Record rec);
void addResource(List *list1, Resource resource);
void showList(const List *list, int action);
void modChoresMenu(List *list);
void modChores(List *list, int code,Chores input,int action);
void showItemChores(const List *list,int id);
void showTree(Leaf *tree);
void printRec(Record rec);


Node *newChores(Chores item){
  Node *node =(Node *)malloc(sizeof(Node));
  
  node->data.id = item.id;
  strcpy(node->data.description,item.description);
  strcpy(node->data.type,item.type);
  node->data.difficulty=item.difficulty;
  node->data.time = item.time;
  strcpy(node->data.leader,item.leader);
  node->data.vertex=0;

  node->data.Tree = newTree();

  node->next= NULL;
  
  return node;
}

Node *newResource(Resource item){
	Node *node = (Node *)malloc(sizeof(Node));
	
	node->resource.code=item.code;
	strcpy(node->resource.name, item.name);
	strcpy(node->resource.type, item.type);
	strcpy(node->resource.load, item.load);
	node.Resource.size= item.size;
	strcpy(node->resource.leader, item.leader);
	
	node->next= NULL;
	
	return node;
}

List *newList(){
  List *list;

  list = (List *) malloc(sizeof(List));

  list->start=NULL;
  list->range = 0;

  return list;
}

Tree *newTree(){
  Tree *root;

  root = (Tree *) malloc(sizeof(Tree));

  root->root=NULL;


  return root;
}

void nullMatrix(int matrix[][20]){
  int i,j;
  for(i = 0; i < 20; i++){
    for(j = 0; j < 20; j++){
      matrix[i][j] = 0;
    }
  }
}

int existChores(List *list,int choresId){
  Node *aux;
  int values = 0;
  aux = list->start;
  while(aux != NULL){
    if(aux->data.id==choresId){
        values = 1;
        break;
    }
    aux = aux->next;
  }
  
  return values;
}

Node *searchChores(List *list, int id){
  Node *aux;
  
  aux = list->start;
  while(aux != NULL){
    if(aux->data.id == id){
      
      return aux;
    }
    aux = aux->next;
  }
  return NULL;
}


int existRecord(Leaf *tree, int code){
  Leaf *aux = tree;

  if(aux != NULL){
    if(code < aux->data.id ){
      existRecord(aux->left, code);
    }
    else if(code > aux->data.id ){
      existRecord(aux->right, code);
    }
    else{
      
      return 1;
    }
  }
  else{
    return 0;
  }
  
}

void showList(const List *list, int action){
  Node *aux;
  int i = 1;
  if(action == 1){
    for(aux = list->start; aux != NULL; aux = aux->next){
      printf("\nChores: %d \nId: %d \nDescription:\n%s\ntype: %s\ndifficulty: %d\ntime: %d minutes\nLeader: %s\n",i,aux->data.id,
        aux->data.description,aux->data.type,aux->data.difficulty,aux->data.time,aux->data.leader);
      i++;
    }
  }
  else if(action == 2){
    printf("The added project resources are: \n");
    if(list->start==NULL){
      printf("No resources added");
    }
    else{
      for(aux = list->start; aux!= NULL; aux = aux->next){
      
        printf("Resource: %d", i);
        printf("\nID: %d \n", aux->resource.code);
        printf("Name: %s \n", &aux->resource.name);
        printf("Type: %s \n", &aux->resource.type);
        printf("Load: %s \n", &aux->resource.load);
        printf("Size: %d \n", aux->resource.size);
        printf("Leader: %s \n", &aux->resource.leader);
        printf("\n");
        fflush(stdin);
    }
		
	  }
	
	  
  }
  else{
    printf("Error, invalid action");
  }
  printf("\n");
  
}


void printRec(Record rec){
  printf("\nId: %d \nRoute: %s \nDescription: \n%s \nType: %s\n", rec.id,rec.route,rec.description,rec.type);
}


void showTree(Leaf *tree)
{
  if (tree != NULL)
  {
    printRec(tree->data);
    showTree(tree->left);
    showTree(tree->right);
  }
}


void showItemChores(const List *list, int id){
    Node *aux;
    aux = list->start;
    while(aux != NULL){
        if(aux->data.id==id){
            break;
        }
        aux = aux->next;
    }
    if(aux == NULL){
        printf("No se encontro la postal");
    }
    else{
        printf("\n--Id: %d \n", aux->data.id);
        printf("--Description:\n %s \n", &aux->data.description);
        printf("--Type: %s \n", &aux->data.type);
        printf("--Difficult: %d \n", aux->data.difficulty);
        printf("--Time: %d \n", aux->data.time);
        printf("--leader: %s \n", aux->data.leader);
        printf("\n");
        fflush(stdin);
    }
    printf("\n");
}

void addChores(List *list, Chores item){
  Node *n, *aux;
	
	if(list->start == NULL) //Valida si la list esta vacia
	{
		//Inserta al start de la list
		list->start = newChores(item);
    list.range++;
		return;
	}
	n = list->start;
	while(n!= NULL)
	{
		aux = n;
		n = n->next;		
	}
	aux->next = newChores(item);
  list->range++;
  
}

void addRecord(Tree *tree, Record rec)
{
  Leaf *new;
  new = (Leaf *)malloc(sizeof(Leaf));
  new->data.id = rec.id;
  strcpy(new->data.route,rec.route);
  strcpy(new->data.description,rec.description);
  strcpy(new->data.type,rec.type);
  new->left = NULL;
  new->right = NULL;
  if (tree->root == NULL)
    tree->root = new;
  else
  {
    Leaf *prev, *aux;
    prev = NULL;
    aux = tree->root;
    while (aux != NULL)
    {
      prev = aux;
      if (rec.id < aux->data.id)
        aux = aux->left;
      else
        aux = aux->right;
    }
    if (rec.id < prev->data.id)
      prev->left = new;
    else
      prev->right = new;
  }
}

void addResource(List *list1, Resource resource){
	Node *n, *aux;
	
	if(list1->start == NULL) 
	{

		list1->start = newResource(resource);
    list1->range++;
		return;
	}
	n = list1->start;
	while(n!= NULL)
	{
		aux = n;
		n = n->next;		
	}
	aux->next = newResource(resource);
  list1->range++;
	
}


void modChores(List *list, int code,Chores input,int action){
    Node *aux;

    aux= list->start;
    fflush(stdin);
    while( aux != NULL){
        if(aux->data.id == code){
            break;
        }
        aux = aux->next;
    }
    
    if(action == 1){
        
        strcpy(aux->data.description,input.description);
        fflush(stdin);
    }
    else if(action == 2){
        strcpy(aux->data.type,input.type);
        fflush(stdin);
    }
    else if(action == 3){
        aux->data.difficulty= input.difficulty;
        fflush(stdin);
    }
    else if(action == 4){
        aux->data.time = input.time;
        fflush(stdin);
    }
    else if(action == 5){
        strcpy(aux->data.leader,input.leader);
        fflush(stdin);
    }
    else{
        printf("Error, action incorrecta");
    }
}


void modChoresMenu(List *list){
  int option,id;
  char userInput[300];
  Chores item;
  int run = 1, type;
  printf("\n\t---MOD TASK---");
  fflush(stdin);
  do{
    printf("\n----\n");
    
    printf("\n--Please choose an option--\n");
    printf("1- Change description\n");
    printf("2- Change type\n");
    printf("3- Change difficult\n");
    printf("4- Change time required\n");
    printf("5- Change manager\n");
    printf("6- Exit\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      fflush(stdin);
      printf("\nEnter the ID of the task: \n");
      scanf("%d", &id);
      printf("\nThe task is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("\nEnter the new description: \n");
        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        strcpy(item.description, userInput);
        modChores(list,id,item,1);
        printf("The new task is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, The ID doesn't exist\n");
      }

      break;
    case 2:
      fflush(stdin);
      printf("\nEnter the ID of the task: \n");
      scanf("%d", &id);
      printf("\nThe task is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("Please, choose the type of the task:\n1. Operative task \n2. Aprobation task \n3. Contract signature \
          \n4. Management task \n5. Changes\n");
        scanf("%d", &type);
        if(type == 1){
          strcpy(item.type, "Operative task");
        }
        else if(type == 2){
          strcpy(item.type, "Aprobation task");
        }
        else if(type == 3){
          strcpy(item.type, "Contract signature");
        }
        else if(type == 4){
          strcpy(item.type, "Management task");
        }
        else if(type == 5){
          strcpy(item.type, "Changes");
        }
        else{
          printf("Error, invalid type");
          continue;
        }
        modChores(list,id,item,2);
        printf("The new task is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, The ID doesn't exist\n");
      }
      break;
    case 3:
      fflush(stdin);
      printf("\nEnter the ID of the task: \n");
      scanf("%d", &id);
      printf("\nThe task is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("\nEnter the new difficult: \n");
        scanf("%d", &item.difficulty);
        modChores(list,id,item,3);
        printf("The new task is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, The ID doesn't exist\n");
      }

      break;
    case 4:
      fflush(stdin);
      printf("\nEnter the ID of the task: \n");
      scanf("%d", &id);
      printf("\nThe task is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("\nWhat's the time required for the task? \n");
        scanf("%d", &item.time);
        modChores(list,id,item,4);
        printf("The new task is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, The ID doesn't exist\n");
      }

      break;
    case 5:
      fflush(stdin);
      printf("\nEnter the ID of the task: \n");
      scanf("%d", &id);
      printf("\nThe task is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("\nWho's the new leader? \n");
        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        strcpy(item.leader, userInput);
        modChores(list,id,item,5);
        printf("The new task is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, The ID doesn't exist\n");
      }

      break;
    case 6:
      run =0;
      break;
    default:
      break;
    }

  }while(run == 1);
}



/*
Inputs: List (list)
- 
Outputs: none
- 
Exceptions: 
- for all tasks exist only one unique id
*/
//Menu for add tasks option

void addChoresMenu(List *list){
    char userInput[300];
    Chores item;
    int type;
    int run = 1;

    printf("\n\tADD TASKS\n");
    fflush(stdin);
    while(run == 1){
        if(list.range > 20){
          printf("you have passed the limit of tasks");
          break;
        }
        printf("\nPlease, enter an id for the task: ");
        scanf("%d", &item.id);
        if(item.id == 0){
        printf("Error, the id can't be 0");
        }
        if(existChores(list,item.id)==1){
        printf("Error, currently there is a task with that id");
        continue;
        }
        fflush(stdin);
        printf("Please, enter a description: ");
        // For read the input with spaces
        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        // for copy the element
        strcpy(item.description, userInput);
        fflush(stdin);
        printf("Please, choose the type of the task:\n1. Operative task \n2. Aprobation task \n3. Contract signature \
          \n4. Management task \n5. Changes\n");
        scanf("%d", &type);
        if(type == 1){
          strcpy(item.type, "Operative task");
        }
        else if(type == 2){
          strcpy(item.type, "Aprobation task");
        }
        else if(type == 3){
          strcpy(item.type, "Contract signature");
        }
        else if(type == 4){
          strcpy(item.type, "Management task");
        }
        else if(type == 5){
          strcpy(item.type, "Changes");
        }
        else{
          printf("Error, invalid type\n");
          continue;
        }
        printf("In the scale 1 to 100, How difficult is this task?: ");
        scanf("%d", &item.difficulty);
        printf("Please, enter the time required for the task(in minutes): ");
        scanf("%d", &item.time);
        fflush(stdin);
        printf("Who is the manager of this task?: ");
        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        strcpy(item.leader, userInput);

        addChores(list,item);
        
        printf("Do you want add another task? \n0. No \n1. yes\n\n");
        scanf("%d", &run);
  }
  showList(list, 1);

}

void addModChoresMenu(List *list){
  int run = 1,option;

  while(run ==1){
    printf("\nPlease choose an option: \n");
    printf("1. Add task \n2. Modify task \n3. Show tasks \n4. Return to main manu\n");
    scanf("%d", &option);
    switch (option){
    case 1:
      addChoresMenu(list);
      break;
    case 2:
      modChoresMenu(list); break;
    case 3:
      showList(list,1);break;
    case 4:
      run = 0;
      break;
    default:
      printf("Error, invalid option");
      break;
    }
  }
}


void ResourceMenu(List *list1){
	Resource item;
	char entry[50];
	int run = 1;
	
	printf("\n\tAdd Project Resource \n");
	fflush(stdin);
	
	while(run == 1){
	    printf("Enter ID: ");
		fflush(stdin);
		scanf("%d", &item.code);
		
		printf("\nEnter the resource name: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")];
		strcpy(item.name, entry);
		
		printf("Write the resource type: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")];
		strcpy(item.type, entry);
		
		printf("Enter resource capacity: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")];
		strcpy(item.load, entry);
		
		printf("Enter the quantity available: ");
		fflush(stdin);
		scanf("%d", &item.size);
		
		
		printf("Write the name of the leader: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")];
		strcpy(item.leader, entry);
		
		addResource(list1, item);
		
		printf("\nDo you want to add another project resource? \n0: No \n1: Yes\n");
		scanf("%d", &run);
		
	}
    showList(list1,2);

}

void addRecordMenu(List *list, int id){
  char userInput[300];
  Record item;
  int run = 1;
  Node *aux;
  aux = searchChores(list, id);

  printf("\n\tADD Document\n");
  fflush(stdin);
  while(run == 1){
    
    printf("\nPlease, enter an id for the document: ");
    scanf("%d", &item.id);
    if(item.id == 0){
    printf("Error, the id can't be 0");
    }
    if(existRecord(aux->data.Tree->root,item.id)==1){
      printf("Error, currently there is a document with that id\n");
      continue;
    }
    fflush(stdin);
    printf("\nPlease, enter a description: \n");
    // For read the input with spaces
    fgets(userInput, sizeof userInput, stdin);
    userInput[strcspn(userInput, "\n")] = 0;
    // for copy the element
    strcpy(item.description, userInput);
    fflush(stdin);
    printf("\nPlease, enter the type of the document: ");
    fgets(userInput, sizeof userInput, stdin);
    userInput[strcspn(userInput, "\n")] = 0;
    strcpy(item.type, userInput);
    
    printf("\nPlease, enter a path for the document: ");
    fflush(stdin);
    fgets(userInput, sizeof userInput, stdin);
    userInput[strcspn(userInput, "\n")] = 0;
    strcpy(item.route, userInput);

    addRecord(aux->data.Tree,item);
    printRec(item);
    printf("\nDo you want add another document? \n0. No \n1. yes\n\n");
    scanf("%d", &run);
  }
  showTree(aux->data.Tree.root);
}



void recordsEdit(List *list){
  int run = 1,option,code;

  while(run ==1){
    printf("\n\tDOCUMENTS MANAGE \n");
    printf("Please enter an id: ");
    scanf("%d",&code);
    if(existChores(list, code) == 1){

      printf("\nPlease choose an option: \n");
      printf("1. Add document \n2. Modify document\n3. Delete document \n4. Show Documents \n5. Return to main manu\n");
      scanf("%d", &option);
      switch (option){
      case 1:
        addRecordMenu(list, code);
        break;
      case 2:
        break;
      case 3:
        break;
      case 5:
        run = 0;
        break;
      default:
        printf("Error, invalid option");
        break;
      }
    }
    else{
      printf("Error, invalid ID");
      break;
    }
  }
  


}


int main() {
  int option;
  List *choresList, *resourcesList;
	choresList = newList();
  	resourcesList = newList();
	do{
    printf("\n\tAPTEC \n");
    printf("\n");
    printf("1- Add and modify task\n");
    printf("2- Manage documents\n");
    printf("3- Do a critical path\n");
    printf("4- Register proyect resourses\n");
    printf("5- Work Breakdown Structure\n");
    printf("6- Fastest route between tasks\n");
    printf("0- Exit \n");
    printf("\n Please, choose an option and press ENTER: ");
    fflush(stdin);
    scanf("%d", &option);


    switch(option){
      case 1: addModChoresMenu(choresList); break;
      case 2: recordsEdit(choresList);break;

      case 4: ResourceMenu(resourcesList);break;

      case 0:
        exit(0); 
        break;
      default: printf("Error, invalid option\n");
    }
    fflush(stdin);
  }while(1);

  return 0;
}

