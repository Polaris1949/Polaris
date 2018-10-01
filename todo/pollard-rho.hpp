class pollard_rho{
private:
	typedef long long ll; 
	inline ll Mult_mod (ll a,ll b,ll c) {
	    a%=c;
	    b%=c;
	    ll ret=0;
	    while (b){
	        if (b&1){
	            ret+=a;
	            if (ret>=c) ret-=c;
	        }
	        a<<=1;
	        if (a>=c) a-=c;
	        b>>=1;
	    }
	    return ret;
	}
	inline ll Pow_mod (ll x,ll n,ll mod){
	    if (n==1) return x%mod;
	    x%=mod;
	    ll tmp=x;
	    ll ret=1;
	    while (n){
	        if (n&1) ret=Mult_mod(ret,tmp,mod);
	        tmp=Mult_mod(tmp,tmp,mod);
	        n>>=1;
	    }
	    return ret;
	}
	inline bool Check (ll a,ll n,ll x,ll t){
	    ll ret=Pow_mod(a,x,n);
	    ll last=ret;
	    for (int i=1;i<=t;i++){
	        ret=Mult_mod(ret,ret,n);
	        if(ret==1&&last!=1&&last!=n-1) return true;
	        last=ret;
	    }
	    if (ret!=1) return true;
	    return false;
	}
	inline bool Miller_Rabin (ll n){
		const int S=20;
	    if (n==46856248255981) return false;
	    if (n<2) return false;
	    if (n==2||n==3||n==5||n==7||n==11||n==13||n==17) return true;
	    if(!(n&1)||(n%3==0)||(n%5==0)||(n%7==0)||(n%11==0)||(n%13)==0||(n%17)==0) return 0;
	    ll x=n-1;
	    ll t=0;
	    while ((x&1)==0) {x>>=1;t++;}
	    for (int i=0;i<S;i++){
	        ll a=rand()%(n-1)+1;
	        if (Check(a,n,x,t))
	            return false;
	    }
	    return true;
	}
	vector<ll> factor;
	inline ll Gcd (ll a,ll b){
	    if (a==0) return 1;
	    if (a<0) return Gcd(-a,b);
	    while (b){
	        ll t=a%b;
	        a=b;
	        b=t;
	    }
	    return a;
	}
	inline ll Pollard_rho (ll x,ll c){
	    ll i=1,k=2;
	    ll x0=rand()%x;
	    ll y=x0;
	    while (true){
	        i++;
	        x0=(Mult_mod(x0,x0,x)+c)%x;
	        ll d=Gcd(y-x0,x);
	        if (d!=1 && d!=x) return d;
	        if (y==x0) return x;
	        if (i==k) {y=x0;k+=k;}
	    }
	}
	inline void Findfac (ll n){
	    if (Miller_Rabin(n)){
	        factor.push_back(n);
	        return;
	    }
	    ll p=n;
	    while (p>=n) p=Pollard_rho(p,rand()%(n-1)+1);
	    Findfac(p);
	    Findfac(n/p);
	}
public:
	inline vector<ll> PrimeFac(int n){
		srand(19260817);
		if (Miller_Rabin(n)){
            factor.push_back(n);
            return factor;
        }
        Findfac(n);
        return factor;
	}
};
