#include "undirectedgraph.h"
using namespace std;

/*********************************************************************
 *
 * UndirectedGraph::UndirectedGraph - Constructor
 *
 *--------------------------------------------------------------------
 * Creates a representation of the undirected graph given by the
 * inputted set of edges.
 *--------------------------------------------------------------------
 * PARAMETERS
 *   vector<Edge> theEdges: the edges of the undirected graph
 *--------------------------------------------------------------------
 * POST-CONDITIONS
 *   The edges and nodes of the graph are stored in their respective
 *   hash map containers, accessible by their unique keys. An
 *   adjacency list is created as the main graph representation.
 *********************************************************************/
UndirectedGraph::UndirectedGraph(const vector<Edge>& theEdges)
{
    Node nodeOne;  // used for instantiating the first node endpoint of an edge
    Node nodeTwo;  // used for instantiating the second node endpoint of an edge

    for (int i = 0; i < theEdges.size(); i++)
    {
        nodeOne = Node(theEdges[i].src);
        nodeTwo = Node(theEdges[i].dst);

        // Check if an edge between the two nodes has already been created
        if (edges[nodeOne.key + nodeTwo.key].src.empty() == false ||
            edges[nodeTwo.key + nodeOne.key].src.empty() == false)
            continue;

        // Create the edge and nodes for the current input edge, and build the adj. list
        edges[theEdges[i].key] = theEdges[i];
        nodes[nodeOne.key] = nodeOne;
        nodes[nodeTwo.key] = nodeTwo;
        nodeOne.cost = theEdges[i].weight;
        nodeTwo.cost = theEdges[i].weight;
        adjList[nodeOne.key].push_back(nodeTwo);
        adjList[nodeTwo.key].push_back(nodeOne);
    }
}

/*********************************************************************
 *
 * UndirectedGraph::shortestPath - Public Method
 *
 *--------------------------------------------------------------------
 * Employs Dijkstra's algorithm to find the shortest path connecting
 * the two given nodes.
 *--------------------------------------------------------------------
 * PARAMETERS
 *   string start: the starting node
 *   string end: the destination node
 * RETURNS
 *   The shortest path represented as a Path object which contains
 *   the edges, nodes, and cost of the path.
 *--------------------------------------------------------------------
 * PRE-CONDITIONS
 *   The arguments 'start' and 'end' must be associated with nodes in
 *   the graph.
 *********************************************************************/
Path UndirectedGraph::shortestPath(string start, string end)
{
    Node curr;   // the current node from which to relax other nodes
    Node child;  // a neighboring node of the current node
    unordered_map<string, bool> inFrontier;  // nodes whose distances have yet to be finalized
    unordered_map<string, bool> explored;    // nodes whose distances have been finalized
    priority_queue<Node, vector<Node>, CompareNodeCost> frontier;// queue of nodes ordered by
                                                                 // minimum cost that need
                                                                 // to be finalized
    deque<string> pathNodes;  // represents the nodes along the shortest path calculated
    Edge pathEdge;  // represents the edges along the shortest path
    Path result;    // the shortest path solution represented as a Path object

    // Place the starting node on the frontier ready to be explored
    curr = Node(start);
    frontier.push(curr);
    inFrontier[curr.key] = true;

    // Continuing exploring nodes until there are no more nodes to explore
    while (!frontier.empty())
    {
        // Pop the node with the minimum cost from the queue
        curr = frontier.top();
        frontier.pop();
        inFrontier[curr.key] = false;
        explored[curr.key] = true;
        nodes[curr.key] = curr;

        // Break the loop if the destination node is reached
        if (curr.key == end)
            break;

        // Iteratively relax all of the distances of the current node's neighbors
        for (int i = 0; i < adjList[curr.key].size(); i++)
        {
            child = adjList[curr.key][i];
            // Skip the neighbor node if it has already been explored
            if (explored[child.key])
                continue;

            child.cost += curr.cost;
            // Update the distance of the neighbor if the new distance is less
            if (child.cost < nodes[child.key].cost || !inFrontier[child.key])
            {
                child.prev = curr.key;
                nodes[child.key] = child;
                frontier.push(child);
            }
            inFrontier[child.key] = true;
        }
    }

    if (curr.key != end)
        return result;

    // Retrace the sequence of nodes constituting the shortest path
    result.cost = curr.cost;
    pathNodes.push_front(curr.key);
    while (!curr.prev.empty())
    {
        curr = nodes[curr.prev];
        pathNodes.push_front(curr.key);
    }

    // Retrace the sequence of edges forming the shortest path
    result.nodes.push_back(curr.key);
    for (int i = 0; i < pathNodes.size() - 1; i++)
    {
        pathEdge = edges[pathNodes[i] + pathNodes[i+1]];
        if (pathEdge.src.empty())
            pathEdge = edges[pathNodes[i+1] + pathNodes[i]];
        result.edges.push_back(pathEdge);
        result.nodes.push_back(pathNodes[i+1]);
    }

    return result;
}

