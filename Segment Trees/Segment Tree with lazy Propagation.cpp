template<typename T>
class Lazyseg {
    public:
    T left, right;
    T sum, lazy;
    Lazyseg *lChild, *rChild;
    Lazyseg(T l, T r):left(l), right(r), lazy(0), sum(0){
        if(left != right){
            T mid = (left+ right)/2;
            lChild = new Lazyseg(left, mid);
            rChild = new Lazyseg(mid+1, right);
            recal();
        }
    }
    
    void recal(){
        if(left == right) return;
        sum = lChild->sum + rChild->sum;
    }
    
    void prop(){
        if(lazy == 0) return;
        if(left == right) {
            sum += lazy;
            lazy = 0;
        } else {
            sum += lazy*(right-left+1);
            lChild->lazy += lazy;
            rChild->lazy += lazy;
            lazy = 0;
        }
    }
    
    void rangeUpdate(lli l, lli r, lli val){
        prop();
        if(l>right || r <left) return;
        if(l<=left && r >= right){
            lazy += val;
            prop();
        } else {
            lChild->rangeUpdate(l, r, val);
            rChild->rangeUpdate(l, r, val);
            recal();
        }
    }
    
    T rangeQuery(lli l, lli r){
        prop();
        if(l > right || r < left) return 0;
        if(l <= left && r >= right){
            return sum;
        } else {
            return lChild->rangeQuery(l, r) + rChild->rangeQuery(l, r);
        }
    }
    ~Lazyseg(){
        if(left != right) {
            delete lChild;
            delete rChild;
        }
    }
};
