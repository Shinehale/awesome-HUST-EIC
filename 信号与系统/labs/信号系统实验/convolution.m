clc;
clear all;

t= linspace(-1,1,500);
w= linspace(-50,50,1000);
width=1;
E=1;
f=tripuls(t,width,0);
g=sqrt(2*E/width)*rectpuls(t,width/2);

subplot(2,4,1);
plot(t,f,t,g,'r'),legend('f(x)', 'g(x)');

ctft1 = CTFT(500,1000,-1,1,-50,50,f);
subplot(2,4,2);
plot(ctft1(1,:),ctft1(2,:),'r'),legend('F(x)');

ctft2= CTFT(500,1000,-1,1,-50,50,g);
G=ctft2(2,:);
subplot(2,4,3);
plot(ctft2(1,:),G),legend('G(x)');

Gg = G.*G;
subplot(2,4,4);
plot(ctft2(1,:),Gg),legend('Gg(x)');


gg = (4/999).*conv(g,g);
t_conv=linspace(-2,2,999);
subplot(2,4,6);
plot(t_conv,gg,'r',t,f);  legend('gg(x)','f(x)');


ctft3 =  CTFT(999,1000,-2,2,-50,50,gg);
subplot(2,4,5);
plot(ctft3(1,:),ctft3(2,:)),legend('Fg(x)');

subplot(2,4,7);
plot(ctft3(1,:),ctft1(2,:),'r',ctft3(1,:),Gg,'g',ctft3(1,:),ctft3(2,:),'b'),legend('F(x)','Gg(x)','Fg(x)');