/*********************************************************************
 *
 * UndirectedGraph::greedyTripCost - Private Method
 *
 *--------------------------------------------------------------------
 * Calculates the cost associated with the path determined purely
 * based on the greedy strategy of picking the next closest unvisited
 * node. This path cost is used in the A* search algorithm for
 * optimization, restricting the number of nodes to be expanded.
 *--------------------------------------------------------------------
 * PARAMETERS
 *   string start: the starting node
 *   unordered_set<string> targets: the set of destination nodes to
 *                                  visit in the path
 * RETURNS
 *   The cost of the path constructed using a naive greedy strategy.
 *--------------------------------------------------------------------
 * PRE-CONDITIONS
 *   All inputted node keys must be valid.
 *********************************************************************/
int UndirectedGraph::greedyTripCost(string start, const unordered_set<string>& targets)
{
    int finalCost = 0;    // the total cost of the path
    int currCost = 0;     // the currect cost of reaching a neighbor
    int bestCost = -1;    // the lowest cost of reaching a neighbor
    string next = "";     // the next node to explore
    string prev = start;  // the previous explored node
    unordered_set<string> unvisited = targets;  // the set of unvisited nodes

    if (targets.size() <= 1)
        return finalCost;

    while (!unvisited.empty())
    {
        bestCost = -1;
        // Iterate through the unvisited nodes to find the closest one to travel to next
        for (auto it = unvisited.begin(); it != unvisited.end(); ++it)
        {
            // Calculate the cost of reaching the unvisited node
            currCost = shortestPath(prev, *it).cost;
            // Update the best cost associated with reaching the closest node
            if (currCost < bestCost || bestCost == -1)
            {
                bestCost = currCost;
                next = *it;
            }
        }

        // Add the best cost to the final cost of the path, and erase the explored node
        // from the set of unvisited nodes
        finalCost += bestCost;
        prev = next;
        unvisited.erase(next);
    }

    return finalCost;
}

/*********************************************************************
 *
 * UndirectedGraph::shortestTripAStar - Public Method
 *
 *--------------------------------------------------------------------
 * Calculates using the A* search algorithm the shortest path that
 * begins at the first node in the target list and visits every other
 * node in the list at least once. Employs a heuristic function that
 * computes the total cost of the MST spanning only the remaining
 * unvisited nodes in that state. The heuristic is admissible and
 * enables this algorithm to provide an optimal solution.
 *--------------------------------------------------------------------
 * PARAMETERS
 *   unordered_set<string> targets: the set of destination nodes to
 *                                  visit in the path
 * RETURNS
 *   The shortest path visiting all of the specified nodes.
 *--------------------------------------------------------------------
 * PRE-CONDITIONS
 *   All inputted node keys must be valid.
 *********************************************************************/
