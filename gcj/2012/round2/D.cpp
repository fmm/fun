#include <bits/stdc++.h>
#define _ << " _ " <<
#define dbg(x) cerr << #x << " == " << x << endl
#define mp(x,y) make_pair((x),(y))
#define pv(x,y) {for(typeof(y) z=(x);z!=(y);z++)cerr<<*z<<" ";cerr<<endl;}
#define rep(x,y) for(int(x)=(0);(x)<int(y);++(x))
#define x first
#define y second
using namespace std;

typedef long long ll;
typedef pair<int,int> pt;

#if 0
#define GENERATE 1
#endif

int R,C;
char cave[66][66];

void read() {
	cin>>R>>C;
	rep(i,R) cin>>cave[i];
}

char work[66][66], mask[66][66];

struct state {
	char a[66][66];
	state() {}
	state(char from[66][66]) {
		rep(i,R+1) rep(j,C+1) a[i][j]=from[i][j];
	}
	int move_left() {
		int change=0;
		for(int i=0;i<R;i++) for(int j=0;j<C;j++) if(a[i][j]=='x') {
			if(work[i][j-1]!='#') {
				if(mask[i][j-1]!='x') return 0;
				a[i][j-1]='x';
				a[i][j]='.';
				change=1;
			}
		}
		return change;
	}
	int move_right() {
		int change=0;
		for(int i=0;i<R;i++) for(int j=C-1;j>=0;j--) if(a[i][j]=='x') {
			if(work[i][j+1]!='#') {
				if(mask[i][j+1]!='x') return 0;
				a[i][j+1]='x';
				a[i][j]='.';
				change=1;
			}
		}
		return change;
	}
	int move_down() {
		int change=0;
		for(int i=R-1;i>=0;i--) for(int j=0;j<C;j++) if(a[i][j]=='x') {
			if(work[i+1][j]!='#') {
				if(mask[i+1][j]!='x') return 0;
				a[i+1][j]='x';
				a[i][j]='.';
				change=1;
			}
		}
		return change;
	}
	int cx() {
		int x=0;
		rep(i,R) rep(j,C) if(a[i][j]=='x') x++;
		return x;
	}
	void imp() {
		rep(i,R) puts(a[i]); puts("~");
	}
	bool operator<(state s) const {
    rep(i,R) rep(j,C) if(a[i][j]!=s.a[i][j]) return a[i][j]<s.a[i][j];
    return false;
  }
};

const bool debug=false;

void go(int ii, int jj) {
	memcpy(work,cave,sizeof cave);
	work[ii][jj]='x';
	for(int i=R-1;i>=0;i--) for(int j=C-1;j>=0;j--) if(work[i][j]=='x') {
		for(int k=j;cave[i][k]!='#';k++) {
			work[i][k]='x';
			if(cave[i-1][k]!='#') work[i-1][k]='x';
		}
		for(int k=j;cave[i][k]!='#';k--) {
			work[i][k]='x';
			if(cave[i-1][k]!='#') work[i-1][k]='x';
		}
	}
	rep(i,R) rep(j,C) if(work[i][j]!='x'&&work[i][j]!='#') work[i][j]='.';
	if(debug) {
		dbg(cave[ii][jj]);
		rep(i,R) puts(work[i]);
	}
	memcpy(mask,work,sizeof work);
	state at(work), tmp;
  for(;;) {
		int ok=0;
    #define DOWN  {tmp=at;if(tmp.move_down()) ok=1, at=tmp;}
    #define LEFT  {tmp=at;if(tmp.move_left()) at=tmp; else break;}
    #define RIGHT {tmp=at;if(tmp.move_right()) at=tmp; else break;}
    rep(i,C+1) rep(j,C+1) {
      rep(x,i) { LEFT; }
      rep(x,j) { RIGHT; }
      DOWN;
    }
    rep(i,C+1) rep(j,C+1) {
      rep(x,j) { RIGHT; }
      rep(x,i) { LEFT; }
      DOWN;
    }
		if(!ok) break;
	}
	
	int lucky=at.cx()==1;
	at=state(mask);
	printf("%c: %d %s\n",cave[ii][jj],at.cx(),lucky?"Lucky":"Unlucky");
}

void process() {
	puts("");
	for(int d='0';d<='9';d++) rep(i,R) rep(j,C) if(cave[i][j]==d) go(i,j);
}

int main() {
	int T;
#ifdef GENERATE
	unsigned int seed=time(0);
	dbg(seed);
	srand(seed);
	T=50;
	for(int testcase=1;testcase<=T;++testcase) {
		fprintf(stderr,"Case #%d:",testcase);
		// *generate input!
		// BEGIN
		// END
#else
	cin>>T;
	for(int testcase=1;testcase<=T;++testcase) {
		fprintf(stdout,"Case #%d:",testcase);
		read();
#endif
    dbg(testcase);
    if(debug&&testcase!=6) continue;
		try {
			process();
		} catch(char const*exception) {
			puts(exception);
		}
	}
	return 0;
}

