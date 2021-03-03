#include <iostream>
#include<io.h>

using namespace std;

typedef struct {
    char str[256];
    int count;
}CountNode;

typedef struct node {
    CountNode data;
    node* next;
}LinkList,LinkListNode;

void initLinkList(LinkList* &head);
void addWordToLinkList(char* str, LinkList* head);
void addNodeToLinkList(LinkListNode* node, LinkList* head);
bool destroyLinkList(LinkList* head);
void wordsCounter(char* str, LinkList* head);
void printTheStastics(LinkList* head);

int main()
{
	//init data structure
	LinkList* head;
	initLinkList(head);

	FILE *fp = fopen("C:/Users/MINIMO/Desktop/test.txt", "r");
	if (!fp) {
	    printf("file open failed");
	    return 0;
	}
	char str[256];
	while (fscanf(fp, "%s", str) != EOF) {
	    //DO THE SHIT
        wordsCounter(str, head);
	}

	printTheStastics(head);

	fclose(fp);
	destroyLinkList(head);

	return 0;
}

void initLinkList(LinkList*& head) {
	head = (LinkList*)malloc(sizeof(LinkList));
	head->next = NULL;
}


bool destroyLinkList(LinkList* head) {
	if (head == NULL) {
	    return false;
	}
	LinkListNode* cur = head;
	LinkListNode* next = cur->next;
	while (!next) {
	    cur = next;
	    next = cur->next;
	    free(cur);
	}
	free(head);
	return true;
}

void addNodeToLinkList(LinkListNode* node, LinkList* head) {
	LinkListNode* temp;
	temp = head;
	while (temp->next != NULL) {
	    temp = temp->next;
	}
	temp->next = node;
	node->next = NULL;
}

void addWordToLinkList(char* str, LinkList* head) {
	LinkListNode* node = (LinkListNode*)malloc(sizeof(LinkListNode));
	strcpy(node->data.str, str);
	node->data.count = 0;
	node->data.count++;
	
	addNodeToLinkList(node, head);
}

void wordsCounter(char* str, LinkList* head) {
	// travel the list,cmp the input str,if the list have the word,count++;
	// if not,add the word(str) to the list
	LinkListNode* travelNode = head->next;
	bool isHadTheWord = false;
	while (travelNode) {
	    if (strcmp(str, travelNode->data.str) == 0) {
		isHadTheWord = true;
		travelNode->data.count++;
		break;
	    }
	    travelNode = travelNode->next;
	}
	if (!isHadTheWord) {
	    addWordToLinkList(str, head);
	}
}

void printTheStastics(LinkList* head) {
	//show the stastics of the words counter
	if (!head) {
	    return; 
	}
	LinkListNode* travelNode = head->next;
	while (travelNode) {
	    printf("%s     counts:%d\n", travelNode->data.str, travelNode->data.count);
	    travelNode = travelNode->next; 
	}
}


