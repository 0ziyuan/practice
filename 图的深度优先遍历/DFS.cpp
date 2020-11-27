#include <stdio.h>
#include <stdlib.h>

int i, j, s;

typedef struct
{
	int** arc;   //�ڽӾ��� �ɿ����߱�   
	int numVertexes, numEdges;
}MGraph;

//ͼ���ڽ�����洢�ṹ
//�߱�ڵ�ṹ��һ��adjvex�����洢�ڽӵ��λ�ã�һ��nextָ������ָ����һ���ڵ�
typedef struct EdgeNode
{
	int adjvex;  //�洢�����±���Ϣ
	struct EdgeNode* next;
} EdgeNode;

//�����ڵ�ṹ
typedef struct
{
	int Vexs;  //�����洢������Ϣ
	EdgeNode* firstedge;  //�����洢��ǰ�������һ������
} VexList;

//�����ö�̬����洢�����Ȼ��numVertex,numEdge��һ��ͼ�Ķ������ͱ���
typedef struct
{
	VexList* q;
	int Vertexs, Edges;
} LGraph;

//����nΪ��������mΪ��������eΪ���бߣ�outΪ������С�1 <= n <= 3000, 1 <= m <= 100000, 0 <= e[i][j] < n��
void solveA(int n, int m, int e[][2], int out[]);//�ڽӾ���
void create(MGraph* G, int e[][2]);
void DFS(MGraph* G, int i, int* visited, int outA[]);
void solveB(int n, int m, int e[][2], int out[]);//�ڽ�����
void Lcreate(LGraph* G, int e[][2]);
void LDFS(LGraph* G, int i, int* visited, int outB[]);

int main() {
	int N = 0, M = 0;
	printf_s("�����붥����:\n");
	scanf_s("%d", &N);
	printf_s("������������:\n");
	scanf_s("%d", &M);
	if (N < 1 || N > 3000 || M < 1 || M > 100000)
	{
		return -1;
	}
	int(*E)[2] = NULL;
	E = (int(*)[2])malloc(sizeof(int) * M * 2);
	int* OUT = (int*)malloc(sizeof(int) * N);
	if (E == NULL ||OUT==NULL)
	{
		return -2;
	}
	printf_s("��������������:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			scanf_s("%d", &E[i][j]);
		}
	}
	solveA(N, M, E, OUT);
	for (i = 0; i < N; i++)
	{
		printf("%d ", OUT[i]);
	}
	printf("\n");
	solveB(N, M, E, OUT);
	for (i = 0; i < N; i++)
	{
		printf("%d ", OUT[i]);
	}
	system("pause");
	return 0;
}

void solveA(int n, int m, int e[][2], int out[])
{
	s = 0;
	MGraph* G = (MGraph*)malloc(sizeof(MGraph));
	G->numVertexes = n;
	G->numEdges = m;
	create(G, e);
	int* visited;
	visited = (int*)calloc(G->numVertexes, sizeof(int));
	for (i = 0; i < G->numVertexes; i++)
		if (visited[i] == 0)
			DFS(G, i, visited, out);
}

void create(MGraph* G, int e[][2])
{
	G->arc = (int**)malloc(sizeof(int*) * G->numVertexes);
	for (i = 0; i < G->numVertexes; i++)
	{
		G->arc[i] = (int*)calloc(G->numVertexes, sizeof(int));
	}
	for (j = 0; j < G->numEdges; j++)
	{
		G->arc[e[j][0]][e[j][1]] = 1;
		G->arc[e[j][1]][e[j][0]] = 1;
	}
}

void DFS(MGraph* G, int i, int* visited, int outA[])
{
	outA[s++] = i;
	visited[i] = 1;   //�����ʵı�� 
	for (int k = 0; k < G->numVertexes; k++)
	{
		if (G->arc[i][k] == 1 && visited[k] == 0)   //��(i,j)������j����δ�����ʣ��ݹ� 
			DFS(G, k, visited, outA);
	}
}

void solveB(int n, int m, int e[][2], int out[])
{
	s = 0;
	LGraph* G = (LGraph*)malloc(sizeof(LGraph));
	G->Vertexs = n;
	G->Edges = m;
	Lcreate(G, e);
	int* visited;
	visited = (int*)calloc(G->Vertexs, sizeof(int));
	for (i = 0; i < G->Vertexs; i++)
		if (visited[i] == 0)
			LDFS(G, i, visited, out);
}

void Lcreate(LGraph* G, int e[][2])
{
	G->q = (VexList*)malloc(sizeof(VexList) * G->Vertexs);
	for (i = 0; i < G->Vertexs; i++)
	{
		G->q[i].Vexs = i;
		G->q[i].firstedge = NULL;
	}
	for (j = 0; j < G->Edges; j++)
	{
		EdgeNode* node1 = (EdgeNode*)malloc(sizeof(EdgeNode));
		node1->adjvex = e[j][1];
		node1->next = NULL;
		if (G->q[e[j][0]].firstedge == NULL)
		{
			G->q[e[j][0]].firstedge = node1;
		}
		else
		{
			EdgeNode* w = G->q[e[j][0]].firstedge;
			while (w->next != NULL)
			{
				w = w->next;
			}
			w->next = node1;
		}
		EdgeNode* node2 = (EdgeNode*)malloc(sizeof(EdgeNode));
		node2->adjvex = e[j][0];
		node2->next = NULL;
		if (G->q[e[j][1]].firstedge == NULL)
		{
			G->q[e[j][1]].firstedge = node2;
		}
		else
		{
			EdgeNode* w = G->q[e[j][1]].firstedge;
			while (w->next != NULL)
			{
				w = w->next;
			}
			w->next = node2;
		}
	}
}

void LDFS(LGraph* G, int i, int* visited, int outB[])
{
	outB[s++] = i;
	visited[i] = 1;   //�����ʵı�� 
	if (G->q[i].firstedge != NULL)
	{
		EdgeNode* t = (G->q[i].firstedge);
		while (visited[t->adjvex] == 1 && t->next != NULL)
		{
			t = t->next;
		}
		if (visited[t->adjvex] == 1 && t->next == NULL)
		{
			return;
		}
		LDFS(G, t->adjvex, visited, outB);
	}
}