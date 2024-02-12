
// Name:Md.Nayem Hossain
// Student Id:220208
// This is a code of graph to find path

#include <stdio.h>

// Structure to represent a node in the graph
struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

// Global array and count for visa information
int visa[50], visacount = 0;
int pathcount = 0;

// Function to add a node to the graph
int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;

    // Check if the node already exists
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }

    // If the node doesn't exist, add it to the graph
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }

    return ncount;
}

// Function to add an adjacent node with cost information
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;

    // Find the index of the node in the graph
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;

            // Add the adjacent node and cost information
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;

            break;
        }
    }
}

// Function to check if a node is already in the list
int added(int *list, int lcount, int nid)
{
    int i = 0;

    // Check if the node is in the list
    for (i = 0; i < lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1; // Node is already in the list
        }
    }

    return 0; // Node is not in the list
}

// Function to check if a node is in the visa array
int have(int node)
{
    for (int i = 0; i < visacount; i++)
    {
        if (visa[i] == node)
        {
            return 1; // Node is in the visa array
        }
    }

    return 0; // Node is not in the visa array
}

// Recursive function to find paths in the graph
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount)
{
    int index = 0, i = 0;

    // Check if the last node in the list is the destination
    if (list[lcount - 1] == end)
    {
        int tcost = 0;

        // Print the path and calculate the total cost
        printf("\n");
        for (i = 0; i < lcount; i++)
        {
            printf("%d ", list[i]);
            tcost += clist[i];
        }

        printf(" cost = %d", tcost);
        pathcount++;
        return;
    }

    // Find the index of the starting node in the graph
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }

    // Explore adjacent nodes
    for (i = 0; i < p[index].adjcount; i++)
    {
        int a = added(list, lcount, p[index].adjs[i]); 
        int b = have(p[index].adjs[i]);                 
       
        if (a == 0 && b == 1)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main()
{
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Input nodes and edges into the graph
    while (1)
    {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);

        // Break if the input is -9
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break;
        }

        // Update node count and add nodes and edges to the graph
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);

        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    int start, end;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);

    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    int x;

    // Input visa information
    while (1)
    {
        scanf("%d", &x);

        // Break if the input is -1
        if (x == -1)
            break;

        // Update visa array and count
        visa[visacount] = x;
        visacount++;
    }

    // Find and print paths in the graph
    findpath(nodes, nodecount, start, end, list, clist, lcount);

    printf("\ntotal path with visas = %d", pathcount);

    return 0;
}