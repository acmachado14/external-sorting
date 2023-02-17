#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstring>

using namespace std;

struct Arquivo {
   char measure[8];
   char quantile[10];
   char sex[25];
   char age[8];
   char geography[15];
   char ethnic[50]; 
   char value[12];
};