
clear;
clc;
tic;
%{
[x,FS]=wavread('1.wav');
sigLength=length(x);
%h=window('hamming',64);
%[B,f,t]=specgram(x,256,22050,h,60);
t=(0:sigLength-1)/FS;
ts=t;
rdxn=x;
%}
%
%data=load('gphone_velocity(2010.5.24-2010.5.31).dat');
%data=load('Gravity.txt');%��������
%data=load('L4Vz.dat');%��������,ʱ���ź�

data=load('Gravity.txt');
ts=data(:,1);%��ȡ��һ������
rdxn=data(:,2);

%rdxn=data(:,4);
% %FS=1;%���ݵĲ���Ƶ��,����0.02sȡһ���㣬�����Ƶ��Ϊ1/0.002;
% N=4096;ts=linspace(0,1,N);
% rdxn=(1+0.3*sin(2*pi*15*ts)).*cos(2*pi*50*ts+0.5*sin(2*pi*15*ts))+sin(2*pi*150*ts);

% N=4096;ts=linspace(0,1,N);
% rdxn=0.5*sin(2*pi*400*ts)+0.5*cos(2*pi*100*ts)+0.6*sin(2*pi*500*ts);



%load ecg1410.txt;
%rdxn=ecg1410;
% load eeg0410.mat;
% rdxn=eeg0410;
N=length(rdxn);%���ݵĳ���
%n=1:N;
fs=N/(ts(N)-ts(1));
%t=n/fs;
t_inst=1:length(rdxn); %time vector (drugoj uzhe)
FS=fs;



%����ԭʼ���ݵı仯����=============================================
figure;
%whitebg(gcf,'black');%%%��ͼ�εĻ��ƴ��ڵı���ɫ����Ϊ��ɫ
plot(ts,rdxn);
%title('gphone-data');
title('ԭʼ�ź�');xlabel('ʱ��  t/ms');ylabel('��ֵ');
%EMD�任
[imf,ort,nbits]=emd(rdxn);
imfsize=size(imf);
i=imfsize(1);

