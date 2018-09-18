clear all
close all
clc

% t1=0:.001:2.5;
% t2=2.5:.001:5;
% t=0:.001:(5+.001);
% a=sin(20*pi*t1+0.5*sin(5*pi*t1));
% b=sin(10*pi*t2+.5*sin(5*pi*t2));
% c=0.5*cos(3*pi*t);
% x=[a(:,:) b(:,:)]+c;
%stop = [0.1,0.1,0.1];
%Ts=0.001;
%Fs=1/Ts;%����Ƶ��
%t=0:Ts:1;

% N=1024;t=linspace(0,1,N);
% signal=sin(2*pi*50*t)+sin(2*pi*10*t);
% x=signal';

N=512;t=linspace(0,1,N);
%N=1024;n=0:N-1;t=Ts*n;
x=sin(2*pi*50*t)+sin(2*pi*10*t);
x=x';
%}
%x1=6*sin(2*pi*100*t)+5*cos(2*pi*400*t)+10*sin(2*pi*1000*t);
%x1=(1+0.3*sin(2*pi*15*ts))*cos(2*pi*50*ts+0.5*sin(2*pi*15*ts))+sin(2*pi*150*ts);
%x1=cos(tan(pi*t));
%x=awgn(x1,40,'measured');%y = awgn(x,SNR,SIGPOWER);xΪ�źţ�SNRΪ����ȣ���SIGPOWERΪ��measured��
%�������ڼ�������֮ǰ�ⶨ�ź�ǿ��
% x=sin(2*pi*90*t)+sin(2*pi*30*t);
% x1=sin(2*pi*90*t)+sin(2*pi*30*t);
%x=sin(2*pi*30*t)+1*randn(1, length(t)); %����ȥ��
%{
y=zeros(1,length(t));
for i=1:500
    x(i)=2*sin(2*pi*240*t(i));
end
for i=501:1000
    x(i)=3*cos(2*pi*180*t(i));
end
%}
[imf,ort,nbits]=emd(x);
%ԭʼ�źŵĻ���==========================================================
figure;
plot(t,x);title('ģ���ź�');ylabel('��ֵ');xlabel('ʱ��  t/s');
%IMF������================================================================
figure;
imfsize=size(imf);
i=imfsize(1);
for j=1:i
    subplot(i/2+1,2,j);plot(t,imf(j,:));
    if(j<i) Ylabel(sprintf('IMF%d', j));
    else Ylabel('Res');
    end
end

%��IMF�������ĺϳ���ԭʼ�źŵıȽ�=========================================
figure;
 newrdxn=x;
 for k=1:i
    newrdxn=newrdxn-imf(k,:);
    subplot(i/2+1,2,k);plot(t,newrdxn);title(sprintf('IMF%d��ʣ���ź�', k));
    %k=k+1;
 end 
figure;
m=0;
for n=1:i
    m=m+imf(n,:);
