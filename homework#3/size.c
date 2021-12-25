#include <stdio.h>
#include <stdlib.h>

void main()
{
    int **x;
    printf("[----- [KwonSungMin] [2018038068] -----]\n");
    //포인터 변수는 32bit운영체제에서 4byte크기를 갖는다.
    //현재 내 운영체제는 32bit이다.
    printf("sizeof(x)=%lu\n",sizeof(x));   //x는 포인터변수값을 갖는다->4바이트 출력
    printf("sizeof(*x)=%lu\n",sizeof(*x)); //위와 마찬가지로 4바이트 출력
    printf("sizeof(**x)=%lu\n",sizeof(**x));
    //위와 같이 4byte크기가 출력되지만, **x은 int값을 갖고 있어서
    //포인터 변수가 아닌 정수형(int형)의 크기인 4byte를 의미한다.

}