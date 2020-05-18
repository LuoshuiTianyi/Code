#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e6+7;
const int MOD=1e9+7;
struct Edge{
    int to;
    int last;
}a[maxn];
int tot;
int n,m,L;
int w[maxn];
int v[maxn];
int f[maxn];
int g[maxn];
int f1[maxn];
int f2[maxn];
int g1[maxn];
int g2[maxn];
int head[maxn];
inline int add(int x,int y){return (x+=y)>=MOD ? x-MOD : x;}
inline int sub(int x,int y){return (x-=y)<  0  ? x+MOD : x;}
inline void HA(int x,int y){a[++tot]=(Edge){y,head[x]};head[x]=tot;}
#define y a[i].to
inline void Dfs(int x){
    f1[x]=f[w[x]-1],f2[x]=f[v[x]-1];
    f[v[x]]=add(f[v[x]],f[v[x]-1]);
    int temp1=g[w[x]+1],temp2=g[v[x]+1];
    for(int i=head[x];i;i=a[i].last)Dfs(a[i].to);
    f[v[x]]=sub(f[v[x]],f[v[x]-1]);
    g1[x]=sub(g[w[x]+1],w[x]<L ? temp1 : 0);
    g2[x]=sub(g[v[x]+1],v[x]<L ? temp2 : 0);
    g[w[x]]=add(g[w[x]],g1[x]);
}
#undef y
char s[1<<25],*sS=s;
#define getchar() (*sS++)
inline void I(int &x){
    register int ch;
    while(ch=getchar(),ch<'/');x=ch-'0';
    while(ch=getchar(),ch>'/')x=x*10+ch-'0';
}
int main(){
//  freopen("in","r",stdin);
  freopen("B.in", "r", stdin);
  freopen("B.ans", "w", stdout);
    fread(s,1,1<<25,stdin),I(n),I(m),I(L);
    for(int i=2,x;i<=n;++i)I(x),HA(x,i);
    for(int i=1;i<=n;++i)I(w[i]);
    int ans=0,T=0;
    while(m>0){
        int K=std::min(n,m);m-=K;
        for(int i=1;i<=K;++i)I(v[i]);
        for(int i=K+1;i<=n;++i)v[i]=w[i];
        memset(f,0,(L+1)<<2);
        memset(g,0,(L+1)<<2);
        f[0]=g[L+1]=1,Dfs(1);
        //int now=g[1];
        //for(int i=1;i<=K;++i){
        //    now=sub(now,f1[i]*1ll*g1[i]%MOD);
        //    now=add(now,f2[i]*1ll*g2[i]%MOD);
        //    ans=add(ans,now*1ll*(++T)%MOD);
        //    w[i]=v[i];
        //}
    }printf("%d\n",ans);
    return 0;
}
