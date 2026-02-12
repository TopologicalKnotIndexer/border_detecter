#pragma once

#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

#include "AbstractIntMatrix.h"
#include "../IntMap/AbstractIntMap.h"
#include "../IntCombine/AbstractIntCombine.h"

class IntMatrix: public AbstractIntMatrix {
protected:
    std::vector<std::vector<int>> matrix_data;
    int rcnt, ccnt;

public:
    virtual ~IntMatrix() {}

    IntMatrix(int r, int c) {
        rcnt = r;
        ccnt = c;

        // create zero line
        std::vector<int> zeros;
        for(int i = 0; i < c; i += 1) {
            zeros.push_back(0);
        }

        // push zero line into matrix_data
        for(int i = 0; i < r; i += 1) {
            matrix_data.push_back(zeros);
        }
    }

    virtual int getRcnt() const override {
        return rcnt;
    }
    virtual int getCcnt() const override {
        return ccnt;
    }

    virtual int getPos(int i, int j) const override {
        assert(0 <= i && i < rcnt && 0 <= j && j < ccnt);
        return matrix_data[i][j];
    }
    virtual void setPos(int i, int j, int v) {
        assert(0 <= i && i < rcnt && 0 <= j && j < ccnt);
        matrix_data[i][j] = v;
    }

    // 把矩阵中每一个值映射一次
    virtual void mapAll(const AbstractIntMap& int_map_func) {
        for(int i = 0; i < rcnt; i += 1) {
            for(int j = 0; j < ccnt; j += 1) {
                matrix_data[i][j] = int_map_func.mapInt(i, j, matrix_data[i][j]);
            }
        }
    }

    // 合并两个相同大小矩阵的值
    virtual IntMatrix combineMatrix(const IntMatrix& rhs, const AbstractIntCombine& aci) {
        assert(getRcnt() == rhs.getRcnt());
        assert(getCcnt() == rhs.getCcnt());

        auto ans = IntMatrix(rcnt, ccnt);
        for(int i = 0; i < rcnt; i += 1) {
            for(int j = 0; j < ccnt; j += 1) {
                ans.setPos(i, j, aci.combineInt(i, j, getPos(i, j), rhs.getPos(i, j)));
            }
        }
        return ans;
    }
};
