#include <bits/stdc++.h>
#include <random>
#define int long long
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int gen(int l, int r){
	uniform_int_distribution<> uni(l,r);
	return uni(rng);
}
double genreal(double l, double r){
	uniform_real_distribution<> uni(l,r);
	return uni(rng);
}
void solve(){
	int n = gen(1,100);
	int m = gen(1,1000);
	cout<<n<<' '<<m<<endl;
}
signed main() {
	int t = 1;
	while(t--){
		solve();
	}
	return 0;
}

