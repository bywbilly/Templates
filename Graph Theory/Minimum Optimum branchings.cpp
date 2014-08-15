#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 99999999;

struct point {
	double x, y;
} p[200];

int pre[200]; //��¼�ýڵ��ǰ��
double graph[200][200], ans; //ͼ����ͽ��
bool visit[110], circle[110]; //visit��¼�õ���û�б����ʹ���circle��¼�ĵ��ǲ�����һ��Ȧ��
int n, m, root; //������+����+���ڵ���

void dfs(int t) { //һ���������������������һ��������ͨ�ռ�
	int i;
	visit[t] = true;
	for (i = 1; i <= n; ++i) {
		if (!visit[i] && graph[t][i] != INF)
			dfs(i);
	}
}

bool check() { //����������������С����ͼ�Ƿ���ڣ���������ڣ���ôһ��dfs��Ӧ�ÿ��Ա��������еĽڵ�
	memset(visit, false, sizeof(visit));
	dfs(root);

	for (int i = 1; i <= n; ++i)
		if (!visit[i])
			return false;
	return true;
}

double dist(int i, int j) {
	return sqrt(
		(p[i].x - p[j].x) * (p[i].x - p[j].x) + 
		(p[i].y - p[j].y) * (p[i].y - p[j].y));
}

int exist_circle() { //�ж�ͼ���ǲ��Ǵ�������Ȧ
	int i;
	int j;
	root = 1;
	pre[root] = root;
	for (i = 1; i <= n; ++i) {
		if (!circle[i] && i != root) {
			pre[i] = i;
			graph[i][i] = INF;

			for (j = 1; j <= n; ++j) {
				if (!circle[j] && graph[j][i] < graph[pre[i]][i])
					pre[i] = j;
			}
		}
	}  //���forѭ�������ҳ����зǸ��ڵ��ǰ���ڵ�
	for (i = 1; i <= n; ++i) {
		if (circle[i]) continue;
		memset(visit, false, sizeof(visit));
		int j = i;
		while (!visit[j]) {
			visit[j] = true;
			j = pre[j];
		}
		if (j == root)
			continue;
		return j;
	} //��Ȧ���̣���󷵻�ֵ��Ȧ�е�һ����

	return -1; //���û��Ȧ������-1
}

void update(int t) { //��Ȧ֮���������
	int i, j;
	ans += graph[pre[t]][t];
	for (i = pre[t]; i != t; i = pre[i]) {
		ans += graph[pre[i]][i];
		circle[i] = true;
	} //���Ȱ�Ȧ��ı�Ȩȫ������������������t�ڵ㣬��Ϊ�ⲿ�ӿ�

	for (i = 1; i <= n; ++i)
		if (!circle[i] && graph[i][t] != INF)
			graph[i][t] -= graph[pre[t]][t];
	//�������forѭ���������Ƕ�t�ڵ������²�����ΪʲôҪ������������Կ����������ѭ��������������

	for (j = pre[t]; j != t; j = pre[j])
		for (int i = 1; i <= n; ++i) {
			if (circle[i])
				continue;
			if (graph[i][j] != INF)
				graph[i][t] = min(graph[i][t], graph[i][j] - graph[pre[j]][j]);
			/**/ //////////////////////////////////////////////////////////////////////////
			graph[t][i] = min(graph[j][i], graph[t][i]);
		}
	//���ѭ����Ȧ�е�����������и���
}

void solve() {
	int j;
	memset(circle, false, sizeof(circle));
	while ((j = exist_circle()) != -1)
		update(j);

	for (j = 1; j <= n; ++j)
		if (j != root && !circle[j])
			ans += graph[pre[j]][j];

	printf("%.2f\n", ans);
}

int main() {
	int i;
	while (scanf("%d%d", &n, &m) != EOF) {
		for (i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j)
				graph[i][j] = INF;

		for (i = 1; i <= n; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);

		for (i = 0; i < m; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			graph[a][b] = dist(a, b);
		}

		root = 1;
		ans = 0;
		if (!check())
			printf("poor snoopy\n");
		else
			solve();
	}

	return 0;
}
