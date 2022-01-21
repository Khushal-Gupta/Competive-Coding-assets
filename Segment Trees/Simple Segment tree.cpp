template<typename T>
class SegTree {
    public:
    T left, right;     // left and right bounds
    T sum;
    SegTree *lChild, *rChild;  // pointer to ledt and right childrens
    
    SegTree(T left, T right, vector<T> &a): left(left), right(right), sum(0){  // if want to copy a value of an array
        if(left == right) {
            sum = a[left];    
        } else {
            T mid = (left + right)/2;
            lChild = new SegTree(left, mid, a);
            rChild = new SegTree(mid+1, right, a);
            sum = lChild->sum + rChild->sum;
        }
    }
    
    SegTree(T left, T right): left(left), right(right), sum(0){         // For creating 0 initialized array provided left and right bounds
        if(left != right){
            T mid = (left + right)/2;
            lChild = new SegTree(left, mid);
            rChild = new SegTree(mid+1, right);
        }
    }

	SegTree(T size): left(0), right(size-1), sum(0){     // If only size is given
        if(left != right){
            T mid = (left + right)/2;
            lChild = new SegTree(left, mid);
            rChild = new SegTree(mid+1, right);
        }
    }

    void update(T index, T val){
        if(left == right){
            sum = val;
            return;
        }
        if(index <= lChild->right){
            (*lChild).update(index, val);
        } else {
            (*rChild).update(index, val);
        }
        recal();
    }
    
    T rangeQuery(T lbound, T rbound){
        if(lbound > right || rbound < left) return 0;   // disjoint interval
        if(lbound <= left && rbound >= right) return sum;   // full cover
        return (*lChild).rangeQuery(lbound, rbound) + (*rChild).rangeQuery(lbound, rbound);   // partial cover;
    }
    
    void recal(){
        if(left == right) return;
        sum = lChild->sum + rChild->sum;
    }

    ~SegTree(){
        if(left != right) {
            delete lChild;
            delete rChild;
        }
    }
};
