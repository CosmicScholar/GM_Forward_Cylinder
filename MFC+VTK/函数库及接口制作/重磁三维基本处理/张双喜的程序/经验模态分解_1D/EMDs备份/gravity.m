%%%=======������ά�����쳣ͼ===============================================
%{
M=800;
D=500;
G=6.67;
 x=-2000:10:2000;
y=-2000:10:2000;
x1=2000:10:6000;
y1=2000:10:6000;
N=401;
g=zeros(N);
g1=zeros(N);
for i=1:N
for j=1:N
g(i,j)=G*M*D./(x(i).^2+y(j).^2+D^2).^1.5;
g1(i,j)=G*M*D./(x(i).^2+y(j).^2+D^2).^1.5;
end
end
x0=zeros(N);
y0=zeros(N);
for i=1:N
    x0(i,:)=x;
    y0(:,i)=y';
end
figure(1);
mesh(x0,y0,g);
figure(2)
mesh(g1);
%}
%=======���Ƶ��������쳣=========================================================

N=400;
D=80;%��Բ���������
d=25;%СԲ���������
R=30;%��Բ����İ뾶
r=15;%СԲ����İ뾶
X=2;%ʣ���ܶ�
z1=X*pi*(R.^2);%��λ���ȴ�Բ�����ʣ������
z2=X*pi*(r.^2);%��λ����СԲ�����ʣ������
G=6.67;%������������
x=zeros(0,2*N+1);
for i=1:(2*N+1)
   x(i)=i-1-N;
end
M=zeros(0,2*N+1);
F=zeros(0,2*N+1);
K=zeros(0,2*N+1);

for j=1:(2*N+1)
    g0=2*G*z2*d/((x(j)+300).^2+d.^2);%�����������α�ʾ
    g1=2*G*z1*D/((x(j)+200).^2+D.^2);
    g2=2*G*z2*d/((x(j)+150).^2+d.^2);
       g6=2*G*z2*d/((x(j)).^2+d.^2);
    g3=2*G*z2*d/((x(j)-150).^2+d.^2);
    g4=2*G*z1*D/((x(j)-200).^2+D.^2);
    g5=2*G*z2*d/((x(j)-300).^2+d.^2);
%     g7=2*G*z1*D/((x(j)-150).^2+D.^2);
%     g8=2*G*z1*D/((x(j)+150).^2+D.^2);
    M(j)=g0+g1+g2+g3+g4+g5+g6;  %���쳣
    F(j)=g0+g2+g3+g5+g6;    %�ֲ��쳣
    K(j)=g1+g4;        %�����쳣
  
end
curve=plot(x,M,'r',x,F,'g',x,K,'k-');
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
title('ģ�������쳣');
%legend('ģ�͵����쳣','ģ�;ֲ��쳣');
%set(lsline,'LineWidth',10);
 set(curve(1),'linewidth',3);%��������1�Ĵ�ϸ
 set(curve(2),'linewidth',1.5);%��������1�Ĵ�ϸ
 set(curve(3),'linewidth',1.5);%��������1�Ĵ�ϸ
 %legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
 %%%%=======ģ��EMD�ֽ�===================================================== 
 
%  q=zeros(0,2*N+1);
%  for i=1:(2*N+1)
%   q(i)=q(0)+M(i);
%  end
[imf,ort,nbits]=emd(M); 
figure;
imfsize=size(imf);
i=imfsize(1);
for j=1:i
    subplot(i/2+1,2,j);plot(x,imf(j,:));
    if(j<i) Ylabel(sprintf('IMF%d', j));
    else Ylabel('Res');
    end
