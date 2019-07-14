#include <iostream>
#include <stdio.h>

typedef struct Node
{
	int self_id;
	int parrent_id;
	int left_id;
	int right_id;

	// depth는 부모의 depth + 1이다.
	int depth;
}node;

typedef struct Data
{
	// 문제의 input으로 들어오는 node의 id를 pool의 idx로 매핑한다.
	// tree를 구성하는 node의 id는 1부터 시작한다.
	int idToidx[50010];

	// tree node poll
	node pool[50010];
	// idx를 1부터 시작시킨다 idToidx에서 할당안됨과 구별하기 위함.
	int idx;
}data;

static data workspace;
static data initializer;

// idx를 return한다.
inline int getNewNode()
{
	return workspace.idx++;
}

// id에 할당된 node의 idx를 return한다.
// 0이 return된다면 node가 할당 되어있지 않다는것이다.
inline int getIdx(int id)
{
	return workspace.idToidx[id];
}

inline void getChild(int p_id, int c_id)
{
	int p_idx = getIdx(p_id);
	int c_idx = getIdx(c_id);

	node* p_ptr = &(workspace.pool[p_idx]);
	node* c_ptr = &(workspace.pool[c_idx]);

	//node* p_ptr = &(workspace.pool[getIdx(p_id)]);
	//node* c_ptr = &(workspace.pool[getIdx(c_id)]);

	//pool의 idx는 1부터 시작하기떄문에 0 이면 없다는거다.
	if (p_ptr->left_id == 0)
	{
		p_ptr->left_id = c_id;
	}
	else
	{
		p_ptr->right_id = c_id;
	}

	c_ptr->parrent_id = p_id;
	c_ptr->depth = p_ptr->depth + 1;

}

inline node* getNode(int id)
{
	return &(workspace.pool[workspace.idToidx[id]]);
}

void dfs(int id)
{
	// 모든 노드에 대해 상위 뎁스별 노드 정보를 저장해둔다.
	// 이 정보는 LCA2(a_id, b_id)쿼리시 사용하기 위합니다.

	//노드의 개수는 최대 5만개이다.
	//어떠한 노드가 가질수있는 최대깊이는 5만개이다.
	//5만 * 5만 

	
	return;
}

int LCA2(int a_id, int b_id)
{
	return 0;
}

int LCA(int a_id, int b_id)
{
	// 두 node의 최소 공통 조상을 찾는다.
	// 두 node중 depth가 더 깊은쪽을 더 얕은 쪽으로 마춰준다.
	// 그뒤 한 depth씩 부모를 타고 올라가며
	// 동일한 부모가 나오면 정지한다.

	node* a_ptr = getNode(a_id);
	node* b_ptr = getNode(b_id);

	//공통조상이 자기자신일 수도 있다 그러므로 시작은 self
	register int a_ans_id = a_ptr->self_id;
	register int b_ans_id = b_ptr->self_id;
	register int a_ans_depth = a_ptr->depth;
	register int b_ans_depth = b_ptr->depth;

	// 조상의 깊이를 통일시켜준다.
	if (a_ans_depth > b_ans_depth)
	{
		// a > b
		while (a_ans_depth != b_ans_depth)
		{
			//a의 상위 조상을 찾는다.
			a_ans_id = workspace.pool[getIdx(a_ans_id)].parrent_id;
			a_ans_depth = workspace.pool[getIdx(a_ans_id)].depth;
		}

	}
	else if (b_ans_depth > a_ans_depth)
	{
		// b > a
		while (a_ans_depth != b_ans_depth)
		{
			b_ans_id = workspace.pool[getIdx(b_ans_id)].parrent_id;
			b_ans_depth = workspace.pool[getIdx(b_ans_id)].depth;
		}

	}
	else
	{
		//same
		//do nothing

	}

	while (a_ans_id != b_ans_id)
	{
		a_ans_id = workspace.pool[getIdx(a_ans_id)].parrent_id;
		a_ans_depth = workspace.pool[getIdx(a_ans_id)].depth;

		b_ans_id = workspace.pool[getIdx(b_ans_id)].parrent_id;
		b_ans_depth = workspace.pool[getIdx(b_ans_id)].depth;

	}

	return a_ans_id;
}

int main()
{

	//init;
	workspace.idx = 1;

	// node의 갯수
	int N = 0;
	//std::cin >> N;
	scanf("%d", &N);


	//input handle
	int a_id = 0, b_id = 0;
	int a_idx = 0 , b_idx = 0;
	for (int i = 1; i < N; i++)
	{
		//std::cin >> a_id;
		//std::cin >> b_id;
		scanf("%d", &a_id);
		scanf("%d", &b_id);

		a_idx = getIdx(a_id);
		b_idx = getIdx(b_id);

		if (a_idx == 0)
		{
			a_idx = getNewNode();
			workspace.pool[a_idx].self_id = a_id;
			workspace.idToidx[a_id] = a_idx;
		}

		if (b_idx == 0)
		{
			b_idx = getNewNode();
			workspace.pool[b_idx].self_id = b_id;
			workspace.idToidx[b_id] = b_idx;
		}

		if (a_id < b_id)
		{
			//a_id > b_id
			//a가 부모 b가 자식
			getChild(a_id, b_id);

		}
		else
		{
			//b_id > a_id
			//b가 부모  a가 자식
			getChild(b_id, a_id);
		}

	}

	int M = 0;
	//std::cin >> M;
	scanf("%d", &M);

	int ret = 0;
	for (int i = 0; i < M; i++)
	{

		//std::cin >> a_id;
		//std::cin >> b_id;

		scanf("%d", &a_id);
		scanf("%d", &b_id);

		ret = LCA(a_id, b_id);

		//공통조상 출력
		printf("%d\n", ret);	
	}

	return 0;

}
