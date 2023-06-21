#include <iostream>
#include "TupleLib/Tuple.h"

int main(){
    tuple<int, double, char, float> t;
    t = make_tuple(5, 3.5, 'a', -24.4f);
    return 0;
}