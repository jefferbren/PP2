//Scheduled Project 2
//Jefferson Sanabria Brenes-2022111213,Carlos Alonso Hernandez Corrales 2022291616, Janys Torres Aguero 2022008183

//Libraries
//stdio.h library is used to include the inputs and ouputs related functions.
#include <stdio.h>

//stdlib.h library is used to work with memory allocations, process controls, etc.
#include <stdlib.h>

//string.h library is used to work with constants and declarations of several functions and types.
#include <string.h>

//limits.h library is used to define several minimun and maximun values.
#include<limits.h>

//Structs
//This structure is made to store the information of the documents associated with chores, called records.
typedef struct record{
  int task;
  int parent;
	int id;
	char route[75];
	char description[400];
	char type[60];
}Record;

//This structure is made to simulate the nodes of a binary tree.
typedef struct leaf{
	Record data;
	struct leaf *left;
	struct leaf *right;
}Leaf;

//This structure is made to simulate a binary tree.
typedef struct tree{
	Leaf *root;
}Tree;

//This structure is made to store the information of the projects, called chores.
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

//This structure is made to store the information of the resources of the chores.
typedef struct resource{
	int code;
	char name[60];
	char type[60];
	char size[10];
	int load;
	char leader[50];
		
}Resource;

//This structure is made to work with several data as nodes.
typedef struct node{
	Chores data;
	Resource resource;
	Record record;
	struct node*next;
}Node;

//This structure is made to store data in lists.
typedef struct list{
	
int range;
Node *start;

}List;

//Here are the several functions used later in the program, thye are called here so in that way, later they work easier.
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
void addRecord(Tree *tree, Record rec, int task);
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
void recordsEdit(List *list, FILE *file);
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
void loadResources(List *list, FILE *file);
void saveResources(List *list, FILE *file);
void loadGraph(int graph[][20], FILE *file,int size);
void saveGraph(int graph[][20], FILE *file,int size);
int isNullGraph(int graph[][20],int size);
void saveTree (Leaf *tree,Leaf *root, FILE *file);
void loadTree(List *list, FILE *file);
void convertList(List *tree, List *chores);


/*Main console menu that appear once the program is executed
> Inputs:
- option (int)
> Outputs:
case 1 | case 2 | case 3 | case 4 | case 5 | case 6
> Restrictions:
- option must be int */
int main() {
  int option;
  List *choresList, *resourcesList, *listTree;
  FILE *fileChores,*fileResources,*fileGraph, *fileTree;
  int graph[20][20];
  nullMatrix(graph);
	choresList = newList();
  	resourcesList = newList();
  	listTree= newList();
  	
  	fileChores = fopen("info\\chores.csv","r+");
  	fileResources=fopen("info\\resources.csv","r+");
  	fileGraph=fopen("info\\graph.csv","r+");
  	fileTree=fopen("info\\tree.csv","r+");
  	if(fileChores !=NULL){
  		loadChores(choresList,fileChores);
	  }
	if(fileResources !=NULL){
  		loadResources(resourcesList,fileResources);
	  }
	if(fileGraph !=NULL){
  		loadGraph(graph,fileGraph,choresList->range);
	  }  
	if (fileTree != NULL){
	    loadTree(listTree,fileTree);
	    if(listTree->start != NULL){
	    	convertList(listTree,choresList);
		}
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
      case 2: recordsEdit(choresList,fileTree);
        break;
      		
	    case 3: 
        if(choresList->start!=NULL){
          criticalPathMenu(choresList, graph);
          saveGraph(graph,fileGraph,choresList->range);
        }
        else{
          printf("\nError, you didn't add chores\n");
        }
        break;
      case 4: 
        ResourceMenu(resourcesList);
        saveResources(resourcesList, fileResources);
        break;
      case 5: if(isNullGraph(graph,choresList->range)!=0){
          primMST(graph, choresList->range);
        }
        else{
          printf("\nError, you didn't add a critical path\n");
        }
        break;
      case 6:fastRouteMenu(choresList,graph);break;
      case 0:
      	if(choresList->start!=NULL){
      		saveChores(choresList,fileChores);
          if(isNullGraph(graph,choresList->range)!=0){
            saveGraph(graph,fileGraph,choresList->range);
          }
          Node *aux;
          rewind(fileTree);
          for(aux= choresList->start;aux!=NULL;aux = aux->next){
          	if(aux->data.Tree->root!=NULL){
          	saveTree(aux->data.Tree->root,aux->data.Tree->root, fileTree);
          }
		      }
		    }
        if(resourcesList->start !=NULL){
          saveResources(resourcesList, fileResources);
        }
        
        exit(0); 
        break;
      default: printf("Error, invalid option\n");
    }
    fflush(stdin);
  }while(1);

  return 0;
}

