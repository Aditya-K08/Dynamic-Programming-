#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) x.begin(),x.end()
#define rep(i,st,n) for(int i=st;i<n;i++)
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr)

int INF = 1e18;

vector<int>dp,cnt,arr,pref;
int n,k;

inline int cost(int l,int r){
    return pref[r] - pref[l-1];
}

array<int,2> solve_dp(int lambda_val){
    dp[0]=0;
    cnt[0]=0;

    rep(i,1,n+1){
        dp[i]=INF;
        cnt[i]=0;
        for(int l=0;l<i;l++){
            int val = dp[l] + cost(l+1,i) + lambda_val;
            if(val < dp[i]){
                dp[i] = val;
                cnt[i] = cnt[l] + 1;
            }
        }
    }
    return {dp[n],cnt[n]};
}

void solve(){
    cin>>n>>k;
    arr.resize(n);
    for(auto &x:arr) cin>>x;

    pref.assign(n+1,0);
    rep(i,1,n+1){
        pref[i] = pref[i-1] + arr[i-1]*arr[i-1];
    }

    dp.resize(n+1);
    cnt.resize(n+1);

    int lo = -INF, hi = INF;

    while(lo < hi){
        int mid = lo + (hi - lo)/2;
        auto [cst,j] = solve_dp(mid);
        if(j > k) lo = mid + 1;
        else hi = mid;
    }

    auto [cst,j] = solve_dp(lo);
    cout << cst - lo*k << endl;
}

int32_t main(){
    fastio();
    solve();
    return 0;
}