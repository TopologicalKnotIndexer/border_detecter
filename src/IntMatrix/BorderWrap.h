#pragma once

#include <algorithm>
#include <memory>
#include "AbstractIntMatrix.h"

// fill same value to the region outside
class BorderWrap: public AbstractIntMatrix {
protected:
    int border_val;
    std::shared_ptr<AbstractIntMatrix> aim;

public:
    virtual ~BorderWrap() {}

    BorderWrap(int _border_val, std::shared_ptr<AbstractIntMatrix> _aim): 
        border_val(_border_val), aim(_aim) {
        
    }

    virtual int getRcnt() const override {
        return aim->getRcnt();
    }

    virtual int getCcnt() const override {
        return aim->getCcnt();
    }

    virtual void debugOutput(std::ostream& out, int width) const override {
        aim->debugOutput(out, width);
    }

    virtual int getPos(int i, int j) const override {
        if(!(0 <= i && i < getRcnt() && 0 <= j && j < getCcnt())) {
            return border_val;
        }
        return aim -> getPos(i, j);
    }

    // 获取所有元素的最大值
    virtual int getMax() const {
        return std::max(aim->getMax(), border_val);
    }
};
