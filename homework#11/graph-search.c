#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 10                 //최대 정점의 수를 10개로 정의
typedef struct list {                //인접리스트에 삽입할 노드 구조체
	int vertex;
	struct list *list;
} list;

typedef struct Graph                //정점의 개수와 인접리스트를 가질 그래프 구조체
{
	int s_vertex;
	list *adjLists[MAX_VERTEX];       //각 정점에 인접항을 연결할 리스트 구조체 배열 선언
	int visited[MAX_VERTEX];          //정점의 방문여부를 저장할 visited 배열
}Graph;


//구현한 함수//
Graph* initializeGraph(Graph *g);            //그래프 초기화                   
void freeGraph(Graph *g);                    //그래프 동적할당 해제
void insertVertex(Graph* g);                     //정점삽입
void insertEdge(Graph* g, int front, int rear);    //두 정점의 연결
void DFS(Graph *g, int v);                          //DFS방법을 이용한 탐색
void BFS(Graph *g, int v);                          //BFS방법을 이용한 탐색
void PrintGraph(Graph *g);                         //그래프의 인접리스트를 출력

//BFS에 사용될 큐
#define MAX_QUEUE_SIZE		10           //최대 정점의 개수가 10개이므로 큐 역시 10개까지 담을수 있다
int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int deQueue();
void enQueue(int vertex);



int main()
{
	Graph* head = NULL;
	char command;
	int u;
	int v;
	int key;
	printf("[----- [KwonSungMin]  [2018038068] -----]\n");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph       = z                                       \n");
		printf(" Insert Vertex          = v      Insert Edge               = e \n");
		printf(" Depth First Search     = d      Breath First Search       = b \n");
		printf(" Print Graph            = p      Quit                      = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			head=initializeGraph(head);
			break;
		case 'q': case 'Q':
			freeGraph(head);
			break;
		case 'v': case 'V':
			insertVertex(head);
			break;
		case 'e': case 'E':
			printf("front : ");
			scanf("%d", &u);
			printf("rear : ");
			scanf("%d", &v);
			//무방향 그래프로 만들기위해서 두번 선언
			insertEdge(head,u, v);
            insertEdge(head,v, u);
			break;

		case 'd': case 'D':
			printf("first : ");
			scanf("%d", &key);
			DFS(head, key);
			//DFS를 하고 나면 visited가 1로 되어있는데, 다른 방법도 하기위해서 따로 초기화
			for (int i = 0; i < MAX_VERTEX; i++)
			{
				head->visited[i] = 0;   //1이면 다녀간것
			}
			break;
		case 'b': case 'B':
			printf("fisrt : ");
			scanf("%d", &key);
			BFS(head, key);
			//BFS를 하고 나면 visited가 1로 되어있는데, 다른 방법도 하기위해서 따로 초기화
			for (int i = 0; i < MAX_VERTEX; i++)
			{
				head->visited[i] = 0;   //1이면 다녀간것
			}
			break;
		case 'p': case 'P':
			PrintGraph(head);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}
//그래프를 초기화
Graph* initializeGraph(Graph *g)
{
	if (g != NULL)                                //그래프가 초기화가 되어있다면
		freeGraph(g);                            //동적할당해제


	g = (Graph*)malloc(sizeof(Graph));
	g->s_vertex = 0;                          //그래프의 정점은 처음에 0
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		g->adjLists[i]= NULL;                //인접리스트를 null로 초기화
		g->visited[i] = 0;   //1이면 다녀간것
	}

	return g;
}
//동적할당한 그래프 동적할당해제
void freeGraph(Graph *g)                  
{
	if (g)  //그래프가 NULL값이 아니라면
	{
		free(g);     //동적할당해제
	}
}
//그래프에 정점 삽입
void insertVertex(Graph* g)
{
	if (g->s_vertex >= MAX_VERTEX)               //10개면 최대 개수
	{
		printf("full vertex\n");                //더이상 추가할수없음을 알려준다,
		return;
	}
	g->s_vertex++;                      //주어진 조건이 최대10개 일때 정점번호가 0~9이므로 최대개수를 알면 정점의 개수와 번호를 알수있다.

}

