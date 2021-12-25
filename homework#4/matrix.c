#include <stdio.h>
#include <stdlib.h>                                //랜덤함수를 사용하기 위해 선언
#include <time.h> 

/* Method Declaration */
int** create_matrix(int row, int col); 
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

	char command;
	printf("[----- [KwonSungMin]  [2018038068] -----]\n");

	int row, col;
	srand(time(NULL));                  //랜덤함수를 사용하기 위해 선언

	printf("Input row and col : ");
	scanf("%d %d", &row, &col);
	//행렬 동적할당
	int** matrix_a = create_matrix(row, col);
	int** matrix_b = create_matrix(row, col);
	int** matrix_a_t = create_matrix(col, row);

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) 
	{ return -1; }      //동적할당이 제대로 이뤄지지 않았다면 -1을 반환

	do {
		//메뉴출력
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'z': case 'Z':                      //행렬초기화
			printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);
			fill_data(matrix_b, row, col);
			break;
		case 'p': case 'P':                      //행렬출력
			printf("Print matrix\n");
			printf("matrix_a\n");
			print_matrix(matrix_a, row, col);
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break;
		case 'a': case 'A':                      //두 행렬을 더한다
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
		case 's': case 'S':                     // 두 행렬을 뺀다
			printf("Subtract two matrices \n");
			subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
		case 't': case 'T':                   //행렬a를 전치행렬로 만든다
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
			print_matrix(matrix_a_t, col, row);
			break;
		case 'm': case 'M':                    //행렬a와 전치행렬을 곱한다.
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
			multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
		case 'q': case 'Q':                   //행렬의 동적할당을 풀어준다.
			printf("Free all matrices..\n");
			free_matrix(matrix_a_t, col, row);
			free_matrix(matrix_a, row, col);
			free_matrix(matrix_b, row, col);
			break;
		default:                                 //다른 커멘트를 눌렀을때 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');             //q또는Q를 눌렀을때 종료
	return 1;                                               //실행이 정상적으로 되었을때 1리턴
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	/* check pre conditions */
	if (row <= 0 || col <= 0)             //열과 행은 항상 0이상이여야한다
	{                                     //그렇지 않으면 에러 메세지 출력
		printf("Check the sizes of row and col!\n");
		return NULL;                     
	}
	//에러가 없다면 정상적으로 2차원배열 동적할당
	int**matrix = (int**)malloc(sizeof(int*)*row);    

	for (int i = 0; i < row; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int)*col);
	}

	if (matrix == NULL) //동적할당이 제대로 이뤄지지 않았다면
	{
		printf("matrix가 생성되지 않았습니다");
		/* proper actions for unexpected conditions */
	}

	return matrix;    //할당된 메트릭스 주소 반환
}
/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf("%5d", matrix[i][j]);                   //행렬의 값을 출력
		}
		printf("\n");
	}
	//반환값이 없기 때문에 후처리 검사는 하지 않는다.
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* check pre conditions */
	if (row <= 0 || col <= 0)      //열과 행은 항상 0이상이여야한다
	{
		printf("Check the sizes of row and col!\n");
		return -1;                 //입력이 잘못되었으면 에러 메세지를출력하고 -1반환
	}
	for (int i = 0; i < row; i++)
	{
		free(matrix[i]);        
	}
	free(matrix);
	//heap영역에 할당된 메모리를 풀어줌
	return 1;                     //실행이 정상적으로 됬다면 1 리턴
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* check pre conditions */
	if (row <= 0 || col <= 0)                        //열과 행은 항상 0이상이여야한다
	{
		printf("Check the sizes of row and col!\n");
		return -1;                                   //입력이 잘못되었으면 에러 메세지를출력하고 -1반환
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix[i][j] = rand() % 20;         //행렬에 0~19사이의 임의숫자를 넣어줌
		}

	}
	return 1;                             //실행이 정상적으로 됬다면 1리턴
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
	/* check pre conditions */
	if (row <= 0 || col <= 0)              //열과 행은 항상 0이상이여야한다
	{
		printf("Check the sizes of row and col!\n");
		return -1;                                    //입력이 잘못되었으면 에러 메세지를출력하고 -1반환
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf("%5d", matrix_a[i][j] + matrix_b[i][j]);              //행렬a+행렬b
		}
		printf("\n");
	}

	return 1;                                  //실행이 정상적으로 됬다면 1리턴
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
	/* check pre conditions */
	if (row <= 0 || col <= 0)          //열과행은 항상 0이상이어야한다.
	{
		printf("Check the sizes of row and col!\n");
		return -1;                           //입력이 잘못되었으면 에러 메세지를출력하고 -1반환
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			printf("%5d", matrix_a[i][j] - matrix_b[i][j]); //행렬a-행렬b
		}
		printf("\n");
	}
	return 1;                          //실행이 정상적으로 됬다면 1리턴
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* check pre conditions */
	if (row <= 0 || col <= 0)                    //열과 행은 항상 0이상이어야한다          
	{
		printf("Check the sizes of row and col!\n");
		return -1;                              //입력이 잘못되었으면 에러 메세지를출력하고 -1반환
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			matrix_t[j][i] = matrix[i][j];                   //(행,열) 을 (열,행) 으로 바꾼다.
		}
	}
	return 1;                             //실행이 정상적으로 됬다면 1리턴
}

/* matrix_axt = matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
	int matrix_axt = 0;
	/* check pre conditions */
	if (row <= 0 || col <= 0)                        //행과열은 항상0이상이여야한다.
	{
		printf("Check the sizes of row and col!\n");
		return -1;                                  //입력이 잘못되었으면 에러 메세지를출력하고 -1반환
	}
	for (int i = 0; i < row; i++)      //_a의 행 개수
	{
		for (int j = 0; j < row; j++)   //_t의 열개수=_a의 행 개수
		{
			matrix_axt = 0;           //행렬곱에 대한 값을 저장하는 변수
			for (int k = 0; k < col; k++)           //_a의 열개수=_t의 행 개수
			{
				matrix_axt += matrix_a[i][k] * matrix_t[k][j];   //(_a의 i행과 _t의 j열의 곱)의 합이 at(ij)의 값
			}
			printf("%5d", matrix_axt);
		}
		printf("\n");
	}

	return 1;                             //실행이 정상적으로 됬다면 1리턴
}