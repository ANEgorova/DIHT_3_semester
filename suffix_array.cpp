#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

struct minLCP {
	int length_LCP;
	int right_suff;
};

struct suffix {
	int index;
	int prior[2];
};

bool operator < (const minLCP& l, const minLCP& r) {
	return l.length_LCP < r.length_LCP;
}

int cmp(const struct suffix& a, const struct suffix& b) {
	return (a.prior[0] == b.prior[0]) ? (a.prior[1] < b.prior[1] ? 1 : 0) :
		(a.prior[0] < b.prior[0] ? 1 : 0);
}

vector<int> buildSuffixArray(const string& S, int n) {
	vector<struct suffix> suffixes(n);
	for (int i = 0; i < n; i++) {
		suffixes[i].index = i;
		suffixes[i].prior[0] = S[i] - 'a';
		suffixes[i].prior[1] = ((i + 1) < n) ? (S[i + 1] - 'a') : -1;
	}

	sort(suffixes.begin(), suffixes.end(), cmp);

	vector<int> ind(n);
	for (int k = 4; k < 2 * n; k = k * 2)
	{
		int rank = 0;
		int prev_rank = suffixes[0].prior[0];
		suffixes[0].prior[0] = rank;
		ind[suffixes[0].index] = 0;

		for (int i = 1; i < n; i++) {
			if (suffixes[i].prior[0] == prev_rank &&
				suffixes[i].prior[1] == suffixes[i - 1].prior[1]) {
				prev_rank = suffixes[i].prior[0];
				suffixes[i].prior[0] = rank;
			}
			else {
				prev_rank = suffixes[i].prior[0];
				suffixes[i].prior[0] = ++rank;
			}
			ind[suffixes[i].index] = i;
		}

		for (int i = 0; i < n; i++) {
			int nextindex = suffixes[i].index + k / 2;
			suffixes[i].prior[1] = (nextindex < n) ?
				suffixes[ind[nextindex]].prior[0] : -1;
		}
		sort(suffixes.begin(), suffixes.end(), cmp);
	}

	vector<int> suffixArr(n);
	for (int i = 0; i < n; i++)
		suffixArr[i] = suffixes[i].index;

	return  suffixArr;
}

void getLCP(vector<int>& str, const vector<int>& sufAr, vector<int>& LCP) {
	int n = sufAr.size();
	vector<int> rank(n);
	str[n] = -1;
	for (int i = 0; i < n; i++)
		rank[sufAr[i]] = i;
	int len = 0;
	for (int i = 0; i < n; i++)
		if (rank[i] > 0){
			int j = sufAr[rank[i] - 1];
			while (str[i + len] == str[j + len]) len++;
			LCP[rank[i]] = len;
			if (len > 0) len--;
		}
}

int main() {
	string S;
	cin >> S;
	int K;
	cin >> K;
	if (K == 1){
		cout << S << endl;
		return 0;
	}
	if (K == 0){
		cerr << "Wrong arguments!" << endl;
		return 0;
	}
	vector<int> sufArr;
	sufArr = buildSuffixArray(S, S.length());
	vector<int> LCP(S.length());
	vector<int> s_inNumber(S.length() + 1);
	for (size_t i = 0; i < S.length(); i++) {
		s_inNumber[i] = S[i];
	}
	getLCP(s_inNumber, sufArr, LCP);

	int left = 1;
	int right = K - 1;
	minLCP resultMax;
	set<pair<int, int> > current_min;
	for (size_t i = left; i < right + 1; i++) {
		current_min.insert(make_pair(LCP[i], i));
	}
	minLCP tmp = { current_min.begin()->first, sufArr[current_min.begin()->second], };
	resultMax = max(resultMax, tmp);
	right++;

	while (right != LCP.size()) {
		current_min.erase(make_pair(LCP[left], left));
		left++;
		current_min.insert(make_pair(LCP[right], right));
		minLCP tmp = { current_min.begin()->first, sufArr[current_min.begin()->second], };
		resultMax = max(resultMax, tmp);
		right++;
	}

	string result = S.substr(resultMax.right_suff, resultMax.length_LCP);
	if (result == "")
		cout << "There is no such string" << endl;
	else cout << result << endl;
}
