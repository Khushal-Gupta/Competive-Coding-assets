#include <bits/stdc++.h>
using namespace std;
#define lli long long int


// Solution to - https://leetcode.com/discuss/interview-question/977904/Quality-of-chocolates


// Merge Sort Tree
// used for querying number of elements <= k in given range [l, r]
// Doesn't support update operations

template<typename T>
class Seg{
    public:
    T left, right;
    Seg *lchild, *rchild;
    vector<T> arr;
    
    void merge(){
        if(left != right){
            int lsize = lchild->arr.size();
            int rsize = rchild->arr.size();
            vector<T> &larr = lchild->arr;
            vector<T> &rarr = rchild->arr;
            int i = 0;
            int p1 = 0, p2 = 0;
            while(p1 < lsize && p2 < rsize){
                if(larr[p1] <= rarr[p2]){
                    arr[i] = larr[p1];
                    i++; p1++;
                } else {
                    arr[i] = rarr[p2];
                    i++; p2++;
                }
            }
            while(p1 < lsize){
                arr[i] = larr[p1];
                i++; p1++;
            }
            while(p2 < rsize){
                arr[i] = rarr[p2];
                i++; p2++;
            }
        }
    }
    
    void recal(){
        if(left == right){
            
        } else {
            merge();
        }
    }
    
    Seg(T l, T r, vector<T> &v): left(l), right(r){
        arr.assign(r-l+1, 0);
        if(l != r){
            T mid = (l+r)/2;
            lchild = new Seg<T>(l, mid, v);
            rchild = new Seg<T>(mid + 1,r, v);
            merge();
        } else {
            arr[0] = v[l];
        }
    }
    // Gives no of elements <= k
    T query(int l, int r, int k){
        if(l > right || r < left) return 0;
        else if(l <= left && r >= right){
            int cnt = lower_bound(arr.begin(), arr.end(), k+1) - arr.begin();
            return cnt;
        } else {
            return lchild->query(l, r, k) +  rchild->query(l, r, k);
        }
    }
};



void solve(){
    lli n, q;
    cin >> n;
    vector<lli> sweet(n), expiry(n);
    for(int i=0;  i<n; i++) cin >> sweet[i];
    for(int i=0;  i<n; i++) cin >> expiry[i];
    cin >> q;
    vector<lli> res(n);
    vector<vector<lli>> query(q);
    for(int i=0; i<q; i++){
        lli a, b;
        cin >> a >> b;
        query[i] = {i, a, b};
    }
    sort(query.begin(), query.end(), [](vector<lli> a, vector<lli> b){
        return a[1] > b[1];
    });
    vector<pair<lli, lli>> vp(n);
    for(int i=0; i<n; i++){
        vp[i] = {sweet[i], expiry[i]};
    }
    sort(vp.begin(), vp.end(), [](pair<lli,lli> a, pair<lli, lli> b){
        return a.first > b.first;
    });
    
    vector<lli> v(n);
    for(int i=0; i<n; i++){
        v[i] = vp[i].second;
    }
    Seg<lli> tree(0, n-1, v);
    int j = 0,k = 0;
    
    for(int i=0; i<q; i++){
        lli swt = query[i][1];
        lli exp = query[i][2];
        lli index = query[i][0];
        while(j < n && vp[j].first > swt){
            j++;
        }
        res[index] = j  - tree.query(0, j-1, exp);
    }
    
    for(lli x: res) cout << x << " ";
    cout << endl;
} 
/*
INPUT - 
5 
16 11 10 20 18
11 9 2 2 4
5
3 20
4 5
9 1
4 6
8 4

OUTPUT
0 2 5 2 2

*/


int main() {
    solve();
    return 0;
}