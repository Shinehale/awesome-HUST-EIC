E=1; T1=1; w1=2*pi/T1;
K1=-10; K2=10;
F_k=K1:1:K2;
a_k=0:1:K2;
b_k=a_k;
N=1000; K=500;
t=linspace(-0.5,0.5,N);
w=linspace(-2*pi,2*pi,K);
f=E/2*square(2*pi*(t+T1/4));
subplot(3,3,1);
plot(t,f); title('original signal');
for k=1:1:(K2-K1+1)
    for n=1:1:N  
            exp_mat(k,n)=exp(-1j*(K1+k-1)*t(1,n)*w1);
    end
end
f_mat=transpose(f);
FS=1/N*transpose(exp_mat*f_mat);
subplot(3,3,2);
stem(F_k,FS); title('F(k)');
for p=1:1:((K2-K1)/2)
    a(1,1)=FS(1,(K2-K1+2)/2);
    a(1,p+1)=FS(1,(K2-K1+2)/2-p)+FS(1,(K2-K1+2)/2+p);
    b(1,1)=0;
    b(1,p+1)=1j*(FS(1,(K2-K1+2)/2+p)-FS(1,(K2-K1+2)/2-p));
end
subplot(3,3,3);
stem(a_k,a); title('a(k)');
subplot(3,3,4);
stem(b_k,b); title('b(k)');
for k=1:1:N
    for n=1:1:(K2/2+1)  
            i_exp_mat(k,n)=cos((n-1)*w1*t(1,k));
    end
end
i_f=i_exp_mat*transpose(a(1,1:(K2/2+1)));
subplot(3,3,5);
plot(t,i_f); title('recover');