//Functions to make graphs, nodes, lists and vertices
//This function is used to make new chores.
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

//This function is used to make new resources of chores.
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

//This function is used to make new lists to store the different data.
List *newList(){
  List *list;

  list = (List *) malloc(sizeof(List));

  list->start=NULL;
  list->range = 0;

  return list;
}

//This function is used to make new binary trees.
Tree *newTree(){
  Tree *root;

  root = (Tree *) malloc(sizeof(Tree));

  root->root=NULL;


  return root;
}

//This function is used to search for any vertices created.
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

/*This function is used to make new vertices.
> Inputs:
- temp (int)
> Outputs:
- vertex added
> Restrictions:
- temp must be int*/
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

/*This function is used to work with different matrices.
> Inputs:
- i (int)
- j (int)
> Outputs:
- matrix
> Restrictions:
- i && j must be int*/
void nullMatrix(int matrix[][20]){
  int i,j;
  for(i = 0; i < 20; i++){
    for(j = 0; j < 20; j++){
      matrix[i][j] = 0;
    }
  }
}

/*This function is used to work with different graphs.
> Inputs:
- i (int)
- j (int)
> Outputs:
- 1 | 0 (int)
> Restrictions:
- i && j must be int*/
int isNullGraph(int graph[][20],int size){
  int i,j;
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      if(graph[i][j] != 0){
        return 1;
      } 
    }
  }
  return 0;
}

/*This function is used to evaluate the existence of the different chores.
> Inputs:
- values (int)
> Outputs:
- values (int)
> Restrictions:
- vlues must be int*/
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

//This function is used to search for a specific chore.
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

//This function is used to evaluate the existence of the different records.
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

/*This function is used to make the program display the corresponding list.
> Inputs:
- i (int)
> Outputs:
- list
> Restrictions:
- i must be (int)*/
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
        printf("Load: %d \n", aux->resource.load);
        printf("Size: %s \n", aux->resource.size);
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

//This function is used to make the program print the correspondin record.
void printRec(Record rec){
  printf("\nId: %d \nRoute: %s \nDescription: \n%s \nType: %s\n", rec.id,rec.route,rec.description,rec.type);
}

//This function is used to make the program display the corresponding tree.
void showTree(Leaf *tree)
{
  if (tree != NULL)
  {
    printRec(tree->data);
    showTree(tree->left);
    showTree(tree->right);
  }
}

//This function is used to make the program display the information of the chores, called items.
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

