#include <iostream>
#include <stdio.h>

//lcrs트리로 구현해보자.
typedef struct Node
{
	int id;
	Node* childs;
	Node* siblings;
}node;

typedef struct Data
{
	node nodes[50010];
	int idx;

	node* idToptr[50010];

	int pId[50010];
	int depth[50010];
}data;

static data workspace;

inline node* getNewNode()
{
	return &(workspace.nodes[workspace.idx++]);
}

void dfs(int pid, node* ptr, int depth)
{
	//필요한 정보는 자기자신의 pid와 depth정보다.
	//깊이 우선으로 돌며 각 id별로 pid정보와 depth정보를 기록한다.

	if (ptr == 0)
	{
		return;
	}

	workspace.pId[ptr->id] = pid;
	workspace.depth[ptr->id] = depth;

	if (ptr->childs)
	{
		dfs(ptr->id, ptr->childs, depth + 1);
	}

	if (ptr->siblings)
	{
		node* siblings = ptr->siblings;

		while (siblings)
		{
			dfs(pid, siblings, depth);
			siblings = siblings->siblings;
		}
		
	}

	return;
}

int LCA(int a, int b)
{
	//swap
	if (workspace.depth[a] < workspace.depth[b])
	{
		int tmp = 0;
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

int main()
{
	int N = 0;
	std::cin >> N;
	int a, b;
	int tmp;
	node* a_ptr;
	node* b_ptr;

	for (int i = 1; i < N; i++)
	{
		std::cin >> a;
		std::cin >> b;

		//swap
		if (a > b)
		{
			tmp = b;
			b = a;
			a = tmp;
		}

		//build tree here!
		if (workspace.idToptr[a] == 0)
		{
			a_ptr = workspace.idToptr[a] = getNewNode();
			a_ptr->id = a;
		}
		else
		{
			a_ptr = workspace.idToptr[a];
		}

		if (workspace.idToptr[b] == 0)
		{
			b_ptr = workspace.idToptr[b] = getNewNode();
			b_ptr->id = b;
		}
		else
		{
			b_ptr = workspace.idToptr[b];
		}

		b_ptr->siblings = a_ptr->childs;
		a_ptr->childs = b_ptr;	

	}
	//dfs(int pid, node * ptr, int depth)
	dfs(-1, workspace.idToptr[1], 1);

	int M = 0;
	std::cin >> M;

	for (int i = 0; i < M; i++)
	{
		std::cin >> a;
		std::cin >> b;
		printf("%d\n", LCA(a, b));
	}

	return 0;
}
