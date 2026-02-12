#include <fstream>

#include "DataInput/FileDataInput.h"
#include "IntMatrix/ZeroOneMatrix.h"
#include "BFS/BfsAlgo.h"

int main(int argc, char** argv) {

    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <txt_filepath>" << std::endl;
        return 0;
    }

    FileDataInput file_data_input;

    auto inp = std::ifstream(std::string(argv[1]));
    auto imx = file_data_input.loadMatrix(inp);
    auto mmx = ZeroOneMatrix(imx);

    // 从左上角位置出发，遍历所有能走的空白位置
    BfsAlgo bfs_algo;
    auto vis_mx = bfs_algo.search(mmx, 0, 0);
    vis_mx.debugOutput(std::cout);
    
    return 0;
}