//정점간에 간선 연결
//인접리스트를 구성할때 오른쪽으로 오름차순이 되도록 삽입(작은순으로)
void insertEdge(Graph* g, int front, int rear)
{
	list* p;                       //각 정점의 인접리스트를 따라가기 위한 리스트 변수 선언
	list *previous = NULL;         //이전 리스트를 기억할 변수 선언
	p = g->adjLists[front];             //front->rear 형식으로 연결하기 때문에 front의 인접리스트는 rear를 vertex로 가짐
	if (front >= g->s_vertex || rear >= g->s_vertex)   //정점의 개수보다 더 큰 정점이 들어오면 오류메세지 출력
	{
		printf("no vertex\n");
		return;
	}
	if (front < 0 || rear < 0)   //음수가 들어오면 오류메세지 출력
	{
		printf("no vertex\n");
		return;
	}
	list* node = (list*)malloc(sizeof(list));               //삽입할 리스트노드 생성
	node->vertex = rear;                                    //rear를 vertex값으로 삽입
	node->list = NULL;        
	if (g->adjLists[front] == NULL)                        //인접한 정점이 없을때
	{
		g->adjLists[front] = node;                        //해당 리스트노드를 대입
	}
	else
	{
		for (; p; p=p->list)
		{
			if (p->vertex == rear)              //리스트의 정점과 rear이 같으면 이미 생성된 간선이라서 오류메세지 출력
			{
				printf("can`t make\n");     
				return;                         //함수 종료
			}
			if (p->vertex > rear)              //front를 정점으로 가지는 인접항중 rear보다 크면
			{
				break;                         //for문을 나감
			}
			previous = p;                     //이전노드를 저장하기위해 선언
		}
		if (p == g->adjLists[front])         //가장 큰 인접항이 인접리스트의 첫번째면 그 앞에 리스트노드  삽입
		{
			node->list = g->adjLists[front];
			g->adjLists[front] = node;
		}
		else                               //두 인접항 사이에 삽입
		{
			node->list = p;
			previous->list = node;
		}
	}

}

//DFS 탐색 방법 V 부터 탐색, 작은 번호의 vertex부터 탐색-> 인접리스트를 작은 인접항순으로 정렬해두었음
void DFS(Graph *g,int v)
{
	list *w;
	g->visited[v] = 1;              //v를 탐색했으니 1을 대입
	printf("[ %d ]", v);
	for (w = g->adjLists[v]; w; w = w->list)           //v에 인접한 리스트를 쭉 따라가면서
	{
		if (!g->visited[w->vertex])                   //그 인접항리스트의 정점을 지나가지않았다면
		{
			DFS(g , w->vertex);                       //DFS 순환 호출
		}
	}
}
//BFS 탐색 방법 V부터 탐색, 작은 번호의 vertex부터 탐색-> 인접리스트를 작은 인접항순으로 정렬해두었음
void BFS(Graph *g, int v)
{
	list* w;
	front = rear = -1;                 //q 초기화
	printf("[ %d ]", v);
	g->visited[v] = 1;                 //방문한 정점 확인
	enQueue(v);                        //처음 방문한 정점을 큐에 삽입
	while (1)
	{
		v = deQueue();                //큐에 넣은 정점을 반환
		if (v == 9999)                //rear과 front가 같은경우, 9999를 반환==큐에 더이상 정점이 없다(다 탐색했다는 의미)
		{
			break;
		}
		for (w = g->adjLists[v]; w; w = w->list)                  //큐에서 반환받은 정점의 인접항들을 방문
		{
			if (!g->visited[w->vertex])                           //방문하지 않았다면
			{
				printf("[ %d ]", w->vertex);
				enQueue(w->vertex);                               //큐에 삽입하고
				g->visited[w->vertex] = 1;                        //방문한 정점이라고 체크
			}

		}
	}
}

int deQueue()               //queue-dequeue
{
	if (rear == front)            //rear과 front가 같으면 데이터가 없는것이므로
	{
		return 9999;           //NULL리턴
	}
	return queue[++front];     //데이터가 있으면 front의 시작이 -1 이기때문에 ++front가 가리키는 인덱스의 주소를 리턴
}

void enQueue(int vertex)
{
	if (rear >= MAX_QUEUE_SIZE - 1)      //rear 배열의크기를 넘어가는 경우 에러메세지 출력
	{
		printf("full\n");
	}
	else                            //배열의 크기를 넘어가지 않았다면 데이터 저장
	{
		queue[++rear] = vertex;
	}

}

//그래프의 인접리스트 출력
void PrintGraph(Graph *g)
{
	list *p;
	for (int i = 0; i < g->s_vertex; i++)
	{
		p = g->adjLists[i];
		printf("adjlist of vertex[ %d ] : ", i);
		for (; p; p = p->list)
			printf(" [ %d ]", p->vertex);
		printf("\n");
	}
}