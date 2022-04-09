#include <iostream>

using namespace std;

int main()
{
    int result = 1;

    for(int i = 0; i < 3; i++)
    {
        int temp;
        cin >> temp;

        result *= temp;
    }

    int cnt[10];

    for(int i = 0; i < 10; i++)
        cnt[i] = 0;

    while(result > 0)
    {
        int temp = result % 10;
        result /= 10;
        cnt[temp] += 1; 
    }

    for(int i = 0; i < 10; i++)
    {
        cout << cnt[i] << endl;
    }
    return 0;
}