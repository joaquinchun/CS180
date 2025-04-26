#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

struct node 
{
    int val;
    std::vector<node*> neighbors;
    node(int v) : val(v) {}
};

struct pair
{
    int distance;
    unsigned int count;
    pair(int d, int c) : distance(d), count(c) {}
};



// Forward declaration
pair distance(const node* v, const node* w, std::unordered_set<const node*>& seen);

unsigned int numShortestPaths(node* v, node* w)
{
    std::unordered_set<const node*> seen;
    pair p = distance(v, w, seen);
    std::cout << "Count: " << p.count << "\tDistance " << p.distance << std::endl;
    return p.count;
}

pair distance(const node* v, const node* w, std::unordered_set<const node*>& seen)
{
    int distanceMin = INT_MAX;
    unsigned int count = 0;

    if (v == w)
        return pair(0, 1);

    for (auto n : v->neighbors)
    {
        if (seen.find(n) == seen.end())
        {
            seen.insert(n);
            pair p = distance(n, w, seen);
            seen.erase(n); // backtrack for other paths
            if (p.distance != -1) // only consider valid paths
            {
                p.distance += 1;
                if (p.distance < distanceMin)
                {
                    distanceMin = p.distance;
                    count = p.count;
                }
                else if (p.distance == distanceMin)
                {
                    count += p.count;
                }
            }
        }
    }

    return distanceMin == INT_MAX ? pair(-1, 0) : pair(distanceMin, count);
}

unsigned int shortestPathCount(node* v, node*w)
{
    if (v==w)
        return 1;
    std::queue<node*> nodes;
    std::unordered_map<node*,int> distances;
    std::unordered_map<node*,int> count;
    unsigned int results = 0;
    int distance_min = INT_MAX;

    nodes.push(v);
    distances[v] = 0;
    count[v] = 1;

    while(!nodes.empty())
    {
        v = nodes.front();
        nodes.pop();

        if (distances[v] > distance_min)
            break;
        
        if (v == w)
        {
            if (distance_min == INT_MAX)
                distance_min = distances[v];
            results += count[v];
            continue;
        }

        for (auto neighbor : v->neighbors)
        {
            if (distances.find(neighbor) == distances.end())
            {
                distances[neighbor] = distances[v] + 1;
                count[neighbor] = count[v];
                nodes.push(neighbor);
            }
            else if (distances[neighbor] == distances[v] + 1)
                count[neighbor] += count[v];
        }
    }
    return results;
}


void addUndirectedEdge(node* a, node* b) {
    a->neighbors.push_back(b);
    b->neighbors.push_back(a);
}

std::unordered_map<int, node*> createTestGraph() {
    std::unordered_map<int, node*> nodes;
    
    // Create nodes 0 through 9
    for (int i = 0; i <= 9; ++i) {
        nodes[i] = new node(i);
    }
    
    // Create edges to form an interesting graph
    addUndirectedEdge(nodes[0], nodes[1]);
    addUndirectedEdge(nodes[0], nodes[2]);
    addUndirectedEdge(nodes[1], nodes[2]);
    addUndirectedEdge(nodes[1], nodes[3]);
    addUndirectedEdge(nodes[2], nodes[4]);
    addUndirectedEdge(nodes[3], nodes[4]);
    addUndirectedEdge(nodes[3], nodes[5]);
    addUndirectedEdge(nodes[4], nodes[5]);
    addUndirectedEdge(nodes[4], nodes[6]);
    addUndirectedEdge(nodes[5], nodes[7]);
    addUndirectedEdge(nodes[6], nodes[7]);
    addUndirectedEdge(nodes[6], nodes[8]);
    addUndirectedEdge(nodes[7], nodes[8]);
    addUndirectedEdge(nodes[7], nodes[9]);
    addUndirectedEdge(nodes[8], nodes[9]);
    
    return nodes;
}

// Clean up the graph
void deleteGraph(std::unordered_map<int, node*>& nodes) {
    for (auto& pair : nodes) {
        delete pair.second;
    }
    nodes.clear();
}

int main()
{
    auto nodes = createTestGraph();
    
    std::cout << shortestPathCount(nodes[0], nodes[9]) << std::endl;  // 4
    std::cout << shortestPathCount(nodes[0], nodes[5]) << std::endl;  // 2
    std::cout << shortestPathCount(nodes[1], nodes[8]) << std::endl;  // 2
    std::cout << shortestPathCount(nodes[4], nodes[9]) << std::endl;  // 3
    std::cout << shortestPathCount(nodes[0], nodes[4]) << std::endl;  // 2
    
    deleteGraph(nodes);
    return 0;
}
