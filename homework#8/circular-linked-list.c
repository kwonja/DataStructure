/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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
			initialize(&headnode);
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));           //연결리스트에 노드가 없으면 링크가 자기 자신을 가리키도록 설정
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
/* h와 연결된 listNode 메모리 해제
	 */
	listNode* prev = NULL;
    listNode* head=h;   //헤드노드의 주소를 저장하기 위한 변수
	do {
		prev =h->rlink;  //첫번째 노드부터 동적할당해제 시작
		h = h->rlink;
		free(prev);  //해당노드 동적할당 해제
	}while(h!=head);  //처음노드부터 헤드노드로 돌아오기 전까지
    free(head);    // 나머지 노드들을 삭제후 남은 헤드노드를 동적할당 해제
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
    listNode *head=h;                                           //맨 뒤에오는 노드를 헤드와 연결하기 위해서 따로 지정
    listNode *temp=(listNode*)malloc(sizeof(listNode));
    temp->key=key;
    while(h->rlink!=head)               //h가 맨 끝에 위치할때까지
    {
        h=h->rlink;                      //h를 이동
    }
    //헤더노드만 존재할때에도 정상으로 작동
    h->rlink=temp;
    temp->rlink=head;
    head->llink=temp;
    temp->llink=h;

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
    listNode *head=h; //삭제후 연결할 헤드노드를 지정
    listNode *previous=NULL;    //마지막 노드 삭제후 헤드노드에 연결해주기 위해 구조체 포인터 변수 선언
    if(h->rlink!=head)        //연결리스트에 헤드노드를 제외한 노드가 존재할때
    {
    while(h->rlink!=head)
    {
        h=h->rlink;
        previous=h->llink;        //h의 이전주소를 기억해야한다
    }                             //동적할당후 헤드노드에 다시 연결해줘야하기때문
    free(h);                  //해제후
    previous->rlink=head;     //연결
    head->llink=previous;
    }
    else                        //헤드노드만 존재할때 오류메세지 출력
    printf("empty\n"); 


	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    listNode* head=h;    //h의 처음주소,헤드노드를 기억하기 위해 선언
    listNode* first=h->rlink;   //temp로 받은 데이터를처음으로 지칭하기 위해서 first 선언
                                //원형 다중 연결리스트가 되려면 공백이 있어야한다
    listNode *temp=(listNode*)malloc(sizeof(listNode));
    temp->key=key;
    if(head!=first)        //헤드노드말고 다른 노드가 존재할때
    {
    head->rlink=temp;
    temp->llink=head;
    temp->rlink=first;
    first->llink=temp;
    }
    else                   //헤드노드만 존재할때
    {
        head->rlink=temp;
        temp->rlink=head;
        head->llink=temp;
        temp->llink=head;
    }

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    listNode * head=h;            //헤더노드 생성
    listNode *first=h->rlink;     //삭제할 노드를 지정하는 노드 생성
    if(h->rlink!=head)    //헤드노드말고 다른노드가 존재할때
    {                        
        head->rlink=first->rlink;
        first->rlink->llink=head;
        free(first);     //첫번째 노드 동적할당해제->삭제
    }
    else                //헤드노만 존재할때 삭제할 노드가 없으므로 에러메세지 출력
    printf("empty\n");                          

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
    listNode* head=h;                           //연결리스트의 헤드노드 생성
	listNode *middle,*trail;               //역순으로 바꾸기위해 중간 과정에서 필요한 노드 생성
    listNode *first=h->rlink;               //역순을 할때 head는 그대로 있고 나머지 노드만 역순을 해야하기 위해 첫 노드의 주소를 받음
	middle=head;                             //역순의 마지막이 head를 가리키기 위해 선언
	while(first!=head)                             //first의 주소가 head일때 까지(연결리스트의 처음)
	{
		trail=middle;                     //trial에 middle의 주소를 전달(처음에는 trail이 head라서 역순의 마지막이 head를 가리키게됨)
		middle=first;                         //처음주소를 middle에 전달
        first=first->rlink;                         //연결리스트의 다음(오른쪽)으로 이동
		middle->rlink=trail;                //trail의 주소를 middle->rlink에 전달
        trail->llink=middle;            //역순이라서 trail의 왼쪽주소(llink)에 middle이 배치되어야한다.
	}
	//연결리스트가 rlink로가면서 middle이 first의 주소를 받고 middle의 주소를 trail이  가지고 있어서 
	//middle->rlink=trail을 통해 역순으로 연결시켜준다
    head->rlink=middle;
    middle->llink=head;
    //새로 연결된 이중 연결리스트의 처음노드의 주소와 head를 연결시켜 다중원형연결리스트 완성
	return 0;
}



