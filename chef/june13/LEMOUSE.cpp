#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cfloat>
#include <climits>
#include <cctype>
#include <cmath>
#include <cassert>
#include <ctime>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <complex>
#include <limits>
#include <functional>
#include <numeric>

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

int n,m;
char A[111][111];
int f[111][111][1<<9];
int g[111][111][1<<9],h;

/*
	 012
	 3x5
	 678
 */

int go(int i, int j, int ja) {

	int &res = f[i][j][ja];
	int &mk =  g[i][j][ja];

	if(mk==h) return res;

	res=0;
	mk=h;

	// center
	if(A[i][j]=='1') {
		res += !(ja>>4&1);
		ja |= (1<<4);
	}

	// up
	if(i-1>=0 && A[i-1][j]=='1') {
		res += !(ja>>1&1);
		ja |= (1<<1);
	}

	// down
	if(i+1<n && A[i+1][j]=='1') {	
		res += !(ja>>7&1);
		ja |= (1<<7);
	}

	// left
	if(j-1>=0 && A[i][j-1]=='1') {
		res += !(ja>>3&1);
		ja |= (1<<3);
	}

	// right
	if(j+1<m && A[i][j+1]=='1') {
		res += !(ja>>5&1);
		ja |= (1<<5);
	}

	if(i+1==n&&j+1==m) return res;

	/*
		 012
		 3x5
		 678

		 12?
		 4x?
		 78?

		 345
		 6x8
		 ???
	 */

	int ja1=0;
	ja1 |= (ja>>1&1)<<0;
	ja1 |= (ja>>2&1)<<1;
	ja1 |= (ja>>4&1)<<3;
	ja1 |= (ja>>5&1)<<4;
	ja1 |= (ja>>7&1)<<6;
	ja1 |= (ja>>8&1)<<7;

	int ja2=0;
	ja2 |= (ja>>3&1)<<0;
	ja2 |= (ja>>4&1)<<1;
	ja2 |= (ja>>5&1)<<2;
	ja2 |= (ja>>6&1)<<3;
	ja2 |= (ja>>7&1)<<4;
	ja2 |= (ja>>8&1)<<5;

	int a = (i+1<n) ? go(i+1,j,ja2) : 1e9;
	int b = (j+1<m) ? go(i,j+1,ja1) : 1e9;

	res += min(a,b);

	return res;
}

int main() {
	cin.sync_with_stdio(false);
	int T;
	for(cin>>T;T;T--) {
		cin>>n>>m;
		rep(i,n) cin>>A[i];
		++h;
		int R=go(0,0,0);
		printf("%d\n",R);
	}
	return 0;
}
