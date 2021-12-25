#include <stdio.h>
#define MAX_SIZE 100

float sum(float [],int);
float input[MAX_SIZE],answer;
int i;
void main()
{
    printf("[----- [KwonSungMin] [2018038068] -----]\n");
    for(i=0;i<MAX_SIZE; i++)
    {
        input[i]=i;
    }
    /* for checking call by reference */
    printf("address of input = %p\n", input);
   answer=sum(input,MAX_SIZE);
   printf("The sum is: %f\n",answer);
}

float sum(float list[MAX_SIZE],int n)
{
    printf("value of list = %p\n",list); //input의 주소와 list의 값이 같다
    printf("address of list = %p\n",&list); //list의 주소는 위의 두값과 다르게 나온다.
    //list[]가 포인터처럼 쓰임을 알수있다.
   int i;
   float tempsum=0;
   for(i=0;i<n;i++)
   {
       tempsum+=list[i]; //list가 input의 주소를 가리키기때문에 input[i]와 같은 의미이다.
   }
   return tempsum;

}