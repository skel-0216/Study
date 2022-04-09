#include <iostream>

using namespace std;

int main()
{
    int cnt = 0;
    cin >> cnt;

    int* list =new int[cnt];

    for(int i = 0; i < cnt; i++)
    {
        int temp;
        cin >> temp;
        list[i] = temp;
    }

    int temp_max = INT32_MIN;
    int temp_min = INT32_MAX;


    for(int i = 0; i <cnt; i++)
    {
        if(temp_max < list[i])
            temp_max = list[i];

        if(temp_min > list[i])
            temp_min = list[i];
    }

    cout << temp_min << ' ' << temp_max;

    delete list;
    return 0;
}

