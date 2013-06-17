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

const int maxn=1000;
pair<int,int> stick[maxn+10];
int good[maxn+10], sz;
int n,k;

int main() {
	cin.sync_with_stdio(false);
	int T;
	for(T=1;T;T--){
		cin>>n>>k;
		rep(i,n) cin>>stick[i].first, stick[i].second=i+1;
		sort(stick,stick+n);
		for(int i=sz=0;i+2*k<=n;i++) {
			long long s=0,l=0;
			for(int j=0;j<k;j++) s+=(l=stick[i+j+k].first);
			if(s>2*l) good[sz++]=i;
		}
		rep(mask,1<<k<<k) if(mask&1) if(__builtin_popcount(mask)==k) {
			rep(ii,sz) {
				int i=good[ii];
				long long sa=0,la=0,sb=0,lb=0;
				rep(j,2*k) {
					if(mask>>j&1) sa+=(la=stick[i+j].first);
					else sb+=(lb=stick[i+j].first);
				}
				if(sa>2*la && sb>2*lb) {
					puts("Yes");
					rep(j,2*k) if((mask>>j&1)==0) printf("%d ",stick[i+j].second);
					rep(j,2*k) if((mask>>j&1)!=0) printf("%d ",stick[i+j].second);
					return 0;
				}
			}
		}
	}
	puts("No");
	return 0;
}

