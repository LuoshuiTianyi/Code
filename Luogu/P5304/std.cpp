#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100000+10;
const int maxm=500000+10;
const ll inf=9187201950435737471;    
int n,m,k,a[maxn],X[maxm],Y[maxm],W[maxm],col[2][maxn],head[maxn],tot;
ll dis[2][maxn],ans;bool vis[maxn],iscity[maxn];

struct Edge
{
    int to,next,val;
}e[maxm];

struct node
{
    ll dis;int id;
    node(ll _dis=0,int _id=0):dis(_dis),id(_id){}
};
inline bool operator < (const node &a,const node &b)
{
    return a.dis>b.dis;
}

inline int read()
{
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}

inline void addedge(int x,int y,int w)
{
    e[++tot].to=y;
    e[tot].val=w;
    e[tot].next=head[x];
    head[x]=tot;
}

inline void Dijkstra(ll *dis,int *col)
{
    for(int i=1;i<=n;i++) dis[i]=inf,vis[i]=0;
    priority_queue<node> pq;
    for(int i=1;i<=k;i++) dis[a[i]]=0,col[a[i]]=a[i],pq.push(node(0,a[i]));
    while(!pq.empty())
    {
        int u=pq.top().id;pq.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(dis[v]>dis[u]+e[i].val)
            {
                dis[v]=dis[u]+e[i].val;
                col[v]=col[u];
                pq.push(node(dis[v],v));
            }
        }
    }
}

inline void solve()
{
    n=read(),m=read(),k=read();
    int x,y,w;
    for(int i=1;i<=m;i++)
    {
        x=read(),y=read(),w=read();
        if(x!=y) addedge(x,y,w);
        X[i]=x;Y[i]=y;W[i]=w;
    }
    for(int i=1;i<=k;i++) a[i]=read(),iscity[a[i]]=1;
    Dijkstra(dis[0],col[0]);
    for(int i=1;i<=n;i++) head[i]=0;
    tot=0;
    for(int i=1;i<=m;i++)
        if(X[i]!=Y[i]) addedge(Y[i],X[i],W[i]);
    Dijkstra(dis[1],col[1]);
    ans=inf;
    for(int i=1;i<=m;i++)
    {
        x=X[i];y=Y[i];w=W[i];
        if(col[0][x]&&col[1][y]&&col[0][x]!=col[1][y]) ans=min(ans,dis[0][x]+dis[1][y]+w);
    }
    for (int i = 1; i <= n; i++) cout << dis[1][i] << " ";
    cout << endl;
    printf("%lld\n",ans);
    for(int i=1;i<=n;i++) head[i]=iscity[i]=0;
    tot=0;
}

int main()
{
    freopen("5304.in", "r", stdin);
    freopen("5304.ans", "w", stdout);
    int T=read();
    while(T--) solve();
    return 0;
}
