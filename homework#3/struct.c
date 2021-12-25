#include <stdio.h>

struct student1{
    char lastName;
    int studentId;
    char grade;
};
//typedef 없이 구조체 선언

typedef struct{
    char lastName;
    int studentId;
    char grade;
}student2;
//typedef 를 포함한 구조체 선언
int main()
{
    printf("[----- [KwonSungMin] [2018038068] -----]\n");
    struct student1 st1={'A',100,'A'}; //student1 구조체를 가져오려면 struct 를 반드시 써줘야한다.
    printf("st1.lastName = %c\n",st1.lastName);
    printf("st1.studentId = %d\n",st1.studentId);
    printf("st1.grade = %c\n",st1.grade);

    student2 st2={'B',200,'B'};
    //student2 는 typedef를 사용함으로 struct 를 안써줘도 된다.
    student2 st3;
    st3=st2;
    //구조 치환이 가능하다(대입가능)

    printf("\nst3.lastName = %c\n",st3.lastName);
    printf("st3.studentId = %d\n",st3.studentId);
    printf("st3.grade = %c\n",st3.grade);
    //st2에 넣은값과 st3의 값이 같다는것을 알수있다.

    /* equality test */
    /*
    if(st3==st2)                   -> 전체 구조의 동등성 검사는 에러가 난다
    printf("equal\n");                만약 하고싶다면 구조체 멤버변수를 각자 비교해줘야한다.
    else
    printf("not equal\n"); */

    return 0;

}
