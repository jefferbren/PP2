//Scheduled Project 2
//Jefferson Sanabria Brenes-2022111213,Carlos Alonso Hernandez Corrales 2022291616, Janys Torres Aguero 2022008183

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

//STRUCTS
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

//FUNCTIONS OF THE PRJECT
List *newList();
Tree *newTree();
Node *newChores(Chores data);
Node *newResource(Resource item);
Node *foundVertex(List *list,int vertex);
void loadChores(List *list, FILE *file);
void saveChores(List *list, FILE *file);
void addVertex(List *list);
void nMatrix(int matrix[][20]);
Node *searchChores(List *list, int id);
int currentChores(List *list,int choresId);
void addModChoresMenu(List *list);
void ResourceMenu(List *list1);
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
Leaf* searchTree(Leaf *tree, int id);
Leaf* searchPrev(Leaf *tree, Leaf *prev, int id);
Leaf *minimum(Leaf *node);
Leaf *deleteRecord(Leaf *root, int id);
void deleteRecordMenu(Tree *tree);
void modifyRecordMenu(Tree *tree);
void recordsEdit(List *list);
void printGraph(int graph[][20], int size, List *list);
void addEdge(int graph[][20], int row, int column, int weight);
void criticalPathMenu(List *list, int graph[][20]);
int minKey(int key[], int mstSet[], int range);
int printMST(int parent[], int graph[20][20], int size);
void primMST(int graph[20][20], int size);
void nullMatrix(int matrix[][20]);
int existArray(int vertex, int proceed[20],int size);
void Dijkstra(int graph[20][20], int i, int start, int array[2], int proceed[20] );
void printRoute(int route[2][20], int size,List *list);
void foundRoute(int graph[][20],int route[][20],int start,int final ,int size,List *list);
void fastRouteMenu(List *list, int graph[][20]);
//MAIN MENU
int main() {
  int option;
  List *choresList, *resourcesList;
  FILE *fileChores;
  int graph[MAX][MAX];
  nullMatrix(graph);
	choresList = newList();
  	resourcesList = newList();
  	
  	fileChores = fopen("info\\chores.csv","r+");
  	if(fileChores !=NULL){
  		loadChores(choresList,fileChores);
	  }
	  
	do{
    printf("\n\tAPTEC \n");
    printf("\n");
    printf("1- Add or modify chore\n");
    printf("2- Manage records\n");
    printf("3- Add a critical route\n");
    printf("4- Add proyect resources\n");
    printf("5- WBS\n");
    printf("6- Reccomended route(Fastest)\n");
    printf("0- Exit \n");
    printf("\nSelect an option and press Enter: ");
    fflush(stdin);
    scanf("%d", &option);


    switch(option){
      case 1: addModChoresMenu(choresList); 
        	addVertex(choresList);
        	saveChores(choresList,fileChores);
      		  break;
      case 2: recordsEdit(choresList);break;
	  case 3: criticalPathMenu(choresList, graph);break;
      case 4: ResourceMenu(resourcesList);break;
      case 5: primMST(graph, choresList->range);break;
      case 6:fastRouteMenu(choresList,graph);break;
      case 0:
      	if(choresList->start!=NULL){
      		saveChores(choresList,fileChores);
		  }
        exit(0); 
        break;
      default: printf("Error, invalid option\n");
    }
    fflush(stdin);
  }while(1);

  return 0;
}

//FUNCTIONS FOR MAKE GRAPHS, NODES, LISTS AND VERTEX
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
	node->resource.load = item.load;
	strcpy(node->resource.size,item.size);
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

Node *foundVertex(List *list,int vertex){
	Node *aux;
	aux = list->start;
	while(aux!=NULL){
		if(aux->data.vertex==vertex){
			return aux;
		}
		aux=aux->next;
	}
	return NULL;
}

