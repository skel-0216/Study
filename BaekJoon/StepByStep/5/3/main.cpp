#include <iostream>
#include <vector>

bool check_hans(int a);

int main()
{
    int input;
    std::cin >> input;

    int cnt = 0;
    for(int i = 1; i <= input; i++)
    {
        if(check_hans(i))
            cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}

bool check_hans(int a)
{
    int temp = a;
    std::vector<int> list;
    while(temp > 0)
    {
        list.push_back(temp%10);
        temp /= 10;
    }

    if(list.size() <= 1)
        return true;

    int gap = list.at(0) - list.at(1);
    for(int i = 1; i < list.size() - 1; i++)
    {
        if(gap != (list.at(i) - list.at(i + 1)))
            return false;
    }

    return true;
}
