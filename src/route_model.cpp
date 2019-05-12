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
    // auto n_Roads = Roads();
    for (auto & road : Roads()){
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

RouteModel::Node* RouteModel::Node::FindNeighbor(std::vector<int> node_indices){
    Node *closest_node = nullptr;
    Node node; 

    for (auto node_index : node_indices){
        node = parent_model->SNodes()[node_index];
        if ( !node.visited && this->distance(node) != 0){
            if ( closest_node == nullptr || this->distance(node) < this->distance(*closest_node)){
                closest_node = &parent_model->SNodes()[node_index];
            }
        } 
    }

    return closest_node;
}

void RouteModel::Node::FindNeighbors(){
    for (auto & road : parent_model->node_to_road[this->index]){
        if ( FindNeighbor(parent_model->Ways()[road->way].nodes) != nullptr){
            this->neighbors.emplace_back(FindNeighbor(parent_model->Ways()[road->way].nodes));
        }
    }
}

RouteModel::Node& RouteModel::FindClosestNode(float x , float y){
    RouteModel::Node t_Node ;
    t_Node.x = x ;
    t_Node.y = y ;

    float min_dist = std::numeric_limits<float>::max();
    float t_dist = 0.0;
    int closest_idx = 0;

    for (auto & road : Roads()){
        if (road.type != Model::Road::Type::Footway){
            for (int node_idx : Ways()[road.way].nodes){
                t_dist = t_Node.distance(SNodes()[node_idx]);
                if (t_dist < min_dist){
                    min_dist = t_dist;
                    closest_idx = node_idx;
                }
            }
        }
    }

    return SNodes()[closest_idx];
}