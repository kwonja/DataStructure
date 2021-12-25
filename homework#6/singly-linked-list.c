/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>                       //헤더파일 선언
#include<stdlib.h>                     //동적할당을 위해 선언

/* 필요한 헤더파일 추가 */

typedef struct Node {                  //노드에 대한 구조체 생성
	int key;
	struct Node* link;
} listNode;

typedef struct Head {                   //노드를 가지고 있는 first 포인터 구조체 생성
	struct Node* first;
}headNode;

/* 함수 리스트 */
headNode* initialize(headNode* h);              //연결리스트를 초기화 하는 함수
int freeList(headNode* h);                      //초기화한 연결리스트를 동적할당하는 함수

int insertFirst(headNode* h, int key);          //연결리스트의 처음에 노드를 삽입하는 함수
int insertNode(headNode* h, int key);           //연결리스트를 돌면서 입력한 key값보다 큰 값이 나오는 노드 바로 앞에 key에 대한 노드를 추가하는 함수
int insertLast(headNode* h, int key);           //연결리스트의 마지막에 노드를 삽입하는 함수

int deleteFirst(headNode* h);                   //연결리스트의 첫번째 노드를 삭제하는 함수
int deleteNode(headNode* h, int key);           //연결리스트를 돌면서 삭제할 값을 입력받아 그값에 대한 노드를 삭제하는 함수
int deleteLast(headNode* h);                    //연결리스트의 마지막 노드를 삭제하는 함수
int invertList(headNode* h);                    //연결리스트를 역순으로 바꾸는 함수

