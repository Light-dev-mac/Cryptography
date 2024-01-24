// 高速指数演算法を用いたDiffie_Hellman鍵配送方式及び、ElGamal暗号のプログラム 

#include <stdio.h>
#include <math.h>

long exp_operation(long g,long exp,long p);
long Diffie_Hellman(long a,long b,long g,long p);
long ElGamal_enc(long p,long K,long M);
long ElGamal_dec(long g,long p,long K,long C);
long Euclid(long a,long n);

main(){
	long a;     // Alice側の秘密鍵
	long b;     // Bob側の秘密鍵
	long p,g;   // 公開する情報
	long M,C;   // 平文及び暗号文
	long K;     // 共通鍵
	long C1;    // 復号後の値

	// 各値の設定
	a=6;   // Aliceの秘密鍵 0<a<p
	b=4;   // Bobの秘密鍵 0<b<p
	p=32767;   // p<32768の大きな素数
	M=1456;   // 平文(メッセージ)

	// (Z/pZ)の生成元gを見つける
	g=2;
	while(exp_operation(g,(p-1)/2,p)==1){
		g++;
	}

	// Diffie_Hellman鍵配送方式を用いて共通鍵(K)を生成
	K=Diffie_Hellman(a,b,g,p);

	// ElGamal暗号と鍵Kを使って、平文Mを暗号文Cに暗号化する
	C=ElGamal_enc(p,K,M);

	// 暗号文Cと鍵Kを用いて、復号を行う
	C1=ElGamal_dec(g,p,K,C);

	// 結果の表示
	printf("平文  :%ld\n",M);
	printf("共通鍵:%ld\n",K);
	printf("暗号文:%ld\n",C);
	printf("復号  :%ld\n",C1);
}

// Diffie_Hellman鍵配送方式を用いて、共通鍵を生成
long Diffie_Hellman(long a,long b,long g,long p){
	long A,B;

	// 穴埋め箇所
	// 4ヶ所、高速指数演算法の関数を使って計算してください
	// また、Bob側の鍵とAlice側の鍵が同じであることを確認してください


	// Bob側 B=g^b mod p の計算
	B=exp_operation(g,b,p);  
	// Alice側 A=g^a mod p の計算
	A=exp_operation(g,a,p);  
	// Bob側 A^b=g^ab mod p の計算
	long Ab=exp_operation(A,b,p);  
	// Alice側 B^a=g^ab mod p の計算
	long Ba=exp_operation(B,a,p); 
	// Alice,Bobどちらかの鍵を返す (AliceとBobは同じ鍵を持っている筈なので、どちらでもよい)
	return Ab;
}


// 高速指数演算法  g^exp mod pを高速に計算する関数
long exp_operation(long g,long exp,long p){
	
	// 穴埋め箇所
	// 高速指数演算法のプログラムを書いてください
	if(exp==0)
	return 1;
	if(exp%2==0)
    return exp_operation(g * g% p, exp / 2, p);
  	else
    return g * exp_operation(g, exp - 1, p) % p;
}


// ElGamal暗号の暗号化
long ElGamal_enc(long p,long K,long M){
	
	// 穴埋め箇所
	// 暗号文を計算してください return文の1行のみで構いません
	// 暗号文を返す
	return exp_operation(K*M,1,p);
}

// ElGamal暗号の復号化
long ElGamal_dec(long g,long p,long K,long C){
	long K1;

	// Kの逆元K^(-1)を求める 授業プリントでは K=α^b となっている
	// K*K^(-1) mod p=1 となる K^(-1)を求める

	K1=Euclid(K,p);
	return((C*K1)%p);	
}

// 拡張Euclid互除法
long Euclid(long a,long n){
	long u1,u2;		// 拡張部分
	long r1,r2;		// Euclid 互除法
	long q,w;		// q は商（r2/r1の床関数）の保持。w は r_k, u_k の計算用一時変数

	r1=n; 
	r2=a;
	u1=0; 
	u2=1;

	while(r1>0){
		q=r2/r1;
		w=r2-q*r1;
		r2=r1;
		r1=w;
		w=u2-q*u1;
		u2=u1;
		u1=w;
	}
	return ((u2+n)%n);		// u2 が負数のこともあるので n を足して mod n しておく
}

/*実行結果
平文  :1456
共通鍵:512
暗号文:24598
復号  :1456
*/
