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

#define REP(i,a,b) for(i=a;i<b;i++)
#define EPS 1e-10
#define PI 3.141592653589793238462

// laycurse's fft

/* pnt denotes complex numbers: x=real part, y=imaginary part */
typedef struct struct_point{double x,y;}pnt;

pnt pntPlus(pnt a,pnt b){a.x+=b.x; a.y+=b.y; return a;}
pnt pntMinus(pnt a,pnt b){a.x-=b.x; a.y-=b.y; return a;}
pnt pntMultiple(pnt a,pnt b){pnt c; c.x=a.x*b.x-a.y*b.y; c.y=a.x*b.y+a.y*b.x; return c;}
pnt pntMultipleDouble(pnt a,double k){a.x*=k; a.y*=k; return a;}

pnt pntPolar(double r,double t){pnt a; a.x=r*cos(t); a.y=r*sin(t); return a;} /* r * exp(i*t), i=sqrt(-1) */
pnt pntGenerator(double x,double y){pnt res; res.x=x; res.y=y; return res;}   /* x + i*y */

/* Fast Fourier Transform */
/* n = size of a = a power of 2, theta = 2*PI/n */
/* for inverse fft, theta = -2*PI/n */
void fft(int n, double theta, pnt a[]){
	int i, j, k, m, mh;
	pnt w, x;
	for(m=n; m>=2; m/=2){
		mh = m / 2;
		rep(i,mh){
			w = pntPolar(1, i*theta);
			for(j=i; j<n; j+=m){
				k = j+mh;
				x = pntMinus(a[j], a[k]);
				a[j] = pntPlus(a[j], a[k]);
				a[k] = pntMultiple(w, x);
			}
		}
		theta *= 2;
	}
	i = 0;
	REP(j,1,n-1){
		for(k=n/2; k > (i ^= k); k/=2);
		if(j < i) w=a[i], a[i]=a[j], a[j]=w;
	}
}

const int maxn=(65536*2);
int x[maxn],y[maxn];
int R,C,N;
int row[maxn],column[maxn],diagonal[maxn];
pnt a[maxn], b[maxn];
int cd[maxn];

void pre(int n, pnt a[]) {
	fft(n,2*PI/n,a);
}

void doit(int n, pnt a[], pnt b[]) {
	rep(i,n) a[i] = pntMultiple(a[i],b[i]);
	fft(n,-2*PI/n,a);
}

int main() {
	cin.sync_with_stdio(false);
	int T;
	cin>>T;
	for(int testcase=1;testcase<=T;testcase++) {
		cin>>R>>C>>N;
		rep(i,N) {
			cin>>x[i]>>y[i];
			x[i]=R-x[i]+1;
		}
		rep(i,R+1) row[i]=0;
		rep(i,C+1) column[i]=0;
		rep(i,R+C+1) diagonal[i]=0;
		rep(i,N) {
			row[x[i]]=C;
			column[y[i]]=R;
			int d=x[i]+y[i];
			if(!diagonal[d]) {
				int d1=0;
				for(int dd=max(R,C);dd>0;) {
					int nd1=d1+dd;
					if(x[i]+nd1<=R&&y[i]-nd1>=1) d1=nd1;
					else dd/=2;
				}
				int d2=0;
				for(int dd=max(R,C);dd>0;) {
					int nd2=d2+dd;
					if(x[i]-nd2>=1&&y[i]+nd2<=C) d2=nd2;
					else dd/=2;
				}
				diagonal[d]=1+d1+d2;
			}
		}
		rep(i,maxn) a[i] = pntGenerator((i<=R&&row[i]>0),0);
		rep(i,maxn) b[i] = pntGenerator((i<=C&&column[i]>0),0);
		rep(i,R+C+1) cd[i] = 0;
		rep(i,R+1) if(row[i]) cd[i+1] += 1, cd[i+C+1] -= 1;
		rep(i,C+1) if(column[i]) cd[i+1] += 1, cd[i+R+1] -= 1;
		rep(i,R+C) cd[i+1] += cd[i];
		int n=R+C+1;
		while(n&(n-1))n++;
		pre(n,a), pre(n,b), doit(n,a,b);
		rep(i,R+C+1) if(diagonal[i]) {
			int ways = cd[i] - (int)(a[i].x/n + 0.7777777);
			diagonal[i] -= ways;
		}
		long long answer=0, nr=0, nc=0;
		rep(i,R+1) answer += row[i], nr += row[i]!=0;
		rep(i,C+1) answer += column[i], nc += column[i]!=0;
		rep(i,R+C+1) if(diagonal[i]>0) answer += diagonal[i];
		answer -= nr*nc;
		answer = (long long)R*C - answer;
		printf("Case %d: %lld\n",testcase,answer);
	}
	return 0;
}
