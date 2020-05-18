#include<bits/stdc++.h>
using namespace std;
#define maxn 1000010
#define ll long long
const int mod=1000000007;
 
char s[1<<25],*S=s;
#define getchar() (*S++)
 
template < typename tp >
inline void read ( tp & dig ) {
    char ch=getchar();int flag=0;dig=0;
    while(!isdigit(ch)){if(ch=='-')flag=1;ch=getchar();}
    while(isdigit(ch))dig=dig*10+ch-'0',ch=getchar();
    if(flag)dig=-dig;
}
  
int f[maxn],g[maxn],f1[maxn],f2[maxn],g1[maxn],g2[maxn],ans[maxn];
int lnum,fst[maxn<<1],nxt[maxn<<1],to[maxn<<1];
int n,m,L,cnt,a[maxn],b[maxn],fa[maxn];
  
inline int F(ll x){return x>=mod?x-mod:x;}
inline void add_edge(int u,int v){
    nxt[++lnum]=fst[u];fst[u]=lnum;to[lnum]=v;
}
 
inline void dfs(int u){
    f1[u]=f[a[u]-1];f2[u]=f[b[u]-1];
    f[b[u]]=F(f[b[u]]+f[b[u]-1]);
    int t1=g[a[u]+1],t2=g[b[u]+1];
    for(int i=fst[u];i;i=nxt[i])dfs(to[i]);
    f[b[u]]=F(f[b[u]]+mod-f[b[u]-1]);
    g1[u]=F(g[a[u]+1]-t1*(a[u]<L)+mod);
    g2[u]=F(g[b[u]+1]-t2*(b[u]<L)+mod);
    g[a[u]]=F(g[a[u]]+g1[u]);
}
 
int main()
{
  
#ifndef ONLINE_JUDGE
    freopen("tree.in","r",stdin);
    freopen("tree.ans","w",stdout);
#endif
  
    fread(s,1,1<<25,stdin);
    read(n);read(m);read(L);
    for(int i=2;i<=n;++i)
        read(fa[i]),add_edge(fa[i],i);
    for(int i=1;i<=n;++i)read(a[i]);
    while(m){
        int lim=min(n,m);m-=lim;
        for(int i=1;i<=lim;++i)read(b[i]);
        for(int i=lim+1;i<=n;++i)b[i]=a[i];
        for(int i=1;i<=L;++i)f[i]=g[i]=0;
        f[0]=g[L+1]=1;dfs(1);int now=g[1];
        for(int i=1;i<=lim;++i){
            now=F(now-1LL*f1[i]*g1[i]%mod+mod);
            now=F(now+1LL*f2[i]*g2[i]%mod);
            ans[++cnt]=now;a[i]=b[i];
        }
    }int res=0;
    for(int i=1;i<=cnt;++i)
        res=(1LL*i*ans[i]+res)%mod;
    printf("%d\n",res);
    return 0;
  
}
