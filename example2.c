#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int vertices;
    int* visited;
    Node** adjacencyLists;
} Graph;


Node* createNode(int data) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->visited = calloc(vertices, sizeof(int));
    graph->adjacencyLists = malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjacencyLists[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyLists[src];
    graph->adjacencyLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyLists[dest];
    graph->adjacencyLists[dest] = newNode;
}

void wipeVisited(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(Graph* graph, int vertex) {
    Node* temp = graph->adjacencyLists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(Graph* graph, int startVertex) {
    int* queue = malloc(graph->vertices * sizeof(int));
    int front = 0, rear = 0;

    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        Node* temp = graph->adjacencyLists[current];
        while (temp) {
            int adjVertex = temp->data;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    free(queue);
}

int main() {
    int vertices, edges;
    printf("Numar de noduri: ");
    scanf("%d", &vertices);
    printf("Numar de muchii: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Introdu %d muchii (noduri numerotate de la 0 la %d):\n", edges, vertices - 1);
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int startVertex;
    printf("Start DFS: ");
    scanf("%d", &startVertex);
    printf("Parcurgere DFS: ");
    DFS(graph, startVertex);
    printf("\n");

    wipeVisited(graph);

    printf("Start BFS: ");
    scanf("%d", &startVertex);
    printf("Parcurgere BFS: ");
    BFS(graph, startVertex);
    printf("\n");

    return 0;
}
