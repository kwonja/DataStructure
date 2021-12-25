#include <stdio.h>
int main()
{
int i;
int *ptr;
int **dptr;
i = 1234;
printf("[----- [KwonSungMin] [2018038068] -----]\n");
printf("[checking values before ptr = &i] \n");               
printf("value of i == %d\n", i);                        
printf("address of i == %p\n", &i);                     
printf("value of ptr == %p\n", ptr);                 
printf("address of ptr == %p\n", &ptr);

ptr = &i; /* ptr is now holding the address of i */

printf("\n[checking values after ptr = &i] \n");
printf("value of i == %d\n", i);
printf("address of i == %p\n", &i);
printf("value of ptr == %p\n", ptr);          //ptr의 값이 i의 주소값과 같다
printf("address of ptr == %p\n", &ptr);
printf("value of *ptr == %d\n", *ptr);        //i의 값과 같다.

dptr = &ptr; /* dptr is now holding the address of ptr */
printf("\n[checking values after dptr = &ptr] \n");
printf("value of i == %d\n", i);
printf("address of i == %p\n", &i);
printf("value of ptr == %p\n", ptr);
printf("address of ptr == %p\n", &ptr);
printf("value of *ptr == %d\n", *ptr);
printf("value of dptr == %p\n", dptr);           //ptr의 주소값과 같다
printf("address of dptr == %p\n", &dptr);
printf("value of *dptr == %p\n", *dptr);           //ptr이 가지고 있는 i의 주소값과 같다.
printf("value of **dptr == %d\n", **dptr);          //i의 값과 같다.
*ptr = 7777; /* changing the value of *ptr */ //ptr의 값이 가리키는 주소에 해당하는 값을 바꾼다. ->i의 값이 바뀐다
printf("\n[after *ptr = 7777] \n");
printf("value of i == %d\n", i);
printf("value of *ptr == %d\n", *ptr);
printf("value of **dptr == %d\n", **dptr);
**dptr = 8888; /* changing the value of **dptr */  //dptr의 값이 두번 가리키는 주소에 해당하는 값을 바꾼다.->i의 값이 바뀐다
printf("\n[after **dptr = 8888] \n");
printf("value of i == %d\n", i);
printf("value of *ptr == %d\n", *ptr);
printf("value of **dptr == %d\n", **dptr);
return 0;
}