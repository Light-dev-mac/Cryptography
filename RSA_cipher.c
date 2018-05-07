// 参考用プログラムです。穴埋め箇所を埋めるなどして、プログラムを完成させてください。
// 学籍番号 14D8103006L  氏名 堀有耀
// 暗号理論 プログラム課題２
// RSA暗号と署名

#include <stdio.h>
#include <stdlib.h>
// 高速指数演算法  g^exp mod pを高速に計算する関数
/*long exp_operation(long g,long exp,long p){
  long two=1, ans=1;
 	 long div=exp, per=exp;

  	while(div!=0){

    	per=div%2;
    	div=div/2;

    	if(per==1) ans = (ans*two*g)%p;

    	two *= 2;
  	}

 	 return(ans);
}*/
long exp_operation(long x, long n, long m){
  if(n == 0)
    return 1;
  if(n % 2 == 0)
    return exp_operation(x * x % m, n / 2, m);
  else
    return x * exp_operation(x, n - 1, m) % m;
}
long Euclid(long a,long n){
long u0,u1,u2,v0,v1,v2,r0,r1,r2,q1;
r0=a;
r1=n;
u0=1;
u1=0;
v0=0;
v1=1;
while(r1>0){
  q1=r0/r1; //printf("%d\n",q1);
  r2=r0%r1; //printf("%d\n",r2);
  u2=u0-q1*u1; //printf("%d\n",u2);
  v2=v0-q1*v1; //printf("%d\n",v2);
  r0=r1; //printf("%d\n",r0);
  r1=r2; //printf("r1==%d\n",r1);
  u0=u1; //printf("%d\n",u0);
  u1=u2;//printf("%d\n",u1);
  v1=v2;//printf("%d\n",v1);
}
		if(u0<0){
      return(u0+n);
    }else{
      return u0;
    }
}
//RSA暗号化
long RSA_enc(long M, long e, long n){
  return exp_operation(M,e,n);
}
//RSAで復号化
long RSA_dec(long C, long d, long n){
  return exp_operation(C,d,n);
}

long CRT_dec(long C,long d,long p,long q){

  long x1=exp_operation(C,d,p);
  long x2=exp_operation(C,d,q);
  long invp=Euclid(p,q);
  long invq=Euclid(q,p);
  long x;
  x=(q*invq*x1+p*invp*x2)%(p*q);

  return(x);
}

//RSA署名
long RSA_sign(long M, long d, long n){



  return exp_operation(M,d,n);
}

//RSA検証
long RSA_ver(long S, long e, long n){



  return exp_operation(S,e,n);
}

int main(void){
  long p,q;  //大きな素数
  long M;    //平文
  long C1;   //RSA復号後の値
  long C2;   //CRT復号後の値
  long C;    //暗号後の値
  long n;    //p*q
  long Euler_n; // Φ(n)
  long e;    //公開鍵
  long d;    //eの逆元
  long S;    //署名文
  long s;    //検証後の値

  M=36;
  p=29;
  q=17;
  n=p*q;
  e=3;

  Euler_n=(p-1)*(q-1);
  printf("Euler_n==%d\n",Euler_n);
  d=Euclid(e,Euler_n);
  printf("d==%d\n",d );
  C=RSA_enc(M,e,n);
  C1=RSA_dec(C,d,n);
  C2=CRT_dec(C,d,p,q);
  S=RSA_sign(M,d,n);
  s=RSA_ver(S,e,n);

  printf("平文     :\t %ld\n", M);
  printf("公開鍵   :\t %ld\n", e);
  printf("秘密鍵   :\t %ld\n", d);
  printf("暗号化   :\t %ld\n", C);
  printf("RSA復号化:\t %ld\n", C1);
  printf("CRT復号化:\t %ld\n", C2);
  printf("署名文   :\t %ld\n", S);
  printf("検証     :\t %ld\n", s);


  return(0);
}
