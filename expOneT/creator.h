#pragma once
#include <vector>
#include "shape.h"
using namespace std;

class creator
{
public:
	virtual shape* create() = 0;
};
