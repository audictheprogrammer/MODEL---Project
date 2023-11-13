#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <cmath>

#include "double_c.hpp"

int main(){

    double_c z;
    z.x = 3;
    z.y = -1.7;

    print(z);
    
    return 0;
}
