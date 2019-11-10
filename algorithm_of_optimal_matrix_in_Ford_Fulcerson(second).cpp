#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <queue>
#include <string> 
#include <fstream> 
using namespace std;

int max_f_way(vector<int> flow, vector<vector<int>> matrix, int n) {
	int c = INT_MAX;
	for (int i = flow[1], now = 1; i != -1; now = i, i = flow[i]) {
		if (c > matrix[i][now]) c = matrix[i][now];
	}
	return c;
}

vector<int> bfs(vector<vector<int>> matrix, int n)
{
	queue<int> q;
	vector<int> used(n, 0);
	vector<int> flow(n, -1);
	q.push(0);
	used[0] = 1;
	while (!q.empty() && flow[1] == -1)
	{
		int now = q.front();
		q.pop();
		for (int i = 0; i < n && flow[1] == -1; i++) {
			if (matrix[now][i] > 0 && used[i] == 0) {
				q.push(i);
				used[i] = 1;
				if (flow[i] == -1)	flow[i] = now;
			}

		}
	}
	return flow;
}
int max_flow(vector<vector<int>> matrix, int n) {
	//vector<vector<int>> residual_network;	//copy matrix;
	vector<int> way;
	int max_way_flow = 0;
	int flow_now;
	do {
		way = bfs(/*residual_network*/matrix, n);
		if (way[1] != -1) {
			flow_now = max_f_way(way, /*residual_network*/matrix, n);
			for (int i = way[1], now = 1; i != -1; now = i, i = way[i]) {
				matrix[i][now] -= flow_now;
				matrix[now][i] += flow_now;
			}
			max_way_flow += flow_now;
		}
	} while (way[1] != -1);

	return max_way_flow;
}


void makeResult(string name,string name2)
{
	ifstream fin,fun;
	fin.open(name);

	if (!fin.is_open())
		return;

	int a,b,n,m;
	fin >> a >> b;
	vector<int> gorz;
	vector<int> vert;
	for (int j = 0; j < a; ++j) {
		fin >> m;
		gorz.push_back(m);
	}
	for (int j = 0; j < b; ++j) {
		fin >> m;
		vert.push_back(m);
	}

	n = a + b + 2;
	vector<vector<int>>matrix(n, vector<int>(n));
	for (int i = 0; i < a; ++i) {
		matrix[0][i + 2] = gorz[i];
		matrix[i + 2][0] = gorz[i];
	}

	vector<vector<int>>matrix2(a, vector<int>());
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < b; ++j) {
			m = min(gorz[i], vert[j]);
			vert[j] -= m;
			gorz[i] -= m;
			matrix2[i].push_back(m);
		}
	}
	
	for (int i = 0; i < b; ++i) {
		matrix[1][a + 2+i] = INT_MAX;
		matrix[a + i+2][1] = INT_MAX;
	}
	for (int i = 2; i < a+2; ++i) {
		for (int j = a+2; j < n; ++j) {
			matrix[i][j] = matrix2[i-2][j-a-2];
			matrix[j][i] = matrix2[i-2][j-a - 2];
		}
	}
	
	/*for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}*/
	fun.open(name2);
	int result;
	fun >> result;
	int p = max_flow(matrix, n);
	cout << endl << "----------------" << endl << "max flow = "<< p << endl << "----------------" << endl;
	if (result == p) cout << "true"<< endl;
	else cout << "false"<< endl;
}
int main() {

	
	makeResult("test1.in","test1.out");

	system("pause");
	return 0;
}
