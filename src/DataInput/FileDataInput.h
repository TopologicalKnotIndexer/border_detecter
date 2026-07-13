#pragma once

#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "AbstractDataInput.h"

class FileDataInput: public AbstractDataInput {
public:
    virtual ~FileDataInput() {}

    virtual IntMatrix loadMatrix(std::istream& input) const override {
        std::vector<std::vector<int>> rows;
        std::string line;
        while(std::getline(input, line)) {
            std::stringstream stream(line);
            std::vector<int> row;
            int value;
            while(stream >> value) {
                row.push_back(value);
            }
            if(stream.fail() && !stream.eof()) {
                throw std::invalid_argument("matrix contains a non-integer token");
            }
            if(!row.empty()) {
                rows.push_back(std::move(row));
            }
        }
        if(input.bad()) {
            throw std::runtime_error("failed while reading matrix input");
        }
        if(rows.empty()) {
            throw std::invalid_argument("matrix input is empty");
        }
        const std::size_t column_count = rows.front().size();
        for(const auto& row: rows) {
            if(row.size() != column_count) {
                throw std::invalid_argument("matrix rows have different lengths");
            }
        }

        IntMatrix matrix(static_cast<int>(rows.size()), static_cast<int>(column_count));
        for(std::size_t row = 0; row < rows.size(); row += 1) {
            for(std::size_t column = 0; column < column_count; column += 1) {
                matrix.setPos(static_cast<int>(row), static_cast<int>(column), rows[row][column]);
            }
        }
        return matrix;
    }
};
