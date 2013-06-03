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

#define rep(x,n) for(int x = 0; x < int(n); ++x)
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
 
const int maxn=100000+10;
int a[10][7];
vector<int> add[10], rem[10];

char A[maxn],B[maxn],C[maxn];
int ta, tb, tc, n;

int bug(int x, int y) {
  int only_x=0,only_y=0;
  rep(i,7) {
    if(a[x][i]&&!a[y][i]) only_x++;
    if(!a[x][i]&&a[y][i]) only_y++;
  }
  return only_x == 1 && only_y == 1; // swap these
}

enum state {
	BEGIN, MUST_PUT_ONE, MUST_TAKE_ONE, DONE
};

int f(int z) { return z%10; }
int g(int z) { return z/10; }

int vis[maxn][2][4],passo;

int go(int pos, int carry, state st) {
	if(pos>=n) {
		return carry==0 && st==DONE;
	}
	
	if(vis[pos][carry][st]==passo) {
		return 0;
	} else {
		vis[pos][carry][st]=passo;
	}

	int da=(pos<ta?A[pos]:'0')-'0';
	int db=(pos<tb?B[pos]:'0')-'0';
	int dc=(pos<tc?C[pos]:'0')-'0';
	
	// do nothing
	if( f(da+db+carry) == dc ) {
		if( go(pos+1,g(da+db+carry),st) ) {
			return 1;
		}
	}

	// take one match
	if(st == BEGIN || st == MUST_TAKE_ONE) {
		state new_st = (st == BEGIN ? MUST_PUT_ONE : DONE);
		//A
		if(pos<ta) rep(i,rem[da].size()) {
			int nda=rem[da][i];
			if( f(nda+db+carry) == dc ) {
				if( go(pos+1,g(nda+db+carry),new_st) ) {
					A[pos]=nda+'0';
					return 1;
				}
			}
		}
		//B
		if(pos<tb) rep(i,rem[db].size()) {
			int ndb=rem[db][i];
			if( f(da+ndb+carry) == dc ) {
				if( go(pos+1,g(da+ndb+carry),new_st) ) {
					B[pos]=ndb+'0';
					return 1;
				}
			}
		}
		//C
		if(pos<tc) rep(i,rem[dc].size()) {
			int ndc=rem[dc][i];
			if( f(da+db+carry) == ndc ) {
				if( go(pos+1,g(da+db+carry),new_st) ) {
					C[pos]=ndc+'0';
					return 1;
				}
			}
		}
	}

	// place one match
	if(st == BEGIN || st == MUST_PUT_ONE) {
		state new_st = (st == BEGIN ? MUST_TAKE_ONE : DONE);
		//A
		if(pos<ta) rep(i,add[da].size()) {
			int nda=add[da][i];
			if( f(nda+db+carry) == dc ) {
				if( go(pos+1,g(nda+db+carry),new_st) ) {
					A[pos]=nda+'0';
					return 1;
				}
			}
		}
		//B
		if(pos<tb) rep(i,add[db].size()) {
			int ndb=add[db][i];
			if( f(da+ndb+carry) == dc ) {
				if( go(pos+1,g(da+ndb+carry),new_st) ) {
					B[pos]=ndb+'0';
					return 1;
				}
			}
		}
		//C
		if(pos<tc) rep(i,add[dc].size()) {
			int ndc=add[dc][i];
			if( f(da+db+carry) == ndc ) {
				if( go(pos+1,g(da+db+carry),new_st) ) {
					C[pos]=ndc+'0';
					return 1;
				}
			}
		}
	}

	// move one match
	if(st == BEGIN) {
		// A -> B
		if(pos<ta&&pos<tb) rep(i,rem[da].size()) rep(j,add[db].size()) {
			int nda=rem[da][i], ndb=add[db][j];
			if( f(nda+ndb+carry) == dc ) {
				if( go(pos+1,g(nda+ndb+carry),DONE) ) {
					A[pos]=nda+'0';
					B[pos]=ndb+'0';
					return 1;
				}
			}
		}
		// B -> A
		if(pos<ta&&pos<tb) rep(i,add[da].size()) rep(j,rem[db].size()) {
			int nda=add[da][i], ndb=rem[db][j];
			if( f(nda+ndb+carry) == dc ) {
				if( go(pos+1,g(nda+ndb+carry),DONE) ) {
					A[pos]=nda+'0';
					B[pos]=ndb+'0';
					return 1;
				}
			}
		}
		// A -> C
		if(pos<ta&&pos<tc) rep(i,rem[da].size()) rep(j,add[dc].size()) {
			int nda=rem[da][i], ndc=add[dc][j];
			if( f(nda+db+carry) == ndc ) {
				if( go(pos+1,g(nda+db+carry),DONE) ) {
					A[pos]=nda+'0';
					C[pos]=ndc+'0';
					return 1;
				}
			}
		}
		// C -> A
		if(pos<ta&&pos<tc) rep(i,add[da].size()) rep(j,rem[dc].size()) {
			int nda=add[da][i], ndc=rem[dc][j];
			if( f(nda+db+carry) == ndc ) {
				if( go(pos+1,g(nda+db+carry),DONE) ) {
					A[pos]=nda+'0';
					C[pos]=ndc+'0';
					return 1;
				}
			}
		}
		// B -> C
		if(pos<tb&&pos<tc) rep(i,rem[db].size()) rep(j,add[dc].size()) {
			int ndb=rem[db][i], ndc=add[dc][j];
			if( f(da+ndb+carry) == ndc ) {
				if( go(pos+1,g(da+ndb+carry),DONE) ) {
					B[pos]=ndb+'0';
					C[pos]=ndc+'0';
					return 1;
				}
			}
		}
		// C -> B
		if(pos<tb&&pos<tc) rep(i,add[db].size()) rep(j,rem[dc].size()) {
			int ndb=add[db][i], ndc=rem[dc][j];
			if( f(da+ndb+carry) == ndc ) {
				if( go(pos+1,g(da+ndb+carry),DONE) ) {
					B[pos]=ndb+'0';
					C[pos]=ndc+'0';
					return 1;
				}
			}
		}
		// A -> A
		if(pos<ta) rep(nda,10) if(bug(da,nda)) {
			if( f(nda+db+carry) == dc ) {
				if( go(pos+1,g(nda+db+carry),DONE) ) {
					A[pos]=nda+'0';
					return 1;
				}
			}
		}
		// B -> B
		if(pos<tb) rep(ndb,10) if(bug(db,ndb)) {
			if( f(da+ndb+carry) == dc ) {
				if( go(pos+1,g(da+ndb+carry),DONE) ) {
					B[pos]=ndb+'0';
					return 1;
				}
			}
		}
		// C -> C
		if(pos<tc) rep(ndc,10) if(bug(dc,ndc)) {
			if( f(da+db+carry) == ndc ) {
				if( go(pos+1,g(da+db+carry),DONE) ) {
					C[pos]=ndc+'0';
					return 1;
				}
			}
		}
	}

	return 0;
}