//This function is used to add chores to work with.
void addChores(List *list, Chores item){
  Node *n, *aux;
	
	if(list->start == NULL) 
	{
		
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

//This function is used to add records to work with, necessary as they store chores information.
void addRecord(Tree *tree, Record rec, int task)
{
  Leaf *new;
  new = (Leaf *)malloc(sizeof(Leaf));
  new->data.id = rec.id;
  strcpy(new->data.route,rec.route);
  strcpy(new->data.description,rec.description);
  strcpy(new->data.type,rec.type);
  new->data.task= task;
  new->left = NULL;
  new->right = NULL;
  if (tree->root == NULL){
    new->data.parent=0;
    tree->root = new;
  }
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
    new->data.parent = prev->data.id;
    if (rec.id < prev->data.id)
      prev->left = new;
    else
      prev->right = new;
  }
}

//This function is used to add resources to the different chores.
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

//This function is used to add full lists of records.
void addRecordList(List *list1, Record rec){
	Node *n, *aux, *new;
  	new = (Node *)malloc(sizeof(Node));
  	new->record.id = rec.id;
  	strcpy(new->record.route,rec.route);
  	strcpy(new->record.description,rec.description);
  	strcpy(new->record.type,rec.type);
  	new->record.task= rec.task;
	  new->record.parent = rec.parent;
  	new->next=NULL;
  	
	if(list1->start == NULL) 
	{

		list1->start = new;
    list1->range++;
		return;
	}
	n = list1->start;
	while(n!= NULL)
	{
		aux = n;
		n = n->next;		
	}
	aux->next = new;
  list1->range++;
	
}

//This function is used to make the program read the several information of the chores.
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

//This function is used to make the program read the several information of the resources.
Resource resourcesData(char *line){
  Resource data;
  char *token;

  token = strtok(line, ",");
  data.code = atoi(token);

  token = strtok(NULL, ",");
  strcpy(data.name,token);
  
  token = strtok(NULL, ",");
  strcpy(data.type,token);
  
  token = strtok(NULL, ",");
  strcpy(data.size,token);

  token = strtok(NULL, ",");
  data.load = atoi(token);

  token = strtok(NULL, ",");
  strcpy(data.leader,token);

  return data;
}

/*This function is used to make the program read the several information of the graphs.
> Inputs:
- i (int)
- row (int)
- size (int)
> Outputs:
- graphData
> Restrictions:
- i && row && size must be int*/
void graphData(char *line, int row[20],int size){
  
  char *token;
  int i;

  token = strtok(line, ",");
  row[0] = atoi(token);

  for(i=1; i<size; i++){
    token = strtok(NULL, ",");
    row[i] = atoi(token);
  }
}

//This function is used to make the program read the several information of the records.
Record recordsData(char *line){
  Record data;
  char *token;

  token = strtok(line, ",");
  data.task = atoi(token);

  token = strtok(NULL, ",");
  data.parent= atoi(token);
  
  token = strtok(NULL, ",");
  data.id= atoi(token);
  
  token = strtok(NULL, ",");
  strcpy(data.route,token);

  token = strtok(NULL, ",");
  strcpy(data.description, token);

  token = strtok(NULL, ",");
  strcpy(data.type,token);

  return data;
}

/*This function is used to make the program upload the chores information to .csv files.
> Inputs:
- line (char)
> Outputs:
- chore loaded
> Restrictions:
- line must be char*/
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

/*This function is used to make the program upload the resources information to .csv files.
> Inputs:
- line (char)
> Outputs:
- resource loaded
> Restrictions:
- line must be char*/
void loadResources(List *list, FILE *file){
  char line[650];
  Resource item;
  

  while(!feof(file)){
      
    fgets(line, 600,file);
    
    if(strcmp(line, "NULL") == 0){
      break;
    }

    item = resourcesData(line);

    addResource(list, item);
  }
}

/*This function is used to make the program upload the graphs information to .csv files.
> Inputs:
- line (char)
- i (int)
- j (int)
> Outputs:
- resource loaded
> Restrictions:
- line must be char
- i && j must be int*/
void loadGraph(int graph[][20], FILE *file,int size){
  char line[650];
  int row[size];
  int i=0,j;
  

  while(!feof(file)){
      
    fgets(line, 600,file);
    
    if(strcmp(line, "NULL") == 0){
      break;
    }
    graphData(line,row,size);
    for(j=0;j<size;j++){
      graph[i][j]= row[j]; 
    }
    i++;
  }
}

/*This function is used to make the program upload the trees information to .csv files.
> Inputs:
- line (char)
> Outputs:
- resource loaded
> Restrictions:
- line must be char*/
void loadTree(List *list, FILE *file){
  char line[650];
  Record item;
  

  while(!feof(file)){
      
    fgets(line, 600,file);
    
    if(strcmp(line, "NULL") == 0){
      break;
    }

    item = recordsData(line);

    addRecordList(list, item);
  }
}

//This function is used to save all the resources updates made in the .csv files.
void saveResources(List *list, FILE *file){
 rewind(file);
    
	Node *aux;
  
	for(aux= list->start;aux!=NULL;aux=aux->next){
    fflush(file);
		if(aux->next==NULL){
			fprintf(file,"%d,%s,%s,%s,%d,%s", aux->resource.code,aux->resource.name, aux->resource.type,
      aux->resource.size,aux->resource.load,aux->resource.leader);
		}
		else{
			fprintf(file,"%d,%s,%s,%s,%d,%s\n", aux->resource.code,aux->resource.name, aux->resource.type,
      aux->resource.size,aux->resource.load,aux->resource.leader);
		}
  
	}
}

/*This function is used to save all the graphs updates made in the .csv files.
> Inputs:
- i (int)
- j (int)
> Outputs:
- graphs updates saved.
> Restrictions:
- i && j must be int*/
void saveGraph(int graph[][20], FILE *file,int size){
 rewind(file);
    
	int i,j;
  
	for(i=0; i<size; i++){
    for(j=0;j<size; j++){
      fflush(file);
      if(j+1!= size){
			  fprintf(file,"%d,", graph[i][j]);
      }
      else if(j+1 == size && i+1  != size){
        fprintf(file,"%d\n", graph[i][j]);
      }
      else{
        fprintf(file,"%d", graph[i][j]);
      }
    }
	}
}

//This function is used to save all the chores updates made in the .csv files.
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

//This function is used to save all the trees updates made in the .csv files.
void saveTree (Leaf *tree,Leaf *root, FILE *file){
  	if (tree != NULL)
  {
    fflush(file);
	if (tree->data.id==root->data.id){

	fprintf(file,"%d,%d,%d,%s,%s,%s\n",tree->data.task,tree->data.parent,tree->data.id,tree->data.route,tree->data.description,
	tree->data.type);
	}
	else{
	fprintf(file,"\n%d,%d,%d,%s,%s,%s\n",tree->data.task,tree->data.parent,tree->data.id,tree->data.route,tree->data.description,
	tree->data.type);
	}
	
	saveTree(tree->left,root,file);
	saveTree(tree->right,root,file);
  }
}

/*This function is used to find the root of a tree.
> Inputs:
- task (int)
- option (int)
- root (int)
> Outputs:
- item (int)
> Restrictions:
- task && option && root must be int*/
Record searchRoot(int task, List *list, int option, int root,Tree *tree){
	Node *aux;
	Record item;
	aux = list->start;
	if(option == 1){
		while(aux!=NULL){
			if(aux->record.task == task){
				if(aux->record.parent == 0){
					item = aux->record;
					break;
				}
			}
			aux = aux->next;
		}
		return item;
	}
	else if(option == 2){
		while(aux!=NULL){
			if(aux->record.task == task && aux->record.id != root){
				if(existRecord(tree->root,aux->record.id) != 1){
				item = aux->record;
				break;
        }
			}
			aux = aux->next;
		}
		return item;
	}
	else{
		printf("Error");
	}
}

//This function is used to convert the list from the tree.csv into a tree to be printed by the program.
void convertList(List *tree, List *chores){
	Node *aux1, *aux2;
	Record item, child;
	aux2 = chores->start;
		while (aux2!=NULL){
			aux1 = tree->start;
			while(aux1!=NULL){
				if(aux1->record.id == tree->start->record.id){
					item = searchRoot(aux2->data.id,tree,1,0,aux2->data.Tree);
					addRecord(aux2->data.Tree,item,aux2->data.id);
			}
			else if(aux1->record.id != item.id && aux1->record.task == aux2->data.id){
				child = searchRoot(aux2->data.id,tree,2,item.id,aux2->data.Tree);
				addRecord(aux2->data.Tree,child,aux2->data.id);
			}
			else{
				aux1 = aux1->next;
				continue;
			}
			aux1 = aux1->next;
		}
		aux2 = aux2->next;
	}
}

//This function is used to modify the information of the different chores.
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

/*This information is used to make the program display the menu to operate the modification of the different chores.
> Inputs:
- option (int)
- id (int)
> Ouputs:
- case 1 | case 2 | case 3 | case 4 | case 5 | case 6*/
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

/*This function is used to make the program display the menu to operate the addition of chores.
> Inputs:
- type (int)
- run (int)
> Outputs:
- chore added
> Restrictions:
- type && run must be int*/
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

        fgets(userInput, sizeof userInput, stdin);
        userInput[strcspn(userInput, "\n")] = 0;

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

/*This function is used to make the program display the menu to operate the chores overall.
> Inputs:
- run (int)
> Outputs:
- case 1 | case 2 | case 3 | case 4
> Restrictions:
- run must be int*/
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

/*This function is used to make the program display the menu to operate the resources of the chores.
> Inputs:
- entry (char)
- run (int)
> Outputs:
- resource added*/
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
		entry[strcspn(entry, "\n")]=0;
		strcpy(item.name, entry);
		
		printf("Enter the resource type: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")]=0;
		strcpy(item.type, entry);
		
		printf("Enter resource load: ");
		fflush(stdin);
		scanf("%d",&item.load);
		
		printf("Enter the size of the resource: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")]=0;
		strcpy(item.size, entry);
		
		
		printf("Write the name of the leader: ");
		fflush(stdin);
		fgets(entry, sizeof entry, stdin);
		entry[strcspn(entry, "\n")]=0;
		strcpy(item.leader, entry);
		
		addResource(list1, item);
		
		printf("\nDo you want add more resouces? \n0.No \n1.Yes\n");
		scanf("%d", &run);
		
	}
    showList(list1,2);

}

