#pragma once

#include "IntMatrix.h"
#include "../IntMap/NotIntMap.h"

class ZeroOneMatrix: public IntMatrix {
public:
    virtual ~ZeroOneMatrix() {}
    ZeroOneMatrix(int rcnt, int ccnt): IntMatrix(rcnt, ccnt) {}
    ZeroOneMatrix(const IntMatrix& mat): IntMatrix(mat.getRcnt(), mat.getCcnt()) {
        for(int i = 0; i < rcnt; i += 1) {
            for(int j = 0; j < ccnt; j += 1) {
                setPos(i, j, mat.getPos(i, j) != 0);
            }
        }
    }

    virtual void setPos(int i, int j, int v) override {
        assert(v == 0 || v == 1);
        this -> IntMatrix::setPos(i, j, v);
    }

    virtual int getPos(int i, int j) const override {
        return this -> IntMatrix::getPos(i, j) != 0;
    }

    // 对所有位置的值域取反
    virtual void notAll() {
        mapAll(NotIntMap());
    }
};
