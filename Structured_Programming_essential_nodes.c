# Advance-programming-laboratory
#include <stdio.h>
#include <stdbool.h>

// Define a structure to represent a node in a graph
struct Node {
    int nodeid;        // Node ID
    int adjcount;      // Number of adjacent nodes
    int adjs[10];      // IDs of adjacent nodes
    int costs[10];     // Costs associated with adjacent nodes
};

// Function to add a node to the list of nodes
// Returns the updated count of nodes
int addNode(struct Node *p, int nid, int count) {
    int i = 0, ncount = count;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) {
            break;
        }
    }
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node to a given node
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i = 0, index;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;
            break;
        }
    }
}

// Function to check if a node is already in the list
int added(int *list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) {
            return 1;
        }
    }
    return 0;
}

// Function to find paths between two nodes in the graph
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount, bool *essential) {
    int index = 0, i = 0;

    // Check if list contains the end node
    if (list[lcount - 1] == end) {
        int tcost = 0;
        printf("\nPath:");
        for (i = 0; i < lcount; i++) {
            printf(" %d ", list[i]);
            tcost += clist[i];
        }
        printf(" Cost = %d", tcost);

        printf("\nEssential Nodes:");
        for (i = 0; i < count; i++) {
            if (essential[i]) {
                printf(" %d ", p[i].nodeid);
            }
        }
        printf("\n");
        return;
    }

    // Find the index of the start node
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }

    // Iterate through adjacent nodes of the start node
    for (i = 0; i < p[index].adjcount; i++) {
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            if (p[index].adjs[i] != end) {
                essential[index] = true;
            }

            // Recursively find paths
            findpath(p, count, p[index].adjs[i], end, list, clist, lcount, essential);
            lcount--;
            essential[index] = false;
        }
    }
}

int main() {
    struct Node nodes[50];           // Array to hold nodes
    bool essential[50] = {false};    // Array to track essential nodes
    int nodecount = 0;                // Count of nodes
    int n1 = 0, n2 = 0, c = 0;        // Variables to store node IDs and costs

    // Input loop to add nodes and edges to the graph
    while (1) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);

        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    // Input start and end nodes for finding paths
    int start, end;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    // Call the function to find paths
    findpath(nodes, nodecount, start, end, list, clist, lcount, essential);

    return 0;
}
