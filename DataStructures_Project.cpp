
#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    // Constructor of Class Node
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class Graph {
public:
    int V; // Number of vertices
    Node** adjList; // For Storing Nodes in 2D Matrix

    // Constructor of Class Graph 
    Graph(int vertices) 
    {
        V = vertices;
        adjList = new Node * [V];
        // Initializing all values as nullptr
        for (int i = 0; i < V; ++i) 
        {
            adjList[i] = nullptr;
        }
    }
    // Function for Adding Edge
    void addEdge(int v, int w) 
    {
        Node* newNode = new Node(w);
        newNode->next = adjList[v];
        adjList[v] = newNode;
    }
    // Function for Searching Edge between two Vertices
    bool searchEdge(int v, int w) 
    {
        Node* current = adjList[v];
        while (current != nullptr) {
            if (current->data == w) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    // Function To get Last Vertex
    int getLastVertex() 
    {
        int lastVertex = -1;
        for (int i = 0; i < V; ++i) {
            if (adjList[i] != nullptr) {
                lastVertex = i;
            }
        }
        return lastVertex;
    }
    // Function for Finding the Shortest Distance between 1st and last node
    int shortestDistance(int s, int end) 
    {
        if(end<=6)
            return 1;

        int visited[V*2] = {1};
        bool flag=true;
        int distance=0; 
        int k=0;

        // For first distance
        for(int start=s;start<end-2;start++)
        {
            k++;
            // For storing the visited node
            visited[k] = adjList[start]->data;
            // Checking condition For aerial route 
            if(start+1!=adjList[start]->data)
            {
                for(int i=0;i<k-1;i++)
                {
                    // Checking Condition for matching with visited node
                    if(adjList[start]->data==visited[i])
                    {
                        flag = false;
                    }
                }
                // Increment in Distance for aerial route
                if(flag)
                {
                    start = adjList[start]->data;
                    distance+=4;
                }
                else
                {
                    start++;
                }
            }
            if(start==end-2)
                break;
            // Increment in Distance
            distance++;
        }
        distance++;

        // For second Distance 
        int distance2=0;
        for(int start=s;start<end-2;start++)
        {
            flag = true;
            // Checking condition For aerial route 
            if(start+1!=adjList[start]->data)
            {
                // Checking Condition for comparison between two consecutive nodes in case of aerial route
                if(adjList[start]->next->data>adjList[start]->data)
                    flag = false;
                // Increment in Distance for aerial route
                if(flag)
                {
                    start = adjList[start]->data;
                    distance2+=4;
                }
                else
                {
                    start++;
                }
            }
            if(start==end-2)
                break;
            // Increment in Distance
            distance2++;
        }
        distance2++;

        // Comparing the distance
        if(distance>distance2)
            distance = distance2;

        if(distance%6==0)
            return (distance/6)+1;

        return distance/6;
    }
    // Function for BFS Traversal
    void breadthFirstSearch(int startVertex) 
    {
        // Creating Dynamic Array for Visiting Nodes
        bool* visited = new bool[V];
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
        }

        queue<int> q;
        // Pushing the visited node
        visited[startVertex] = true;
        q.push(startVertex);
        // Checking conditions for next visited nodes
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            // Printing visited nodes
            cout << current << " ";
            // Checking conditions for next visited nodes
            for (int neighbor = 0; neighbor < V; ++neighbor) 
            {
                if (!visited[neighbor]) 
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        // Deleting visited nodes array to free the memory
        delete[] visited;
    }
    // Function for Printing the graph
    void printGraph() 
    {
        for (int v = 0; v < V; ++v) 
        {
            Node* temp = adjList[v];
            // checking for temp node
            if(temp!=nullptr)
                cout << endl<<"Adjacency list of vertex " << v << ": ";
            while (temp != nullptr) 
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
        }
        cout<<endl;
    }
    // Destructor to free the memory
    ~Graph() {
        // Deleting the all graph nodes
        for (int i = 0; i < V; ++i) {
            Node* current = adjList[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] adjList;
    }
};

int main() {
    // Create a graph for n vertices
    int n;
    cout<<"Enter the number of nodes/cities: ";
    cin>>n;
    Graph g(n);
    int choice;
    // Entering nodes for city route
    for(int i=1;i<n;i++)
    {
       g.addEdge(i, i+1);
    }

    while (true) {
        cout << "\n 1 : Add Edges for aerial root\n";
        cout << " 2 : Print Graph\n";
        cout << " 3 : Search Edge\n";
        cout << " 4 : Get Last Vertex\n";
        cout << " 5 : Minimum Steps to Last Vertex\n";
        cout << " 6 : To Display BFS Traversal\n";
        cout << " 0 : Break\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1) 
        {
            // Entering nodes/vertices for aerial route
            int a, b;
            cout << "Enter the 1st vertex you want to join: ";
            cin >> a;
            cout << "Enter the 2nd vertex you want to join: ";
            cin >> b;
            if(a<=n && b<=n)
            {
                g.addEdge(a, b);
            }
            else
            {
                cout<<"You are entering the vertex out of range"<<endl;
            }
        }
        else if (choice == 2)
        {
            // Printing the graph
            g.printGraph();
        }
        else if (choice == 3) 
        {
            // Searching the Edge
            int v, w;
            cout << "Enter the vertices to search edge between: ";
            cin >> v >> w;
            if (g.searchEdge(v, w)) {
                cout << "Edge exists between vertices " << v << " and " << w << endl;
            }
            else {
                cout << "No edge between vertices " << v << " and " << w << endl;
            }
        }
        else if (choice == 4) 
        {
            // Getting Last Vertex
            int lastVertex = g.getLastVertex();
            if (lastVertex != -1) {
                cout << "Last vertex in the graph: " << lastVertex << endl;
            }
            else {
                cout << "Graph is empty" << endl;
            }
        }
        else if (choice == 5) 
        {
            // Minimum days from 1 to last vertex
            cout << "Minimum days from start vertex to reach the last vertex: " << g.shortestDistance(1,n) <<endl;
        }
        else if (choice == 6) 
        {
            // BFS Traversal
            cout<<"Breadth First Search Traversal: ";
            g.breadthFirstSearch(1);
        }
        else if (choice == 0) {
            // Stopping the loop
            break;
        }
        else {
            cout << "Invalid input. Try Again" << endl;
            continue;
        }
    }

    return 0;
}