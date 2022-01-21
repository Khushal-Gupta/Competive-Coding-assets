#define lli long long int

const lli MOD = 1e9+7;

// Addition
lli add(lli a, lli b){
    a += b;
    while(a < 0) a+= MOD;
    a %= MOD;
    return a;
}


// Multiplication
lli mul(lli a, lli b){
	return (a*b)%MOD;
}

// Fast method to get a^b
lli binpower(lli a, lli b){
    lli z = 1;
    while(b){
        if(b & 1) z = mul(z,a);
        a = mul(a, a);
        b /=2;
    }
    return z;
}

// Modulo inverse of b
lli modinv(lli b){
    return binpower(b, MOD-2);
}