void addVertex(List *list){
	Node *aux;
	int temp=0;
	aux=list->start;
	while(aux!=NULL){
		aux->data.vertex=temp;
		aux=aux->next;
		temp++;
	}
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
        printf("\nId: %d \n", aux->resource.code);
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
    printf("Error, try again");
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
        printf("Chore not found");
    }
    else{
        printf("\n--Id: %d \n", aux->data.id);
        printf("Description:\n %s \n", &aux->data.description);
        printf("Type: %s \n", &aux->data.type);
        printf("Difficulty: %d \n", aux->data.difficulty);
        printf("Time: %d \n", aux->data.time);
        printf("leader: %s \n", aux->data.leader);
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
        list->range++;
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

Chores dataChores(char *line){
  Chores data;
  char *token;

  token = strtok(line, ",");
  data.id = atoi(token);

  token = strtok(NULL, ",");
  data.vertex= atoi(token);
  
  token = strtok(NULL, ",");
  strcpy(data.description,token);
  
  token = strtok(NULL, ",");
  strcpy(data.type,token);

  token = strtok(NULL, ",");
  data.difficulty = atoi(token);

  token=strtok(NULL,",");
  data.time= atoi(token);

  token = strtok(NULL, ",");
  strcpy(data.leader,token);

  return data;
}


void loadChores(List *list, FILE *file){
  char line[650];
  Chores item;
  
  while(!feof(file)){
      
    fgets(line, 650,file);
    
    if(strcmp(line, "NULL") == 0){
      break;
    }
    item = dataChores(line);
    addChores(list, item);
  }
}

void saveChores(List *list, FILE *file){
 rewind(file);
	Node *aux;
	for(aux = list->start;aux!=NULL;aux=aux->next){
    fflush(file);
		if(aux->next==NULL){
			fprintf(file,"%d,%d,%s,%s,%d,%d,%s", aux->data.id, aux->data.vertex,aux->data.description, aux->data.type, 
        aux->data.difficulty, aux->data.time, aux->data.leader);
		}
		else{
			fprintf(file,"%d,%d,%s,%s,%d,%d,%s\n", aux->data.id, aux->data.vertex,aux->data.description, aux->data.type, 
        aux->data.difficulty, aux->data.time, aux->data.leader);
		}
	}
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
        printf("Error, invalid action");
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
    
    printf("\nSelect a number and press Enter\n");
    printf("1.Modify description\n");
    printf("2.Modify type\n");
    printf("3.Modify difficulty\n");
    printf("4.Modify time required\n");
    printf("5.Modify leader\n");
    printf("6.Exit\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
      fflush(stdin);
      printf("\nEnter the Id of the chore to modify: \n");
      scanf("%d", &id);
      printf("\nThe actual chore is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("\nEnter the new description: \n");
        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        strcpy(item.description, userInput);
        modChores(list,id,item,1);
        printf("The chore modify is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, id not found\n");
      }

      break;
    case 2:
      fflush(stdin);
      printf("\nEnter the Id of the chore to modify: \n");
      scanf("%d", &id);
      printf("\nThe actual chore is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("Please, select the new type:\n1.Operative chore \n2. Aprobation chore \n3. Contract signature \
          \n4. Management chore \n5. Changes\n");
        scanf("%d", &type);
        if(type == 1){
          strcpy(item.type, "Operative chore");
        }
        else if(type == 2){
          strcpy(item.type, "Aprobation chore");
        }
        else if(type == 3){
          strcpy(item.type, "Contract signature");
        }
        else if(type == 4){
          strcpy(item.type, "Management chore");
        }
        else if(type == 5){
          strcpy(item.type, "Changes");
        }
        else{
          printf("Error, invalid selection");
          continue;
        }
        modChores(list,id,item,2);
        printf("The new chore is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, id not found");
      }
      break;
    case 3:
      fflush(stdin);
      printf("\nEnter the Id of the chore: \n");
      scanf("%d", &id);
      printf("\nThe actual chore is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("\nEnter the new difficulty: \n");
        scanf("%d", &item.difficulty);
        modChores(list,id,item,3);
        printf("The modify chore is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, id not found\n");
      }

      break;
    case 4:
      fflush(stdin);
      printf("\nEnter the Id of the chore: \n");
      scanf("%d", &id);
      printf("\nThe actual chore is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("\nEnter the new time required for the chore \n");
        scanf("%d", &item.time);
        modChores(list,id,item,4);
        printf("The new chore is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, id not found\n");
      }

      break;
    case 5:
      fflush(stdin);
      printf("\nEnter the Id of the chore: \n");
      scanf("%d", &id);
      printf("\nThe actual chore is: \n");
      showItemChores(list, id);
      if(existChores(list, id) == 1){
        fflush(stdin);
        printf("\nEnter the new leader \n");
        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        strcpy(item.leader, userInput);
        modChores(list,id,item,5);
        printf("The new chore is: \n");
        showItemChores(list,id);
      }
      else{
        printf("\nError, id not found\n");
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

    printf("\n\tNEW CHORES\n");
    fflush(stdin);
    while(run == 1){
        if(list->range > 20){
          printf("One project only use a maximum of 20 chores");
          break;
        }
        printf("\nEnter the id for the chore: ");
        scanf("%d", &item.id);
        if(item.id == 0){
        printf("Error, 0 cannot be an id");
        }
        if(existChores(list,item.id)==1){
        printf("Error, the id already exist");
        continue;
        }
        fflush(stdin);
        printf("Enter a description: ");
        // For read the input with spaces
        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        // for copy the element
        strcpy(item.description, userInput);
        fflush(stdin);
        printf("Please, select the new type:\n1.Operative chore \n2. Aprobation chore \n3. Contract signature \
          \n4. Management chore \n5. Changes\n");
        scanf("%d", &type);
        if(type == 1){
          strcpy(item.type, "Operative chore");
        }
        else if(type == 2){
          strcpy(item.type, "Aprobation chore");
        }
        else if(type == 3){
          strcpy(item.type, "Contract signature");
        }
        else if(type == 4){
          strcpy(item.type, "Management chore");
        }
        else if(type == 5){
          strcpy(item.type, "Changes");
        }
        else{
          printf("Error, invalid type\n");
          continue;
        }
        printf("What is the difficulty from 1 to 10?: ");
        scanf("%d", &item.difficulty);
        printf("Please, enter the time required for the task(in minutes): ");
        scanf("%d", &item.time);
        fflush(stdin);
        printf("Who is the leader of the chore?: ");
        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;
        strcpy(item.leader, userInput);

        addChores(list,item);
        
        printf("Do you want add more chores? \n0.No \n1.Yes\n\n");
        scanf("%d", &run);
  }
  showList(list, 1);

}

void addModChoresMenu(List *list){
  int run = 1,option;

  while(run ==1){
    printf("\nPlease choose an option: \n");
    printf("1. Add Chores \n2. Modify chores \n3. Show chores \n4. Exit\n");
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
	
	printf("\n\tAdd Resources \n");
	fflush(stdin);
	
	while(run == 1){
	    printf("Enter code: ");
		fflush(stdin);
		scanf("%d", &item.code);
		
		printf("\nEnter the resource name: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")];
		strcpy(item.name, entry);
		
		printf("Enter the resource type: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")];
		strcpy(item.type, entry);
		
		printf("Enter resource load: ");
		fflush(stdin);
		scanf("%d",&item.load);
		
		printf("Enter the size of the resource: ");
		fflush(stdin);
		scanf("%d", &item.size);
		
		
		printf("Write the name of the leader: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")];
		strcpy(item.leader, entry);
		
		addResource(list1, item);
		
		printf("\nDo you want add more resouces? \n0.No \n1.Yes\n");
		scanf("%d", &run);
		
	}
    showList(list1,2);

}


Leaf* searchTree(Leaf *tree, int id){
	Leaf *aux = tree;
	
	if(aux != NULL)
	{
		if(id < aux->data.id){
			searchTree(aux->left, id);
		}
		else if(id > aux->data.id){
			searchTree(aux->right, id);
		}
		else
			return aux;	
	}
	else
		return NULL;	
}

Leaf* searchPrev(Leaf *tree, Leaf *prev, int id){
	Leaf *aux = tree;
	
	if(aux != NULL)
	{
		if(id < aux->data.id){
      prev = aux;
			searchPrev(aux->left,prev,id);
		}
		else if(id > aux->data.id){
      prev = aux;
			searchPrev(aux->right,prev , id);
		}
		else
			return prev;	
	}
	else
		return NULL;	
}

Leaf *minimum(Leaf *node){
    Leaf *min;
    min = node;
    while(min->left != NULL){
        min = min->left;
    }
    if(min != NULL){
        return min;
    }
    else{
        return NULL;
    }


}
Leaf *deleteRecord(Leaf *root, int id)
{
	if (root == NULL) return root;
	
	// Para saber si es hacia la L (es menor)
	if (id < root->data.id)
		root -> left = deleteRecord(root -> left, id);
	
	// Para saber si es hacia la R (es mayor)
	else if (id > root -> data.id)
		root -> right = deleteRecord(root -> right, id);
	
	else
	{
		// Si es sencillo o sin hijos
		if (root -> left == NULL)
		{
			Leaf *aux = root -> right;
			free(root);
			return aux;
		}
		
		else if (root -> right == NULL)
		{
			Leaf *aux = root -> left;
			free(root);
			return aux;
		}
		// Si tiene dos hijos
		Leaf* aux = minimum(root -> right);
		
		// Para copiar el id
		root -> data.id = aux -> data.id;
		// Para eliminar el id
		root -> right = deleteRecord(root -> right, aux->data.id);
	}
	
	return root;
}


void deleteRecordMenu(Tree *tree){
  int id, run = 1;
  Leaf *aux;
  while(run == 1){
    printf("\n\tDELETE RECORD\n");
    printf("\nEnter the id of the record: ");
    scanf("%d", &id);
    
    if(existRecord(tree->root,id)==1){
      aux = searchTree(tree->root, id);
      printf("\nThe record to delete is: \n");
      printRec(aux->data);
      deleteRecord(tree->root,id);
      printf("\nThe delete has been completed\n");

      printf("\nDo you want delete another record? \n1. yes \n0. no\n");
      scanf("%d", &run);
    }
    else{
      printf("\nError, id not found\n");
      continue;
    }
  }

}


void modifyRecordMenu(Tree *tree){
  int option,code, run = 1;
  char input[300];
  Leaf *aux;

  while(run == 1){
    printf("\n\tMODIFY RECORD\n");
    printf("\nEnter an opcion\n");
    printf("1- Modify route\n");
    printf("2- Modify description\n");
    printf("3- Modify type\n");
    printf("4- Return\n");
    scanf("%d", &option);
    if(option == 4){
      break;
    }
    fflush(stdin);
    printf("\nEnter the code\n");
    scanf("%d", &code);
    if(existRecord(tree->root, code) == 1){
      switch (option)
      {
      case 1:
        aux = searchTree(tree->root,code);
        printf("\nThe actual record is: \n");
        printRec(aux->data);
        fflush(stdin);
        printf("\nEnter the new route: \n");
        fgets(input, sizeof input, stdin);
        input[strcspn(input, "\n")] = 0;
        strcpy(aux->data.route,input);
        
        printf("The new record is: \n");
        printRec(aux->data);
        break;
      case 2:
        aux = searchTree(tree->root,code);
        printf("\nThe actual record is: \n");
        printRec(aux->data);
        fflush(stdin);
        printf("\nEnter the new description: \n");
        fgets(input, sizeof input, stdin);
        input[strcspn(input, "\n")] = 0;
        strcpy(aux->data.description,input);
        
        printf("The new record is: \n");
        printRec(aux->data);
        break;
      case 3:
        aux = searchTree(tree->root,code);
        printf("\nThe record is: \n");
        printRec(aux->data);
        fflush(stdin);
        printf("\nEnter the new type: \n");
        fgets(input, sizeof input, stdin);
        input[strcspn(input, "\n")] = 0;
        strcpy(aux->data.type,input);
        
        printf("The new record is: \n");
        printRec(aux->data);
        break;
      default:
        printf("\nError, invalid option\n");
        break;
      }
    }
    else{
      printf("\nError, the record doesn't exist\n");
    }
  }
}


void addRecordMenu(Node *chores){
  char userInput[300];
  Record item;
  int run = 1;

  printf("\n\tADD RECORD\n");
  fflush(stdin);
  while(run == 1){
    
    printf("\nEnter id for the document: ");
    scanf("%d", &item.id);
    if(item.id == 0){
    printf("Error, 0 cannot be an id");
    }
    if(existRecord(chores->data.Tree->root,item.id)==1){
      printf("Error, the id already exist\n");
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
    printf("\nEnter the type of the record: ");
    fgets(userInput, sizeof userInput, stdin);
    userInput[strcspn(userInput, "\n")] = 0;
    strcpy(item.type, userInput);
    
    printf("\nEnter a route for the document: ");
    fflush(stdin);
    fgets(userInput, sizeof userInput, stdin);
    userInput[strcspn(userInput, "\n")] = 0;
    strcpy(item.route, userInput);

    addRecord(chores->data.Tree,item);
    printRec(item);
    printf("\nDo you want add more records? \n0.No \n1.Yes\n\n");
    scanf("%d", &run);
  }
  showTree(chores->data.Tree->root);
}



void recordsEdit(List *list){
  int run = 1,option,code;
  Node *aux;

  while(run ==1){
    printf("\n\tRECORDS MANAGE \n");
    printf("Enter the code: ");
    scanf("%d",&code);
    if(existChores(list, code) == 1){
      aux = searchChores(list, code);
      printf("\nSelect number and press Enter: \n");
      printf("1.Add record \n2.Modify record\n3.Delete record \n4.Show records \n5.Exit\n");
      scanf("%d", &option);
      switch (option){
      case 1:
        addRecordMenu(aux); break;
      case 2:
        break;
      case 3:
        break;
      case 5:
        run = 0;
        break;
      default:
        printf("Error, invalid option"); break;
      }
    }
    else{
      printf("Error, invalid code");
      break;
    }
  }
  
}


void printGraph(int graph[][20], int size, List *list){
  int i, j;
  Node *aux;
  aux = list->start;
  for (i = 0; i < size; i++) {
    
    printf("chores %d: ", aux->data.id);
    for (j = 0; j < size; j++) {
      printf("%d ", graph[i][j]);
    }
    aux = aux->next;
    printf("\n");
  }
}

void addEdge(int graph[][20], int row, int column, int weight){
  graph[row][column] =  weight;
}

void criticalPathMenu(List *list, int graph[][20]){
  int run = 1,option,code,i;
  int aux= list->range;
  Node *chores1,*chores2;
  printf("\n\tCritical route\n");
  while(run ==1){
    printf("Select an option:\n1.New critical path\n 2.Show the actual graph\n 3. exit\n");
    scanf("%d", &option);

    if(option == 1){
      printf("Enter the code of the initial chore: \n");
      scanf("%d",&code);
      if(existChores(list,code)==1){
      chores1 = searchChores(list,code);
      i=0;
      while( i < aux-1){
        printf("\nPlease, enter the code of the next chore: \n");
        scanf("%d",&code);
        if(existChores(list,code)==1){
          chores2 = searchChores(list, code);
          addEdge(graph,chores1->data.vertex,chores2->data.vertex,chores2->data.difficulty);
          chores1= chores2;
          i++;
        
        }
        else{
          printf("\nError, the system cannot found the chore\n");
        }
      }
      }
      else{
        printf("\nError, the system cannot found the chore\n");
      }
    }
    else if(option == 2){
      printGraph(graph, aux, list);
    }
    else if(option == 3){
      break;
    }
    else{
      printf("\nError, invalid option\n");
    }
  }
}

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], int mstSet[], int range)
{
	// Initialize min value
	int min = INT_MAX, min_index;
	int v =0;
	for (v = 0; v < range; v++){
		if (mstSet[v] == 0 && key[v] < min){
			min = key[v], min_index = v;
    }
  }

	return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
int printMST(int parent[], int graph[20][20], int size)
{
	printf("Edge \tWeight\n");
	int i =1;
	for (i = 1; i < size; i++){
		printf("%d - %d \t%d \n", parent[i], i,
			graph[i][parent[i]]);
  }
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int graph[20][20], int size)
{
	// Array to store constructed MST
	int parent[size];
	// Key values used to pick minimum weight edge in cut
	int key[size];
	// To represent set of vertices included in MST
	int mstSet[size];

	// Initialize all keys as INFINITE
	int i =0;
	for (i = 0; i < size; i++){
		key[i] = INT_MAX, mstSet[i] = 0;
  }
	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first
	// vertex.
	key[0] = 0;
	parent[0] = -1; // First node is always root of MST

	// The MST will have V vertices
	int count =0;
	for (count = 0; count < size - 1; count++) {
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, mstSet, size);

		// Add the picked vertex to the MST Set
		mstSet[u] = 1;

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST
		int v=0;
		for (v = 0; v < size; v++)

			// graph[u][v] is non zero only for adjacent
			// vertices of m mstSet[v] is false for vertices
			// not yet included in MST Update the key only
			// if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]){
				parent[v] = u, key[v] = graph[u][v];
      }
	}

	// print the constructed MST
	printMST(parent, graph, size);
}

