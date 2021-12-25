#include "../include/algorithm.h"
#include "../include/io.h"
#include "../include/util.h"

void logDebug (char c){
   c = 'a';
}

int main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
  logDebug('!');
}
