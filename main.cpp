//Yashwanth Narayan Shravanaboyina Besta
//this program creates a directed, weighted graph using an adjacency table and allows the user to add/remove vertices and edges, find the shortest path between two vertices, and print the adjacency table.
//date: 5/23/2026
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int MAX_VERTICES = 20;
const int MAX_LABEL_LENGTH = 50;
const int NO_EDGE = -1;
const int INF = numeric_limits<int>::max() / 4;

class Graph {
private:
    vector<vector<char> > labels;
    vector<vector<int> > adjacencyTable;

    int findVertexIndex(const char label[]) const {
        for (int i = 0; i < static_cast<int>(labels.size()); i++) {
            if (strcmp(labels[i].data(), label) == 0) {
                return i;
            }
        }
        return -1;
    }

    vector<char> makeLabel(const char label[]) const {
        vector<char> storedLabel(MAX_LABEL_LENGTH + 1, '\0');
        strncpy(storedLabel.data(), label, MAX_LABEL_LENGTH);
        storedLabel[MAX_LABEL_LENGTH] = '\0';
        return storedLabel;
    }

public:
    void addVertex(const char label[]) {
        if (strlen(label) == 0) {
            cout << "Vertex label cannot be empty." << endl;
            return;
        }
        if (findVertexIndex(label) != -1) {
            cout << "Vertex already exists." << endl;
            return;
        }
        if (static_cast<int>(labels.size()) >= MAX_VERTICES) {
            cout << "Graph is full. Maximum vertices: " << MAX_VERTICES << endl;
            return;
        }

        labels.push_back(makeLabel(label));

        // Add a new column to every existing row.
        for (int i = 0; i < static_cast<int>(adjacencyTable.size()); i++) {
            adjacencyTable[i].push_back(NO_EDGE);
        }

        // Add a new row for the new vertex.
        adjacencyTable.push_back(vector<int>(labels.size(), NO_EDGE));
        cout << "Added vertex: " << label << endl;
    }

    void addEdge(const char from[], const char to[], int weight) {
        int fromIndex = findVertexIndex(from);
        int toIndex = findVertexIndex(to);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Both vertices must exist before adding an edge." << endl;
            return;
        }
        if (weight <= 0) {
            cout << "Edge weight must be a positive integer." << endl;
            return;
        }

