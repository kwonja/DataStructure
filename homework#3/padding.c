#include <stdio.h>

struct student{
    char lastName[13];   //13byte
    int studentId;      //4byte
    short grade;        //2byte
};

int main()
{
    struct student pst;
    printf("[----- [KwonSungMin] [2018038068] -----]\n");
    printf("size of student = %ld\n",sizeof(struct student)); //typedef를 사용하지 않아서 struct를 붙여줌
    /*
    구조체의 바이트를 전부 더하면 19byte인데 출력은 24가 나온다.
    이말은 패딩이 일어났다는 말인데, 구조체는 메모리를 생성할때 구조체 멤버 변수중 자료형이 가장큰것을 기준으로 한다.
    pst는 int형 변수가 가장크기때문에 4byte에 맞춰 정렬한다.
    lastName[13]의 경우에도 마지막 lastName[12]가 4byte 메모리에 들어가고 3byte가 남는데
    이를 padding 하고,
    grade 는 2byte가 들어가고 2byte가 남아서 이를 padding 해서,
    총 5byte를 더 padding 했기 때문에 19+5=24, 24바이트가 출력된것이다.
    */
    printf("size of int = %ld\n",sizeof(int));
    printf("size of short = %ld\n",sizeof(short));
}