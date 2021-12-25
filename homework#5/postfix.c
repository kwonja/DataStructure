/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>                                         //헤더파일 선언
#include<stdlib.h>                                        
#include<string.h>                                        //strncpy(),strncat() 을 사용하기 위해 선언

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x);   //postfixStack 배열 안에 연산자를 넣는다
char postfixPop();           //postfixStack배열에 가장 나중에 들어온 값을 꺼낸다.
void evalPush(int x);          //evalStack 배열 안에 연산자를 넣는다
int evalPop();                 //evalStack 배열에 가장 나중에 들어온 값을 꺼낸다
void getInfix();
precedence getToken(char symbol);    //infix로 들어온 값을 숫자로 바꿔줌
precedence getPriority(char x);       //getToken에 들어온 값을 반환
void charCat(char* c);                //postfixExp에 문자열을 저장해주기 위한 함수
void toPostfix();                     //infix값을 후위연산자로 변환하는 함수
void debug();                          //현재 어떻게 진행되는지 출력해주는 함수
void reset();                          //infix를 입력받기 전 데이터로 돌아가는 함수
void evaluation();                     //postfixExp로 바뀐 infixExp를 계산하는 함수

int main()
{
	char command;
	printf("[----- [KwonSungMin]  [2018038068] -----]\n");
	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)                   //postfixStack에 연산자를 저장하는 함수
{
	postfixStack[++postfixStackTop] = x;     //top이 가리키고있는곳에 +1한 곳에 새로운 연산자 저장
}

char postfixPop()                        //postfixStack에 있는 연산자를 꺼내는 함수
{
	char x;                              //꺼내는 연산자를 받는 변수
	if (postfixStackTop == -1)            //top=-1이면 꺼낼것이 없다.
		return '\0';
	else {                                               //꺼낼것이 있다면
		x = postfixStack[postfixStackTop--];            //현재 top이 가리키고 있는 postfixStack배열의 값을 x에 꺼내고 top을 1만큼 내려준다.
	}
	return x;                                        //꺼낸값 반환
}

void evalPush(int x)                                //evalStack에 계산하는 값을 저장하는 함수
{
	evalStack[++evalStackTop] = x;                  //x에 값을 top+1 이 가리키는 곳에 저장
}

int evalPop()                                      //evalStack에서 값을 꺼내는 함수
{
	if (evalStackTop == -1)                        //top이 -1 이면 꺼낼값이 없다
		return -1;
	else                                               //꺼낼값이 있으면
		return evalStack[evalStackTop--];              //evalStack에서 top이 가라키는 값을 꺼내고 top을 -1 해준다.
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()                                 //infix값을 입력받는 함수
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);
}

precedence getToken(char symbol)                // getToken 함수로 연산자를 받으면 숫자로 변경해 쉽게 연산자 우선순위를 구별할수있다
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}
}

precedence getPriority(char x)              ////getToken에 들어온 값을 반환-> 우선순위 비교를 한다는것을 쉽게 알기위해서 따로 선언
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	char x1; //postfixPop이 반환하는 값을 전달하기위해 임시로 사용하는 변수

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')      //exp가 널(문장의 끝)이 아니면
	{
		x = *exp;                             //infix의 값을 x에 전달
		if (getToken(x) == operand)           //연산자가 아닌 일반 숫자(operand)라면
			charCat(&x);                      //postfixExp에 바로 붙여준다.
		else if (getToken(x) == rparen)       //만약 오른쪽 괄호가 나온다면
		{
			while (getToken(postfixStack[postfixStackTop]) != lparen)    //왼쪽괄호가 나오기전까지
			{
				x1 = postfixPop();           //postfitStack배열에 푸시됬던 연산자를 반환
				charCat(&x1);               //반환된 값을 postfixtExp에 붙인다.
			}
			x1=postfixPop();               //왼쪽괄호도 빼야하기때문에 마지막에 pop을 해줌 -> postfixPop 함수가 반환값이 있어서 일단은 x1에 준다.
		}                                   //어짜피 버려지는값이라서 왼쪽에 어떤변수가 오던 상관없다.
		else    //연산자가 getToken에 들어왔다면
		{
			if (getToken(x)!=lparen)   //(가 처음으로 들어왔다면 바로 push할수 있도록 설정 -> *( 이렇게 연속되면 (가 먼저인데 0이라서 *가 먼저라고 인식
			{
				if (getPriority(postfixStack[postfixStackTop]) >= getPriority(x))
					//만약 새로 받은 연산자가 기존이 postfixStack의 top에 있는 것보다 우선순위가 높다면
				{
					x1 = postfixPop(); //top에 있는 값을 꺼내고
					charCat(&x1);      //postfixExp에 붙인다
				}
			}

			postfixPush(x);  //x에 대한 정보를 postfixStack의 top+1에 저장
		}
		exp++;  //exp가 가리키는곳을 한칸씩 증가시킨다
	}
	//infix의 값을 사용하고 나왔을때
	//postfixStack에 연산자가 남아있으면 postfixexp에 마저 붙여줘야한다.
	while(postfixStackTop!=-1) 
	{
		x1 = postfixPop();   //임시변수에 꺼낸값을 반환
		charCat(&x1);        //postfixExp에 붙인다.
	}

}
void debug()                               //프로그램이 어떻게 진행되고있는지 출력하는 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()                          //infix를 입력해주기 전 상태로 돌아가게 하는 함수
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()                                 //postfixExp에 저장된 후위연산의 결과를 계산하는 함수
{
	/* postfixExp, evalStack을 이용한 계산 */
	char *exp;                  //postfixExp의 주소를 받을 변수
	int op1, op2;               //연산할 두 오퍼랜드 선언
	exp = postfixExp;           //postfixExp의 주소를 exp에 전달
	while (*exp != '\0')         //exp문장의끝 NULL값을 가지고 있다->문장이 끝나면 종료
	{
		if (getToken(*exp) == operand)  //exp의 값이 연산자가 아니면
			evalPush(*exp - '0');       //evalPush은 int형을 반환하기때문에 아스키코드 '0'(48)을 빼줘서 int값으로 처리해줌
		else                          //exp의 값이 연산자이면
		{
			op1 = evalPop();                   //연산자를 받기전 값을 꺼내고
			op2 = evalPop();                   //그 전에 들어온 값을 꺼내
			switch (*exp)                      //들어온 연산자에 맞춰서 계산해준다
			{
			case '*':                       //곱셈의 경우
				evalResult = op2 * op1;
				evalPush(evalResult);        //연산결과를 evalStack배열의 top+1에 저장
				break;
			case '/':                       //나눗셈의 경우
				evalResult = op2 / op1;
				evalPush(evalResult);       //연산결과를 evalStack배열의 top+1에 저장
				break;
			case '+':                      //덧셈의 경우
				evalResult = op2 + op1;
				evalPush(evalResult);      //연산결과를 evalStack배열의 top+1에 저장
				break;
			case '-':                    //뺄셈 의 경우
				evalResult = op2 - op1;
				evalPush(evalResult);   //연산결과를 evalStack배열의 top+1에 저장
				break;
			}
		}
		//결과를 마치면 evalResult에 최종 결과값이 저장되어 있다.
		exp++;  //exp가 가리키는곳을 한칸씩 증가시킴
	}

}