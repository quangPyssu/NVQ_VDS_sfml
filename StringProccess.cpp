#include "StringProccess.h"

void StringProccess::StringFilter(string& S)
{
	init_data.clear();
    int temp = 0;
    
    if (S.size() == 0)  return;
    int i = 0;

    for (i = 0; i < S.size(); i++)
    {
        if (S[i] >= '0' && S[i] <= '9')
        {
            temp = temp * 10 + (S[i] - '0');
            continue;
        }

        if (S[i] == ' ')
        {
            init_data.push_back(temp);
            temp = 0;
            continue;
        }
    }
    
    init_data.push_back(temp);
    while (init_data.size() > 20) init_data.pop_back();

    S = "";
}




