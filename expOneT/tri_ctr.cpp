#include <iostream>
#include "tri_ctr.h"
using namespace std;

shape* tri_ctr::create() {
	return new tri;
}