//This function is used to search for a specific binary tree.
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

//This function is used to search the previous value in a binary tree.
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

//This function is used to search for the minimum value in a binary tree.
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

//This function is used to make the program simulate the elimination of records as a binary tree.
Leaf *deleteRecord(Leaf *root, int id)
{
	if (root == NULL) return root;
	

	if (id < root->data.id)
		root -> left = deleteRecord(root -> left, id);
	

	else if (id > root -> data.id)
		root -> right = deleteRecord(root -> right, id);
	
	else
	{

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

		Leaf* aux = minimum(root -> right);
		

		root -> data.id = aux -> data.id;

		root -> right = deleteRecord(root -> right, aux->data.id);
	}
	
	return root;
}

/* This function is used to make the program display the menu to operate the elimination of records.
> Inputs:
- id (int)
- run (int)
> Outputs: 
- record deleted.*/
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
      break;
    }
  }

}

/*This function is used to make the program display the menu to operate the modification of the records.
> Inputs:
- option (int)
- code (int)
- run (int)
> Outputs:
- case 1 | case 2 | case 3*/
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

/*This function is used to make the program display the menu to operate the addition of records.
> Inputs:
- userInput (char)
- run (int)
> Outputs:
- record added
> Restrictions:
- userInput must be char
- run must be int*/
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

    fgets(userInput, sizeof userInput, stdin);
    userInput[strcspn(userInput, "\n")] = 0;

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

    addRecord(chores->data.Tree,item,chores->data.id);
    printRec(item);
    printf("\nDo you want add more records? \n0.No \n1.Yes\n\n");
    scanf("%d", &run);
  }
  showTree(chores->data.Tree->root);
}

