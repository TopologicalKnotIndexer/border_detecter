#include <fstream>

#include "DataInput/FileDataInput.h"
#include "IntMatrix/ZeroOneMatrix.h"

int main(int argc, char** argv) {

    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <txt_filepath>" << std::endl;
        return 0;
    }

    FileDataInput file_data_input;

    auto inp = std::ifstream(std::string(argv[1]));
    auto imx = file_data_input.loadMatrix(inp);
    auto mmx = ZeroOneMatrix(imx);

    mmx.debugOutput(std::cout);

    return 0;
}
