#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/*********************************************************************
 *
 * UndirectedGraph
 *
 *--------------------------------------------------------------------
 * This file contains utilities for an undirected graph, including
 * functions for performing A* search to calculate a custom, optimal
 * path within a graph.
 *--------------------------------------------------------------------
 * File Contents
 *   struct Node: represents a graph node
 *   struct Edge: represents a graph edge
 *   struct Path: represents a path in the graph
 *   struct State: represents a state in the A* search algorithm
 *   class UndirectedGraph: represents an undirected graph
 *********************************************************************/

struct Node
{
    std::string key;  // unique key identifying the node
    int cost;         // the cost to reach the node
    std::string prev; // the connecting node associated with the cost

    Node() : key(""), cost(0), prev("") {}
    Node(std::string theKey, int theCost = 0) : key(theKey), cost(theCost) {}

    friend bool operator==(const Node& lhs, const Node& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator!=(const Node& lhs, const Node& rhs)
    {
        return !operator==(lhs, rhs);
    }
};

// Comparator for priority queue or similar container to form min-heap based on Node::cost
struct CompareNodeCost
{
    bool operator()(const Node& lhs, const Node& rhs)
    {
        return lhs.cost > rhs.cost;
    }
};

struct Edge
{
    std::string src;  // the key of the first node
    std::string dst;  // the key of the second node
    std::string key;  // unique key identifying the edge
    int weight;       // the weight of the edge

    Edge() : src(""), dst(""), key(""), weight(0) {}
    Edge(std::string node1, std::string node2, int theWeight = 0)
        : src(node1), dst(node2), key(node1 + node2), weight(theWeight) {}
    Edge(Node node1, Node node2, int theWeight = 0)
        : src(node1.key), dst(node2.key), key(node1.key + node2.key), weight(theWeight) {}

    friend bool operator==(const Edge& lhs, const Edge& rhs)
    {
        return (lhs.src == rhs.src && lhs.dst == rhs.dst) ||
               (lhs.src == rhs.dst && lhs.dst == rhs.src);
    }
    friend bool operator!=(const Edge& lhs, const Edge& rhs)
    {
        return !operator==(lhs, rhs);
    }
};

// Comparator for sorting edges in a vector in terms of increasing weight
struct CompareEdgeWeight
{
    bool operator()(const Edge& lhs, const Edge& rhs)
    {
        return lhs.weight < rhs.weight;
    }
};

struct Path
{
    std::vector<Edge> edges;         // the sequence of edges along the path
    std::vector<std::string> nodes;  // the sequence of nodes along the path
    int cost;                        // total cost of the path

    Path() : cost(0) {}
};

struct State
{
    std::vector<std::string> visited;           // nodes that have been visited
    std::unordered_set<std::string> unvisited;  // nodes that have not been visited
    int pathCost;                               // the 'g' cost of the state
    int heurCost;                               // the 'h' cost, or heuristic cost
    int totalCost;                              // the total cost g + h

    State() : pathCost(0), heurCost(0), totalCost(0) {}
};

// Comparator for priority queue to form min-heap of states for A* search
struct CompareStateCost
{
    bool operator()(const State& lhs, const State& rhs)
    {
        if (lhs.totalCost == rhs.totalCost)
            return lhs.pathCost < rhs.pathCost;
        return lhs.totalCost > rhs.totalCost;
    }
};

/*********************************************************************
 * UndirectedGraph Class
 *   This class manages three attributes to represent an undirected
 *   graph: the edges, nodes, and adjacency list. All three attributes
 *   are hash maps to maximize efficiency for the relevant functions
 *   performed by this class.
 *********************************************************************/
class UndirectedGraph
{
    public:
        UndirectedGraph() = default;
        UndirectedGraph(const std::vector<Edge>& theEdges);

        Path shortestPath(std::string start, std::string end);
        Path shortestTripAStar(const std::vector<std::string>& targets);

    private:
        int greedyTripCost(std::string start,
                           const std::unordered_set<std::string>& targets);
        int kruskalMSTHeur(const std::unordered_set<std::string>& targets,
                           const std::vector<Edge>& compoundEdges);
        std::string findRoot(std::string node,
                             const std::unordered_map<std::string, std::string>& parent);

        std::unordered_map<std::string, Edge> edges;
        std::unordered_map<std::string, Node> nodes;
        std::unordered_map<std::string, std::vector<Node>> adjList;
};

#endif // UNDIRECTEDGRAPH_H
