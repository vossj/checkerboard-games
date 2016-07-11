#include <iostream>
#include "chessobjs.h"

using namespace Chess;
using namespace std;

int main()
{
    Position P;
    P.SetToInitialPosition();
    cout << P;
    
    return 0;
}

