vector<int> to_vec(const string &s, int norm = 0) {
	vector<int> v(s.size());
	for (int i = 0; i < (int)s.size(); i++) v[i] = s[i] - norm;
	return v;
}

struct ZArray {
	vector<int> z;
	ZArray(const vector<int> &p) : z(zarray(p)) {}
	static vector<int> zarray(const vector<int> &s) {
		vint zarr(s.size());
		int l = 0, r = 0;
		for(int i = 1; i<s.size(); i++){
			zarr[i] = min(r-i, zarr[i-l]);
			zarr[i] = max(zarr[i],0LL);
			for(;zarr[i] + i < s.size() && s[i+zarr[i]] == s[zarr[i]]; zarr[i]++);
			if(i+zarr[i]>r){
				r = i + zarr[i];
				l = i;
			}
		}
		return zarr;
	}
};

