#include <iostream>
#include <string>

using namespace std;

int main()
{
    int count = 0;
    char temp = 0;
    bool space = true;

    while(temp != '\n') 
    {
        temp = getchar();

        switch (temp)
        {
        case ' ':
            space = true;
            break;
        
        default:
            if(space==true)
            {
                ++count;
            }
            space = false;
            break;
        }
    }

    cout << count << endl;
    return 0;
}