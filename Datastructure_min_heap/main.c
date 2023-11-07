
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000

//kruskal
int parent[MAX_VERTICES]; // 부모 노드

void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}

// curr가 속한 집합 반환
int set_find(int curr) {
	if (parent[curr] == -1) {
		return curr;
	}
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// 두 개의 원소가 속한 집합을 합침
void set_union(int a, int b) {
	int root1 = set_find(a); // 노드 a의 루트를 찾는다.
	int root2 = set_find(b); // 노드 b의 루트를 찾는다.
	if (root1 != root2) { // 합한다.
		parent[root1] = root2;
		
	}
}

typedef struct Edge { // 간선을 나타내는 구조체 heap에 사용 !!!!!
	int start, end, weight;
}elementE;

typedef struct Graph {
	int n;
	struct Edge edges[2 * MAX_VERTICES];
} Graph;

// 그래프 초기화
void graph_init(Graph* g) {
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// 간선 삽입 연산
void insert_edge(Graph* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort()에 사용되는 함수
int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

void kruskal(Graph* g) {
	int edge_accepted = 0; // 현재까지 선택된 간선의 수
	int uset, vset; // 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n); // 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);
	printf("크루스칼 최소 신장 트리 알고리즘 \n");

	printf("Qsort사용 \n");
	int i = 0;
	while (edge_accepted < (g->n - 1)) { // 간선의 수 < (n - 1)


		e = g->edges[i];
		uset = set_find(e.start); // 정점 u의 집합 번호
		vset = set_find(e.end); // 정점 v의 집합 번호
		if (uset != vset) { // 서로 속한 집합이 다르면
			printf("간선( % d, % d) % d 선택\n", e.start, e.end, e.weight);

			set_union(uset, vset); // 두 개의 집합을 합친다.
		}
		edge_accepted++;
		i++;
	}
}



//------------------------------------------------------------------------------------------------
//heap
#define ME 100



typedef struct {
	int key;
}element;

typedef struct {
	elementE heap[ME]; // heap의 자료형을 elementE  edge로함 
	int heap_size;
}HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));

}

void init(HeapType* h) {
	h->heap_size = 0;
}
void print_heap(HeapType* h) {
	if (h->heap_size == 0) return;
	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].weight);

	}
	printf("\n");
}
//여기;
void insert_min_heap(HeapType* h, elementE item) {//element item 을 g->edges.weig
	int i = ++(h->heap_size);//맨마지막 노드에 들어가있다고 가정하고 시작 

	while (item.weight < h->heap[i / 2].weight && i != 1) {//부모노드랑 비교

		h->heap[i] = h->heap[i / 2];
		i /= 2;


	}
	h->heap[i] = item;
	print_heap(h);

}

elementE  delete_min_heap(HeapType* h) {
	int parent, child;
	elementE item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];//마지막거가 위로 올라가야 하니까 마지막 꺼놓고 heapsize를 줄인다

	parent = 1;
	child = 2;


	while (child <= h->heap_size) {//추후 보는걸로
		//둘중에 더 작은
		if (child < h->heap_size && (h->heap[child].weight) >(h->heap[child + 1].weight)) {
			child++;
		}
		if (temp.weight < h->heap[child].weight) break;//밑에서 온값이 아까전에 두 차일드 중에 비교한값중에 더 큰값과 비교해도 더크면
		//그냥 둔다 ->나중에 parent값에다가 temp넣을거라서 그냥 두면 됨

		h->heap[parent] = h->heap[child];// temp값이 차일드 값 보다 작은경우 위치를 바꾼다 아랫값을 위로 올린다.
		parent = child;//이제 기준을 아까 차일드값으로 옮긴다
		child *= 2;

	}

	h->heap[parent] = temp;//추후  밑에것을 끌어올렸으니까 차일드 값에다가 temp값 넣어주면 됨
	print_heap(h);
	return item;//heap에 있는 하나의 값 
}



void heap_sort(Graph* g) {

	int i;
	HeapType* h;

	h = create();
	init(h);

	for (i = 0; i < g->n; i++) {
		insert_min_heap(h, g->edges[i]);

	}

	for (i =0; i <= (g->n - 1); i++) {// 0에서 부터 n-1까지 
	//	printf(" debuging heap sort : %d, %d, %d ||||",g->edges[i].start,g->edges[i].end,g->edges[i].weight);
		g->edges[i] = delete_min_heap(h); 

	}
	free(h);
}




//------------------------------------------------------------------------------------------------------




//--
void heap_kruskal(Graph* g) {
	int edge_accepted = 0; // 현재까지 선택된 간선의 수
	int uset, vset; // 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n); // 집합 초기화
	heap_sort(g);
	//qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("크루스칼 최소 신장 트리 알고리즘 \n");

	printf("heap sort 사용 \n");
	int i = 0;
	while (edge_accepted < (g->n - 1)) { // 간선의 수 < (n - 1)


		e = g->edges[i];
		uset = set_find(e.start); // 정점 u의 집합 번호
		vset = set_find(e.end); // 정점 v의 집합 번호
		if (uset != vset) { // 서로 속한 집합이 다르면
			printf("간선( % d, % d) % d 선택\n", e.start, e.end, e.weight);

			set_union(uset, vset); // 두 개의 집합을 합친다.
		}
		edge_accepted++;
		i++;
	}
}
//--

int main() {

	Graph* g;
	g = (Graph*)malloc(sizeof(Graph));
	graph_init(g);


	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);

	insert_edge(g, 2, 1, 3);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 2, 4, 4);

	insert_edge(g, 3, 2, 5);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);


	insert_edge(g, 4, 2, 4);
	insert_edge(g, 4, 3, 2);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 10, 16);


	insert_edge(g, 5, 2, 1);
	insert_edge(g, 5, 4, 13);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);

	insert_edge(g, 6, 1, 11);
	insert_edge(g, 6, 2, 7);
	insert_edge(g, 6, 5, 9);

	insert_edge(g, 7, 1, 12);
	insert_edge(g, 7, 2, 8);
	insert_edge(g, 7, 3, 6);
	insert_edge(g, 7, 8, 13);

	insert_edge(g, 8, 3, 5);
	insert_edge(g, 8, 4, 14);
	insert_edge(g, 8, 7, 13);
	insert_edge(g, 8, 10, 15);

	insert_edge(g, 9, 5, 18);
	insert_edge(g, 9, 10, 10);

	insert_edge(g, 10, 4, 16);
	insert_edge(g, 10, 5, 17);
	insert_edge(g, 10, 8, 15);
	insert_edge(g, 10, 9, 10);


	//heap_sort(g);

	//for (int i = 0; i <g->n; i++) {
	//	printf("%d ", g->edges[i].weight);
	//}
	//printf("\n end \n");

	heap_kruskal(g);
	kruskal(g);
	free(g);
	return 0;
}