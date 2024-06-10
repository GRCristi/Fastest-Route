
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define numar 100
#define Raza 6371



typedef struct {
    double x;
    double y;
    char *name;
    int number;
} Point;

typedef struct {
    int source;
    int destination;
    double weight;
} Edge;

typedef struct {
    Point nodes[numar ];
    int numNodes;
    double adjacencyMatrix[numar][numar];
} Graph;

double distance(Point* p, Point* q);

Point* addNode(Graph* graph, const char* name, double x, double y, int number) {
    Point* newNode = (Point*)malloc(sizeof(Point));
    newNode->x = x;
    newNode->y = y;
    newNode->number = number;
    newNode->name = strdup(name);
    graph->nodes[number] = *newNode;
    graph->numNodes++;

    return newNode;
}

void addEdge(Graph* graph, Point *p,Point *q) {

    Edge newEdge;
    newEdge.source=p->number;
    newEdge.destination=q->number;
    newEdge.weight=distance(p,q);
    graph->adjacencyMatrix[p->number][q->number] = distance(p,q);
    graph->adjacencyMatrix[q->number][p->number] = distance(p,q);


}

double distance(Point* p, Point* q) {
    double latitude1, longitude1, height1, latitude2, longitude2, height2;

    double x1 = p->y * 0.017;
    double y1 = p->x * 0.017;
    double x2 = q->y * 0.017;
    double y2 = q->x * 0.017;

    height1 = Raza * cos(y1);
    latitude1 = Raza * sin(y1) * cos(x1);
    longitude1 = Raza * sin(y1) * sin(x1);

    height2 = Raza * cos(y2);
    latitude2 = Raza * sin(y2) * cos(x2);
    longitude2 = Raza * sin(y2) * sin(x2);

    double distance = (latitude1 - latitude2) * (latitude1 - latitude2) +
                      (longitude1 - longitude2) * (longitude1 - longitude2) +
                      (height1 - height2) * (height1 - height2);

    return sqrt(distance);
}

void bfs(Graph* graph, Point* start, Point* end) {
    bool visited[numar] = {false};
    int queue[numar];
    int front = 0, rear = 0;
    double distances[numar];
    int previous[numar];  // Keep track of previous nodes for reconstructing the path
    int path[numar];
    int pathIndex = 0;

    for (int i = 0; i < numar; ++i) {
        distances[i] = INFINITY;
        previous[i] = -1;  // Initialize previous nodes to -1
    }

    queue[rear++] = start->number;
    visited[start->number] = true;
    distances[start->number] = 0.0;

    while (front != rear) {
        int current = queue[front++];
        path[pathIndex++] = current;

        if (current == end->number) {
            // Reconstruct the path
            printf("Path: ");
            int node = end->number;
            while (node != -1) {
                printf("%s ", graph->nodes[node].name);
                node = previous[node];
            }
            printf("\nTotal Distance: %.2f km\n", distances[end->number]);
            return;
        }

        for (int i = 0; i < graph->numNodes; ++i) {
            if (!visited[i] && graph->adjacencyMatrix[current][i] != 0) {
                queue[rear++] = i;
                visited[i] = true;
                distances[i] = distances[current] + graph->adjacencyMatrix[current][i];
                previous[i] = current;  // Record the previous node
            }
        }
    }

    printf("No path found.\n");
}



int main() {
    Graph *graph=malloc(sizeof (Graph));
    Point *c1=addNode(graph,"Bucuresti",44.26,26.06,0);
    Point *c2=addNode(graph,"Ploiesti",44.94, 26.03,1);
    Point *c3= addNode(graph,"Brasov",45.65,25.61,2);
    Point *c4= addNode(graph,"Constanta",44.18,28.63,3);
    Point *c5= addNode(graph,"Cluj", 46.77,23.62,4);
    Point *c6= addNode(graph,"Timisoara",45.74,21.20,5);
    Point *c7= addNode(graph,"Iasi", 47.15,27.6,6);
    Point *c8= addNode(graph,"Craiova", 44.33,23.8,7);
    Point *c9= addNode(graph,"Oradea", 47.04,21.91,8);
    Point *c10= addNode(graph,"Arad", 46.18,21.32,9);
    Point *c11= addNode(graph,"Pitesti", 44.85,24.86,10);
    Point *c12= addNode(graph,"Sibiu", 45.79,24.12,11);
    Point *c13= addNode(graph,"Suceava", 47.63,26.25,12);
    Point *c14= addNode(graph,"Targu Jiu", 45.04,23.27,13);
    Point *c15= addNode(graph,"Baia Mare", 47.65,23.57,14);
    Point *c16= addNode(graph,"Alba Iulia",46.4,23.34,15);
    Point *c17= addNode(graph,"Focsani",45.41,27.11,16);
    addEdge(graph,c1,c2);
    addEdge(graph,c2,c3);
    addEdge(graph,c4,c1);
    addEdge(graph,c3,c12);
    addEdge(graph,c12,c14);
    addEdge(graph,c8,c6);
    addEdge(graph,c10,c6);
    addEdge(graph,c9,c10);
    addEdge(graph,c15,c9);
    addEdge(graph,c2,c11);
    addEdge(graph,c11,c12);
    addEdge(graph, c14,c8);
    addEdge(graph,c5,c9);
    addEdge(graph,c5,c15);
    addEdge(graph,c14,c6);
    addEdge(graph,c5,c13);
    addEdge(graph,c13,c15);
    addEdge(graph,c13,c7);
    addEdge(graph,c7,c3);
    addEdge(graph,c11,c8);
    addEdge(graph,c16,c5);
    addEdge(graph,c16,c12);
    addEdge(graph,c17,c3);
    addEdge(graph,c17,c4);
    addEdge(graph,c17,c2);
    addEdge(graph,c17,c7);
    Point *start=NULL,*end=NULL;
    char ans[10], city1[50], city2[50];
    int i;

    do {
            printf("Where do you want your journey to start?\n");
            scanf("%s", city1);
            printf("Where do you want your journey to end?\n");
            scanf("%s", city2);
            for (i = 0; i < graph->numNodes; i++) {
                if (strcmp(graph->nodes[i].name, city1) == 0) start = &graph->nodes[i];
                else if (strcmp(graph->nodes[i].name, city2) == 0) end = &graph->nodes[i];
            }
        bfs(graph, start, end);
        printf("Would you like to do something else ['no' to stop]? ");
        scanf("%s", ans);
    } while (strcmp(ans, "no") != 0);



    free(graph);
    return 0;
}
