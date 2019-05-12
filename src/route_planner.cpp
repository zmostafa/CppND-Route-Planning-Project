#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Scaling floats to percentages ..
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node){

    std::vector<RouteModel::Node> path_found {};
    distance = 0.0;

    while( current_node->parent != nullptr){
        path_found.push_back(*current_node);
        distance += current_node->distance(*(current_node->parent));
        current_node = current_node->parent;
    }
    // While loop ends,so current_node is the starting node of the search as its parent is nullptr.
    path_found.push_back(*current_node);
    distance *= m_Model.MetricScale();
    return path_found;
}

void RoutePlanner::AStarSearch(){

    // end_node->parent = start_node;
    // m_Model.path = ConstructFinalPath(end_node);
    RouteModel::Node* current_node = nullptr;
    start_node->visited = true;
    open_list.push_back(start_node);

    while (!open_list.empty())
    {
        current_node = RoutePlanner::NextNode();
        if (current_node->distance(*end_node) == 0)
        {
            m_Model.path = ConstructFinalPath(current_node);
            return;
        }

        RoutePlanner::AddNeighbors(current_node);
    }
    
}

float RoutePlanner::CalculateHValue(const RouteModel::Node* node){
    return node->distance(*end_node);
}

RouteModel::Node* RoutePlanner::NextNode(){

    // using lambda experssion with algorithms https://www.walletfox.com/course/sortvectorofcustomobjects11.php
    std::sort(open_list.begin() , open_list.end(), [](const auto &_1st , const auto &_2nd){
        return _1st->h_value + _1st->g_value < _2nd->h_value + _2nd->g_value;
    });

    RouteModel::Node* lowest_node = open_list.front();
    open_list.erase(open_list.begin());
    return lowest_node;
}

void RoutePlanner::AddNeighbors(RouteModel::Node* current_node){
    current_node->FindNeighbors();
    for (auto *neighbor : current_node->neighbors){
        neighbor->parent = current_node;
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        neighbor->h_value = this->CalculateHValue(neighbor);
        open_list.push_back(neighbor);
        neighbor->visited = true;
    }
}