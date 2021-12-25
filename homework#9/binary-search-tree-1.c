/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
    printf("[----- [KwonSungMin]  [2018038068] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)          //중위순회
{
	if(ptr)                               //노드가 NULL일때 까지
	{
		inorderTraversal(ptr->left);      //왼쪽으로 재귀함수를 통해 왼쪽 끝노드까지 간다
		printf("[ %d ] ",ptr->key);       //단말노드의 왼쪽이 널이면 그 해당 단말노드 출력
		inorderTraversal(ptr->right);     //출력후 해당 단말노드의 오른쪽으로 이동
	}
}

void preorderTraversal(Node* ptr)          //전위순회
{
	if(ptr)                               //노드가 NULL일때 까지
	{
		printf("[ %d ] ",ptr->key);       //노드를 탐색하면서 노드 출력후
		preorderTraversal(ptr->left);      //왼쪽으로 이동
		preorderTraversal(ptr->right);     //왼쪽으로 이동후 단말노드의 왼쪽이 NULL이면 오른쪽으로 이동
		                                  //오른쪽으로 이동후 단말노드의 오른쪽이 NULL이면 이전 함수로 이동
	}

}

void postorderTraversal(Node* ptr)          //후위순회
{

	if(ptr)                               //노드가 NULL일때 까지
	{
		postorderTraversal(ptr->left);      //왼쪽으로 재귀함수를 통해 왼쪽 끝노드까지 간다
		postorderTraversal(ptr->right);     //단말노드의 왼쪽이 널이면 오른쪽으로 재귀함수를 통해 이동
		 printf("[ %d ] ",ptr->key);      //단말노드의 오른쪽도 NULL이면 그 해당하는 단말노드를 출력
	}

}


int insert(Node* head, int key)                //이진탐색트리 삽입
{
	//새로 삽입할 노드 초기화
	Node* temp=(Node*)malloc(sizeof(Node));
	temp->key=key;
	temp->left=NULL;
	temp->right=NULL;
	Node *node=head->left;

	if(head->left==NULL)     //루트노드가 없을때
	{
		head->left=temp;     //루트노드 삽입
	}
	else
	{
		while(node!=NULL)        //노드가 NULL일때까지
		{
			if(node->key<key)    //노드보다 클때
			{
				if(node->right==NULL)   //오른쪽이 널이면
				{
					node->right=temp;             //단말노드까지 온것이므로 삽입
					break;
				}
				node=node->right;   //오른쪽이 널이 아니면 오른쪽으로 이동
			}
			else                  //부모노드보다 작다면
			{
				if(node->left==NULL)            //왼쪽이 널이면
				{
					node->left=temp;             //parent->left==NULL이면 단말노드까지 온것이므로 삽입
					break;
				}
				 node=node->left;     // 왼쪽이 널이 아니면 왼쪽으로 이동
			}
		}
	}
}

int deleteLeafNode(Node* head, int key)           //단말노드 삭제
{
	Node* ptr=head->left;                    //루트노드를 가리킨다
	Node* previous=NULL;                    //삭제후 이전노드를 NULL로 초기화 해주기 위해서 선언
	int check=0;                           //삭제를 하기위한 체크(0이면 해당 단말노드가 없다고 출력)
	while (ptr)                               //노드가 NULL일때 까지
	{
		if(previous==NULL)                 //루트노드를 삭제할경우
		{
					free(ptr);                     //삭제후
					head->left=NULL;               //헤드노드 왼쪽 초기화
					break;
		}
		if(ptr->key==key)                      //해당노드가 key값이랑 일치하면
		{
			if(ptr->left==NULL&&ptr->right==NULL)   //해당노드가 왼쪽과 오른쪽이 없다->단말노드인지 확인을하고
			{
		        check=1;                            //단말노드면 check에 1대입
				                                    //단말노드로 올때 이전노드에서 왼쪽에서 온지 오른쪽에서 온지 확인
				if(previous->left!=NULL)            //왼쪽 노드가 널이면 발생하는 예외처리
				{
				  if(previous->left->key==key)       //왼쪽으로 해당 왼쪽노드의 key값이 같으면
				  {
					free(ptr);                        //동적할당해제->삭제
					previous->left=NULL;              //삭제후 이전노드가 가리키는곳을 NULL로 초기화
				  }
				}
				if(previous->right!=NULL)         //오른쪽 노드가 널이면 발생하는 예외처리
				{
				 if(previous->right->key==key)    //그 오른쪽의 key값이 일치하면
				 {
					free(ptr);                    //동적할당해제->삭제
					previous->right=NULL;         //삭제후 이전노드가 가리키는곳을 NULL로 초기화
				 }
				}
				break;                          //key값과 일치하는 노드를 삭제후 while문을 나감
			}
		}
		if(ptr->key<key)                           //key값이 현재 노드보다 크면
		{
			previous=ptr;                          //이전노드를 확인하기 위해 대입하고
			ptr=ptr->right;                        //오른쪽으로 이동
		}
		else                                      //key값이 현재 노드보다 작으면
		{
			previous=ptr;                         //이전노드를 확인하기 위해 대입하고
		    ptr=ptr->left;                         //왼쪽으로 이동
		}
	}
	if(check==0)                                   //check가 0이면 key값을 가지고 있는 노드가 없어서 오류 메세지 출력
	{
	   printf("the node [ %d ] is not a leaf\n", key);
	}
}

Node* searchRecursive(Node* ptr, int key)               //재귀함수를 통한 이진탐색트리
{
	if(!ptr) return NULL;                               //노드가 널이면 리턴 NULL
	if(ptr->key==key) return ptr;                        //찾을key를 가지고 있는 노드의 주소를 리턴
	if(ptr->key<key) return searchRecursive(ptr->right,key);//key가 노드보다 크면 오른쪽으로 탐색
	else return searchRecursive(ptr->left,key);             //작으면 왼쪽으로 탐색

}

Node* searchIterative(Node* head, int key)              //재귀함수를 사용하지않은 이진탐색트리
{
	Node* node=head->left;                            //루트노드 선언
	while(node)                                        //노드가 0일때까지 중위순회로 탐색
	{
		if(node->key==key)                             //탐색도중 key와 같은 값을 가지는 노드를 발견하면
		{
		return node;                                   //해당노드의 주소를 리턴
		}
		if(node->key<key)                             //key가 해당노드의 key보다 크면
		node=node->right;                             //오른쪽으로 이동
		else                                          //key가 해당노드의 key보다 작으면
		node=node->left;                             //왼쪽으로 이동
	}
	return NULL;                                     //노드의 key와 key가 같은값이 없으면 NULL을 리턴
}


int freeBST(Node* head)                              //이진탐색트리 동적할당해제
{
	if (head)                         //후위순위(recursive)로 탐색하면서 노드 동적할당해제
	{
		freeBST(head->left);                  //왼쪽으로 가다가 node가 널이되면 탈출
		if (head->right != head)                //head노드에서 오른쪽으로 가면 무한루프에 걸리게 되므로 오른쪽이 자기자신을 가리키는 경우를 제외
		{
			freeBST(head->right);                 //오른쪽으로 이동 후 node가 널이면 탈출
		}
		free(head);                            //왼쪽,오른쪽 노드가 없으면 해당 노드 동적할당 해제
	}
}