end
%ʹ��ѭ���Ը���IMF�����������
m=m+newrdxn;%����ԭʼ�źţ�IMF��������ʣ���ź�
%m=imf(3,:)+imf(4,:)+imf(5,:)+imf(6,:)+newrdxn;%lk����ԭʼ�źţ���ʵ��ȥ��
subplot(3,1,1);plot(t,x);%plot(t,x,'b',t,m,'r');
title('ԭʼ�ź�');%legend('ԭʼ�ź�','�ϳɺ���ź�');
subplot(3,1,2);plot(t,m);title('�ϳɺ���ź�');
diffence=m-x;
subplot(3,1,3);plot(t,diffence);title('�ֽ�ϳɺ���ź���ԭʼ�źŵ����');
%axis tight;
%����ԭʼ�źŵ�Ƶ��========================================================
figure;
[A,f,tt] = hhspectrum(imf(1:end-1,:));
%plot(fftshift(abs(fft(x,1024))));
plot(abs(fft(x)));
title('Ƶ��ͼ');ylabel('��ֵ');xlabel('ʱ��');
axis([0,500,0,1000]);%�����������ȡֵ��Χ
%axis tight;%����ֵ�仯��Χ����Ϊ�̶�
% HHT�任==============================================================
freq_resol=300;
[A,f,tt] = hhspectrum(imf(1:end,:));%HHT�׻��������һ����IMF������hhspectrum��imf���������з���
%im=toimage(A,f,tt);
%[A,f,tt] = hhspectrum(imf(1:end-1,:));
[im,ttt,ff] = toimage(A,f,tt,length(tt),freq_resol);
%disp_hhs(im,t);%���ƹ�һ��Ƶ��
disp_hhs(im,[],N);%������ʵƵ�ʣ�NΪ����Ƶ��
set(gca,'xtick',[0:409.6:4096],'xticklabel',[0:0.1:1]);%����x���꣬ǰ������Ҫһ��
%hgsave('HH_Spectrum');%������'HH_Spectrum'����ͼƬ
colorbar('yticklabel',{[0:2:20]})%��ɫ�����ָ�ֵ������£��ɸ�����ȡֵ��Χ�޸�����㵽�����仯
%colorbar;
%HHT�߼���============================================================
 %im=flipud(im);%��һ��ʹ�������·�ת
 fs=1;
for kkk=1:size(im,1)
    aaa(kkk)=sum(im(kkk,:))*1/fs;
end
figure;
%f=(0:N-3)/N*(fs/2);
plot(N*ff(1,:),aaa);%��һ��Ƶ�ʳ��ڲ���Ƶ�ʾ�����ʵƵ��,NΪ����Ƶ��
%plot(ff(1,:),aaa);%��ȡ��һ��Ƶ��
axis tight;
title('�߼���');%��ʾÿ��Ƶ�ʵ������
xlabel('Ƶ��');ylabel('��ֵ');
axis([0,500,0,1000]);%�����������ȡֵ��Χ
%�������ǹ�һ����Ƶ��
%%%�߼��ױ�ʾ�ź���ĳһƵ���ڸ���ʱ�̵ķ�ֵֵ֮�ͣ�������ʵ�ķ�ӦƵ�����ź����Ƿ����
%������ʱ��ĳһ˲ʱƵ�ʵ���������ֵ�������������ź��и�Ƶ�ʵ����������ܷ�ֵ�������߼����ߵĸ߶�
%%%�ӱ߼����Ͽ��Կ����ź�Ƶ�ʷֲ�����ʵ���
%plot(f,aaa);
%D=logspace(min(log(ff)),max(log(ff)),size(ff,2));
%loglog(D,aaa);
% [S,freq]=hspec(imf,1000);
%  figure;
%  w1=size(A,2);
%  w2=size(f,2);
  
%[AA,F] = mhs(A,f,0,0.5,1000);

%D=logspace(min(log(F)),max(log(F)),size(F,2));
%loglog(F,AA);
%plot(log(F),log(AA));

