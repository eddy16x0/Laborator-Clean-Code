#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int v;
    int* visited;
    Node** adjList;
} Graph;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->v = vertices;
    graph->visited = (int*)calloc(vertices, sizeof(int));
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->v; i++) {
        graph->visited[i] = 0;
    }
}

int dfs(Graph* graph, int src, int target) {
    if (src == target) return 1;
    graph->visited[src] = 1;

    Node* temp = graph->adjList[src];
    while (temp != NULL) {
        if (!graph->visited[temp->data]) {
            if (dfs(graph, temp->data, target)) {
                return 1;
            }
        }
        temp = temp->next;
    }

    return 0;
}

int main() {
    int n, m;
    printf("Cate restaurante sunt (noduri)? ");
    scanf("%d", &n);

    printf("Cate legaturi directe (muchii)? ");
    scanf("%d", &m);

    Graph* graph = createGraph(n);

    printf("Introdu %d muchii (ex: 0 1):\n", m);
    for (int i = 0; i < m; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int r1, r2;
    printf("Verificam daca exista drum intre doua restaurante.\n");
    printf("Restaurant 1: ");
    scanf("%d", &r1);
    printf("Restaurant 2: ");
    scanf("%d", &r2);

    resetVisited(graph);
    if (dfs(graph, r1, r2)) {
        printf("Exista drum intre %d si %d\n", r1, r2);
    } else {
        printf("Nu exista drum intre %d si %d\n", r1, r2);
    }

    return 0;
}
