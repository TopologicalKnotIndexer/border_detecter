#pragma once

#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../IntMap/AbstractIntMap.h"
#include "../IntCombine/AbstractIntCombine.h"

class AbstractIntMatrix {
public:
    virtual ~AbstractIntMatrix() {}

    virtual int getRcnt() const = 0;
    virtual int getCcnt() const = 0;

    virtual int getPos(int i, int j) const = 0;

    // 输出所有元素的值
    virtual void debugOutput(std::ostream& out) const = 0;
};