end   
%}    
%================================���ܶȲ�Բ����ģ��============================== 
%{
N=1500;
D=600;%��Բ���������
%D1=1000;%�����Բ���������
d=150;%СԲ���������
%R1=80;%�����Բ����İ뾶
R=30;%��Բ����İ뾶
r=15;%СԲ����İ뾶
X=1000;%ʣ���ܶ�
z1=X*pi*(R.^2);%��λ���ȴ�Բ�����ʣ������
z2=X*pi*(r.^2);%��λ����СԲ�����ʣ������
%z3=X*pi*(R1.^2);%��λ���ȸ����Բ�����ʣ������
G=6.667*power(10,-11);%������������
x=zeros(1,2*N);
for i=1:(2*N)
   x(i)=i-1-N;
end
M=zeros(1,2*N);
F=zeros(1,2*N);
K1=zeros(1,2*N);
%Q=zeros(1,2*N);
for j=1:(2*N)
    g0=2*G*z2*r/((x(j)+1200).^2+d.^2);%�����������α�ʾ
    g1=2*G*z1*R/((x(j)+800).^2+D.^2);
    g2=2*G*z2*r/((x(j)+500).^2+d.^2);
    g3=2*G*z2*r/((x(j)-500).^2+d.^2);
    g4=2*G*z1*R/((x(j)-800).^2+D.^2);
    g5=2*G*z2*r/((x(j)-1200).^2+d.^2);
   %g6=2*G*z3*R1/((x(j)).^2+D1.^2);
    M(j)=g0+g1+g2+g3+g4+g5;  %���쳣
    F(j)=g0+g2+g3+g5;%�ֲ��쳣
    K1(j)=g1+g4;%�����쳣
    %Q(j)=g6;
end
figure
curve=plot(x,M*power(10,6),'r',x,F*power(10,6),'g',x,K1*power(10,6),'k');
%curve=plot(x,M,'r',x,F,'g',x,K,'k',x,Q,'c');
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
title('ģ�������쳣');
%legend('ģ�͵����쳣','ģ�;ֲ��쳣');
%set(lsline,'LineWidth',10);
set(curve(1),'linewidth',3);%��������1�Ĵ�ϸ
set(curve(2),'linewidth',1.5);%��������1�Ĵ�ϸ
set(curve(3),'linewidth',1.5);%��������1�Ĵ�ϸ
%set(curve(4),'linewidth',1.5);%��������1�Ĵ�ϸ
 %legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
%legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
% rdxn=zeros(1,2*N);%��ȡ������
% for i=1:(2*N)
%     rdxn(i)=M(i);
% end
[imf,ort,nbits]=emd(M);
%IMF������================================================================
figure;
imfsize=size(imf);
i=imfsize(1);

for j=1:i
    
    subplot(i,1,j);curve=plot(x,imf(j,:)*power(10,6));set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
    if(j<i) Ylabel(sprintf('IMF%d', j));
    else Ylabel('Res');
    end
end

%��IMF�����ع����۲��ع����========================
% sum=0;
% for j=1:i
%    sum= sum+imf(j,:);
% end
% figure
% diffence=sum-M;
% plot(x,diffence);title('�����ع����');
% ylabel('�����ع����ֵ  ��g/g.u');xlabel('����ֵ  X/m');   
%figure
%===================================����|Ck|��|g|�ķ�ֵ======================================================
MAX=M(find(diff(sign(diff(M)))==-2)+1)
%�󼫴�ֵ
MIN=M(find(diff(sign(diff(M)))==2)+1)
%��Сֵ
DOC=min(MIN);%��ȡ��Сֵ
%�Ƚ������߽�ֵ����С�Ĵ�С
if(M(1)<DOC)
    DOC=M(1);
end
if(M(3000)<DOC)
    DOC=M(3000)
end
g=max(MAX)-DOC
%g=max(MAX)-min(MIN)
%%%%%==========�����쳣�ķ���ֵ======================
rexdn=zeros(1,3000);
rexdn=imf(1,:);
MAX=rexdn(find(diff(sign(diff(rexdn)))==-2)+1)
%�󼫴�ֵ
MIN=rexdn(find(diff(sign(diff(rexdn)))==2)+1)
%��Сֵ
doc=min(MIN);%��ȡ��Сֵ
%�Ƚ������߽�ֵ����С�Ĵ�С
if(rexdn(1)<doc)
    doc=rexdn(1);
end
if(rexdn(3000)<doc)
    doc=rexdn(3000)
end

Ck=max(MAX)-doc
%Ck=max(MAX)-min(MIN)
%%%%%==========IMF�����ķ���ֵ===============
figure
d=150;%����ģ�ͣ��ɸ��ݶ��������׼���Ҫ�����쳣������������֪
%p=3*x^.2/(x.^2+d^.2);
%p=3*power(x,2)/(power(x,2)+power(d,2));%����ģ��ϵ��
p=2*power(x,2)/(power(x,2)+power(d,2));%Բ����ģ��ϵ��
t=Ck/g;
K=1.5/p;%ˮƽ����ĵ��ӣ�ȡϵ��1~2֮�������
greg=imf(1,:)+K*t*imf(3,:);
subplot(211)
plot(x,F*power(10,6),'k',x,greg*power(10,6),'r-');
%axis([-1500,1500,1,10]);
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
legend('ģ�����۾ֲ��쳣','EMD�ֽ��ع��ֲ��쳣');
subplot(212)
diffence=F-greg;
plot(x,diffence*power(10,6));
title('�ع����');xlabel('����ֵ X/m');ylabel('���ֵ ��g/g.u ');

figure
subplot(211)
en=imf(1,:)+imf(2,:)+imf(3,:)-greg;%�ع������쳣
plot(x,K1*power(10,6),'k',x,en*power(10,6),'m');
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
%axis([-1500,1500,1,6]);
legend('ģ�����������쳣','EMD�ֽ��ع������쳣');
subplot(212)
Diffence=K1-en;
plot(x,Diffence*power(10,6));
title('�ع����');xlabel('����ֵ X/m');ylabel('���ֵ ��g/g.u ');
figure
subplot(211)
curve=plot(x,greg*power(10,6));title('EMD�ֽ��ع��ֲ������쳣');
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
subplot(212)
curve=plot(x,en*power(10,6));title('EMD�ֽ��ع����������쳣');
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');

%==========�������������========================================
figure
fs=1;%����Ƶ��
N=3000; n=0:N-1; q=n*1/N;
%yy=greg;%�ֲ������쳣
%yy=en;%���������쳣
yy=M;%���������쳣
y=fft(yy,N);
R=real(y);%ʵ��
I=imag(y);%�鲿
E=power(R,2)+power(I,2);
Xn=log(E);
curve=plot(q,Xn,'b');axis([0,0.05,-50,-15]);
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
title('������������ף�Radial logarithmic power spectrum��');
ylabel('lnE(��)');xlabel('��');
%=======================================================================

%}
%====================�����ܶȲ�����ģ��===================================
%{
N=2000;
D=500;%�����������
%D1=1000;%�����Բ���������
d=50;%С���������  ��λm
%R1=80;%�����Բ����İ뾶
R=50;%������İ뾶
r=35;%С����İ뾶
X=1000;%����ʣ���ܶ� ��λg/cm3
X0=4000;%С��ʣ���ܶ�   ��λg/cm3
MM=(4/3)*pi*power(R,3)*X;%�������ʣ������ ��λΪkg
mm=(4/3)*pi*power(r,3)*X0;%С�����ʣ������  ��λΪkg
% z1=X*pi*(R.^2);%��λ���ȴ�Բ�����ʣ������
% z2=X*pi*(r.^2);%��λ����СԲ�����ʣ������
%z3=X*pi*(R1.^2);%��λ���ȸ����Բ�����ʣ������
G=6.667*power(10,-11);%������������
X1=-1000;%����ʣ���ܶ�
X10=-4000;%С��ʣ���ܶ�  ��λg/cm3
MM1=(4/3)*pi*power(R,3)*X1;%�������ʣ������
mm1=(4/3)*pi*power(r,3)*X10;%С�����ʣ������
x=zeros(1,2*N);
for i=1:(2*N)
   x(i)=i-1-N;
end
M=zeros(1,2*N);
F=zeros(1,2*N);
K1=zeros(1,2*N);
%Q=zeros(1,2*N);
for j=1:(2*N)
    g0=G*mm*d/(((x(j)+1200).^2+d.^2)^.3/2);
    g1=G*MM*D/(((x(j)+800).^2+D.^2)^.3/2);
    g2=G*mm*d/(((x(j)+400).^2+d.^2)^.3/2);
    
%     g0=2*G*z2*r/((x(j)+1200).^2+d.^2);%�����������α�ʾ
%     g1=2*G*z1*R/((x(j)+800).^2+D.^2);
%     g2=2*G*z2*r/((x(j)+500).^2+d.^2);
    %%%=================================================
           
    %%%=================================================
     g3=G*mm1*d/(((x(j)-400).^2+d.^2)^.3/2);
     g4=G*MM1*D/(((x(j)-800).^2+D.^2)^.3/2);
     g5=G*mm1*d/(((x(j)-1200).^2+d.^2)^.3/2);
%     g3=2*G*z2*r/((x(j)-500).^2+d.^2);
%     g4=2*G*z1*R/((x(j)-800).^2+D.^2);
%     g5=2*G*z2*r/((x(j)-1200).^2+d.^2);
   %g6=2*G*z3*R1/((x(j)).^2+D1.^2);
    M(j)=g0+g1+g2+g3+g4+g5;  %���쳣
    F(j)=g0+g2+g3+g5;%�ֲ��쳣
    K1(j)=g1+g4;%�����쳣
    %Q(j)=g6;
end
figure
curve=plot(x,M,'r',x,F,'g',x,K1,'k');
%curve=plot(x,F,'r');
%curve=plot(x,M,'r',x,F,'g',x,K,'k',x,Q,'c');
ylabel('����ֵ��g  m/s2');xlabel('����ֵ  X/m');
title('ģ�������쳣');
legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�;ֲ��쳣');
%set(lsline,'LineWidth',10);
set(curve(1),'linewidth',3);%��������1�Ĵ�ϸ
%set(curve(2),'linewidth',1.5);%��������1�Ĵ�ϸ
%set(curve(3),'linewidth',1.5);%��������1�Ĵ�ϸ
%set(curve(4),'linewidth',1.5);%��������1�Ĵ�ϸ
 %legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
%legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
% rdxn=zeros(1,2*N);%��ȡ������
% for i=1:(2*N)
%     rdxn(i)=M(i);
% end

[imf,ort,nbits]=emd(M);
%IMF������================================================================
figure;
imfsize=size(imf);
i=imfsize(1);

for j=1:i
    
    subplot(i,1,j);curve=plot(x,imf(j,:));set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
    if(j<i) Ylabel(sprintf('IMF%d', j));
    else Ylabel('Res');
    end
end

%��IMF�����ع����۲��ع����========================
% sum=0;
% for j=1:i
%    sum= sum+imf(j,:);
% end
% figure
% diffence=sum-M;
% plot(x,diffence);title('�����ع����');
% ylabel('�����ع����ֵ  ��g/g.u');xlabel('����ֵ  X/m');   
%figure
%===================================����|Ck|��|g|�ķ�ֵ======================================================

MAX=M(find(diff(sign(diff(M)))==-2)+1)
%�󼫴�ֵ
MIN=M(find(diff(sign(diff(M)))==2)+1)
%��Сֵ
DOC=min(MIN);%��ȡ��Сֵ
EXCEL=max(MAX);%��ȡ���ֵ
if(M(1)>EXCEL)
    EXCEL=M(1);
end
if(M(4000)>EXCEL)
    EXCEL=M(4000)
end
%�Ƚ������߽�ֵ����Сֵ�Ĵ�С
if(M(1)<DOC)
    DOC=M(1);
end
if(M(4000)<DOC)
    DOC=M(4000)
end
%g=EXCEL-DOC
g=max(MAX)-min(MIN)
%��ʽΪ����ֵΪ���ֵ����СֵΪ��Сֵ�����
%%%%%==========�����쳣�ķ���ֵ======================
rexdn=zeros(1,4000);
rexdn=imf(1,:);
MAX=rexdn(find(diff(sign(diff(rexdn)))==-2)+1)
%�󼫴�ֵ
MIN=rexdn(find(diff(sign(diff(rexdn)))==2)+1)
%��Сֵ
doc=min(MIN);%��ȡ��Сֵ
excel=max(MAX);%��ȡ���ֵ
if(rexdn(1)>excel)
    excel=rexdn(1);
end
if(M(4000)>excel)
    excel=rexdn(4000)
end
%�Ƚ������߽�ֵ����С�Ĵ�С
if(rexdn(1)<doc)
    doc=rexdn(1);
end
if(rexdn(4000)<doc)
    doc=rexdn(4000)
end

%Ck=excel-doc
Ck=max(MAX)-min(MIN)
%��ʽΪ����ֵΪ���ֵ����СֵΪ��Сֵ�����
%%%%%==========IMF�����ķ���ֵ===============
figure
d=50;%����ģ�ͣ��ɸ��ݶ��������׼���Ҫ�����쳣������������֪
%p=3*x^.2/(x.^2+d^.2);
p=3*power(x,2)/(power(x,2)+power(d,2));%����ģ��ϵ��
%p=2*power(x,2)/(power(x,2)+power(d,2));%Բ����ģ��ϵ��
t=Ck/g;
K=4/p;%ˮƽ����ĵ��ӣ�ȡϵ��1~2֮�������
greg=imf(1,:)+K*t*imf(2,:);
subplot(211)
plot(x,F,'k',x,greg,'r-');
%axis([-1500,1500,1,10]);
ylabel('����ֵ��g  m/s2');xlabel('����ֵ  X/m');
legend('ģ�����۾ֲ��쳣','EMD�ֽ��ع��ֲ��쳣');
subplot(212)
diffence=F-greg;
plot(x,diffence);
title('�ع����');xlabel('����ֵ X/m');ylabel('���ֵ ��g/mGal ');

figure
subplot(211)
%en=imf(1,:)+imf(2,:)+imf(3,:)-greg;%�ع������쳣
en=M-greg;
plot(x,K1,'k',x,en,'m');
ylabel('����ֵ��g  m/s2');xlabel('����ֵ  X/m');
%axis([-1500,1500,1,6]);
legend('ģ�����������쳣','EMD�ֽ��ع������쳣');
subplot(212)
Diffence=K1-en;
plot(x,Diffence);
title('�ع����');xlabel('����ֵ X/m');ylabel('���ֵ��g  m/s2 ');
figure
subplot(211)
curve=plot(x,greg);title('EMD�ֽ��ع��ֲ������쳣');
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
ylabel('����ֵ��g  m/s2');xlabel('����ֵ  X/m');
subplot(212)
curve=plot(x,en);title('EMD�ֽ��ع����������쳣');
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
ylabel('����ֵ��g  m/s2');xlabel('����ֵ  X/m');


%==========�������������========================================
figure
fs=1;%����Ƶ��
N=4000; n=0:N-1; q=n*1/N;
%yy=greg;%�ֲ������쳣
%yy=en;%���������쳣
yy=M;%���������쳣
y=fft(yy,N);
R=real(y);%ʵ��
I=imag(y);%�鲿
E=power(R,2)+power(I,2);
Xn=log(E);
curve=plot(q,Xn,'b');axis([0,0.05,-10,20]);
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
title('������������ף�Radial logarithmic power spectrum��');
ylabel('lnE(��)');xlabel('��');
%=======================================================================
%}