%{
%FFT��ʾƵ��==============(������ʾ��ƽ���źŵ�Ƶ�ף����岻��==========================================
%
N1=4096;%2����������,�������������ݵĲ�������=============��������ʱ������ʵ�������Ҫ�޸���
n=0:N1-1;%t=1/4096
fs=4096;%����Ƶ��,�����ݲ���Ƶ��һ��==========��Ҫ�޸���
X=fft(rdxn,N1);
% figure;
% plot(abs(X));
figure;
%whitebg(gcf,'black');%%%��ͼ�εĻ��ƴ��ڵı���ɫ����Ϊ��ɫ
plot(n*fs/N1,abs(X));%axis([0,1000,0,15000]);
%axis tight;
title('ԭʼ�źŵ�Ƶ��ͼ');
%}

%��IMF�������������====================================================
figure;
%whitebg(gcf,'black');%%%��ͼ�εĻ��ƴ��ڵı���ɫ����Ϊ��ɫ
%title('EMD�ֽ�');
newrdxn=rdxn';
for j=1:i
    subplot(i/2+1,2,j);plot(ts,imf(j,:));
     if(j<i) Ylabel(sprintf('IMF%d', j));
     else Ylabel('Res');
     end
   %  newrdxn=newrdxn-imf(j,:);
end
% subplot(i/2+1,2,j+1);
% plot(newrdxn);Ylabel('������');%���һ�ηֽ�Ĳ�����
 %ÿ�ֽ�һ�κ�Ĳ�����==================================================
 figure;
% title('������');
 newrdxn=rdxn';
 for k=1:i
     newrdxn=newrdxn-imf(k,:);
     subplot(i/2+1,2,k);plot(ts,newrdxn);
     k=k+1;
 end
%{
 %IMF-Fourier ��===========================================================
  figure;
  %whitebg(gcf,'black');%%%��ͼ�εĻ��ƴ��ڵı���ɫ����Ϊ��ɫ
% M = length(imf);
% N = length(x);
% c = linspace(0,(N-1)*Ts,N);   
N1=N; 
for v=1:i
    t=fft(imf(v,:),N1);
    subplot(i/2,2,v),%i/2��ʾͼ�ε���ʾ��ʽ���ɸ�����Ҫ��������
    plot(n*fs/N1,abs(t));axis tight;
    if(v<i)Ylabel(sprintf('IMF%d', v));%title(sprintf('IMF%d-Fourier ��', v));
    else Ylabel('Res');%title('Res-Fourier ��');
    end
    %ylabel('IMF-Fourier �� ')
    %v=v+1;
end
%}  
%HHT�任===============================================================
freq_resol=300;
[A,f,tt] = hhspectrum(imf(1:end-1,:));
[im,ttt,ff] = toimage(A,f,tt,length(tt),freq_resol);%��ÿ��IMF�źźϳ���ȡHilbert�ף�im��Ӧ�����ֵ��ff:ÿ�������Ӧ������Ƶ�ʣ����������ʱ�䣬����ΪƵ��
%disp_hhs(im,ttt);
disp_hhs(im,[],FS);%FSΪ���ݲ���Ƶ��
%set(gca,'xtick',[0:441.3108242:length(rdxn)],'xticklabel',[0:0.02:0.1007]);%����x���꣬ǰ������Ҫһ��
%length(rdxn)Ϊ���ݳ��ȣ�length(rdxn)/250.2��2.388/0.5���
colorbar('yticklabel',{[0:2:20]})%��ɫ�����ָ�ֵ������£��ɸ�����ȡֵ��Χ�޸�����㵽�����仯
%colorbar;
hgsave('HH_Spectrum');
%colormap(flipud(gray)); % �ڰ���ʾ,��ӡ�Ƚ�����
% axisx=max(ttt);
% axisy=max(ff);
% WriteGrd(im,'time_frqence.grd',axisx,axisy);

%HHT�߼���===========================================================
%%%�߼��״�ͳ�������ϱ�������������ÿ��Ƶ�ʵ���ۻ���ֵ�ֲ����߼��׿��Դ����ƽ���źţ����
%%%�ź��д���ĳһƵ�ʵ��������֣��ͱ�ʾһ���и�Ƶ�ʵ��񶯲����֣�Ҳ���Ǳ߼����ܱȽ�׼ȷ�ط�
%%%ӳ�źŵ�ʵ��Ƶ�ʳɷ�
fs=1;
%fs=FS;
 %im=flipud(im);%��һ��ʹ�������·�ת
for kkk=1:size(im,1)
    aaa(kkk)=sum(im(kkk,:))*1/fs;
end
figure;
%whitebg(gcf,'black');%%%��ͼ�εĻ��ƴ��ڵı���ɫ����Ϊ��ɫ
%f=(0:N-3)/N*(fs/2);
plot(FS*ff(1,:),aaa);axis tight;
title('�߼���');%��һ��Ƶ�ʳ��ڲ���Ƶ�ʾ�����ʵƵ��,FSΪ����Ƶ��
xlabel('Ƶ��  f/Hz');ylabel('��ֵ');
%%==============����������ݽ��д����ļ�==============================
%{
%x=0:pi/100000:2*pi;
%N=length(x);
g1=zeros(1,N);%NΪ�źŵĳ���
g2=zeros(1,N);
g3=zeros(1,N);
g4=zeros(1,N);
diffence=zeros(1,N);
fid1=fopen('��Ƶ�ź�12.dat','wt');
fid2=fopen('��Ƶ�ź�12.dat','wt');
%fprintf(fid,'%s    %s\n','������','����ֵ');%���ڿ�ʼ��ע������Ϣ
Q=0;

for j=1:i
    %g(i)=7*sin(x(i))+1;
    if(i<=4)
        g1(j)=Q+imf(j,:);
        fprintf(fid1,'%f %f\n',ts,g1(j));
    end
    if(i>4)
        g2(j)=Q+imf(j,:);
        fprintf(fid2,'%f %f\n',ts,g2(j));
    end
end

for i=1:2
  g1=g1+imf(i,:);%+imf(2,:)+imf(3,:)+imf(4,:);
end
for i=3:4
   g2=g2+imf(i,:);%+imf(6,:)+imf(7,:)+imf(8,:)+;
end
   g3=imf(5,:)+imf(6,:);
   g4=imf(7,:)+imf(8,:);
 fprintf(fid1,'%f  %f \n',ts,g1);
 fprintf(fid2,'%f  %f \n',ts,g2);
%plot(x,g,'g+');
fclose(fid1);
fclose(fid2);
%===================================
%}


%{
g1=zeros(1,N);%NΪ�źŵĳ���
g2=zeros(1,N);
g3=zeros(1,N);
g4=zeros(1,N);
%g5=zeros(1,N);
g1=imf(1,:)+imf(2,:)+imf(3,:)+imf(4,:);
g2=imf(5,:)+imf(6,:)+imf(7,:)+imf(8,:);
g3=imf(9,:)+imf(10,:)+imf(11,:)+imf(12,:);
g4=imf(13,:)+imf(14,:)+imf(15,:)+imf(16,:)+imf(17,:)+imf(18,:);
%g5=
rdxn=rdxn';
figure
subplot(511)
plot(ts,rdxn);
title('ԭʼ�ź�');
subplot(512)
plot(ts,g1);
title('��Ƶ�ź�')
subplot(513)
plot(ts,g2);
title('�θ�Ƶ�ź�');
subplot(514)
plot(ts,g3);
title('��Ƶ�ź�');
subplot(515)
plot(ts,g4);
title('�ε�Ƶ��Ϣ')

figure
g1=g1';
g2=g2';
g3=g3';
g4=g4'
%g5=g5';
subplot(311)
plot(ts,rdxn);
title('ԭʼ�ź�');
subplot(312)
plot(ts,g1+g2+g3+g4);
title('�ֽ��ع�����ź�');
subplot(313)
rdxn=rdxn';
diffence=g1+g2+g3+g4-rdxn;
plot(ts,diffence);
title('�źŷֽ��ع�������');

%}







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
toc;
%%%=========����EMD��С����ֵ�˲�============================================
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
%%%����ddencmp�ĵ���==============(Ч���Ϻ�)====================================
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
plot(ts,rdxn);title('������ԭʼ�ź�');axis tight;
subplot(412);
plot(ts,q);title('�˲��ϳɺ���ź�');axis tight;
subplot(413);
%err=q-x;
q=q';%��ά������ת�ã�ʹ����rdxn��ά��һֱ
plot(ts,rdxn,'b',ts,q,'r');legend('������ԭʼ�ź�','�˲��ϳɺ���ź�');
title('�˲�Ч���Ƚ�');axis tight;
diffence=q-ts;%�˲�ǰ��Ĳ�ֵ
subplot(414);
plot(ts,diffence,'g');title('�˲�ǰ��Ĳ�ֵ');
axis tight;
%}
%%%==============����С���任����ʱƵ����===============================================
%{
%fs=4096;  %����Ƶ�ʣ��ɸ�����Ҫ���ò���Ƶ�ʣ�һ��Ϊ2����������
fs=FS;
%{
R=xlsread('Gravity');%��ȡ����
t=R(:,1);
s=R(:,2);
%}
%a=load('Gravity.txt');
%{
t=data(:,1);%��ȡ��һ������
s=rdxn;%��ȡ�ڶ�������
%}
t=ts;
s=rdxn;
%��ȡ��һ�У��ڶ��б�ʾ������ t=a(1,:);s=a(2,:);
%======С���任ʱƵͼ�Ļ���========================================================
%wavename='cmor3-3';%��С��
wavename='db4';%�������Ϊ4������Ƶ��Ϊ2 С���Ĵ������������Ƶ��ȡ��Խ��ʱƵͼ�Ϸ�ӳ��ʱƵ�ۼ���Խ��
totalscal=256;                    %�߶����еĳ��ȣ���scal�ĳ���
wcf=centfrq(wavename);            %С��������Ƶ��
cparam=2*wcf*totalscal;           %Ϊ�õ����ʵĳ߶�������Ĳ���
a=totalscal:-1:1;  
scal=cparam./a;                   %�õ������߶ȣ���ʹת���õ�Ƶ������Ϊ�Ȳ�����
coefs=cwt(s,scal,wavename);       %�õ�С��ϵ��
f=scal2frq(scal,wavename,1/fs);   %���߶�ת��ΪƵ��
figure;
imagesc(t,f,abs(coefs));          %����ɫ��ͼ
axis('xy');
colorbar;
%colormap(flipud(gray));% �ڰ���ʾ,��ӡ�Ƚ�����
xlabel('ʱ��  t/ms');
ylabel('Ƶ��  f/Hz');%Ƶ��������ֵΪ����Ƶ�ʵ�1/2
title('С���任��WT��ʱƵͼ');
%}
%==================================================================================