
clc
clear all
close all

N=1024/2;
n=0:N-1;
t=[0:1:1000];
%�����ź�
%y=5*cos(2*pi*20*t)+4*sin(2*pi*40*t)+3*cos(pi*t);
y=sin(2*pi*30*t)+2*sin(2*pi*60*t);
figure;
%whitebg(gcf,'black');%%%��ͼ�εĻ��ƴ��ڵı���ɫ����Ϊ��ɫ
plot(t,y);title('ԭʼ�ź�');

%FFT��ʾƵ��
fs=10;%����Ƶ��
X=fft(y,N);

% figure;
% plot(abs(X));
figure;
%whitebg(gcf,'black');%%%��ͼ�εĻ��ƴ��ڵı���ɫ����Ϊ��ɫ
plot(n*fs/N,abs(X));title('ԭʼ�źŵ�Ƶ��ͼ');

%EMD�任
[imf,ort,nbits]=emd(y);
imfsize=size(imf);
i=imfsize(1);

%��IMF������������
newrdxn=y;
figure;
for j=1:i
    subplot(i/2+1,2,j);plot(imf(j,:));%Ylabel('IMF');
     Ylabel(sprintf('IMF%d', j));
    newrdxn=newrdxn-imf(j,:);
end
% subplot(i/2+1,2,j+1);
% plot(newrdxn);Ylabel('������');

%ÿ�ֽ�һ�κ�Ĳ�����
figure;
newrdxn=y;
for k=1:i
    newrdxn=newrdxn-imf(k,:);
    subplot(i/2+1,2,k);plot(newrdxn);title('������');
end

%HHT�任
[A,f,tt] = hhspectrum(imf(1:end-1,:));
[im,tt,ff] = toimage(A,f,tt,512);
disp_hhs(im,tt);
hgsave('HH_Spectrum');
%HHT�߼���
for kkk=1:512
    aaa(kkk)=sum(im(kkk,:));
end
 figure;
plot(ff(1,:),aaa);title('�߼���');
%figure;
%plot(n*fs/2/N,aaa);

