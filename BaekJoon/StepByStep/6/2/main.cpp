#include <iostream>

int d(int a);


int main()
{
    bool* list = new bool[10000];
    for(int i = 0; i < 10000; i++)
    {
        list[i] = true;
    }
    for(int i = 0; i < 10000; i++)
    {
        if(d(i) < 10000)
            list[d(i)] = false;
        else
            continue;
    }

    for(int i = 0; i < 10000; i++)
        if(list[i] == true)
            printf("%d\n", i);

    return 0;
}

int d(int a)
{
    int temp = a;
    while(temp > 0)
    {
        a += temp % 10;
        temp /= 10;
    }
    return a;
}