        adjacencyTable[fromIndex][toIndex] = weight;
        cout << "Added directed edge: " << from << " -> " << to
             << " with weight " << weight << endl;
    }

    void removeVertex(const char label[]) {
        int index = findVertexIndex(label);
        if (index == -1) {
            cout << "Vertex not found." << endl;
            return;
        }

        labels.erase(labels.begin() + index);
        adjacencyTable.erase(adjacencyTable.begin() + index);

        // Remove the deleted vertex column from every remaining row.
        for (int i = 0; i < static_cast<int>(adjacencyTable.size()); i++) {
            adjacencyTable[i].erase(adjacencyTable[i].begin() + index);
        }

        cout << "Removed vertex and all connected edges: " << label << endl;
    }

    void removeEdge(const char from[], const char to[]) {
        int fromIndex = findVertexIndex(from);
        int toIndex = findVertexIndex(to);

        if (fromIndex == -1 || toIndex == -1) {
            cout << "Both vertices must exist before removing an edge." << endl;
            return;
        }
        if (adjacencyTable[fromIndex][toIndex] == NO_EDGE) {
            cout << "No edge exists from " << from << " to " << to << "." << endl;
            return;
        }

        adjacencyTable[fromIndex][toIndex] = NO_EDGE;
        cout << "Removed directed edge: " << from << " -> " << to << endl;
    }

    void printAdjacencyTable() const {
        if (labels.empty()) {
            cout << "Graph is empty." << endl;
            return;
        }

        cout << endl << "Adjacency Table" << endl;
        cout << setw(10) << "";

        for (int i = 0; i < static_cast<int>(labels.size()); i++) {
            cout << setw(10) << labels[i].data();
        }
        cout << endl;

        for (int row = 0; row < static_cast<int>(labels.size()); row++) {
            cout << setw(10) << labels[row].data();
            for (int col = 0; col < static_cast<int>(labels.size()); col++) {
                if (adjacencyTable[row][col] == NO_EDGE) {
                    cout << setw(10) << "-";
                } else {
                    cout << setw(10) << adjacencyTable[row][col];
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void findShortestPath(const char start[], const char end[]) const {
        int startIndex = findVertexIndex(start);
        int endIndex = findVertexIndex(end);

        if (startIndex == -1 || endIndex == -1) {
            cout << "Both vertices must exist before searching." << endl;
            return;
        }

        int vertexCount = labels.size();
        vector<int> distance(vertexCount, INF);
        vector<int> previous(vertexCount, -1);
        vector<bool> visited(vertexCount, false);

        distance[startIndex] = 0;

        // Dijkstra's Algorithm:
        // Repeatedly choose the unvisited vertex with the smallest distance,
        // then relax all outgoing edges from that vertex.
        for (int step = 0; step < vertexCount; step++) {
            int current = -1;
            int bestDistance = INF;

            for (int i = 0; i < vertexCount; i++) {
                if (!visited[i] && distance[i] < bestDistance) {
                    bestDistance = distance[i];
                    current = i;
                }
            }

            if (current == -1) {
                break;
            }

            visited[current] = true;

            for (int neighbor = 0; neighbor < vertexCount; neighbor++) {
                int weight = adjacencyTable[current][neighbor];
                if (weight != NO_EDGE && !visited[neighbor]) {
                    int newDistance = distance[current] + weight;
                    if (newDistance < distance[neighbor]) {
                        distance[neighbor] = newDistance;
                        previous[neighbor] = current;
                    }
                }
            }
        }

        if (distance[endIndex] == INF) {
            cout << "No path exists from " << start << " to " << end << "." << endl;
            return;
        }

        vector<int> path;
        for (int current = endIndex; current != -1; current = previous[current]) {
            path.push_back(current);
        }
        reverse(path.begin(), path.end());

        cout << "Shortest path: ";
        for (int i = 0; i < static_cast<int>(path.size()); i++) {
            cout << labels[path[i]].data();
            if (i < static_cast<int>(path.size()) - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Total weight: " << distance[endIndex] << endl;
    }
};

void printMenu() {
    cout << endl;
    cout << "Graph Creator Menu" << endl;
    cout << "1. Add Vertex" << endl;
    cout << "2. Add Edge" << endl;
    cout << "3. Remove Vertex" << endl;
    cout << "4. Remove Edge" << endl;
    cout << "5. Find Shortest Path" << endl;
    cout << "6. Print Adjacency Table" << endl;
    cout << "7. Quit" << endl;
    cout << "Choose an option: ";
}

void readLabel(char label[]) {
    cin >> setw(MAX_LABEL_LENGTH + 1) >> label;
}

int main() {
    Graph graph;
    int choice = 0;

    cout << "Directed Weighted Graph Creator" << endl;

    while (choice != 7) {
        printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from 1 to 7." << endl;
            continue;
        }

        if (choice == 1) {
            char label[MAX_LABEL_LENGTH + 1];
            cout << "Enter vertex label: ";
            readLabel(label);
            graph.addVertex(label);
        } else if (choice == 2) {
            char from[MAX_LABEL_LENGTH + 1];
            char to[MAX_LABEL_LENGTH + 1];
            int weight;
            cout << "Enter starting vertex: ";
            readLabel(from);
            cout << "Enter ending vertex: ";
            readLabel(to);
            cout << "Enter positive edge weight: ";
            cin >> weight;
            graph.addEdge(from, to, weight);
        } else if (choice == 3) {
            char label[MAX_LABEL_LENGTH + 1];
            cout << "Enter vertex label to remove: ";
            readLabel(label);
            graph.removeVertex(label);
        } else if (choice == 4) {
            char from[MAX_LABEL_LENGTH + 1];
            char to[MAX_LABEL_LENGTH + 1];
            cout << "Enter starting vertex: ";
            readLabel(from);
            cout << "Enter ending vertex: ";
            readLabel(to);
            graph.removeEdge(from, to);
        } else if (choice == 5) {
            char start[MAX_LABEL_LENGTH + 1];
            char end[MAX_LABEL_LENGTH + 1];
            cout << "Enter starting vertex: ";
            readLabel(start);
            cout << "Enter ending vertex: ";
            readLabel(end);
            graph.findShortestPath(start, end);
        } else if (choice == 6) {
            graph.printAdjacencyTable();
        } else if (choice == 7) {
            cout << "Goodbye!" << endl;
        } else {
            cout << "Please enter a number from 1 to 7." << endl;
        }
    }

    return 0;
}
