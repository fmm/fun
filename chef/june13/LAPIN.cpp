#include <bits/stdc++.h>
#define rep(x,n) for(int x = 0; x < n; ++x)
#define print(x) cout << x << endl
#define dbg(x) cerr << #x << " == " << x << endl
#define _ << " , " <<
#define mp make_pair
#define x first
#define y second
using namespace std;

template<class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }

typedef long long ll;
typedef pair<int,int> pii;

void fix(string &s) {
	sort(s.begin(),s.begin()+s.size()/2);
}

int main() {
  int T;
	for(cin>>T;T;T--){
		string s;
		cin>>s;
		fix(s);
		reverse(s.begin(),s.end());
		fix(s);
		int ok=1;
		rep(i,s.size()) if(s[i]!=s[s.size()-i-1]) ok=0;
		puts(ok?"YES":"NO");
	}
	return 0;
}

