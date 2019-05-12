#include "route_model.h"
#include <iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {
    int n_Counter = 0;
    for (auto node : this->Nodes()){
        m_Nodes.push_back(Node(n_Counter, this, node));
        n_Counter++;
    }
    // Create hashtable for node to road
    CreateNodeToRoadHashmap();
}

void RouteModel::CreateNodeToRoadHashmap(){
    auto n_Roads = Roads();
    for (auto road : n_Roads){
        if (road.type != Model::Road::Type::Footway){
            for (auto node_idx : Ways()[road.way].nodes){
                if ( node_to_road.find(node_idx) == node_to_road.end()){
                    node_to_road[node_idx] = std::vector<const Model::Road *> {};
                }
                node_to_road[node_idx].push_back(&road);
            }
        }
    }     
}