/*This function is used to make the program display the menu to operate the records overall
> Inputs:
- run (int)
- option (int)
- code (int)
> Outputs:
- case 1 | case 2 | case 3 | case 5
> Restrictions:
- run && option && code must be int*/
void recordsEdit(List *list, FILE *file){
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
      	modifyRecordMenu(aux->data.Tree);
        break;
      case 3:
      	deleteRecordMenu(aux->data.Tree);
        break;
        case 4:
        printf("\nThe tree of records is: \n");
        showTree(aux->data.Tree->root);
        break;
      case 5:
      	rewind(file);
      	saveTree(aux->data.Tree->root,aux->data.Tree->root,file);
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

/*This function is used to make the program display a specific graph
> Inputs:
- i (int)
- j (int)
> Outputs:
- graph printed
> Restrictions:
- i && j must be int*/
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

//This function is used to add the edges of a graph.
void addEdge(int graph[][20], int row, int column, int weight){
  graph[row][column] =  weight;
}

/*This function is used to make the program display the menu to operate the Dijkstra algorithm to find the shortest paths in a graph.
> Inputs:
- run (int)
- option (int)
- code (int)
- i (int)
> Outputs:
- path printed*/
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

/*This function is used to search for the vertex with the minimum value.
> Inputs:
- min (int)
- min_index (int)
- v (int)
> Outputs:
- min_index (int)
> Restrictions:
- min && min_index must be int*/
int minKey(int key[], int mstSet[], int range)
{

	int min = INT_MAX, min_index;
	int v =0;
	for (v = 0; v < range; v++){
		if (mstSet[v] == 0 && key[v] < min){
			min = key[v], min_index = v;
    }
  }

	return min_index;
}

/*This function is used to make the program display the corresponding MST
> Inputs:
- i (int)
> Outputs:
- MST printed
> Restrictions:
- i must be int*/
int printMST(int parent[], int graph[20][20], int size)
{
	printf("Edge \tWeight\n");
	int i =1;
	for (i = 1; i < size; i++){
		printf("%d - %d \t%d \n", parent[i], i,
			graph[i][parent[i]]);
  }
}

//This function is used to make the program perform the Prim algorithm on the MST.
void primMST(int graph[20][20], int size)
{

	int parent[size];

	int key[size];

	int mstSet[size];


	int i =0;
	for (i = 0; i < size; i++){
		key[i] = INT_MAX, mstSet[i] = 0;
  }



	key[0] = 0;
	parent[0] = -1; 


	int count =0;
	for (count = 0; count < size - 1; count++) {


		int u = minKey(key, mstSet, size);


		mstSet[u] = 1;





		int v=0;
		for (v = 0; v < size; v++)





			if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]){
				parent[v] = u, key[v] = graph[u][v];
      }
	}


	printMST(parent, graph, size);
}

