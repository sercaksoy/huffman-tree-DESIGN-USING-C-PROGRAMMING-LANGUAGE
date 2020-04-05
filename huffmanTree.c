#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 100


struct node{
	char letter; 
	int frequency;
	struct node * left;
	struct node * right;
	struct node * next;
};

struct que{
	struct node * data;    // Notice that this pointer, pointing nodes.
	struct que * nextq;
};

typedef struct node node ;
typedef struct que que;

node * insert(node * head, char ch){ // ----- Creating and Inserting a node with given char.
	node * insertOne = (node *)malloc(sizeof(node));
	insertOne -> letter = ch;
	insertOne -> frequency = 1;
	insertOne -> next = head;
	insertOne -> left = NULL;
	insertOne -> right = NULL;
	return insertOne;                 // Returning new node as head.
} // ----------------------------------------------------------------------------------------
node * search(node * head, char ch){ // ----- Searchin the node with given char.
	if(head == NULL)
		return NULL;                   // If there is no list then there is none of nodes 
	node * iter = head;                    // with given char.
	while(iter != NULL){
		if(iter -> letter == ch )      // If our loop find the char
			return iter;	       // it returns the node.
		iter = iter -> next;
	}
	return NULL;                           // If the loop couldn't find,it returns NULL.
} // ---------------------------------------------------------------------------
node * insertionSort(node * head, node * chOne){ // ----- This function is the where magic happens.
	if(chOne -> next == NULL)                         // If list consists of a single node 
		return head;                               // then sorted list is the same node.
	if(chOne -> frequency < chOne -> next -> frequency) // If the choosen node already ordered.
		return head;
	node * iter = head; 
	if(chOne != head){                                 // There is a given node to be applied sort
		while(iter -> next != chOne)
			iter = iter -> next;
		iter -> next = chOne -> next;              // Loop find that node and then there we are tearing its link 
		iter = chOne;                              // Now we are searching from that node to find where to insert it.
		while(iter -> next != NULL && iter -> next -> frequency <= chOne -> frequency){
			iter = iter -> next;	           // Searching until it finds a node with more frequency integer.
		}
		chOne -> next = iter -> next;              // Connecting new links.
		iter -> next = chOne;
		return head;                               // This function returns head in the case of we change head.
	}                                             
	while(iter -> next != NULL && iter -> next -> frequency <= chOne -> frequency){
		iter = iter -> next;	
	}
	node * temp = iter -> next;
	node * temp2 = head -> next;
	iter -> next = head;
	head -> next = temp;
	
	return temp2;	
	
} // --------------------------------------------------------------------------
node * insertIternal(node * head,node * iternal){
	node * iter = head;
	while(iter -> next != NULL && iternal->frequency >= iter->next->frequency){
		iter = iter -> next;         // Inserting internals by Insertion Sort method.
	}                                    // Every smaller frequency node left behind.
	iternal -> next = iter -> next;
	iter -> next = iternal;
	return head;
} // --------------------------------------------------------------------------
node * toTree(node * head){ // So far we have created a linked list.And this function returns it as a Tree.
	if(head == NULL)         // A condition for, if we haven't created a list so far.
		return NULL;
	node * iter = head;
	while(iter != NULL && iter -> next != NULL){  // This iterator jumping on the nodes and creating iternalNodes. 
		int sumFre = iter -> frequency + iter -> next -> frequency;
		node * iternalNode = (node *)malloc(sizeof(node));
		iternalNode -> frequency = sumFre;
		iternalNode -> left = iter;                // Then giving nodes to the iternalNode as children.
		iternalNode -> right = iter->next;         // ..
		iternalNode -> letter = '\0';              // Itilazing the iternal nodes letter.
		head = insertIternal(head,iternalNode);
		iter = iter -> next -> next;			
	}
	return iter;                                     // Returning the Root.
		
} // --------------------------------------------------------------------------
que * enQ(que ** head, que * last, node * data){ // ----- Creating a queue to print tree level order.
	que * newnode = (que *)malloc(sizeof(que));   // I will use linked list implementation for queue.
	newnode -> nextq = NULL;                      // Itilazing queue's attributes.
	newnode -> data = data;                       // ..
	if(*head == NULL){                            // We are trying to insert a node pointer into queue
		*head = newnode;                      // but if queue hasn't created yet ?
		return newnode;                       // Then we are creating a new queue and then changing head as new node
	}
	last -> nextq = newnode;
	return newnode;                               // New created node is going to be our lastnode in the queue.
} // --------------------------------------------------------------------------
node * deQ(que ** head){ // ----- Calling nodes from top of our queue.
	if(*head == NULL)
		return NULL;
	node * temp = (*head) -> data; // As i told before we are calling them from top
	(*head) = (*head) -> nextq;    // So we need to update new head.
	return temp;                   // Returning the node which popped out.
} // --------------------------------------------------------------------------

