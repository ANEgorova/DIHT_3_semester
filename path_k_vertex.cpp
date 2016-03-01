#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
 
vector<int> find_path(int end, vector<int> parent){
	vector<int> path;
	for (int j = end; j != -1; j = parent[j])
		path.push_back(j);
	reverse(path.begin(), path.end());
	return path;
}

pair<int, int>	find_max_pair(vector<int> parent, vector<vector<int>> ListAdj){
	vector<pair<int, int>> path(ListAdj.size());
	for (size_t i = 1; i < ListAdj.size(); i++){
		path[i].first = -1;
		path[i].second = i;
	}

	for (size_t i = 1; i < ListAdj.size(); ++i){
		for (int j = i; j != -1; j = parent[j])
			path[i].first++;
	}
	return (*max_element(path.begin(), path.end()));
}

vector<int> BFS(vector<vector<int>> ListAdj, int start, int size){
	
	queue<int> wait;
	wait.push(start);
	vector<bool> used(size, false);
	vector<int> dist(size), parent(size);
	used[start] = true;
	parent[start] = -1;
	while (!wait.empty()) {
		int top_vert = wait.front();
		wait.pop();
		for (size_t i = 0; i < ListAdj[top_vert].size(); i++) {
			int tmp_vert = ListAdj[top_vert][i];
			if (!used[tmp_vert]) {
				used[tmp_vert] = true;
				wait.push(tmp_vert);
				dist[tmp_vert] = dist[top_vert] + 1;
				parent[tmp_vert] = top_vert;
			}
		}
	}
	return parent;
}

int move_in_diameter(vector<int> diameter_vertex, int index, int request_dist){

	if (index - request_dist >= 0)
		return diameter_vertex[index - request_dist];
	else {
		if (index + request_dist < diameter_vertex.size())
			return diameter_vertex[index + request_dist];
		else
			return -1;
	}
}

int main(){
	int N, Q;

	cin >> N;
	size_t i = 0;
	vector<vector<int>> ListAdj(N + 1);
	int start, end;
	for (i = 0; i < N - 1; i++) {
		cin >> start >> end;
		ListAdj[start].push_back(end);
		ListAdj[end].push_back(start);
	}

	cin >> Q;
	vector<pair<int, int>> Requests(Q);
	for (i = 0; i < Q; i++) {
		cin >> Requests[i].first >> Requests[i].second;
	}
	
	
	int Start_diameter = find_max_pair(BFS(ListAdj, 1, N + 1), ListAdj).second;
	pair<int, int> length_vert = find_max_pair(BFS(ListAdj, Start_diameter, N + 1), ListAdj);
	int diameter = length_vert.first;
	int End_diameter = length_vert.second;
	vector<int> parent = BFS(ListAdj, Start_diameter, N + 1);
	vector<int> diameter_vertex = find_path(End_diameter, parent);
	vector<int> index_diameter(N + 1, -1);

	
	vector<bool> isInDiameter(N + 1, false);
	for (i = 0; i < diameter_vertex.size(); i++) {
		isInDiameter[diameter_vertex[i]] = true;
		index_diameter[diameter_vertex[i]] = i;
	}
	
	vector<vector<int>> ParentI(N + 1);
	double diameter_log;
	if (diameter == 0){
		diameter_log = 1;
		for (i = 1; i < N + 1; i++){
			ParentI[i].resize(diameter_log);
		}
	}
	else{
		diameter_log = ceil(log(diameter) / log(2));
		for (i = 1; i < N + 1; i++){
			ParentI[i].resize((int)diameter_log + 1);
		}
	}

	
	for (i = 1; i < N + 1; i++) {
		if (isInDiameter[i])
			ParentI[i][0] = -2;
		else
			ParentI[i][0] = parent[i];
	}

	vector<int> max_jump_index(N + 1);
	for (size_t j = 1; j <= diameter_log; j++){
		if (diameter == 0) break;
		else{
			for (i = 1; i < N + 1; i++) {
				if (isInDiameter[i])
					ParentI[i][j] = -2;
				else {
					if (ParentI[i][j - 1] == -2)
						ParentI[i][j] = -2;
					else {
						ParentI[i][j] = ParentI[ParentI[i][j - 1]][j - 1];
						if (ParentI[ParentI[i][j - 1]][j - 1] == -2)
							max_jump_index[i] = j - 1;
					}

				}
			}
		}	
	}

	int result = 0;
	
	for (i = 0; i < Q; i++) {
		if (Requests[i].second > diameter){
			cout << "-1" << endl;
			continue;
		}
		if (isInDiameter[Requests[i].first]) { 
			int index = index_diameter[Requests[i].first];
			result = move_in_diameter(diameter_vertex, index, Requests[i].second);
		}
		else {
			int tmp_jump = 0;
			int start_jump = 0;
			int l = 0;
			int j = 0;
			if (Requests[i].second < pow(2, max_jump_index[i])){
				while (tmp_jump != Requests[i].second){
					
					
					while (start_jump > Requests[i].second){
						l = ParentI[i][max_jump_index[i] - j];
						start_jump = pow(2, max_jump_index[i] - j);
						j--;
					}
					
					i = l;
					tmp_jump += start_jump;
					j = 0;
				}
				result = l;
			}
			else {
				while (!isInDiameter[l]) {
					l = ParentI[Requests[i].first][max_jump_index[i]];
					tmp_jump += pow(2, max_jump_index[i]);
					if (tmp_jump == Requests[i].second){
						result = l;
						break;
					}
				}
					int index = index_diameter[l];
					result = move_in_diameter(diameter_vertex, index, Requests[i].second - tmp_jump);
			}
		}
		cout << result << endl;
	}	
}