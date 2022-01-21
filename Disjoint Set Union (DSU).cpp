template<typename T>
class DSU {
    public:
    T length;
    vector<T> par;
    DSU(T n): length(n) {
        // assign all nodes as -1. Negative par[i] denotes that it is parent of the set and its magnitude denote size of the set
        par.assign(length, -1);    
    }
    T getParent(T elem){
        T parent = elem;
        while(par[parent] >= 0){
            parent = par[parent];
        }
        // Path collapsing
        while(parent != elem){
            // To collapse the the size of chains
            // if parent of this element is other than itself update it
            T nextelem = par[elem];
            par[elem] = parent;
            elem = nextelem;
        }
        return parent;
    }
    
    void unionNodes(T a, T b){
        T parent_a = getParent(a);
        T parent_b = getParent(b);
        if(parent_a == parent_b) return;  // already in the same set, no need to update
        T size_par_a = getSetSize(a);
        T size_par_b = getSetSize(b);
        if(size_par_a >= size_par_b){
            par[parent_b] = parent_a; 
            par[parent_a] = - (size_par_a + size_par_b);
        } else {
            par[parent_a] = parent_b;
            par[parent_b] = - (size_par_a + size_par_b);
        }
    }
    
    T getSetSize(T elem){
        return abs(par[getParent(elem)]);
    }
};
