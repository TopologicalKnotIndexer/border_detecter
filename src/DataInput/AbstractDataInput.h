#pragma once

#include <iostream>
#include "../IntMatrix/IntMatrix.h"

class AbstractDataInput {
public:
    virtual ~AbstractDataInput(){}
    virtual IntMatrix loadMatrix(std::istream& in) = 0;
};
