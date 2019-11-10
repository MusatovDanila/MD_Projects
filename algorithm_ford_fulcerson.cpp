#include<iostream>
#include<vector>
#include <queue>
#include <string> 
#include <fstream> 

using namespace std;

int max_f_way(vector<int> flow, vector<vector<int>> matrix, int n) {
	int c = 1000000000;
	for (int i = flow[1], now = 1; i != -1; now = i, i = flow[i]) {
		if (c > matrix[i][now]) c= matrix[i][now];
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
	while (!q.empty()&& flow[1]==-1)
	{
		int now = q.front();
		q.pop();
		for (int i = 0; i < n && flow[1]==-1; i++) {
			if (matrix[now][i] > 0 && used[i]==0 ) {
				q.push(i);
				used[i] = 1;
				if(flow[i]==-1)	flow[i] = now;
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


void makeResult(string name)
{
	ifstream fin;
	fin.open(name);

	if (!fin.is_open())
		return;

	int n;
	fin >> n;
	int  a;
	vector<vector<int>> matrix(n, vector<int>());

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n;++j) { 
			fin >> a;
			matrix[i].push_back(a);
		}
	}
	
	

	cout << endl << "----------------" << endl << "max flow = " << max_flow(matrix, n) << endl << "----------------" << endl;
}


	int main() {
	makeResult("test1.in");
	system("pause");
	return 0;
}
