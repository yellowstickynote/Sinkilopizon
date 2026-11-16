struct ZArray {
	vector<int> z;
	template <class C> ZArray(const C &p) : z(zarray(p)) {}
	template <class C> static vector<int> zarray(const C &s) {
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
