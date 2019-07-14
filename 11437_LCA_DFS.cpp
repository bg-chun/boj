#include <iostream>
#include <stdio.h>

typedef struct Vector
{
	int v;
	Vector* next;
}vector;

typedef struct Data
{
	vector* vectors[50010];
	vector vectorNode[100010];
	int vIdx;

	int visited[50010];
	int pId[50010];
	int depth[50010];
}data;

static data workspace;

inline vector* getNewVectorNode(int v)
{
	workspace.vectorNode[workspace.vIdx].v = v;
	return &(workspace.vectorNode[workspace.vIdx++]);
}

static int tmp;
inline int LCA(int a, int b)
{
	//swap
	if (workspace.depth[a] < workspace.depth[b])
	{
		tmp = a;
		a = b;
		b = tmp;
	}

	//a의 depth가 더 깊다. b와 같아질떄까지 올려준다.
	while (workspace.depth[a] != workspace.depth[b])
	{
		a = workspace.pId[a];
	}

	//깊이가 같아졌으면 공통 조상이 나올때까지 반복한다.
	
	while (a != b)
	{
		a = workspace.pId[a];
		b = workspace.pId[b];
	}

	return a;
}

void dfs_calc(int pid, int id, int depth)
{
	if (workspace.visited[id] == 1)
	{
		return;
	}

	workspace.visited[id] = 1;

	workspace.pId[id] = pid;
	workspace.depth[id] = depth;

	vector* node = workspace.vectors[id];

	while (node)
	{
		if (workspace.visited[node->v] != 1)
		{
			dfs_calc(id, node->v, depth + 1);
		}
		node = node->next;
	}

	return;
}
static int N, M, a, b;
static vector* tmpV;
int main()
{
	//std::cin >> N;
	scanf("%d", &N);
	
	

	for (register int i = 1; i < N; i++)
	{
		//std::cin >> a;
		//std::cin >> b;
		scanf("%d", &a);
		scanf("%d", &b);

		if (workspace.vectors[a] == 0)
		{
			workspace.vectors[a] = getNewVectorNode(b);
		}
		else
		{
			tmpV = workspace.vectors[a];
			workspace.vectors[a] = getNewVectorNode(b);
			workspace.vectors[a]->next = tmpV;
		}

		if (workspace.vectors[b] == 0)
		{
			workspace.vectors[b] = getNewVectorNode(a);
		}
		else
		{
			tmpV = workspace.vectors[b];
			workspace.vectors[b] = getNewVectorNode(a);
			workspace.vectors[b]->next = tmpV;
		}

	}

	//void dfs_calc(int pid, int id, int depth)
	dfs_calc(-1, 1, 0);



	M = 0;
	std::cin >> M;

	for (register int i = 0; i < M; i++)
	{
		//std::cin >> a;
		//std::cin >> b;
		scanf("%d", &a);
		scanf("%d", &b);
		printf("%d\n", LCA(a, b));
	}

	return 0;
}
