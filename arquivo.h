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
   char area[25];
   char sex[8];
   char age[15];
   char geography[50];
   char ethnic[12];
   char value[10];
};