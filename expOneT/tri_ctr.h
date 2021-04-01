#pragma once
#include "creator.h"
#include "shape.h"
#include "tri.h"

class tri_ctr :public creator
{
	shape* create();
};