Path UndirectedGraph::shortestTripAStar(const vector<string>& targets)
{
    State currState;       // the current state being expanded
    State childState;      // a child state generated from the current state
    int greedyCost = 0;    // the cost of the path constructed using the greedy strategy
    int currPathCost = 0;  // the cost of the path to reach the next unvisited node
    int currHeurCost = 0;  // the heuristic cost given by the MST heuristic function
    Edge currCompound;     // the shortest path between two target nodes represented as an edge
    vector<Edge> compoundEdges;  // the set of all paths between each and every target node
    unordered_map<string, int> compoundWeights;  // the costs of the paths between target nodes
    priority_queue<State, vector<State>, CompareStateCost> frontier;// the open queue of states
    Path currPath;  // used for retracing the entire solution path
    Path result;    // the solution path to be returned

    if (targets.empty())
        return result;
    result.nodes.push_back(targets[0]);
    if (targets.size() == 1)
        return result;

    // Pre-compute the costs of all paths connecting each target node with every other
    // target node
    for (int i = 0; i < targets.size() - 1; i++)
    {
        for (int j = i + 1; j < targets.size(); j++)
        {
            currCompound = Edge(targets[i], targets[j]);
            currCompound.weight = shortestPath(targets[i], targets[j]).cost;
            // Store the path as an edge in a vector
            compoundEdges.push_back(currCompound);
            // Store the cost of the path in a hash map for fast retrieval
            compoundWeights[currCompound.key] = currCompound.weight;
        }
    }

    // Sort the vector of path edges in terms of increasing cost to be used for building
    // the MST in the heuristic function by using Kruskal's algorithm
    sort(compoundEdges.begin(), compoundEdges.end(), CompareEdgeWeight());

    // Initialize the starting state with the first node to begin from
    currState.visited.push_back(targets[0]);
    currState.unvisited.insert(targets.begin(), targets.end());
    currState.pathCost = 0;
    currState.heurCost = kruskalMSTHeur(currState.unvisited, compoundEdges);
    currState.totalCost = currState.pathCost + currState.heurCost;
    currState.unvisited.erase(targets[0]);

    // Push the starting state to the open queue
    frontier.push(currState);

    // Calculate the cost of the path constructed using the greedy strategy, which will be
    // used to limit the number of states to be expanded. This is a non-optimal path cost,
    // and any state that has a cost higher that this greedy cost should not be expanded.
    greedyCost = greedyTripCost(targets[0], currState.unvisited);

    while (!frontier.empty())
    {
        // Pop the state from the open queue with the current minimum cost so it can be
        // expanded
        currState = frontier.top();
        frontier.pop();

        // If there are no more unvisited nodes in the state, the state is the goal state
        if (currState.unvisited.empty())
            break;

        // Calculate the heuristic cost for all of the childen states, which is the same
        currHeurCost = kruskalMSTHeur(currState.unvisited, compoundEdges);

        // Generate a child state for every remaining unvisited node
        for (auto it = currState.unvisited.begin(); it != currState.unvisited.end(); ++it)
        {
            childState = currState;

            // Access the path cost to reach the unvisited node using the hash map of path
            // edge weights constructed earlier
            currPathCost = compoundWeights[childState.visited.back() + *it];
            if (currPathCost == 0)
                currPathCost = compoundWeights[*it + childState.visited.back()];
            childState.pathCost += currPathCost;
            childState.heurCost = currHeurCost;
            childState.totalCost = childState.pathCost + childState.heurCost;

            // Skip adding the child to the open queue if its cost exceeds the greedyCost
            if (childState.totalCost > greedyCost)
                continue;

            childState.visited.push_back(*it);
            childState.unvisited.erase(*it);

            // Add the child to the open queue
            frontier.push(childState);
        }
    }

    // Retrace the path and store the solution in the result Path object
    result.cost = currState.pathCost;
    for (int i = 1; i < currState.visited.size(); i++)
    {
        currPath = shortestPath(result.nodes.back(), currState.visited[i]);
        result.nodes.insert(result.nodes.end(), currPath.nodes.begin() + 1, currPath.nodes.end());
        result.edges.insert(result.edges.end(), currPath.edges.begin(), currPath.edges.end());
    }

    return result;
}

/*********************************************************************
 *
 * UndirectedGraph::kruskalMSTHeur - Private Method
 *
 *--------------------------------------------------------------------
 * Calculates the cost of the MST spanning only the set of inputted
 * target nodes. This cost will be the heuristic cost provided to the
 * A* search algorithm.
 *--------------------------------------------------------------------
 * PARAMETERS
 *   unordered_set<string> targets: the set of nodes to be spanned by
 *                                  the MST
 *   vector<Edge>& compoundEdges: ordered set of path edges used for
 *                                building the MST with Kruskal's
 * RETURNS
 *   The MST heuristic cost associated with the given set of nodes.
 *--------------------------------------------------------------------
 * PRE-CONDITIONS
 *   All inputted node keys must be valid.
 *********************************************************************/
int UndirectedGraph::kruskalMSTHeur(const unordered_set<string>& targets,
                                    const vector<Edge>& compoundEdges)
{
    int cost = 0;         // the MST heuristic cost
    string srcRoot = "";  // the root node of the tree where the first edge node is in
    string dstRoot = "";  // the root node of the tree where the second edge node is in
    unordered_map<string, string> parent;  // the record of parent nodes
    unordered_map<string, int> treeCt;     // the number of nodes in a tree

    if (targets.size() <= 1)
        return 0;

    for (int i = 0; i < compoundEdges.size(); i++)
    {
        if (targets.find(compoundEdges[i].src) == targets.end() ||
            targets.find(compoundEdges[i].dst) == targets.end())
            continue;

        if (parent[compoundEdges[i].src] == "")
        {
            parent[compoundEdges[i].src] = compoundEdges[i].src;
            treeCt[compoundEdges[i].src] = 1;
        }
        if (parent[compoundEdges[i].dst] == "")
        {
            parent[compoundEdges[i].dst] = compoundEdges[i].dst;
            treeCt[compoundEdges[i].dst] = 1;
        }

        // Search for the root parent node of the two nodes
        srcRoot = findRoot(compoundEdges[i].src, parent);
        dstRoot = findRoot(compoundEdges[i].dst, parent);

        // Skip adding the edge if the two nodes are in the same tree to prevent cycles
        if (srcRoot == dstRoot)
            continue;

        // Merge the two nodes and their trees, and update the total MST cost
        parent[dstRoot] = srcRoot;
        treeCt[srcRoot] += treeCt[dstRoot];
        cost += compoundEdges[i].weight;

        // Stop adding edges when all target nodes belong in the same tree
        if (treeCt[srcRoot] == targets.size())
            break;
    }

    return cost;
}

string UndirectedGraph::findRoot(string node, const unordered_map<string, string>& parent)
{
    string curr = node;

    while (parent.at(curr) != curr)
    {
        curr = parent.at(curr);
    }

    return curr;
}
