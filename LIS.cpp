vector<int> LIS(vector<int>& v) {
	int N = v.size();
	vector<int> dp(N, 1<<30), id(N);
	for (int i = 0; i < N; i++) {
		id[i] = lower_bound(dp.begin(), dp.end(), v[i]) - dp.begin();
		dp[id[i]] = v[i];
	}
	int nl = *max_element(id.begin(), id.end());
	vector<int> ret(nl+1);
	for (int i = 0; i < N; i++) {
		if (id[N-1-i] == nl) ret[nl--] = v[N-1-i];
	}
	return ret;
}