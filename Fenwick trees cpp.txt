template<typename T>
class Fenwick {
	// Use it like 0 indexed array
	// if you create Fenwick(n) it will have indices from 0 to n-1
    public:
    T n;
    vector<T> bit;
    Fenwick(T _n): n(_n){
        bit.assign(n+1, 0);
    }
    void update(T i, T val){
        for(i++; i <= n; i += i&(-i)) bit[i] += val;
    }
    T query(T i){
        T res = 0;
        for(i++; i > 0; i -= i&(-i)) res += bit[i];
        return res;
    }
};
