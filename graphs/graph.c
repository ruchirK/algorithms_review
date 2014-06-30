#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct edge {
	int dest; // the index of the vertex that this edge points to
	int weight; //optional id you want to make it weighted
	struct edge* next; //pointer to the next edge for this graph
}; 
struct vertex {
	struct edge* edge;
	int degree;
};
struct graph {
	struct vertex[] vertices; //
	int number_vertices;
	int max_size;
	char directed;
}; 

int init_graph(int size, struct graph** graph, char is_directed) {
	if (size < 1 || graph == NULL) {		
		return -1;
	}
	struct graph* new_graph = (struct graph*) calloc(1, sizeof (struct graph));
	struct vertex* vertex_array = (struct vertex*) calloc(size, sizeof (struct vertex));
	if (new_grauph == NULL || vertices == NULL) { return -1; }
	graph->vertices = vertex_array;
	graph-> max_size = size;
	graph->directed = is_directed;
	*graph = new_graph;
	return 0; 

}

int insert_vertex(struct graph* graph) {
	if (graph == NULL || graph->number_vertices == graph->max_size) {
		return -1;
	}
	struct vertex* new_vertex = (struct vertex*) calloc(1, sizeof(struct vertex)); 
	if (new_vertex == NULL ) {
		return -1;
	}

	//everything in vertex has is zero 
	graph->vertices[number_vertices++] = new_vertex;
	return 0; 

}

