#include <iostream>

int main()
{
    int nums[10];
    int cnt = 0;

    for(int i = 0; i<10;i++)
    {
        std::cin >> nums[i];
        nums[i] %= 42;
    }
    for(int i = 0; i < 10; i++)
    {
        int j;
        for(j = 0; j < i; j++)
        {
            if(nums[i] == nums[j]) break;
        }
        if(i==j) cnt++;
    }

    printf("%d\n", cnt);

    return 0;
}