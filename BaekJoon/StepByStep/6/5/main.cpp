#include<iostream>
#include<string>

using namespace std;

void to_upper(string& input)
{
    for(int i = 0; i < input.length(); i++)
    {
        if(input[i] >= 'a')
        {
            input[i] -= ('a'-'A');
        }
    }
}

int main()
{
    string input;
    int count['z' - 'a' + 1];

    // initialize count
    for(int i = 0; i < 'z'-'a'+1; i++)
    {
        count[i] = 0;
    }

    cin >> input;

    to_upper(input);
    // count alphabets
    for(int i = 0; i < 'z'-'a'+1; i++)
    {
        for(int j = 0; j < input.length(); j++)
        {
            if(input[j] == ('A'+i))
            {
                count[i]++;
            }
        }
    }

    // find max
    int same_count = 0;
    int max = -1;
    int pos = 0;

    for(int i = 0; i < 'Z'-'A'+1; i++)
    {
        if(count[i] > max)
        {
            max = count[i];
            pos = i;
            same_count = 0;
        }
        else if (count[i] == max)
        {
            same_count++;
        }
    }

    if(same_count > 0)
        cout << "?" << endl;
    else
        cout << char('A' + pos) << endl;

    return 0;
}