#include <stdio.h>
#include <stdlib.h>

void main()
{
    printf("[----- [KwonSungMin] [2018038068] -----]\n");
    int list[5];
    int *plist[5]={NULL,};    //배열 포인터 선언

    plist[0]=(int *)malloc(sizeof(int));   //plist[0]에 heap 영역에서 할당한 주소값을 줌

    list[0]=1;           //list[0]에 1 대입
    list[1]=100;         //list[1]에 100 대입

    *plist[0]=200;       //plist[0]이 200에 해당하는 값을 가지는 주소를 가짐-> 그 주소가 200을 가리킨다.

    printf("value of list[0] = %d\n",list[0]);
    printf("address of list[0]       = %p\n",&list[0]);
    printf("value of list            = %p\n",list);
    printf("address of list (&list)  = %p\n",&list);
    //배열의 이름과 배열의 첫번째 원소의 주소와 배열의 주소가 같다.

    printf("---------------------------------------------\n\n");
    printf("value of list[1]         = %d\n",list[1]);
    printf("address of list[1]       = %p\n",&list[1]);
    printf("value of *(list+1)       = %d\n",*(list+1)); //list[1]과 같다.
    printf("address of list+1        = %p\n", list+1);
    //list+1 과 list[1]의 주소값이 같다는 사실을 알수 있다.
    //주소는 list가 int형이라서 (list+1)을 해주게 되면 4byte만큼 증가
    //4만큼 증가한곳이 (list+1)이 위치한 주소이다.

    printf("---------------------------------------------\n\n");
    printf("value of *plist[0]       = %d\n",*plist[0]);     //*plist[0]이 가리키는 값 200 출력
    printf("&plist[0]                = %p\n",&plist[0]);
    printf("&plist                   = %p\n",&plist);
    printf("plist                    = %p\n",plist);
    //포인터 배열의 이름과 배열의 첫번째 원소의 주소와 배열의 주소가 같다..
    printf("plist[0]                 = %p\n",plist[0]); //plilst[0]은 200의 주소를 담고있다.
                                                        //이 주소는 heap영역에 할당된 주소이다.
    printf("plist[1]                 = %p\n",plist[1]);
    printf("plist[2]                 = %p\n",plist[2]);
    printf("plist[3]                 = %p\n",plist[3]);
    printf("plist[4]                 = %p\n",plist[4]);
    //plist[1]부터 plist[4]까지는 널로 초기화해서 결과에 널값이 나온다.

    free(plist[0]);
    //동적할당 해제

}