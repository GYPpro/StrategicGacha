#include <iostream>
#include <stdlib.h>
#include <myDisplyTool.h>
#include <myRand.h>
#include <myMathTool.h>

using namespace std;

int main()
{
    int T[1001] = {0};
    for(int i = 0;i < 1000000;i ++)
    {
      // int r = (int)(rand()*100)/RAND_MAX;
      int r = rand();
      for(;r >= 30000;)r = rand();
      r %= 100;
      T[r] ++;
    }
    for(int i = 0;i < 101;i ++)
    {
        cout << T[i] << endl;
    } 
    cout << RAND_MAX << endl;
    system("pause");

}
