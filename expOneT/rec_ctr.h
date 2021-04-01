#pragma once
#include "creator.h"
#include "shape.h"
#include "rec.h"

class rec_ctr :public creator
{
	shape* create();
};

