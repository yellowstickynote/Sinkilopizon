struct Xortrie {
	struct Node {
		int nxt[2] = {0, 0};
		int cnt = 0;
	};
	vector<Node> t;
	Xortrie() : t(1) {}
	Xortrie(const vector<int>& a) : Xortrie() {
		for (int x : a) update(x, 1);
	}
	void update(int x, int val = 1) {
		int u = 0;
		t[u].cnt += val;
		for (int i = 30; i >= 0; i--) {
			int b = (x >> i) & 1;
			if (!t[u].nxt[b]) {
				t[u].nxt[b] = t.size();
				t.push_back(Node());
			}
			u = t[u].nxt[b];
			t[u].cnt += val;
		}
	}
	int maxxor(int x) {
		if (t[0].cnt == 0) return 0;
		int u = 0, res = 0;
		for (int i = 30; i >= 0; i--) {
			int b = (x >> i) & 1;
			int opt = b ^ 1;
			if (t[u].nxt[opt] && t[t[u].nxt[opt]].cnt){
				res |= (1 << i);
				u = t[u].nxt[opt];
			} else {
				u = t[u].nxt[b];
			}
		}
		return res;
	}
};
