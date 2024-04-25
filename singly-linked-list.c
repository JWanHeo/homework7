/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node { // int�� ������ key�� ���� ����Ʈ�� ����Ű�� ������ link�� ��ҷ� ������ listNode ����ü ����
	int key;
	struct Node* link;
} listNode;

typedef struct Head { // ù��° ��带 ����Ű�� ������  first�� ��ҷ� ������ headNode ����ü ����
	struct Node* first;
} headNode; 


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- ������ 2020069031 -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* curr = h->first; // ���� ��带 ����Ű�� ������

	/*���Ḯ��Ʈ�� ����ִ� ���*/
	if(curr == NULL) { // ���Ḯ��Ʈ�� ����ִ� ���
		insertFirst(h, key); // ù��° ��� ����
		return 0;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� ����
	node->key = key; // ������ ����� key�� �Է¹��� key�� �ʱ�ȭ

	/*ù��° ����� key�� �Է¹��� key���� ū ���*/
	if(curr->key >= key) {
		node->link = curr; // ������ ����� link�� ù��° ���� ����
		h->first = node; // ù��° ���� ������ ��带 ����
		return 0;
	}
	
	while(curr->link != NULL) { // ���� ����� ���� ��尡 ���� ������ �ݺ� ����
		if(curr->link->key >= key) { // ���� ���� ����� key�� �Է¹��� key���� ũ��,
			node->link = curr->link; // ������ ����� link�� curr�� �ּҷ� �ʱ�ȭ
			curr->link = node; // ���� ����� link�� ������ ���� ����
			return 0; // �Լ� ����
		}
		curr = curr->link; // ���� ���� ���� ���� ����
	}

	/*������ ����� key������ Ȯ������ �� �Է¹��� key���� ���� ���*/
	curr->link = node;
	node->link = NULL;

	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* curr = h->first; // ���� ��带 ����Ű�� ������

	while(curr->link != NULL) { // ���� ����� ���� ��尡 ���� ������ �ݺ� ����
		curr = curr->link; // ���� ���� ���� ���� ����
	}
	
	listNode* node = (listNode*)malloc(sizeof(listNode)); // ��� ����
	node->key = key; // ����� Ű�� �ʱ�ȭ
	node->link = NULL; // link�� NULL�� �ʱ�ȭ
	
	curr->link = node; // ������ ����� link�� ������ node�� ����Ű���� ����

	return 0;
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	listNode* firstNode = h->first; // firstNode�� ù��° ��带 ����Ű���� �ʱ�ȭ

  /*���Ḯ��Ʈ�� ����ִ� ���*/
	if(firstNode == NULL) {
		printf("����Ʈ�� ����ֽ��ϴ�.");
		return 0;
	}

	h->first = h->first->link; // ��� �����Ͱ� �ι�° ��带 ����Ű���� ����
	free(firstNode); // ù��° ��� ����(�޸� ����)

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	listNode* curr = h->first; // ���� ��带 ����Ű�� ������

	/*���Ḯ��Ʈ�� ����ִ� ���*/
	if(curr == NULL) {
		printf("����Ʈ�� ����ֽ��ϴ�.");
		return 0;
	}

	/*ù��° ����� key�� �Է¹��� key�� ������ ���*/
	if(curr->key == key) {
		listNode* temp = curr; // ���� ��带 ����Ű�� temp
		h->first = curr->link; // ��� �����Ͱ� ���� ��带 ����Ű���� ����
		curr = h->first; // ���� ��带 ���� ���� ����
		free(temp);	// ������ ���� ��� ����
		return 0;
	}

	while(curr != NULL && curr->link != NULL) { // ����Ʈ�� ��� ��� ��ȸ
		if(curr->link->key == key) { // ���� ����� key�� �Է¹��� key�� ���� ���
			listNode* temp = curr->link; // ���� ���� temp �ʱ�ȭ
			curr->link = curr->link->link; // ���� ����� ���� ��带 ���� ����� ���� ���� ���� 
			free(temp); // ������ ���� ��� ����
			return 0;
		}
		curr = curr->link;
	}

	return 0;
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	listNode* curr = h->first; // ���� ��带 ����Ű�� ������

  /*����Ʈ�� ����ִ� ���*/
	if(curr == NULL) {
		printf("����Ʈ�� ����ֽ��ϴ�.");
		return 0;
	}

	/*����Ʈ�� ��Ұ� �ϳ��� �ִ� ���*/
	if(curr->link == NULL) {
		h->first = NULL; // ��� �����͸� NULL �����ͷ� ����
		free(curr); // ��������Ͱ� ����Ű�� ��� ����
		return 0;
	}

	while(curr->link->link != NULL) { // ���� ����� ���� ���� ��尡 ���� ������ �ݺ� ����
		curr = curr->link; // ���� ���� ���� ���� ����
	}

	free(curr->link); // ���� ����� ���� ��� ����
	curr->link = NULL; // ���� ����� link�� NULL�� �ʱ�ȭ

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {

	listNode* curr = h->first; // ���� ���
	listNode* prev = NULL; // ���� ���
	listNode* next = NULL; // ���� ���

	while(curr != NULL) { // ���� ��尡 NULL�� ������ �ݺ�
		next = curr->link; // next�� ���� ��� ����
		curr->link = prev; // ���� ����� ���� ��带 ���� ���� ����
		prev = curr; // ���� ��带 ���� ���� �̵�
		curr = next; // ���� ��带 ������ ���� ���� �̵�
	}

	h->first = prev; // ��� ��带 ������ ������ ���� ���� 

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