%%%%===========����EMD(EEMD)��С����ֵȥ��=============================================
%����ԭ�� (1)��ԭʼ��������x(t)����EEMD�ֽ⣬��ֽ����Ϊx;
%          (2)���ڵ�һ��IMF��������������ֱ�ӽ���ȥ��
%          (3)��IMF2-IMFk������ֵ���봦��
%          (4)����ֵ������ĸ�IMF������ʣ����������ع����õ��������ź�
%%%=====%%%%ʵ�ֶ�һά�ź��Զ�����===========(Ч���Ϻ�)=============
%{
 q=0;
for j=1:i
    xt = zeros(1,length(t));
    % ���ź�nx��С������sym5�ֽ⵽��5��  �ɶ�С�����������޸���sym3
    % ��minimaxi������ֵ��Сֵ��ֵѡ���ϵ�����д������������ź�
    %sqtwolog ȡͨ�÷�ֵ��heursure;����ʽ��ֵѡ��rigrsure����ƫ��Ȼ����
    lev = 2;%С���ֽ�Ĳ���
    xt= wden(imf(j,:),'minimaxi','s','mln',lev,'sym5');  %sym3Ϊ���õ�С������;mln���ݲ�ͬ�������������������ֵ��
    %sln ���ݵ�һ���ϵ��������������Ĺ�����������ֵ one ��ʾ������
    q=q+xt;
end
%}
%%%%============%%%��С���ֽ�ϵ��������ֵ����Ȼ��Դ�����С��ϵ�������ع��ﵽȥ���Ŀ��===��Ч���Ϻã�
%%%%%ע��С������ѡ��ͷֽ�߶ȵ�ѡ�񣬷ֽ�߶�Խ��ȥ��Ч��Խ����======================
%{
q=0;
for j=1:i
    xt = zeros(1,length(t));
   [c,l]=wavedec(imf(j,:),2,'db6');
   %���ó߶�����
   n=[1,2];
   %���÷�ֵ����
   p=[120,110];%n,p�ĳ��ȱ�����ͬ
   %�Ը�Ƶϵ�����з�ֵ����
   %nc=wthcoef('d',c,l,n,p,'s');
   nc=wthcoef('d',c,l,n);
   %nc=wthcoef('a',c,l);%��Ƶ�ɷ�
   %���������С���ֽ�ṹ�����ع���[nc,l]����һ���µ�С���ֽ�ṹ
   xt = waverec(nc,l,'db6');
   q=q+xt;
end
%}
%%%%============����������׼ƫ��=========(Ч���Ϻ�)============
%{
q=0;
for j=1:i
    xt = zeros(1,length(t));
    %��С������ 'db6'���źŽ���3��ֽ�
   [c,l] = wavedec(imf(j,:),3, 'db6');   
   %���Ƴ߶�1��������׼ƫ��
   sigma = wnoisest(c,l,1);      
   alpha = 2; %����Ϊһ������1��ʵ��
   %��ȡ��������еķ�ֵ
   thr = wbmpen(c,l,sigma,alpha) ;   %c,lΪ����ȥ���ź�С���ֽ�ṹ
   keepapp = 1;%��ȡֵΪ1ʱ����Ƶϵ����������ֵ��������֮��Ƶϵ��Ҫ��������
   %���źŽ�������
   xt= wdencmp('gbl',c,l,'db6',3,thr,'s',keepapp);
   q=q+xt;
end
%}
%%%����ddencmp�ĵ���==============(Ч���Ϻ�)======
%{
q=0;
for j=1:i
    xt = zeros(1,length(t));
    % ��ȡ����ķ�ֵ
   [thr,sorh,keepapp] = ddencmp('den','wv',imf(j,:));   %den��ʾ����ȥ�룬wv��ʾѡ��С��
   % ���źŽ�������
   xt = wdencmp('gbl',imf(j,:),'db4',2,thr,sorh,keepapp);%gbl��ʾѡ����ͬ����ֵ,3��ʾС���ֽ�Ĳ���
   
%    %%%����thselect�ĵ���
%    %��ȡ����ķ�ֵ
%    THR=thselect(nx,'rigrsure');%����Ӧ��ֵѡ��ʹ��stein����ƫ���չ���ԭ��
%    %'heursure'ʹ������ʽ��ֵѡ��;'sqtwolog'��ֵ����sqrt(2*log(length(x)));'minimaxi'�ü���Сԭ��ѡ����ֵ
%    % ���źŽ�������
%    xd=wdencmp('gbl',nx,'db4',2,THR,'h');%sΪ����2ֵ��h��ʾӲ��ֵ
   
   q=q+xt;
end
%}
%%%������������ȥ��=====ȥ��Ч������======
%{
q=0;
for j=1:i
    %xt = zeros(1,length(t));
    % �õ�sym5С������������
    lshaar = liftwave('haar');
    % ���ELS������������
    els = {'p',[-0.125 0.125],0};
    lsnew = addlift(lshaar,els);
    % ��������С���ֽ�
   [cA1,cD1] = lwt(imf(j,:),lsnew);
   [cA2,cD2] = lwt(cA1,lsnew);%%%�ٶԽ����źŽ�������С���ֽ�
   length = size(cA2,2);
   c = zeros(1,length*4);
   for i = 1:length;
    c(i) = cA2(i);
   end
   for i = length+1:2*length;
    c(i) = cD2(i-length);
   end;
   for i = length*2+1:4*length;
    c(i) = cD1(i-2*length);
   end;
   l(1) = length;
   l(2) = length;
   l(3) = length*2;
   l(4) = length*4;
   %���Ƴ߶�2��������׼ƫ��
   sigma = wnoisest(c,l,2);      
   alpha = 2;%���ڴ����ĵ�����������������һ������1��ʵ����һ��ȡ2
   %��ȡ��������е�ȫ�ַ�ֵ
   thr = wbmpen(c,l,sigma,alpha) ;   
   keepapp = 1;%%%��Ƶϵ����������ֵ��������֮Ҫ������ֵ����
   %���źŽ�������
   xt= wdencmp('gbl',c,l,'db4',2,thr,'s',keepapp);
   %%%gblȫ����ֵ��lvbÿһ���ò�ͬ����ֵ���д���2��ʾ�ֽ�Ĳ���
   %%%s��ʾ����ֵ��h��ʾӲ��ֵ

   q=q+xt;
end
%}
%{
figure;
subplot(411);
plot(t,x1);title('��������ԭʼ�ź�');
subplot(412);
plot(t,x);title('������ԭʼ�ź�');axis tight;
subplot(413);
plot(t,q);title('�˲��ϳɺ���ź�');axis tight;
subplot(414);
%err=q-x;
plot(t,x,'b',t,q,'r');legend('������ԭʼ�ź�','�˲��ϳɺ���ź�');
title('�˲�Ч���Ƚ�');axis tight;
%}
%================����С����������ֵ�˲�=====================================
%{
figure
%%%ʹ��db2С�������ź�x����s��ֽ�
%%%%ʹ��shannon��
s=3;%�ɶ�������޸�
wpt=wpdec(x,s,'db2');
%plot(wpt);
%%%�������ϵ��
for m=1:s
    for n=1:2^m
        cfs(m,n)=wpcoef(wpt,[m,n-1]);
        figure
        plot(cfs(m,n));
    end
end
%}
%{
%%%����ddencmp�ĵ���==============(Ч���Ϻ�)======
q=0;
for m=1:s
    for n=1:2^m
    xt = zeros(1,length(t));
    % ��ȡ����ķ�ֵ
   [thr,sorh,keepapp] = ddencmp('den','wv',cfs(m,n));   %den��ʾ����ȥ�룬wv��ʾѡ��С��
   % ���źŽ�������
   xt = wdencmp('gbl',imf(j,:),'db4',2,thr,sorh,keepapp);%gbl��ʾѡ����ͬ����ֵ,3��ʾС���ֽ�Ĳ���
   
%    %%%����thselect�ĵ���
%    %��ȡ����ķ�ֵ
%    THR=thselect(nx,'rigrsure');%����Ӧ��ֵѡ��ʹ��stein����ƫ���չ���ԭ��
%    %'heursure'ʹ������ʽ��ֵѡ��;'sqtwolog'��ֵ����sqrt(2*log(length(x)));'minimaxi'�ü���Сԭ��ѡ����ֵ
%    % ���źŽ�������
%    xd=wdencmp('gbl',nx,'db4',2,THR,'h');%sΪ����2ֵ��h��ʾӲ��ֵ
   q=q+xt;
    end
end
plot(q);
%}
%%%====�۲�ȥ��Ч���ĺû�========================================
%{
m='rm';%Ҳ��������Ϊ��rv��
%x1Ϊԭʼ�źţ�xΪ�ع��źţ�
value=SNR(x1,x,m)    %���δ������źŵ������
%%%����ddencmp�ĵ��ã�ʵ����ֵȥ��====================
    xt = zeros(1,length(t));
    % ��ȡ����ķ�ֵ
   [thr,sorh,keepapp] = ddencmp('den','wv',x);   %den��ʾ����ȥ�룬wv��ʾѡ��С��
   % ���źŽ�������
   xt = wdencmp('gbl',x,'db4',3,thr,sorh,keepapp);%gbl��ʾѡ����ͬ����ֵ,3��ʾС���ֽ�Ĳ���
%    %%%����thselect�ĵ���
%    %��ȡ����ķ�ֵ
%    THR=thselect(nx,'rigrsure');%����Ӧ��ֵѡ��ʹ��stein����ƫ���չ���ԭ��
%    %'heursure'ʹ������ʽ��ֵѡ��;'sqtwolog'��ֵ����sqrt(2*log(length(x)));'minimaxi'�ü���Сԭ��ѡ����ֵ
%    % ���źŽ�������
%    xd=wdencmp('gbl',nx,'db4',2,THR,'h');%sΪ����2ֵ��h��ʾӲ��
value1=SNR(x1,xt,m)   %��þ���С����ֵ�����������
%%%====����EMD��С����ֵ�˲�====================================
q=0;
for j=1:i
    xt = zeros(1,length(t));
    % ��ȡ����ķ�ֵ
   [thr,sorh,keepapp] = ddencmp('den','wv',imf(j,:));   %den��ʾ����ȥ�룬wv��ʾѡ��С��
   % ���źŽ�������
   xt = wdencmp('gbl',imf(j,:),'db4',3,thr,sorh,keepapp);%gbl��ʾѡ����ͬ����ֵ,3��ʾС���ֽ�Ĳ��� 
%    %%%����thselect�ĵ���
%    %��ȡ����ķ�ֵ
%    THR=thselect(nx,'rigrsure');%����Ӧ��ֵѡ��ʹ��stein����ƫ���չ���ԭ��
%    %'heursure'ʹ������ʽ��ֵѡ��;'sqtwolog'��ֵ����sqrt(2*log(length(x)));'minimaxi'�ü���Сԭ��ѡ����ֵ
%    % ���źŽ�������
%    xd=wdencmp('gbl',nx,'db4',2,THR,'h');%sΪ����2ֵ��h��ʾӲ��ֵ
   q=q+xt;
end
%m='rm';%Ҳ��������Ϊ��rv��
value2=SNR(x1,q,m)   %��þ�������EMDС����ֵ�����������
%%%������Ƚϸ�ʱ��С���ֽ����������Ϊ2,��������Ƚϵ�ʱ��С���ֽ���������ô�Щ��
%%%������Ƚϴ��ʱ��С��ȥ��Ч���Ϻã�������Ƚ�С��ʱ�򣬻���EMDС����ֵȥ�봦��Ч����
%}
%{
figure
subplot(311)
plot(t,x1);title('�������ź�');
xlabel('ʱ��');ylabel('��ֵ');
subplot(312)
plot(t,xt);title('С����ֵȥ���ź�');
xlabel('ʱ��');ylabel('��ֵ');
subplot(313)
plot(t,q);title('����EMDС����ֵȥ���ź�');
xlabel('ʱ��');ylabel('��ֵ');
%}
%%====================С���任����ʱƵ����=================================
%{
%%interpreting the cwt coefficients
��������ԭ��

    1.��Ҫ�õ���С���������е���������

    COEFS = cwt(S,SCALES,'wname') 
    ˵�����ú�����ʵ������С���任������SΪ�����źţ�SCALESΪ�߶ȣ�wnameΪС�����ơ�
          COEFSΪ��������С���任�󷵻ص�ϵ������
        
    FREQ = centfrq('wname')
    ˵�����ú����������wname������ĸС��������Ƶ�ʡ�

    F = scal2frq(A,'wname',DELTA) 
    ˵�����ú����ܽ��߶�ת��Ϊʵ��Ƶ�ʣ�����AΪ�߶ȣ�wnameΪС�����ƣ�DELTAΪ�������ڡ�

    ע����������������������ʽ������ɲ���matlab�İ����ĵ���

    2.�߶���Ƶ��֮��Ĺ�ϵ

    ��aΪ�߶ȣ�fsΪ����Ƶ�ʣ�FcΪС������Ƶ�ʣ���a��Ӧ��ʵ��Ƶ��FaΪ
                      
                      Fa��Fc��fs/a                                     (1)

��Ȼ��ΪʹС���߶�ͼ��Ƶ�ʷ�ΧΪ(0,fs/2)���߶ȷ�ΧӦΪ(2*Fc,inf),����inf��ʾΪ�������ʵ��Ӧ���У�ֻ��ȡ�߶��㹻�󼴿ɡ�
   
    3.�߶����е�ȷ�� 

    ��ʽ(1)���Կ�����Ϊʹת�����Ƶ��������һ�Ȳ����У��߶����б���ȡΪ������ʽ��
    
                 c/totalscal,...,c/(totalscal-1),c/4,c/2,c        (2)  

���У�totalscal�Ƕ��źŽ���С���任ʱ���ó߶����еĳ���(ͨ����ҪԤ���趨��)��cΪһ������

   ���潲��c���󷨡�
     
    ����ʽ(1)���׿������߶�c/totalscal����Ӧ��ʵ��Ƶ��ӦΪfs/2�����ǿɵ�

                      c=2��Fc/totalscal                               (3)

��ʽ(3)����ʽ(2)��õ�������ĳ߶����С�
    
    4.ʱƵͼ�Ļ���

    ȷ����С�����ͳ߶Ⱥ󣬾Ϳ�����cwt��С��ϵ��coefs��ϵ���Ǹ���ʱҪȡģ����Ȼ����scal2frq���߶�����ת��Ϊʵ��Ƶ������f��
�����ʱ������t����imagesc(t,f,abs(coefs))���ܻ���С��ʱƵͼ��

    ע�⣺ֱ�ӽ��߶�����ȡΪ�Ȳ����У�����1:1:64����ֻ�ܵõ���ȷ�ĳ߶ȣ�ʱ�䣭С��ϵ��ͼ�����޷�����ת��ΪƵ�ʣ�ʱ�䣭С��ϵ��ͼ��������Ϊ��ʱ��Ƶ�ʼ����Ϊ������
��ʱ����ͨ�����ķ������߶�ת��ΪƵ�ʻ�ֱ���޸ĳ߶����ע��ͬ�����ñ��������ܵķ���ֻ�ܵõ�Ƶ�ʣ�ʱ�䣭С��ϵ��ͼ�����ܵõ���ȷ�ĳ߶ȣ�ʱ�䣭С��ϵ��ͼ

˵����(1)Ӧ��ʱֻ��ı�wavename��totalscal�����������ɡ�
              (2)����������У����ѡ�ø���morletС��������С���ķ���Ч�����ã�����morletС���Ĵ������������Ƶ��ȡ��Խ��ʱƵͼ�Ϸ�ӳ��ʱƵ�ۼ���Խ�á�

%}
%{
% clear;
% clc;
fs=4096;  %����Ƶ�ʣ��ɸ�����Ҫ���ò���Ƶ�ʣ�һ��Ϊ2����������
% f1=100;                         
% f2=200;
% t=0:1/fs:1; %��ȡ�����轫��ע��
%{
R=xlsread('Gravity');%��ȡ����
t=R(:,1);
s=R(:,2);
%}
%s=10*sin(2*pi*f1*t)+15*sin(2*pi*f2*t);  %������ͬƵ�������źźϳɵķ����ź�
%s=sin(2*pi*f1*t)/2;  
%%%%�ֶκ�����ʱƵ����================================================
figure
s=x1;
%%%С��ʱƵͼ����=======================================================
wavename='cmor3-3';   %С������ ��С��cgau8��shan1-1.5,bior4.4,coif5,sym6,db4
%wavename='bior3.5';
totalscal=256;                    %�߶����еĳ��ȣ���scal�ĳ���,�ɸ���ʵ����Ҫ������и���
wcf=centfrq(wavename);            %С��������Ƶ��
cparam=2*wcf*totalscal;           %Ϊ�õ����ʵĳ߶�������Ĳ���
a=totalscal:-1:1; 
scal=cparam./a;                   %�õ������߶ȣ���ʹת���õ�Ƶ������Ϊ�Ȳ�����
coefs=cwt(s,scal,wavename);       %�õ�С��ϵ��
f=scal2frq(scal,wavename,1/fs);   %���߶�ת��Ϊʵ��Ƶ��
%�߶ȵĵ�����Ӧ��Ƶ�ʣ��߶ȴ�Ƶ�ʵͣ�Ƶ�ʷֱ��ʸߣ�ʱ��ֱ��ʵͣ��߶�С��Ƶ�ʸߣ�Ƶ�ʷֱ��ʵͣ�ʱ��ֱ��ʸ�
imagesc(t,f,abs(coefs));          %����ɫ��ͼ
axis xy;colormap jet;
colorbar;
%colormap(flipud(gray));% �ڰ���ʾ,��ӡ�Ƚ�����
xlabel('ʱ�� t/s');
ylabel('Ƶ�� f/Hz');%Ƶ��������ֵΪ����Ƶ�ʵ�1/2
title('С���任ʱƵͼ');
figure;
mesh(t,f,abs(coefs));colormap jet;
xlabel('ʱ�� t/s');
ylabel('Ƶ�� f/Hz');
zlabel('��ֵ');
title('С���任ʱƵͼ');
axis tight;
%}
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
%{
%%%====
%��db1С���������źŽ��ж�߶�С���ֽ�
[C,L]=wavedec(M,3,'sym1');
%��ȡ�߶�1�ĵ�Ƶϵ��
cA1=appcoef(C,L,'sym1',1);
%��ȡ�߶�2�ĵ�Ƶϵ��
cA2=appcoef(C,L,'sym1',3);
%��ȡ�߶�1�ĸ�Ƶϵ��
cD1=detcoef(C,L,1);
%��ȡ�߶�2�ĸ�Ƶϵ��
cD2=detcoef(C,L,3);
figure
subplot(411)
plot(cA1);
subplot(412)
plot(cD1);
subplot(413)
plot(cA2);
subplot(414)
plot(cD2);
%%%===================����ƽ������������=========================================
%}
%{

dt = 1;%ʱ��������dt��ms
fn = 1000/(2*dt);%�ο�˹��Ƶ�ʣ�hz
fmin=0;%��СƵ�ʴ�0Hz��ʼ
fmax=fn %���Ƶ��Ϊ�ο�˹��Ƶ��

%-----���ò�ͬƵ�ʵ�Ricker�Ӳ�����һ���ϳɼ�¼--------------------------------
fp1=150;
fp2=90;
fp3=60;
fp4=30;
wave_t=120; %�Ӳ���ʱ�䳤�ȣ�ms
w_t=-wave_t/(2*1000):dt/1000:wave_t/(2*1000);
rick1=(1-2*(pi*fp1*(w_t)).^2).*exp(-(pi*fp1*(w_t)).^2);
w_t=-wave_t/(2*1000):dt/1000:wave_t/(2*1000);
rick2=-1*(1-2*(pi*fp2*(w_t)).^2).*exp(-(pi*fp2*(w_t)).^2);
w_t=-wave_t/(2*1000):dt/1000:wave_t/(2*1000);
rick3=(1-2*(pi*fp3*(w_t)).^2).*exp(-(pi*fp3*(w_t)).^2);
w_t=-wave_t/(2*1000):dt/1000:wave_t/(2*1000);
rick4=-1*(1-2*(pi*fp4*(w_t)).^2).*exp(-(pi*fp4*(w_t)).^2);
syn1=[rick1 rick2 rick3 rick4];
wave_t=100; %�Ӳ���ʱ�䳤�ȣ�ms
w_t=-wave_t/(2*1000):dt/1000:wave_t/(2*1000);
rick1=(1-2*(pi*fp1*(w_t)).^2).*exp(-(pi*fp1*(w_t)).^2);
w_t=-wave_t/(2*1000):dt/1000:wave_t/(2*1000);
rick2=-1*(1-2*(pi*fp2*(w_t)).^2).*exp(-(pi*fp2*(w_t)).^2);
w_t=-wave_t/(2*1000):dt/1000:wave_t/(2*1000);
rick3=(1-2*(pi*fp3*(w_t)).^2).*exp(-(pi*fp3*(w_t)).^2);
w_t=-wave_t/(2*1000):dt/1000:wave_t/(2*1000);
rick4=-1*(1-2*(pi*fp4*(w_t)).^2).*exp(-(pi*fp4*(w_t)).^2);
syn2=[rick1 rick2 rick3 rick4 zeros(1,80)];
syn=syn1+syn2;%�ϳ�һ���ź�

N=1000;%����Ƶ��
[imf,ort,nbits]=emd(syn);
w_t=0:dt:length(syn)-1;
%{
figure
plot(w_t,syn);title('ģ���ź�');xlabel('ʱ��  t/ms');
ylabel('��ֵ');
figure
N=512;n=0:N-1;t=0.001*n;q=n*1000/N;
y=fft(syn,N);plot(q,abs(y));title('��FFT�õ���ģ���źŵ�Ƶ��');
xlabel('Ƶ��  f/Hz');ylabel('��ֵ');
%}
%IMF������================================================================
%ԭʼ�źŵĻ���==========================================================

%IMF������================================================================
figure;
imfsize=size(imf);
i=imfsize(1);
%��IMF�������ĺϳ���ԭʼ�źŵıȽ�=========================================

% HHT�任==============================================================
figure
freq_resol=300;
[A,f,tt] = hhspectrum(imf(1:end-1,:));%HHT�׻��������һ����IMF������hhspectrum��imf���������з���
%im=toimage(A,f,tt);
%[A,f,tt] = hhspectrum(imf(1:end-1,:));
[im,ttt,ff] = toimage(A,f,tt,length(tt),freq_resol);
%disp_hhs(im,t);%���ƹ�һ��Ƶ��
disp_hhs(im,[],N);%������ʵƵ�ʣ�NΪ����Ƶ��
set(gca,'xtick',[0:50:length(syn)],'xticklabel',[0:50:length(syn)]);%����x���꣬ǰ������Ҫһ��
%hgsave('HH_Spectrum');%������'HH_Spectrum'����ͼƬ
%colorbar('yticklabel',{[0:2:20]})%��ɫ�����ָ�ֵ������£��ɸ�����ȡֵ��Χ�޸�����㵽�����仯
colorbar;
%HHT�߼���============================================================
 %im=flipud(im);%��һ��ʹ�������·�ת
 N=1000;%����Ƶ��
 fs=1;
for kkk=1:size(im,1)
    aaa(kkk)=sum(im(kkk,:))*1/fs;
end
figure;
%f=(0:N-3)/N*(fs/2);
plot(N*ff(1,:),aaa);%��һ��Ƶ�ʳ��ڲ���Ƶ�ʾ�����ʵƵ��,NΪ����Ƶ��
%plot(ff(1,:),aaa);%��ȡ��һ��Ƶ��
axis tight;
title('�߼���');%��ʾÿ��Ƶ�ʵ������
xlabel('Ƶ��  f/Hz');ylabel('��ֵ');
%}
