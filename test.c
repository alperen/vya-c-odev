#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    while(1){
        Sleep(1000);

        int x = rand();

        printf("%d %d \n",x, x % 30 + 10);
    }
    return 0;
}
