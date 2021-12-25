#include <stdio.h>
void print1(int*ptr,int rows);

int main()
{
    int one[]={0,1,2,3,4};
    printf("[----- [KwonSungMin] [2018038068] -----]\n");
    printf("one      = %p\n",one);
    printf("&one     = %p\n",&one);
    printf("&one[0]  = %p\n", &one[0]);
    printf("\n");

    print1(&one[0],5);
    //one[0]의 주소를 ptr에 준다.

    return 0;
}

void print1(int *ptr,int rows)
//포인터를 통해 one배열의 주소값을 참조한다.
{/* print out a one-dimensional array suing a pointer */
   int i;
   printf("Address \t Contnets\n");
   for(i=0;i<rows;i++)
   {
       printf("%p \t  %5d\n",ptr+i,*(ptr+i));
   }
   //주소가 4씩 증가하면서 one[0]부터 one[4]까지의 값의 주소를 가리킨다는 사실을 알수있다.
   printf("\n");

}