int read() {
	if(cin >> A); else return 0;
	rep(i,2) cin >> B;
	rep(i,2) cin >> C;
	return 1;
}

int read2() {
loop:
  int xa=rand()%2 + 1;
  int xb=rand()%2 + 1;
  rep(i,xa) A[i]=rand()%10+'0'; A[xa]=0;
  rep(i,xb) B[i]=rand()%10+'0'; B[xb]=0;
  int xc=0;
  for(int ca=0,i=0,j=0;i<xa||j<xb||ca;) {
    int d1=i<xa?A[i++]-'0':0;
    int d2=j<xb?B[j++]-'0':0;
    C[xc++]=f(d1+d2+ca)+'0';
    ca=g(d1+d2+ca);
  }
  C[xc]=0;
  reverse(A,A+xa);
  reverse(B,B+xb);
  reverse(C,C+xc);
  // A -> B
  vector<char *> V(3); V[0]=A,V[1]=B,V[2]=C;
  char *from=V[rand()%3], *to=V[rand()%3];
  rep(z,100) {
    // from
    int pos1=rand()%(strlen(from));
    int ant1=from[pos1]-'0';
    if(rem[ant1].size()<=0) continue;
    random_shuffle(rem[ant1].begin(),rem[ant1].end());
    int nxt1=rem[ant1].back();
    // to
    int pos2=rand()%(strlen(to));
    int ant2=to[pos2]-'0';
    if(from==to&&pos1==pos2)ant2=nxt1;
    if(add[ant2].size()<=0) continue;
    random_shuffle(add[ant2].begin(),add[ant2].end());
    int nxt2=add[ant2].back();
    printf("(OLD) %s + %s = %s\n",A,B,C);
    from[pos1]=nxt1+'0', to[pos2]=nxt2+'0';
    printf("(NEW) %s + %s = %s\n",A,B,C);
    return 1;
  }
  goto loop;
}

void process() {
	ta=strlen(A),tb=strlen(B),tc=strlen(C);
	reverse(A,A+ta);
	reverse(B,B+tb);
	reverse(C,C+tc);
	n=max(ta,max(tb,tc));
	++passo;
	int pd = go(0,0,BEGIN);
	reverse(A,A+ta);
	reverse(B,B+tb);
	reverse(C,C+tc);
	printf("%s + %s = %s\n",A,B,C);
	rep(i,17) putchar('*'); puts("");
}

int main() {
	// 0
	rep(i,7) if(i!=2) a[0][i]=1;
	// 1
	rep(i,7) if(i==3||i==6) a[1][i]=1;
	// 2
	rep(i,7) if(i!=1&&i!=6) a[2][i]=1;
	// 3
	rep(i,7) if(i!=1&&i!=4) a[3][i]=1;
	// 4
	rep(i,7) if(i!=0&&i!=4&&i!=5) a[4][i]=1;
	// 5
	rep(i,7) if(i!=3&&i!=4) a[5][i]=1;
	// 6
	rep(i,7) if(i!=3) a[6][i]=1;
	// 7
	rep(i,7) if(i==0||i==3||i==6) a[7][i]=1;
	// 8
	rep(i,7) a[8][i]=1;
	// 9
	rep(i,7) if(i!=4) a[9][i]=1;
	rep(i,10) rep(j,10) {
		int diff=0,ii=0,jj=0;
		rep(k,7) {
			diff+=a[i][k]!=a[j][k];
			ii+=a[i][k];
			jj+=a[j][k];
		}
		if(diff==1 && ii>jj) {
			add[j].push_back(i);
			rem[i].push_back(j);
		}
	}
	cin.sync_with_stdio(false);
	while(read()) {
		process();
	}
	return 0;
}