/*/*This function is used to evaluate the existence of the different arrays.
> Inputs:
- temp (int)
- vertex (int)
- proceed (int)
- size (int)
> Outputs:
- 1|0 (int)
> Restrictions:
- temp && vertex && proceed && size must be int*/
int existArray(int vertex, int proceed[20],int size){
  int temp=0;

  for(temp = 0; temp <size; temp++){
    if(proceed[temp]==vertex){
      return 1;
    }
  }
  return 0;
}

/*This function is used to make the program perform the Dijkstra algorithm to the graph created.
> Inputs:
- rate (int)
- largue (int)
- pred (int)
- visited (int)
- temp (int)
- mindistance (int)
- nextnode (int)
- i (int)
- j (int)
> Outputs:
- Dijkstra algorithm
> Restrictions:
- rate && largue && pred && visited && temp && mindistance && nextnode && i && j must be int*/
void Dijkstra(int graph[20][20], int n, int start, int array[2], int proceed[20] ){
  int rate[20][20], largue[20], pred[20];
  int visited[20], temp, mindistance, nextnode,i, j;


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

/*This function is used to work with different arrays.
> Inputs:
- i (int)
> Outputs:
- array
> Restrictions:
- i must be int*/
void nullArray(int array[20]){
  int i;

  for(i = 0;i<20;i++){
    array[i]= INT_MAX;  
  }
}

/*This function is used to print the routes between the several nodes.
> Inputs:
- i (int)
- start (int)
- obj (int)
> Outputs:
- route printed
> Restrictions:
- i && start && obj must be int*/
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

/*This function is used to find the routes between the several nodes.
> Inputs:
- data (int)
- i (int)
- proceed (int)
- run (int)
> Outputs:
- route founded 
> Restrictions:
- data && i && run must be int*/
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

/*This funtion is used to make the program display the routes menu.
> Inputs:
- run (int)
- option (int)
- i (int)
- aux (int)
- start (int)
- obj (int)
> Outputs:
- menu
> Restrictions:
- run && option && i && aux && start && obj must be int
*/
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
