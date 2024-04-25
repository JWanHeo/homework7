/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node { // int형 데이터 key와 다음 리스트를 가리키는 포인터 link를 요소로 가지는 listNode 구조체 정의
	int key;
	struct Node* link;
} listNode;

typedef struct Head { // 첫번째 노드를 가리키는 포인터  first를 요소로 가지는 headNode 구조체 정의
	struct Node* first;
} headNode; 


/* 함수 리스트 */
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
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
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* curr = h->first; // 현재 노드를 가리키는 포인터

	/*연결리스트가 비어있는 경우*/
	if(curr == NULL) { // 연결리스트가 비어있는 경우
		insertFirst(h, key); // 첫번째 노드 생성
		return 0;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 생성
	node->key = key; // 생성한 노드의 key를 입력받은 key로 초기화

	/*첫번째 노드의 key가 입력받은 key보다 큰 경우*/
	if(curr->key >= key) {
		node->link = curr; // 첫번째 노드의 
		h->first = node;	
		return 0;
	}
	
	while(curr->link != NULL) { // 현재 노드의 다음 노드가 없을 때까지 반복 수행
		if(curr->link->key >= key) { // 만약 다음 노드의 key가 입력받은 key보다 크면,
			node->link = curr->link; // 생성한 노드의 link를 curr의 주소로 초기화
			curr->link = node; // 현재 노드의 link를 생성한 노드로 변경
			return 0; // 함수 종료
		}
		curr = curr->link; // 현재 노드는 다음 노드로 변경
	}

	/*마지막 노드의 key값까지 확인했을 때 입력받은 key보다 작은 경우*/
	curr->link = node;
	node->link = NULL;

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* curr = h->first; // 현재 노드를 가리키는 포인터

	while(curr->link != NULL) { // 현재 노드의 다음 노드가 없을 때까지 반복 수행
		curr = curr->link; // 현재 노드는 다음 노드로 변경
	}
	
	listNode* node = (listNode*)malloc(sizeof(listNode)); 
	node->key = key;
	node->link = NULL;
	
	curr->link = node;


	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

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

