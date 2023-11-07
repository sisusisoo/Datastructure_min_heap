
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000

//kruskal
int parent[MAX_VERTICES]; // �θ� ���

void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}

// curr�� ���� ���� ��ȯ
int set_find(int curr) {
	if (parent[curr] == -1) {
		return curr;
	}
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// �� ���� ���Ұ� ���� ������ ��ħ
void set_union(int a, int b) {
	int root1 = set_find(a); // ��� a�� ��Ʈ�� ã�´�.
	int root2 = set_find(b); // ��� b�� ��Ʈ�� ã�´�.
	if (root1 != root2) { // ���Ѵ�.
		parent[root1] = root2;
		
	}
}

typedef struct Edge { // ������ ��Ÿ���� ����ü heap�� ��� !!!!!
	int start, end, weight;
}elementE;

typedef struct Graph {
	int n;
	struct Edge edges[2 * MAX_VERTICES];
} Graph;

// �׷��� �ʱ�ȭ
void graph_init(Graph* g) {
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// ���� ���� ����
void insert_edge(Graph* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort()�� ���Ǵ� �Լ�
int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

void kruskal(Graph* g) {
	int edge_accepted = 0; // ������� ���õ� ������ ��
	int uset, vset; // ���� u�� ���� v�� ���� ��ȣ
	struct Edge e;

	set_init(g->n); // ���� �ʱ�ȭ
	qsort(g->edges, g->n, sizeof(struct Edge), compare);
	printf("ũ�罺Į �ּ� ���� Ʈ�� �˰��� \n");

	printf("Qsort��� \n");
	int i = 0;
	while (edge_accepted < (g->n - 1)) { // ������ �� < (n - 1)


		e = g->edges[i];
		uset = set_find(e.start); // ���� u�� ���� ��ȣ
		vset = set_find(e.end); // ���� v�� ���� ��ȣ
		if (uset != vset) { // ���� ���� ������ �ٸ���
			printf("����( % d, % d) % d ����\n", e.start, e.end, e.weight);

			set_union(uset, vset); // �� ���� ������ ��ģ��.
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
	elementE heap[ME]; // heap�� �ڷ����� elementE  edge���� 
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
//����;
void insert_min_heap(HeapType* h, elementE item) {//element item �� g->edges.weig
	int i = ++(h->heap_size);//�Ǹ����� ��忡 ���ִٰ� �����ϰ� ���� 

	while (item.weight < h->heap[i / 2].weight && i != 1) {//�θ���� ��

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
	temp = h->heap[(h->heap_size)--];//�������Ű� ���� �ö󰡾� �ϴϱ� ������ ������ heapsize�� ���δ�

	parent = 1;
	child = 2;


	while (child <= h->heap_size) {//���� ���°ɷ�
		//���߿� �� ����
		if (child < h->heap_size && (h->heap[child].weight) >(h->heap[child + 1].weight)) {
			child++;
		}
		if (temp.weight < h->heap[child].weight) break;//�ؿ��� �°��� �Ʊ����� �� ���ϵ� �߿� ���Ѱ��߿� �� ū���� ���ص� ��ũ��
		//�׳� �д� ->���߿� parent�����ٰ� temp�����Ŷ� �׳� �θ� ��

		h->heap[parent] = h->heap[child];// temp���� ���ϵ� �� ���� ������� ��ġ�� �ٲ۴� �Ʒ����� ���� �ø���.
		parent = child;//���� ������ �Ʊ� ���ϵ尪���� �ű��
		child *= 2;

	}

	h->heap[parent] = temp;//����  �ؿ����� ����÷����ϱ� ���ϵ� �����ٰ� temp�� �־��ָ� ��
	print_heap(h);
	return item;//heap�� �ִ� �ϳ��� �� 
}



void heap_sort(Graph* g) {

	int i;
	HeapType* h;

	h = create();
	init(h);

	for (i = 0; i < g->n; i++) {
		insert_min_heap(h, g->edges[i]);

	}

	for (i =0; i <= (g->n - 1); i++) {// 0���� ���� n-1���� 
	//	printf(" debuging heap sort : %d, %d, %d ||||",g->edges[i].start,g->edges[i].end,g->edges[i].weight);
		g->edges[i] = delete_min_heap(h); 

	}
	free(h);
}




//------------------------------------------------------------------------------------------------------




//--
void heap_kruskal(Graph* g) {
	int edge_accepted = 0; // ������� ���õ� ������ ��
	int uset, vset; // ���� u�� ���� v�� ���� ��ȣ
	struct Edge e;

	set_init(g->n); // ���� �ʱ�ȭ
	heap_sort(g);
	//qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("ũ�罺Į �ּ� ���� Ʈ�� �˰��� \n");

	printf("heap sort ��� \n");
	int i = 0;
	while (edge_accepted < (g->n - 1)) { // ������ �� < (n - 1)


		e = g->edges[i];
		uset = set_find(e.start); // ���� u�� ���� ��ȣ
		vset = set_find(e.end); // ���� v�� ���� ��ȣ
		if (uset != vset) { // ���� ���� ������ �ٸ���
			printf("����( % d, % d) % d ����\n", e.start, e.end, e.weight);

			set_union(uset, vset); // �� ���� ������ ��ģ��.
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