/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
    listNode *temp = (listNode*)malloc(sizeof(listNode));
    listNode *head=h;                            //나중에 헤드노드를 주소를 사용하기 위해 선언
    listNode *previous=NULL;                     //이전 노드를 저장하기위한 포인터 구조체 변수 선언
	temp->key = key;
    if(h->rlink==h)                            //헤드노드만 존재할때
    {                                         //헤드노드 오른쪽에  삽입
        head->rlink=temp;                         
        temp->rlink=head;
        head->llink=temp;
        temp->llink=head;
    }
    else                                         //헤드노드말고 다른 노드도 존재할때
    {
     while(h->rlink!=head)                     //연결리스트의 처음 헤드노드 전까지
     {
        h=h->rlink;
        if(h->key>=key)                       //h->key가 key보다 크면
        {
            break;
        }
        previous=h;                          //h->key와 그 이전 사이에 삽입해야 하기때문에 이전 주소를 알고 있어야한다.
     }
     if(previous==NULL)              //맨 처음값이 가장클때 previous=h를 하지않으므로 NULL 값 그대로 가지고 있다.
     {                                //헤드노드 오른쪽에 삽입
        head->rlink=temp;
        temp->llink=head;
        temp->rlink=h;
        h->llink=temp;
     }
     else if(previous->rlink==head)        //입력한값이 가장 클 경우 (h의 다음이 헤드노드일때)
                                            //previous를 한 이유는 h->key에 만족하는 값이 없으면 previous가h와 같아진다.
                                            //그래서 맨뒤에 삽입하고 헤드노드와 연결
     {
         h->rlink=temp;
         temp->rlink=head;
         head->llink=temp;
         temp->llink=h;
     }
     else                           //일반적인경우(다중연결리스트의 두 노드 사이에 삽입할때)
     {                                //previous와h사이에 삽입
     previous->rlink=temp;
     temp->rlink=h;
     temp->llink=previous;
     h->llink=temp;
     }
    }


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
    listNode *head=h;                //연결리스트의 헤더노드 주소를 지정
    listNode *previous=NULL;          //삭제후 연결할 이전 노드주소를 담을 변수 선언
    if(h->rlink!=head)                //헤드노드를 제외한 다른노드가 존재할떼
    {
     do
     {
        h=h->rlink;
        if(h->key==key)            //같은 key의 노드가 있으면
        {
            break;
        }
        previous=h;               //같은 key가 없으면 h의 주소를 받으면서 h의 이전주소를 기억->해당 노드 삭제후 h이전과h이후 노드를 연결해야하기때문
     }while(h->rlink!=head);           //처음부터 head 주소 전까지
     if(previous==NULL)  //헤더노드를 제외한 노드가 1개 있을때 previous는 NULL값을 그대로 가지고 있는다.
     {                           //1개노드 삭제
        head->rlink=h->rlink;
        h->rlink->llink=head;
        free(h);
     }
     else if(previous==h)  //같은key가 없을때
     {
         printf("no key\n");
     }
    //key가 같은 노드(h)를 삭제하기 위해서 이전이랑 이후를 연결
     else
     {
     previous->rlink=h->rlink;
     h->rlink->llink=previous;
     free(h);                       //해당노드 동적할당해제->삭제
     }                             
    }
    else                           //만약 헤드노드만 존재한다면 삭제할수없다는 에러메세지 출력
    {
        printf("empty\n");
    }

	return 0;
}


