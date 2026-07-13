#define DEBUG_MAIN (0)

#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>

#include "BFS/BfsAlgo.h"
#include "DataInput/FileDataInput.h"
#include "Graph/ConnectedComponents.h"
#include "Graph/DiagramGraph.h"
#include "IntMatrix/BorderMask.h"
#include "IntMatrix/ZeroOneMatrix.h"


std::set<int> intersect(const std::set<int>& left, const std::set<int>& right) {
    std::set<int> result;
    for(const auto item: left) {
        if(right.find(item) != right.end()) {
            result.insert(item);
        }
    }
    return result;
}


int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <matrix.txt>" << std::endl;
        return 2;
    }

    try {
        std::ifstream input(argv[1]);
        if(!input.is_open()) {
            throw std::runtime_error("could not open input matrix");
        }
        FileDataInput data_input;
        const auto matrix = data_input.loadMatrix(input);
        if(matrix.getMax() <= 0) {
            throw std::invalid_argument("matrix must contain positive arc labels");
        }
        if(matrix.getPos(0, 0) != 0) {
            throw std::invalid_argument("top-left matrix cell must be background (zero)");
        }

        const int target_label = 1;
        const auto obstacle_mask = ZeroOneMatrix(matrix);
        const auto visited_background = BfsAlgo().search(obstacle_mask, 0, 0);
        const auto raw_border = BorderMask(
            std::make_shared<ZeroOneMatrix>(visited_background), 0);
        const auto border_mask = ZeroOneMatrix(raw_border);
        const auto exposed_labels = border_mask.select(matrix);

        const auto diagram_graph = DiagramGraph(matrix);
        auto all_components = ConnectedComponents(diagram_graph).getConnectedComponents();
        std::set<int> target_component;
        for(const auto& component: all_components) {
            if(component.find(target_label) != component.end()) {
                target_component = component;
                break;
            }
        }
        if(target_component.empty()) {
            throw std::invalid_argument("diagram does not contain arc label 1");
        }

        // AC means the component containing label 1 touches the exterior
        // background boundary. WA means it is enclosed by another component.
        std::cout << (intersect(target_component, exposed_labels).empty() ? "WA" : "AC")
                  << std::endl;
        return 0;
    } catch(const std::exception& error) {
        std::cerr << "error: " << error.what() << std::endl;
        return 1;
    }
}
