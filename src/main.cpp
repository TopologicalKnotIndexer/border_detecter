#define DEBUG_MAIN (0)

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

    // 获取整个矩阵中的最大元素
    auto mxv = imx.getMax(); 
    assert(mxv > 0);

    // 将所有非零位置设置为 1
    auto mmx = ZeroOneMatrix(imx);

    if(DEBUG_MAIN) {
        std::cerr << "Solving BFS" << std::endl;
    }

    // 从左上角位置出发，遍历所有能走的空白位置
    // 1 是障碍物，0 是可通行位置
    BfsAlgo bfs_algo;
    auto vis_mx = bfs_algo.search(mmx, 0, 0);

    if(DEBUG_MAIN) {
        std::cerr << "Solving Border" << std::endl;
    }

    // 检索 0 区域的边界位置
    auto border_pos_raw = BorderMask(std::make_shared<ZeroOneMatrix>(vis_mx), 0);
    auto border_pos     = ZeroOneMatrix(border_pos_raw);

    // 在原始数据矩阵中进行筛选
    // 筛选出所有在边界上的节点
    auto set_int = border_pos.select(imx);

    if(DEBUG_MAIN) {
        std::cerr << "Solving Connected Component" << std::endl;
    }

    // 计算原图中的所有联通分支
    // all_cc 包含了所有的 connected component 对应的 std::set<int>
    auto dg = DiagramGraph(imx);
    auto cc_alg = ConnectedComponents(dg);
    auto all_cc = cc_alg.getConnectedComponents();

    // 找到最大编号对应的连通分量
    auto mxv_cc = std::set<int>();
    for(const auto& cc: all_cc) {
        if(cc.find(mxv) != cc.end()) {
            mxv_cc = cc;
        }
    }

    if(DEBUG_MAIN) {
        std::cerr << "Checking Cover" << std::endl;
    }

    // 检查最大联通分支是否是独立在外的
    // 如果最大联通分支是独立在外的，那么我们的算法
    // 能够保证一个连通分支在最外侧，因此大概率说明不改变 pdcode 也可以做联通和
    // 但是这一点需要进一步进行验证
    // 具体做法就是对所有 link 考虑将其所有联通分支 swap 成最大编号联通分支并生成扭结
    if(intersect(mxv_cc, set_int).size() == 0) {
        std::cout << "WA" << std::endl; // 最大编号暴露出来了
    }else {
        std::cout << "AC" << std::endl; // 最大编号没暴露出来
    }
    
    return 0;
}
