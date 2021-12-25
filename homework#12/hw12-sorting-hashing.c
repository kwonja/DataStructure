/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
	printf("[----- [KwonSungMin]  [2018038068] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

//선택 정렬
//배열중에서 가장 작은 값을 찾아서 a[0],a[1] 순서대로 스왑하면서 정렬(오름차순)
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];   //가장 작은값 임의로 지정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			//반복문을 돌면서 배열중 가장 작은 값을 찾는다
			if (min > a[j])
			{
				min = a[j];  //배열의 원소가 min보다 작으면 해당 원소가 작은값임
				minindex = j;  //작은값의 인덱스 저장
			}
		}
		//가장 작은값과 a[i]의 값을 스왑
		a[minindex] = a[i];    
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	//정렬후 결과확인을 위한 배열 출력
	printArray(a);
	return 0;
}
//삽입정렬
//왼쪽을 정렬된 case로,오른쪽을 정렬되지않는 case로 나눈후
//오른쪽의 case에서 원소를 1개씩 가져와 정렬된 case에 넣어 정렬시키는 방식
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);
	//원소가 1개있으면 자동으로 정렬된것으로 인지해서 i=1부터 시작
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
	//비정렬된 case a[i]의 정보를 저장
		t = a[i];
		j = i;
		//정렬된케이스의 원소보다 t가 크면
		//정렬을 하기위해서 계속 뒤로간다
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];
			j--;
		}
		//while문을 빠져나오면 빈 공간이 생기는데, 그곳에 값을 넣어주면 정렬이 된다.
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	//정렬후 결과확인을 위한 배열 출력
	printArray(a);

	return 0;
}

//a[i],a[i+1] 처럼 인접한 두항을 비교해 나가면서 제일 큰 값을 맨 뒤로 보내면서 정렬한다
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		//j=0부터 하게되면 a[-1]과 비교하는 경우가 생겨서 j=1로 수정
		//시간적 효율을 위해서 max_array_size-1로 수정->맨오른쪽에 가장 큰 원소를 넣으면 그곳은 더이상 탐색할 필요가 없음
		for (j = 1; j < MAX_ARRAY_SIZE-i; j++)
		{
			//만약 a[j-1]이 더 크면
			if (a[j-1] > a[j])
			{
				//스왑
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

//셸 정렬
//h만큼 떨어진 배열의 원소들과 삽입정렬과 같은 탐색을 한다
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	//간격 h를 정의
	{
		for (i = 0; i < h; i++)
		{
			//간격수만큼 반복
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				//삽입정렬 과 같은 알고리즘
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					//왼쪽 원소가 오른쪽보다 크면 오른쪽에 대입
					a[k] = a[k-h];
					k -= h;
				}
				//오른쪽에 대입하다가 while문이 끝나면 주고남은 공간이 있는데,그곳에 삽입
				//오른쪽원소가 가장크면 그대로
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
//퀵 정렬
//기준값을 중심으로 왼쪽 부분집합과 오른쪽부분집합으로 분할하여 정렬한다
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		//기준값 정의->맨 오른쪽이 기준점이다
		v = a[n-1];
		//맨 왼쪽
		i = -1;
		//맨 오른쪽
		j = n - 1;

		while(1)
		{
			//왼쪽부터 기준값 보다 작으면 반복
			while(a[++i] < v);
			//오른쪽부터 기준값 보다 크면 반복
			while(a[--j] > v);
			//왼쪽이 오른쪽이랑 같아지거나 넘어가면 중지
			if (i >= j) break;
			// 왼쪽과 오른쪽 노드를 스왑
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		//i와j가 같아져서 나오면
		//그 같아진 원소를 기준점과 스왑
		//오른쪽으로 가면서 더 커지기때문에 i를 기준점과 스왑
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		//이 알고리즘을 계속 반복
		quickSort(a, i);   //왼쪽
		quickSort(a+i+1, n-i-1);//오른쪽
	}


	return 0;
}
//key를 해쉬테이블 사이즈로 나눠서 나온 나머지를 통해 해쉬테이블의 주소에 접근
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

//해싱함수
int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	//해쉬 테이블 초기화
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)

	//선형조사법 방식으로 해싱 함수 구현
	//버컷의 슬롯은 1개이다.
	//배열의 개수와 해싱테이블의 사이즈가 같아서, 슬롯이1개일때 전부
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
	//해쉬 테이블 버킷에 아무것도 들어가 있지 않을때
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1) //무언가 들어가 있으면
			{
				//그 다음주소를 인덱스로 가짐
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			//다음 주소로 넘어가면서 빈공간을 찾으면 대입
			hashtable[index] = key;
		}
	}

	return 0;
}
//key값에 대해서 해싱함수로 인해 만들어진 해싱테이블을 통해서 해당 key값의 주소를 리턴
//탐색의 속도가 빠르다
int search(int *ht, int key)
{
	int index = hashCode(key);
	if(ht[index] == key)
		return index;

    //key를 해생테이블 주소 개수로 나눈 나머지에 해당하는 해싱테이블의 주소에 key값이 없을 경우
	//선형조사법 방식으로 해싱테이블을 구성했기때문에 차례로 내려가면서 해당 인덱스에 key값이 있는지 확인
	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
	//있으면 그 index(주소) 리턴
}