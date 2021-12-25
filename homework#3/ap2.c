#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [KwonSungMin] [2018038068] -----]\n");
    int list[5];
    int *plist[5];

    list[0]=10;
    list[1]=11;

    plist[0]=(int*)malloc(sizeof(int));

    printf("list[0] \t= %d\n",list[0]);
    printf("address of list \t= %p\n",list);
    printf("address of list[0] \t= %p\n",&list[0]);
    printf("address of list + 0 \t= %p\n", list+0);
    printf("address of list + 1 \t= %p\n", list+1);
    printf("address of list + 2 \t= %p\n", list+2);
    printf("address of list + 3 \t= %p\n", list+3);
    printf("address of list + 4 \t= %p\n", list+4);
    printf("address of list[4] \t= %p\n",&list[4]);

    // 결과를 보면 list에 +1만큼 주소가 4byte씩 증가하는것을 볼수있다.
    //그리고 마지막 &list[4]=list+4 의 값이 동일하다.
    //따라서 list+4 이 16byte만큼 주소가 증가하고 그 증가한곳이 list[4]의 주소임을 알수있다.
    free(plist[0]);
}