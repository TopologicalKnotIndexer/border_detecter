#pragma once

#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

class IntMatrix {
private:
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

    int getRcnt() const {
        return rcnt;
    }
    int getCcnt() const {
        return ccnt;
    }

    int getPos(int i, int j) const {
        assert(0 <= i && i < rcnt && 0 <= j && j < ccnt);
        return matrix_data[i][j];
    }
    void setPos(int i, int j, int v) {
        assert(0 <= i && i < rcnt && 0 <= j && j < ccnt);
        matrix_data[i][j] = v;
    }

    void debugOutput(std::ostream& out) const {
        for(int i = 0; i < rcnt; i += 1) {
            for(int j = 0; j < ccnt; j += 1) {
                out << std::setw(4) << getPos(i, j) << " ";
            }
            out << std::endl;
        }
    }
};
