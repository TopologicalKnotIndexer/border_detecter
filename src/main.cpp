#include <fstream>

#include "BFS/BfsAlgo.h"
#include "DataInput/FileDataInput.h"
#include "Graph/ConnectedComponents.h"
#include "Graph/DiagramGraph.h"
#include "IntMatrix/BorderMask.h"
#include "IntMatrix/ZeroOneMatrix.h"

// 计算两个集合的交集
std::set<int> intersect(std::set<int> a, std::set<int> b) {
    std::set<int> ans;
    for(auto item: a) {
        if(b.find(item) != b.end()) {
            ans.insert(item);
        }
    }
    return ans;
}

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
    // 筛选出所有在边界上的节点
    auto set_int = border_pos.select(imx);

    // 计算原图中的所有联通分支
    // all_cc 包含了所有的 connected component 对应的 std::set<int>
    auto dg = DiagramGraph(imx);
    auto cc_alg = ConnectedComponents(dg);
    auto all_cc = cc_alg.getConnectedComponents();

    // 检查是否每个联通分支都被覆盖过
    bool fail = false;
    std::set<int> failed_cc; // 记录没有被边界元素覆盖过的联通分支
    for(auto cc: all_cc) {
        if(intersect(cc, set_int).size() == 0) {
            fail = true;
            failed_cc = cc;
            break;
        }
    }

    if(fail) {
        std::cout << "WA" << std::endl;
        for(auto item: failed_cc) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }else {
        std::cout << "AC" << std::endl;
    }

    return 0;
}
