#pragma once
#include "creator.h"
#include "shape.h"
#include "line.h"

class line_ctr :public creator
{
	shape* create();
};
