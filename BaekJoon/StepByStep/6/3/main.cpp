#include <iostream>
#include <string>

using namespace std;

int main()
{
    string input;
    cin >> input;

    for(int i = 0; i < 'z'-'a' + 1; i++)
    {
        char temp;
        int pos = -1;
        for(int j = 0; j < input.length(); j++)
        {
            if((input[j]-'a') == i)
            {
                pos = j;
                break;
            }
        }
        cout << pos << ' ';
    }
    cout << endl;
    return 0;
}