int existArray(int vertex, int proceed[20],int size){
  int temp=0;

  for(temp = 0; temp <size; temp++){
    if(proceed[temp]==vertex){
      return 1;
    }
  }
  return 0;
}

void Dijkstra(int graph[20][20], int n, int start, int array[2], int proceed[20] ){
  int rate[20][20], largue[20], pred[20];
  int visited[20], temp, mindistance, nextnode,i, j;

  // Creating cost matrix
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (graph[i][j] == 0)
        rate[i][j] = INT_MAX;
      else
        rate[i][j] = graph[i][j];

  for (i = 0; i < n; i++) {
    largue[i] = rate[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  largue[start] = 0;
  visited[start] = 1;
  temp = 1;

  while (temp < n - 1) {
    mindistance = INT_MAX;

    for (i = 0; i < n; i++)
      if (largue[i] < mindistance && !visited[i]) {
        mindistance = largue[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + rate[nextnode][i] < largue[i]) {
          largue[i] = mindistance + rate[nextnode][i];
          pred[i] = nextnode;
        }
    temp++;
  }

  // Printing the distance
  int min = INT_MAX, vertex;
 
  for(i=0;i<n;i++){
    if (i != start) {
      if(largue[i] < min && existArray(i,proceed,n) != 1){
        min = largue[i];
        vertex = i;
        
	    }
    }
  }
	
  array[0]=vertex;
	array[1]= min;
	
}

void nullArray(int array[20]){
  int i;

  for(i = 0;i<MAX;i++){
    array[i]= INT_MAX;  
  }
}

void printRoute(int route[2][20], int size,List *list){
  int i,start,obj;
  Node *chore1,*chore2;
  chore1 = foundVertex(list,route[0][0]);
  chore2= foundVertex(list,route[0][size]);

  start = chore1->data.id;
  obj = chore2->data.id;
  
  printf("The route from %d to %d is: \n",start,obj);
  for(i=0; i<size;i+=2){
    if(i!= 0){
      chore1 = foundVertex(list,route[0][i]);
      chore2 = foundVertex(list,route[0][i+1]);

      start = chore1->data.id;
      obj = chore2->data.id;

      printf("--[%d]-->chore %d--[%d]-->chore %d ",route[1][i],start,route[1][i+1],obj);
    }
    
    else{
      chore1 = foundVertex(list,route[0][i]);
      chore2 = foundVertex(list,route[0][i+1]);

      start = chore1->data.id;
      obj = chore2->data.id;

      printf(" chore %d --[%d]-->chore %d ",start,route[1][i+1],obj);

    }

  }
  chore2 = foundVertex(list,route[0][i]);
  obj = chore2->data.id;

  printf("--[%d]-->chore %d",route[1][i-1],obj);
  
}

void foundRoute(int graph[][20],int route[][20],int start,int final ,int size,List *list){
	int data[2],i, aux, proceed[20], run = 1;
  nullArray(proceed);

  route[0][0]= start;
  route[1][0]= 0;
  proceed[0]= start;
  
  aux = start;
  i=1;
	while(run = 1){
    if(aux!=final){
      Dijkstra(graph,size,aux,data,proceed);
      route[0][i] = data[0];
      route[1][i] = data[1];
      proceed[i]= data[0];
      aux = data[0];
      i++;
    }
    else{
      route[0][i]=final;
      route[1][i] = graph[final][i-1];
      break;
      
    }
	}
  printRoute(route,i-1,list);
}

void fastRouteMenu(List *list, int graph[][20]){
  int run = 1,option,i;
  int aux= list->range;
  int route[2][aux];
  int start, obj;
  Node *chore1,*chore2;
  printf("\n\tRecomended Route\n");
  while(run ==1){
    printf("\nSelect an option: \n1.Recomended route\n2.Exit\n");
    scanf("%d", &option);
    if(option == 1){
      printf("Enter the id of the initial chore: \n");
      scanf("%d",&start);
      if(existChores(list,start)==1){
        chore1 = searchChores(list,start);

        printf("\nEnter the id of the destination chore: \n");
        scanf("%d",&obj);
        
        if(existChores(list,obj)==1){
          chore2 = searchChores(list,obj);

          foundRoute(graph,route,chore1->data.vertex,chore2->data.vertex,aux,list);
        }
        else{
        printf("\nError, the chore doesn't exist\n");
        }
      }
      else{
        printf("\nError, the chore doesn't exist\n");
      }
    }
    else if(option == 2){
      run = 0;
      break;
    }
    else{
      printf("\nError, Invalid option\n");
    }
  }
}

