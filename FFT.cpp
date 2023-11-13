#include <stdlib.h>
#include <stdio.h>


// GCD 
int gcd (int a, int b)
{
  int c;
  while (a != 0) {
    c = a; a = b%a;  b = c;
  }
  return b;
}

// Primitive roots.
int get_prim_root(int size_vect) {
    
    for (int i = 1; i < size_vect; i++) {
        
        if (gcd(i, size_vect) == 1) {
            return i;
        }
    }
    return 0;
}

// FFT.




// IFFT.

