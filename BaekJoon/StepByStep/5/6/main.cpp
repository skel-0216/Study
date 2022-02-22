#include <iostream>
#include <string>

using namespace std;

int main()
{
    int num;
    cin >> num;

    string* list = new string[num];
    for(int i = 0; i < num; i++)
    {
        cin >> list[i];
    }

    for(int i = 0; i < num; i++)
    {
        int sum = 0;
        int temp = 1;
        for(int j = 0; j < list[i].length(); j++)
        {
            if(list[i][j] == 'O')
            {
                sum += temp;
                temp++;
            }
            else
                temp = 1;
        }
        printf("%d\n", sum);
    }


    return 0;
}