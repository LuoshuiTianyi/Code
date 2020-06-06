#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;
const int N=500003;
int n,m;
map<pair<int,int>,int> id;
int cnt;
vector<double> p[N],tmp;
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
void ins(int x,int y)
{
	if(x==0&&y==0) return;
	int xx=x,yy=y;
	int d=gcd(abs(x),abs(y));
	if(d) x/=d,y/=d;
	if(!id.count(make_pair(x,y))) id[make_pair(x,y)]=++cnt;
	p[id[make_pair(x,y)]].push_back(sqrt(1.0*xx*xx+1.0*yy*yy));
}
double solve()
{
	for(int i=1;i<=cnt;i++)
		for(int j=0;j<p[i].size();j++)
			tmp.push_back(p[i][j]*(m-2*j-1));
	sort(tmp.begin(),tmp.end());
	reverse(tmp.begin(),tmp.end());
	double ans=0;
	for(int i=0;i<m;i++)
		ans+=tmp[i];
	return ans;
}
double calc(int s)
{
	double ans=0;
	for(int i=1;i<=cnt;i++)
	{
		if(i==s) continue;
		for(int j=0;j<p[i].size();j++)
			ans+=p[i][j]*(m-2*j-1);
	}
	int h=m/2;
	int lst=m-h-(n-p[s].size());
	for(int i=0;i<m/2;i++)
		ans+=p[s][i]*(m-2*i-1);
	for(int i=0;i<lst;i++)
		ans+=p[s][p[s].size()-1-i]*(m-2*h-2*(lst-i)+1);
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.ans", "w", stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		ins(x,y);
	}
	for(int i=1;i<=cnt;i++)
		sort(p[i].begin(),p[i].end()),reverse(p[i].begin(),p[i].end());
	double ans=solve();
	if(m<n)
	{
		for(int i=1;i<=cnt;i++)
			if(2*(n-p[i].size())<=m) ans=max(ans,calc(i));
	}
	printf("%.10f",ans);
	return 0;
}
