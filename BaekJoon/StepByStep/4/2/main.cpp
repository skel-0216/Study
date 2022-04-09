#include <iostream>

using namespace std;

int main()
{
    int input, index = 0;
    int temp_max = INT32_MIN;

    for(int i = 0; i < 9; i++)
    {
        cin >> input;
        if(input > temp_max)
        {
            index = i + 1;
            temp_max = input;
        }
    }

    printf("%d\n%d\n", temp_max, index);

    return 0;
}