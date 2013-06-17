#include <bits/stdc++.h>
#include <sys/time.h>
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

struct timeval start, now;

void starttimer(){
	gettimeofday(&start, NULL);
}

int elapsed(){
	gettimeofday(&now, NULL);
	return (now.tv_sec-start.tv_sec)*1000000+(now.tv_usec-start.tv_usec);
}

template<class T> void magic(T data[], int nn, int isign) {
	int n = nn << 1, j = 1;
	for(int i = 1,z; i < n; i += 2) {
		if(j > i) swap(data[j], data[i]), swap(data[j+1], data[i+1]);
		for(z = n >> 1; z >= 2 && j > z; j -= z, z >>= 1);
		j += z;
	}
	for(int mmax = 2, istep;n > mmax;mmax = istep) {
		istep = mmax << 1;
		T theta = 2 * M_PI / (isign * mmax);
		T wtemp = sin(0.5 * theta);
		T wpr = - 2.0 * wtemp * wtemp;
		T wpi = sin(theta);
		T wr = 1.0, wi = 0.0;
		for(int m = 1; m < mmax; m += 2) {
			for(int i = m; i <= n; i += istep) {
				j = i + mmax;
				T tempr = wr*data[j]   - wi*data[j+1];
				T tempi = wr*data[j+1] + wi*data[j];
				data[j]    = data[i]   - tempr;
				data[j+1]  = data[i+1] - tempi;
				data[i]   += tempr;
				data[i+1] += tempi;
			}
			wr = (wtemp = wr) * wpr - wi * wpi + wr;
			wi = wi * wpr + wtemp * wpi + wi;
		}	
	}
}

vector<int> best;
const int maxm=100000,sz=131072,maxmod=10;
int B[maxm], M;
int freq[maxm];
int vis[maxm], passo;
int have[maxm], bad[maxm], how;
float a[sz<<3];

void prepare() {
	static int n, did=0;
	if(!did++) for(n=*max_element(B,B+M)*2+1;n&(n-1);++n);
	rep(i,n) {
		a[2*i+1]=(i<maxm?have[i]:0);
		a[2*i+2]=0;
	}
	magic(a,n,+1);
	for(int i=0;i<n;i++) {
		float new_real = a[2*i+1]*a[2*i+1] -a[2*i+2]*a[2*i+2];
		float new_imag = 2*a[2*i+1]*a[2*i+2];
		a[2*i+1] = new_real, a[2*i+2] = new_imag;
	}
	magic(a,n,-1);
	for(int i=0;i<maxm;i++) freq[i]=(int)(a[4*i+1]/n + 0.7777777);
}

void create(int x, int y, int mk) {
	if(x > y) swap(x,y);
	// ? x y
	int a = (x<<1)-y;
	if(0 <= a && a < maxm) vis[a] = mk; 
	// x ? y
	int b = x+y;
	if((b&1) == 0 && 0 <= (b>>1) && (b>>1) < maxm) vis[b>>1] = mk;
	// x y ?
	int c = (y<<1)-x;
	if(0 <= c && c < maxm) vis[c] = mk;
}

void greedy(int mk, vector<int> order, int mod) {
	++how;
	vector< vector<int> > data(mod);
	rep(i,M) data[B[i]%mod].push_back(B[i]);
	vector<int> ans;
	rep(k,order.size()) {
		vector<int> &V=data[order[k]];
		rep(i,V.size()) if(vis[V[i]]!=mk) {
			rep(j,ans.size()) create(ans[j],V[i],mk);
			ans.push_back(V[i]);
		} else ++bad[V[i]];
	}	
	if(ans.size() > best.size()) best=ans;
}

bool compare(int x, int y) {
	return freq[x]<freq[y];
}

vector<int> order[11];
int mod[11];
int q;

void push(string s) {
	vector<int> v;
	stringstream ss(s);
	for(int tmp;ss>>tmp;v.push_back(tmp));
	order[q]=v,mod[q]=v.size(),q++;
}

int process() {
	random_shuffle(B,B+M);
	stable_sort(B,B+M,compare);
	for(int i=0;i<q;i++) {
		if(elapsed()>979500) return 0;
		greedy(++passo,order[i],mod[i]);
	}
	return 1;
}

void read() {
	cin.sync_with_stdio(false);
	cin>>M;
	rep(i,M) cin>>B[i];
}

int main() {
	starttimer();
	push("1 3 4 5 0 2 6 7");
	push("0 1 3 5 7 2 4 6 8");
	push("0 2 3 5 7 1 4 6 8");
	push("1 0");
	push("0 1");
	read();
	rep(i,M) have[B[i]]=1;
	if(true) for(;;) {
		if(elapsed()<832345) prepare();
		if(!process()) break;
		rep(i,M) have[B[i]]=bad[B[i]]<how;
	}
#ifdef FMM
	printf("size= %4d\tscore= %lf\n",(int)best.size(),100.*best.size()/M);
#else
	print(best.size());
	pv(best.begin(),best.end());
#endif
	return 0;
}
