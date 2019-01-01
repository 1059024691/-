#include<stdio.h>
#include<stdlib.h>


#define MAXV 10
#define INF 32767

typedef struct ANode
{
	int adjvex;
	int weight;
	struct ANode *next;
}ArcNode;
typedef struct Vnode
{
	int info;
	ArcNode *firstarc;
}VNode;
typedef struct
{
	VNode adjlist[MAXV];
	int n, e;
}AdjGraph;

/************全局变量***************/
int visit[MAXV];
/************************************/


void CreatGraph(AdjGraph *&G, int a[MAXV][MAXV], int n, int e)
{
	ArcNode *p;		//创建它用来malloc新的空间
	G = (AdjGraph *)malloc(sizeof(AdjGraph));//将头结点数组弄出来 
	for (int i = 0; i < n; i++)
		G->adjlist[i].firstarc = NULL;
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j >= 0; j--)
		{
			if (a[i][j] != 0 && a[i][j] != INF)
			{
				p = (ArcNode *)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->weight = a[i][j];
				p->next = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
		}
	}
	G->n = n;
	G->e = e;
}


void DispGraph(AdjGraph *G)
{
	ArcNode *p = NULL;
	for (int i = 0; i < G->n; i++)
	{
		printf("%3d : ", i);
		p = G->adjlist[i].firstarc;
		while (p != NULL)
		{
			printf("%3d[%2d] ->",p->adjvex,p->weight);
			p = p->next;
		}
		printf("  #\n");
	}
}


void DFSPath(AdjGraph *G, int u, int v, int path[], int d)
{
	ArcNode *p = G->adjlist[u].firstarc;
	visit[u] = 1;
	d++;
	path[d] = u;
	while (p!=NULL)
	{
		if (p->adjvex == v && d > 1)
		{
			for (int i = 0; i <= d; i++)
				printf("%3d", path[i]);
			printf("%3d\n", v);
		}
		if (visit[p->adjvex] == 0)
			DFSPath(G, p->adjvex, v, path, d);
		p = p->next;
	}
	visit[u] = 0;//用来回溯

}

void FindCyclePatha(AdjGraph *G, int k)
{
	int path[MAXV];
	DFSPath(G, k, k, path, -1);
}

void freeit(ArcNode *p)//递归free空间
{
	if (p != NULL)
	{
		freeit(p->next);
		free(p);
	}
}

void DestoryGraph(AdjGraph *&G)
{
	for (int i = 0; i < G->n; i++)
		freeit(G->adjlist[i].firstarc);
	free(G);
}

int main()
{
	int n = 5, e = 7;
	AdjGraph *G = NULL;
	int a[MAXV][MAXV] =
	{
	{0,1,1,0,0},
	{0,0,1,0,0},
	{0,0,0,1,1},
	{0,0,0,1,1},
	{1,0,0,0,0},
	};

	CreatGraph(G, a, n, e);

	printf("Graph G:\n");
	DispGraph(G);

	int k = 0;//回路点

	printf("All loops passing through vertex %d in Graph G:\n",k);

	FindCyclePatha(G, k);

	DestoryGraph(G);
	system("pause");
	return 0;
}