% for i=1:100
%     for j=1:100
%             E=power(R(i)(j),2)+power(I(i)(j),2);
%     end
% end
% E=power(R,2)+power(I,2)
%imshow(abs(y),[-1 5],'notruesize');
%

% Xn=log(E);
% curve=plot(Xn,'b');axis([0,0.05,-10,20]);
% set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
% title('������������ף�Radial logarithmic power spectrum��');
% ylabel('lnE(��)');xlabel('��');
%============================Բ���������==============================================================
%{
N=1500;
D=600;%��Բ���������
%D1=1000;%�����Բ���������
d=150;%СԲ���������
%R1=80;%�����Բ����İ뾶
R=30;%��Բ����İ뾶
r=15;%СԲ����İ뾶
X=1000;%ʣ���ܶ�
z1=X*pi*(R.^2);%��λ���ȴ�Բ�����ʣ������
z2=X*pi*(r.^2);%��λ����СԲ�����ʣ������
%z3=X*pi*(R1.^2);%��λ���ȸ����Բ�����ʣ������
G=6.667*power(10,-11);%������������
%==============================================================

d0=50;%С���������
r0=35;%С����İ뾶
X0=4000;%С��ʣ���ܶ�   ��λkg/m3
mm0=(4/3)*pi*power(r,3)*X0;%С�����ʣ������  ��λΪkg
%g2=G*mm0*d0/(((x(j)+400).^2+d0.^2)^.3/2);

%================================================================
x=zeros(1,2*N);
for i=1:(2*N)
   x(i)=i-1-N;
end
M=zeros(1,2*N);
F=zeros(1,2*N);
K1=zeros(1,2*N);
%Q=zeros(1,2*N);
for j=1:(2*N)
    g0=2*G*z2*r/((x(j)+1200).^2+d.^2);%�����������α�ʾ
    g1=2*G*z1*R/((x(j)+800).^2+D.^2);
    g2=2*G*z2*r/((x(j)+500).^2+d.^2);
    %g3=2*G*z2*r/((x(j)-500).^2+d.^2);
    %g3=G*mm0*d0/(((x(j)-500).^2+d0.^2)^.3/2);
    g3
    g4=2*G*z1*R/((x(j)-800).^2+D.^2);
    %g5=2*G*z2*r/((x(j)-1200).^2+d.^2);
    %g5=G*mm0*d0/(((x(j)-1200).^2+d0.^2)^.3/2);
   %g6=2*G*z3*R1/((x(j)).^2+D1.^2);
    M(j)=g0+g1+g2+g3+g4+g5;  %���쳣
    F(j)=g0+g2+g3+g5;%�ֲ��쳣
    K1(j)=g1+g4;%�����쳣
    %Q(j)=g6;
end
figure
curve=plot(x,M*power(10,6),'r',x,F*power(10,6),'g',x,K1*power(10,6),'k');
%curve=plot(x,M,'r',x,F,'g',x,K,'k',x,Q,'c');
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
title('ģ�������쳣');
%legend('ģ�͵����쳣','ģ�;ֲ��쳣');
%set(lsline,'LineWidth',10);
set(curve(1),'linewidth',3);%��������1�Ĵ�ϸ
set(curve(2),'linewidth',1.5);%��������1�Ĵ�ϸ
set(curve(3),'linewidth',1.5);%��������1�Ĵ�ϸ
%set(curve(4),'linewidth',1.5);%��������1�Ĵ�ϸ
 %legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
%legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
% rdxn=zeros(1,2*N);%��ȡ������
% for i=1:(2*N)
%     rdxn(i)=M(i);
% end
[imf,ort,nbits]=emd(M);
%IMF������================================================================
figure;
imfsize=size(imf);
i=imfsize(1);

for j=1:i
    
    subplot(i,1,j);curve=plot(x,imf(j,:)*power(10,6));set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
    if(j<i) Ylabel(sprintf('IMF%d', j));
    else Ylabel('Res');
    end
end

%��IMF�����ع����۲��ع����========================
% sum=0;
% for j=1:i
%    sum= sum+imf(j,:);
% end
% figure
% diffence=sum-M;
% plot(x,diffence);title('�����ع����');
% ylabel('�����ع����ֵ  ��g/g.u');xlabel('����ֵ  X/m');   
%figure
%===================================����|Ck|��|g|�ķ�ֵ======================================================
MAX=M(find(diff(sign(diff(M)))==-2)+1)
%�󼫴�ֵ
MIN=M(find(diff(sign(diff(M)))==2)+1)
%��Сֵ
DOC=min(MIN);%��ȡ��Сֵ
%�Ƚ������߽�ֵ����С�Ĵ�С
if(M(1)<DOC)
    DOC=M(1);
end
if(M(3000)<DOC)
    DOC=M(3000)
end
g=max(MAX)-DOC
%g=max(MAX)-min(MIN)
%%%%%==========�����쳣�ķ���ֵ======================
rexdn=zeros(1,3000);
rexdn=imf(1,:);
MAX=rexdn(find(diff(sign(diff(rexdn)))==-2)+1)
%�󼫴�ֵ
MIN=rexdn(find(diff(sign(diff(rexdn)))==2)+1)
%��Сֵ
doc=min(MIN);%��ȡ��Сֵ
%�Ƚ������߽�ֵ����С�Ĵ�С
if(rexdn(1)<doc)
    doc=rexdn(1);
end
if(rexdn(3000)<doc)
    doc=rexdn(3000)
end

Ck=max(MAX)-doc
%Ck=max(MAX)-min(MIN)
%%%%%==========IMF�����ķ���ֵ===============
figure
d=150;%����ģ�ͣ��ɸ��ݶ��������׼���Ҫ�����쳣������������֪
%p=3*x^.2/(x.^2+d^.2);
%p=3*power(x,2)/(power(x,2)+power(d,2));%����ģ��ϵ��
p=2*power(x,2)/(power(x,2)+power(d,2));%Բ����ģ��ϵ��
t=Ck/g;
K=1.5/p;%ˮƽ����ĵ��ӣ�ȡϵ��1~2֮�������
greg=imf(1,:)+K*t*imf(3,:);
subplot(211)
plot(x,F*power(10,6),'k',x,greg*power(10,6),'r-');
%axis([-1500,1500,1,10]);
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
legend('ģ�����۾ֲ��쳣','EMD�ֽ��ع��ֲ��쳣');
subplot(212)
diffence=F-greg;
plot(x,diffence*power(10,6));
title('�ع����');xlabel('����ֵ X/m');ylabel('���ֵ ��g/g.u ');

figure
subplot(211)
en=imf(1,:)+imf(2,:)+imf(3,:)-greg;%�ع������쳣
plot(x,K1*power(10,6),'k',x,en*power(10,6),'m');
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
%axis([-1500,1500,1,6]);
legend('ģ�����������쳣','EMD�ֽ��ع������쳣');
subplot(212)
Diffence=K1-en;
plot(x,Diffence*power(10,6));
title('�ع����');xlabel('����ֵ X/m');ylabel('���ֵ ��g/g.u ');
figure
subplot(211)
curve=plot(x,greg*power(10,6));title('EMD�ֽ��ع��ֲ������쳣');
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
subplot(212)
curve=plot(x,en*power(10,6));title('EMD�ֽ��ع����������쳣');
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');

%==========�������������========================================
figure
fs=1;%����Ƶ��
N=3000; n=0:N-1; q=n*1/N;
%yy=greg;%�ֲ������쳣
%yy=en;%���������쳣
yy=M;%���������쳣
y=fft(yy,N);
R=real(y);%ʵ��
I=imag(y);%�鲿
E=power(R,2)+power(I,2);
Xn=log(E);
curve=plot(q,Xn,'b');axis([0,0.05,-50,-15]);
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
title('������������ף�Radial logarithmic power spectrum��');
ylabel('lnE(��)');xlabel('��');
%}
%=========һά�������������==============
data=load('modle1Za.dat');
ts=data(:,1);%��ȡ��һ������
rdxn=data(:,2);
fs=1.0/10;%����Ƶ��
N=length(ts); n=0:N-1; q=n*fs/N;
%yy=greg;%�ֲ������쳣
%yy=en;%���������쳣
yy=rdxn;%���������쳣
y=fft(yy,N);
R=real(y);%ʵ��
I=imag(y);%�鲿
E=power(R,2)+power(I,2);
Xn=log(E);
figure
curve=plot(q,Xn,'b');axis([0,fs/2,4,24]);
set(curve(1),'linewidth',1.5);%��������1�Ĵ�ϸ
title('������������ף�Radial logarithmic power spectrum��');
ylabel('lnE(��)');xlabel('��');

