/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>                     //헤더파일 선언
#include <stdlib.h>                   //동적할당을 사용하기위해 선언

#define MAX_QUEUE_SIZE 4               //Queue의 크기를 4로 고정

typedef char element;                  //element라는 이름을 char형 변수로 쓰기위해 선언
typedef struct {                         //큐에 대한 정보를 구조체로 선언
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();                        //큐를 동적할당으로 생성
int freeQueue(QueueType *cQ);                    //큐에대한 동적할당 해제
int isEmpty(QueueType *cQ);                       //큐안에 값이 없는지 확인 하는 함수
int isFull(QueueType *cQ);                        //큐안에 값이 포화상태인지 확인하는 함수
void enQueue(QueueType *cQ, element item);          //값을 추가하는 함수
void deQueue(QueueType *cQ, element* item);          //처음 들어온 값부터 제거하는 함수
void printQ(QueueType *cQ);                             //큐에 대한 정보 출력
void debugQ(QueueType *cQ);                             //큐에 대한 정보 디버깅
element getElement();                                   //큐에 넣을 값을 정하는 함수


int main(void)
{
	QueueType *cQ = createQueue();                                 //큐를 동적할당으로 생성
	element data;                                                    //큐에 넣을 값에 대한 변수
	char command;
	printf("[----- [KwonSungMin]  [2018038068] -----]\n");
	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();              //큐에 넣을 값을 정한다
			enQueue(cQ, data);                //정한 값을 큐에 넣어준다
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);                //큐에 넣은 데이터를 삭제한다.
			break;
		case 'p': case 'P':
			printQ(cQ);                       //큐에 넣은 데이터를 출력한다
			break;
		case 'b': case 'B':
			debugQ(cQ);                        //큐에 넣은 데이터를 디버깅한다
			break;
		case 'q': case 'Q':
			freeQueue(cQ);                    //할당한 큐를 해제한다.
			break;
		default:                            //잘못입력햇을때 에러메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');           //프로그램 종료


	return 1;  //잘성공했다면 1반환
}

QueueType *createQueue()                                 //큐를 생성하는 함수
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));       //큐를 동적할당
	cQ->front = 0;                              //아무값도 받지 않았을때 front와rear를 0으로 정의
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)                        //동적할당을 해제하는 함수
{
	if (cQ == NULL) return 1;                       //큐가 동적할당을 이루지 않았다면, 바로리턴
	free(cQ);                                       //동적할당을  했다면 해제 후 리턴
	return 1;
}

element getElement()                              //큐에 넣을 값을 정하는 함수
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ)                                //큐에 값이 없음을 확인하는 함수
{
	if (cQ->front == cQ->rear)   //원형큐에서는 front와 rear가 같다면 데이터가 없다는의미이다.
	{ //비어있다면 에러메세지 출력
		printf("Circular Queue is Empty");
		return 1;  //큐가 비어있으면 1을 반환
	}
	else
		return 0;   //그렇지 않다면 0을 반환
}

/* complete the function */
int isFull(QueueType *cQ)              //큐에 값이 포화상태임을 확인하는 함수
{   //원형큐에서는 포화상태와 공백상태를 구분하기 위해 한칸을 비워둔다
	//그래서 rear가 한칸 뒤로 갔을때 front와 만나면 포화상태라는 의미이다.
	//여기서 (cQ->rear + 1) % MAX_QUEUE_SIZE 를 한 이유는 q큐는 배열이기때문에 원형큐에서 배열의 마지막자리에서 한칸 더 가면 배열의 첫번째원소이다.
	//따라서 크기만큼 나눠주면 rear가 배열의 크기를 넘어가도 다시 첫번째원소부터 시작하게 된다.
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE==cQ->front)
	{
		printf("Circular Queue is Full");
		return 1;        //큐가 포화상태이면 1을 반환
	}
	else
		return 0;         //그렇지 않다면 0을 반환
}
/* complete the function */
void enQueue(QueueType *cQ, element item) //큐에 데이터를 저장하는 함수
{
	if (!isFull(cQ)) {              //데이터를 저장할 공간이 있다면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;    //rear가 가리키는곳 뒤에 저장을 해야하기때문에 +1을 해줌
		cQ->queue[cQ->rear] = item;                     //rear+1한곳에 데이터를 저장
	}
    return 0;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)        //큐에 데이터를 제거하는 함수
{
	if (!isEmpty(cQ))                             //삭제할 데이터가 존재한다면
	{
		cQ->queue[cQ->front] = NULL;             //front 값은 NULL공백이다->원활한 출력을 위해 사용
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //front +1가 가리키는 데이터 삭제해야 하기 때문에 front+1을 해준다
        cQ->queue[cQ->front] = NULL;             //front가 가리키는 데이터 삭제
	}
    return 0;
}


void printQ(QueueType *cQ)                 //큐에 대한 정보 출력
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; //front+1부터 출력할 정보가 들어있다
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;       //rear까지 출력하기위해서 +1을 해준다.

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)  //큐에 대한 정보 디버깅
                            //현재 어떤 상태로 입력/삭제 되어있는지,front와rear가 현재 어디를 가리키고 있는지 정보 출력
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}