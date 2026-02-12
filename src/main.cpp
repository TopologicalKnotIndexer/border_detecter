#include <fstream>

#include "DataInput/FileDataInput.h"
#include "IntMatrix/BorderMask.h"
#include "IntMatrix/ZeroOneMatrix.h"
#include "BFS/BfsAlgo.h"

int main(int argc, char** argv) {

    // 检查函数参数是否完整
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <txt_filepath>" << std::endl;
        return 0;
    }

    //  从文件读入数据矩阵
    FileDataInput file_data_input;
    auto inp = std::ifstream(std::string(argv[1]));
    auto imx = file_data_input.loadMatrix(inp);

    // 将所有非零位置设置为 1
    auto mmx = ZeroOneMatrix(imx);

    // 从左上角位置出发，遍历所有能走的空白位置
    // 1 是障碍物，0 是可通行位置
    BfsAlgo bfs_algo;
    auto vis_mx = bfs_algo.search(mmx, 0, 0);

    // 检索 0 区域的边界位置
    auto border_pos_raw = BorderMask(std::make_shared<ZeroOneMatrix>(vis_mx), 0);
    auto border_pos     = ZeroOneMatrix(border_pos_raw);

    // 在原始数据矩阵中进行筛选
    auto set_int = border_pos.select(imx);
    for(auto val: set_int) {
        if(val > 0) {
            std::cout << val << " ";
        }
    }
    std::cout << std::endl;

    return 0;
}