%
%==========EMD���ڶ�ά�����쳣�ķ���======================================
%{
N=1500;
D=600;%��Բ���������
%D1=1000;%�����Բ���������
d=150;%СԲ���������
%R1=80;%�����Բ����İ뾶
R=30;%��Բ����İ뾶
r=15;%СԲ����İ뾶
X=1;%ʣ���ܶ�
z1=X*pi*(R.^2);%��λ���ȴ�Բ�����ʣ������
z2=X*pi*(r.^2);%��λ����СԲ�����ʣ������
%z3=X*pi*(R1.^2);%��λ���ȸ����Բ�����ʣ������
G=6.67;%������������
x=zeros(1,2*N);
for i=1:(2*N)
   x(i)=i-1-N;
end
M=zeros(1,2*N);
F=zeros(1,2*N);
K=zeros(1,2*N);
%Q=zeros(1,2*N);
for j=1:(2*N)
    g0=2*G*z2*r/((x(j)+1200).^2+d.^2);%�����������α�ʾ
    g1=2*G*z1*R/((x(j)+800).^2+D.^2);
    g2=2*G*z2*r/((x(j)+500).^2+d.^2);
    
    g3=2*G*z2*r/((x(j)-500).^2+d.^2);
    g4=2*G*z1*R/((x(j)-800).^2+D.^2);
    g5=2*G*z2*r/((x(j)-1200).^2+d.^2);
   %g6=2*G*z3*R1/((x(j)).^2+D1.^2);
    M(j)=g0+g1+g2+g3+g4+g5;  %���쳣
    F(j)=g0+g2+g3+g5;
    K(j)=g1+g4;
    %Q(j)=g6;
end
figure
curve=plot(x,M,'r',x,F,'g',x,K,'k');
%curve=plot(x,M,'r',x,F,'g',x,K,'k',x,Q,'c');
ylabel('����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
title('ģ�������쳣');
%legend('ģ�͵����쳣','ģ�;ֲ��쳣');
%set(lsline,'LineWidth',10);
set(curve(1),'linewidth',3);%��������1�Ĵ�ϸ
set(curve(2),'linewidth',1.5);%��������1�Ĵ�ϸ
set(curve(3),'linewidth',1.5);%��������1�Ĵ�ϸ
%set(curve(4),'linewidth',1.5);%��������1�Ĵ�ϸ
 %legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
%legend('ģ�͵����쳣','ģ�;ֲ��쳣','ģ�������쳣');
% rdxn=zeros(1,2*N);%��ȡ������
% for i=1:(2*N)
%     rdxn(i)=M(i);
% end
[imf,ort,nbits]=emd(M);
%IMF������================================================================
figure;
imfsize=size(imf);
i=imfsize(1);
for j=1:i
    subplot(i,1,j);plot(x,imf(j,:));
    if(j<i) Ylabel(sprintf('IMF%d', j));
    else Ylabel('Res');
    end
end
%��IMF�����ع����۲��ع����========================
w=zeros(1,2*N);
w(1)=zeros(1,2*N);
for j=1:i
   w(j+1)= w(j)+imf(j,:)
end
diffence=w-M;
plot(x,diffence);title('�����ع����');
ylabel('�����ع����ֵ  ��g/g.u');xlabel('����ֵ  X/m');
%}



































