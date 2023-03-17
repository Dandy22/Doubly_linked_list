#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	char NIM[15], nama[50];
	int umur;
	struct Node *next, *prev;
}*head=NULL, *tail=NULL, *curr=NULL;

struct Node *newNode(char NIM[], char nama[], int umur){
	struct Node* tnode=(struct Node *) malloc (sizeof(struct Node));
	strcpy(tnode->NIM, NIM);
	strcpy(tnode->nama, nama);
	tnode->umur = umur;
	tnode->next = tnode->prev = NULL;
	
	return tnode;
}

void pushHead(char NIM[], char nama[], int umur){
	struct Node* tnode=newNode(NIM, nama, umur);
	if(head==NULL){
		head=tail=tnode;
	}else{
		tnode->next = head;
		head->prev = tnode;
		head = tnode;

	}
		head->prev = NULL;
}

void pushTail(char NIM[], char nama[], int umur){
	struct Node* tnode=newNode(NIM, nama, umur);
	if(head==NULL){
		head=tail=tnode;
	}else{
		tail->next = tnode;
		tnode->prev = tail;
		tail=tnode;
	}
	tail->next = NULL;
}

void pushMid(char NIM[], char nama[], int umur){
	struct Node* tnode = newNode(NIM, nama, umur);
	if(head==NULL){
		head=tail=tnode;
		
	}else if(strcmp(head->NIM, NIM) > 0){
		pushHead(NIM, nama, umur);
	}else if(strcmp(tail->NIM, NIM) < 0){
		pushTail(NIM, nama, umur);
	}
	else{
		struct Node* pos = head;
		while(pos->next != NULL && strcmp(pos->next->NIM, NIM) < 0){
			pos = pos->next;
		}
		tnode->next = pos->next;
		pos->next->prev = tnode;
		pos->next = tnode;
		tnode->prev = tnode;
	}
}

void popHead(){
	if(head==NULL) return;
	if(head==tail){
		free(head);
		head=tail=NULL;
	}else{
		curr = head;
		head = curr->next;
		free(curr);
		head->prev = NULL;
	}
}

void popTail(){
	if(head==NULL) return;
	if(head==tail){
		free(head);
		head=tail=NULL;
	}
	else{
		curr = tail;
		tail = curr->prev;
		free(curr);
		tail->next = NULL;
	}
}

void popMid(char NIM[]){
	if(head==NULL) return;
	if(head==tail){
		head=tail=NULL;
	}else if(strcmp(head->NIM, NIM) == 0){
		popHead();
	}else if(strcmp(tail->NIM, NIM) == 0){
		popTail();
	}else{
		curr = head;
		while(curr->next != NULL && strcmp(curr->next->NIM,NIM) != 0){
			curr = curr->next;
		}
		if(curr->next == NULL) return;
		struct Node* temp = curr->next;
		curr->next = temp->next;
		temp->next->prev = curr;
		free(temp);
	}
}
void search(char NIM[]){
	curr = head;
	if(curr == NULL) return;
	
	while(curr != NULL && strcmp(curr->next->NIM, NIM) != 0){
		curr = curr->next;
	}
	if(curr->next == NULL){
		printf("Not Found\n");
	}
	else {
		printf("Found %s\n", curr->next->NIM);
	}
}

void view(){
	curr = head;
	if(curr == NULL) return;
	while(curr != NULL){
		printf("%s - %s - %d\n", curr->NIM, curr->nama, curr->umur);
		curr = curr->next;
	}
}


int main(){

	pushHead("123","Dandy", 19);
	pushMid("333","Soko", 21);
	pushTail("200","Ryan", 18);
	pushHead("334", "Jojo", 10);
	search("123");
	popMid("333");
	view();
	return 0;
}
