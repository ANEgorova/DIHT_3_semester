#include <iostream>
#include <vector>
#include <limits.h>
#include <math.h>
#include <algorithm>
#include <utility>

const int INF = LONG_MAX;

using namespace std;

struct inVertex{
	int start;
	int end;
	int start_max;
	int end_max;
	int s_suff;
	int e_preff;
	long long sum;
	long long seg_sum;
	long long suff;
	long long preff;
};

void update(inVertex& current, inVertex l, inVertex r){
	current.sum = l.sum + r.sum;
	current.start = l.start;
	current.end = r.end;
	current.preff = max(l.preff, l.sum + r.preff);
	if (current.preff == l.preff){
		current.e_preff = l.e_preff;
	}
	else{
		current.e_preff = r.e_preff;
	}
	current.suff = max(r.suff, r.sum + l.suff);
	if (current.suff == r.suff){
		current.s_suff = r.s_suff;
	}
	else {
		current.s_suff = l.s_suff;
	}
	long long tmp = max(l.seg_sum, r.seg_sum);
	int tmp_s, tmp_e;
	if (tmp == l.seg_sum){
		tmp_s = l.start_max;
		tmp_e = l.end_max;
	}
	else {
		tmp_s = r.start_max;
		tmp_e = r.end_max;
	}
	current.seg_sum = max(tmp, l.suff + r.preff);
	if (current.seg_sum == tmp){
		current.start_max = tmp_s;
		current.end_max = tmp_e;
	}
	else {
		current.start_max = l.s_suff;
		current.end_max = r.e_preff;
	}
}

void build_tree(vector<inVertex>& Vertex, int size){

	int n = 1;
	while (n < Vertex.size())
		n *= 2;
	inVertex badVertex = { 0, 0, 0, 0, 0, 0 , -INF, -INF, -INF, -INF};
	Vertex.resize(2 * n, badVertex);

	int T;
	for (int i = n; i < size + n - 1; i++){
		cin >> T;
		Vertex[i].sum = T;
		Vertex[i].seg_sum = T;
		Vertex[i].start = i - n + 1;
		Vertex[i].end = i - n + 1;
		Vertex[i].suff = T;
		Vertex[i].preff = T;
		Vertex[i].start_max = i - n + 1;
		Vertex[i].end_max = i - n + 1;
		Vertex[i].s_suff = i - n + 1;
		Vertex[i].e_preff = i - n + 1;
	}
	if (Vertex[size + n - 1].start == 0){
		Vertex[size + n - 1].start = Vertex[size + n - 2].start;
		Vertex[size + n - 1].end = Vertex[size + n - 2].end;
	}
	for (int i = n - 1; i > 0; i--){
		update(Vertex[i], Vertex[2 * i], Vertex[2 * i + 1]);
	}
}

inVertex answer_on_request(int l, int r, vector<inVertex> Vertex, int workVertex, int now_l, int now_r){

	if (now_l == l && now_r == r){
		return Vertex[workVertex];
	}
	int half = (now_l + now_r) / 2;
	if (r <= half){
		return answer_on_request(l, r, Vertex, 2 * workVertex, now_l, half);
	}
	if (l > half){
		return answer_on_request(l, r, Vertex, 2 * workVertex + 1, half+1, now_r);
	}

	inVertex result;
	update(result, answer_on_request(l, half, Vertex, 2 * workVertex, now_l, half), answer_on_request(half + 1, r, Vertex, 2 * workVertex + 1, half + 1, now_r));
	return result;
}

int main(){
	int size;
	cin >> size;
	size++;
	long long T;
	vector<inVertex> Vertex(size);
	build_tree(Vertex, size);	
	int size_ofrequest;
	cin >> size_ofrequest;
	vector<pair<int, int>> request(size_ofrequest);
	for (size_t i = 0; i < size_ofrequest; i++) {
		cin >> request[i].first>> request[i].second;
	}

	for (size_t i = 0; i < size_ofrequest; i++){
		
		if (request[i].first == request[i].second){
			cout << request[i].first << " " << request[i].first << endl;
		}
		else if (request[i].first > request[i].second || request[i].first > size || request[i].second > size){
			cout << "Request has wrong arguments!" << endl;
		}
		else{
			inVertex tmp;
			tmp = answer_on_request(request[i].first, request[i].second, Vertex, 1, Vertex[1].start, Vertex[1].end);
			cout << tmp.start_max << " " << tmp.end_max << endl;
		}
	}
}