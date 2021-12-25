#include <stdio.h>
int main()
{
char charType;                         
int integerType;                  
float floatType;                      
double doubleType;                      
printf("[----- [KwonSungMin] [2018038068] -----]\n");
printf("Size of char: %ld byte\n",sizeof(charType));             
printf("Size of int: %ld bytes\n",sizeof(integerType));            
printf("Size of float: %ld bytes\n",sizeof(floatType));          
printf("Size of double: %ld bytes\n",sizeof(doubleType));         
printf("-----------------------------------------\n");
printf("Size of char: %ld byte\n",sizeof(char));                      
printf("Size of int: %ld bytes\n",sizeof(int));                     
printf("Size of float: %ld bytes\n",sizeof(float));                 
printf("Size of double: %ld bytes\n",sizeof(double));              
 // 실행결과를 보면 자료형에 대한 변수를 선언하면 그 변수는 해당 자료형에 대한 크기를 가진다는 사실을 알수있다.
printf("-----------------------------------------\n");
printf("Size of char*: %ld byte\n",sizeof(char*));                 //char*(포인터) 형의 크기
printf("Size of int*: %ld bytes\n",sizeof(int*));                  //int*(포인터) 형의 크기
printf("Size of float*: %ld bytes\n",sizeof(float*));             //float*(포인터) 형의 크기
printf("Size of double*: %ld bytes\n",sizeof(double*));             //doubler*(포인터) 형의 크기

 //실행결과를 보면 포인터형 변수들의 크기가 4byte로 나온다. 현재 나의 운영체제는 32bit 라는 사실을 알수 있다
return 0;
}