void printList(headNode* h);                   //연결리스트를 출력해주는 함수

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [KwonSungMin]  [2018038068] -----]\n");
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

	listNode* node = (listNode*)malloc(sizeof(listNode)); //추가할 연결리스트를 동적할당으로 생성
	node->key = key;                                       //생성한 공간에 key를 전달

	node->link = h->first;                                 //연결리스트  처음의 주소를 생성한 노드의 링크에 전달
	h->first = node;                                       //노드위 주소를 연결리스트의 처음주소로 전달
                                                           //생성한 노드가 연결리스트의 처음에 위치하게 된다.
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode *temp;                                 //입력받을 key를 저장할 노드
    listNode* x;                                    //연결리스트의 처음주소를 받을 노드
    listNode* previous=NULL;                             //x에 대한 이전노드
    temp=(listNode*)malloc(sizeof(listNode));       //삽입할 노드를 동적할당으로 생성
    temp->key=key;                                  //생성한 공간에 key를 전달
    if(!h->first)                                   //연결리스트의 처음 주소가 NULL이라면
    {
        temp->link=NULL;                             //생성한 노드에 링크를 NULL로 넣어주고
        h->first=temp;                               //생성한 노드를 연결리스트의 처음으로 만들어준다.
    }
    else                                          //연결리스트의 처음 주소가 NULL이 아니라면
    {
        x=h->first;                               //연결리스트의 처음주소를 받음
		                                          //이렇게 받지 않고 h->first를 이용해서 받으면 h->first 의 값이 바뀌어버린다
        for(;x;x=x->link)                         //x가 NULL이 될때까지
        {
            if(x->key>=key)                       //x에 해당하는 key가 입력받은key보다 크면
            {
                break;
            }
            previous=x;                           //if문에서 break를 타고 나오면 previous에는 x의 이전 주소가 남아있다.
        }
		if(x==h->first)                          //맨 처음값이 가장클때
		{
			temp->link=x;                       //temp를 연결리스트의 처음으로 바꿔줘여한다
			h->first=temp;
		}
		else{                                     //맨 처음값이 큰게 아닐대
        temp->link=x;                             //x의 주소를 temp->link에 넣고
        previous->link=temp;                      //temp를 이전주소(previous)의 link에 넣어준다.
		}
	}
	                                             //노드삽입이 마지막이여도 x는 NULL이기 때문에 문제가 되지 않는다.
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    listNode* temp;                                    //입력받을 key를 저장할 노드
    listNode* x;                                        //연결리스트의 처음주소를 받을 노드
    x=h->first;                                         //연결리스트의 처음주소를 받음
    temp=(listNode*)malloc(sizeof(*temp));              //삽입할 노드를 동적할당으로 생성

    while(x->link!=NULL)                    //x의  link가 NULL일때 까지 반복
    {
        x=x->link;
    }
	                                      //x->link가 NULL이면 x는 연결리스트의 마지막이다.
    temp->key=key;                        // 생성된 노드에 key값 전달
    temp->link=NULL;                     //생성된 노드의 다음은 없으므로 link에 NULL을 전달
    x->link=temp;                        //X의 link에 생성된 노드의 주소를 전달하여 마지막에 생성된 노드 추가

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode *x;                     //연결리스트의 처음주소를 받을 노드
	x=h->first;                      //연결리스트의 처음주소를 받음
	if(h->first)                     //처음 주소가 NULL이 아니면
	{
	h->first=h->first->link;         //처음 주소의 다음주소(first->link)를 처음주소로 만들어준다
	free(x);                         //처음주소 동적할당 해제->삭제
	}
	else                            //처음주소가 NULL이면 삭제할수없다는 에러메세지 출력
	printf("empty\n");               

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode *previous;                    //x의 이전주소를 기억할 노드 생성
	listNode *x;                           //연결리스트의 처음 주소를 저장할 노드 생성
	if(h->first)                           //처음 주소가 NULL이 아니면
	{
	  x=h->first;                          //연결리스트의 처음주소를 x에 전달
	  if(x->key!=key)                      //연결리스트의 처음주소의 key가 입력받은 key와 다르면
	{
	    for(;x;x=x->link)                 //x가 NULL이 될때까지
	    {
		if(x->key==key)                  //x의 key와 입력받은 key가 같다면
		{
			previous->link=x->link;      //x의 이전주소(previous)가 x의 link안에 있는 다음주소를 가리키게 한다
			free(x);                     //삭제한 노드x에 대해서 동적할당해제->삭제
			break;
		}
		previous=x;                     //if문에서 사용할 x의 이전주소를 기억한다
		}
		if(x==NULL) //연결리스트에 해당하는 key값을 가지는 노드가 없다면 오류 메세지 출력
		{
			printf("no key\n");
		}
	}
	  else //처음 연결리스트의 key값이 입력한 key와 같을때
	    {                            
		 h->first=h->first->link;    //연결리스트의 처음주소를 그 처음의 다음주소로 바꾸고            
		 free(x);                    //x에 있는 처음주소 동적할당해제->삭제
	    }                            //만약 h->first를 동적할당하게되면 위에 두줄을 실행한 후 동적할당을 해제하기때문에 에러발생

	}
	else  //연결리스트의 처음주소가 NULL일때 삭제에대한 오류메세지 출력
	printf("empty\n");
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode *x;                      //연결리스트의 처음주소를 저장할 노드 생성
	listNode *previous;                //x의 이전주소를 기억할 노드 생성
	x=h->first;                        //연결리스트의 처음주소를 x에 전달
	if(x)                             //처음주소가 NULL이 아니면
	{
		while(x->link!=NULL)          //x->link가 NULL이 될때까지
		{
			previous=x;                //previous는 x의 이전 주소를 가짐
			x=x->link;
		}
	    free(x);                      //x->link=NULL을 가지는 x의 주소를 동적할당->삭제
		previous->link=NULL;          //삭제한 x를 previous->link가 가지고 있으면 안되므로 NULL로 초기화
		                              //연결리스트의 마지막이라는것을 확인할수 있게 해준다
	}
	else      //처음주소가 NULL이면 에러메세지 출력
	{
		printf("empty\n");
	}
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* x;                           //연결리스트의 처음주소를 저장할 노드 생성 
	listNode *middle,*trail;               //역순으로 바꾸기위해 중간 과정에서 필요한 노드 생성
	x=h->first;                           //X에 연결리스트의 처음주소를 전달
	middle=NULL;                             //middle 노드를 NULL로 초기화
	while(x)                             //x의 주소가 NULL일때 까지(연결리스트의 끝)
	{
		trail=middle;                     //trial에 middle의 주소를 전달(처음에는 NULL)
		middle=x;                         //처음주소를 middle에 전달
		x=x->link;                         //연결리스트의 다음으로 이동
		middle->link=trail;                //trail의 주소를 middle->link에 전달
	}
	//연결리스트가 뒤로가면서 middle이 x의 주소를 받고 middle의 주소를 trail이  가지고 있어서 
	//middle->link=trail을 통해 역순으로 연결시켜준다
	//while문을 나오면 이 역순으로 바꾼 연결리스트의 처음주소는 middle이 가지고 있다.
	h->first=middle;         //따라서 연결리스트의 처음을 middle로 바꿔준다.
	return 0;
}


void printList(headNode* h) {            //연결리스트를 출력해주는 함수
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