int main(){
	int choice1,size;
	int times = 0, level = 0, levelcheck = 0;
	long int i, stringSize;
	char ch = 'x';
	char *input;
	char filename[MAX];
	node * head = NULL;
	node * increase = NULL;
	printf("To give string by command prompt press 1 , to give from a file press 2\n");
	scanf("%d",&choice1);
	if(choice1 == 1){
		int length = 100;
		input = (char *)malloc(length * sizeof(char));       // Dynamic memory allocation for string.
		size = 0;
		getchar();                                           // Avoid around bug.
		while(ch != '\n'){
			ch = getchar();                              // Taking input char by char.
			if(size >= length-10)
				input = realloc(input,(length+=10)*sizeof(char));
			input[size] = ch;
			size++;
		}
		input[size-1] = '\0';                                // Last character reading '\n' char.
	}

	else{
		FILE * fp ;
		printf("Enter file's name: ");
		scanf("%s",filename);
		fp = fopen(filename,"r");
		if(fp == NULL){
			perror("Unable to open file!");
			exit(1);
		}
		else{	
			fseek(fp, 0, SEEK_END);
			size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			input = (char *)malloc((size+1)*sizeof(char));
			fgets(input,(size+1),fp);
			fclose(fp);
		}
	}
		
		stringSize = strlen(input);      // Calculating the size of string
		for(i = 0; i< stringSize; i++){  // So we can look into it char by char easily.
			increase = search(head,input[i]); // Trying to find that char in list
			if(increase == NULL){             // As a reminder; search function returns NULL 
				head = insert(head,input[i]);  // if the list doesn't contain the char.
			}
			else{
				(increase -> frequency)++;     // If the function finds the char we are increasing its frequency.
				head = insertionSort(head,increase);
				
			}
		}  // Linked List has COMPLETED.
		node * root = toTree(head);
	   	//  Tree has COMPLETED.
		node * temp = root;
		que * qhead = NULL;
		que * qlast = NULL;
			// Necessary nodes have INITIALIZED.
		while(temp != NULL){ 					// Then we are starting to print our levels.
			if(temp->letter != '\0')
				printf("[%c]%d ",temp -> letter, temp -> frequency);  // First of all the node is printing its data.
			else
				printf("%d ",temp->frequency);
			times++;
			if(temp->left == NULL)
				levelcheck +=2;
			if(times == pow(2,level)){                          // If the printing node reached last node of 
				printf("\n");                               // current level then it prints a new line.
				times = levelcheck;
				level++; 
				levelcheck = 0;                             // Reset for the new level.
			}
			if(temp -> left != NULL){                  // Then we are enqueue its left and right children if there is any.
				qlast = enQ(&qhead, qlast, temp -> left);     
				qlast = enQ(&qhead, qlast, temp -> right);
			}
			que * qtemp = qhead;	                           // A temporary que pointer 
			temp = deQ(&qhead);
			free(qtemp);                                    // it is used for; free the popped queue member.
		}
	return 0;
}
