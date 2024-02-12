// Name:Md.Nayem Hossain
// Student Id:220208
// This Is a Code Of Graph to find triangle 

#include <stdio.h>

// Define a structure for a node in the graph
struct Node
{
    int nodeid;        
    int adjcount;      
    int adjs[10];      
    int costs[10];     
};

// Function to add a node to the graph
int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;
    
    // Check if the node with the given ID already exists
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    
    // If the node doesn't exist, add it to the array
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    
    return ncount;
}

// Function to add an edge between two nodes with a given cost
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;
    
    // Find the index of the first node in the array
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;

            break;
        }
    }
}

// Function to find and print triangles in the graph
void findTriangle(struct Node *p, int nodecount)
{
    int trianglecount = 0;
    
    for (int i = 0; i < nodecount; i++)
    {
        for (int j = i + 1; j < nodecount; j++)
        {
            for (int k = j + 1; k < nodecount; k++)
            {
                int flag = 0, flag1 = 0, flag2 = 0;

                // Check if nodes i and j are adjacent
                for (int l = 0; l < p[i].adjcount; l++)
                {
                    if (p[i].adjs[l] == p[j].nodeid)
                    {
                        flag = 1;
                        break;
                    }
                }

                // Check if nodes j and k are adjacent
                for (int m = 0; m < p[j].adjcount; m++)
                {
                    if (p[j].adjs[m] == p[k].nodeid)
                    {
                        flag1 = 1;
                        break;
                    }
                }

                // Check if nodes i and k are adjacent
                for (int n = 0; n < p[i].adjcount; n++)
                {
                    if (p[i].adjs[n] == p[k].nodeid)
                    {
                        flag2 = 1;
                        break;
                    }
                }

                // If all three pairs are adjacent, it forms a triangle
                if (flag == 1 && flag1 == 1 && flag2 == 1)
                {
                    trianglecount++;
                    printf("\nTriangle: %d %d %d", p[i].nodeid, p[j].nodeid, p[k].nodeid);
                }
            }
        }
    }
    
    printf("\nTotal triangle = %d\n", trianglecount);
}

int main()
{
    // Array to store nodes in the graph
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Input loop to read nodes and edges from the user
    while (1)
    {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);

        // If any of the values is -9, exit the loop
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break;
        }

        // Add nodes and edges to the graph
        nodecount = addNode(nodes, n1, nodecount);
        nodecount = addNode(nodes, n2, nodecount);
        addAdjacent(nodes, n1, n2, c, nodecount);
        addAdjacent(nodes, n2, n1, c, nodecount);
    }

    // Find and print triangles in the graph
    findTriangle(nodes, nodecount);

    return 0;
}
