
clear;
clc;

%�����źŵ������
% load LorenzSNR1.mat;
% [DATAfile DATApath]=uigetfile('*.txt','�����ź�');
% FILENAME=[DATApath,DATAfile];
% x=load(FILENAME);
% sig1=x';
% sig2=Y(1:length(sig1));
% % load Lorenz.mat;
% % sig1=x;
% % sig2=Y;
%{
f=30;
fs=1000;
number=200;
t=-number/2+1:number/2;
a=(1-2*(pi*f*t/fs).^2).*exp(-(pi*f*t/fs).^2);
s=awgn(a,10,'measured'); 
%}
N=4096;t=linspace(0,1,N);
%N=1024;n=0:N-1;t=Ts*n;
x=3*sin(2*pi*90*t)+2*cos(2*pi*180*t);
x1=3*sin(2*pi*90*t)+2*cos(2*pi*180*t)+0.1*randn(1,length(t));
sig1=x;   % sig1 ԭʼ�ź�
sig2=x1;   % sig2 �ع��ź�
m='rm';
value=SNR(sig1,sig2,m)
%%%����ddencmp�ĵ��ã�ʵ����ֵȥ��====================
    xt = zeros(1,length(t));
    % ��ȡ����ķ�ֵ
   [thr,sorh,keepapp] = ddencmp('den','wv',x1);   %den��ʾ����ȥ�룬wv��ʾѡ��С��
   % ���źŽ�������
   xt = wdencmp('gbl',x1,'db4',2,thr,sorh,keepapp);%gbl��ʾѡ����ͬ����ֵ,3��ʾС���ֽ�Ĳ���
   
%    %%%����thselect�ĵ���
%    %��ȡ����ķ�ֵ
%    THR=thselect(nx,'rigrsure');%����Ӧ��ֵѡ��ʹ��stein����ƫ���չ���ԭ��
%    %'heursure'ʹ������ʽ��ֵѡ��;'sqtwolog'��ֵ����sqrt(2*log(length(x)));'minimaxi'�ü���Сԭ��ѡ����ֵ
%    % ���źŽ�������
%    xd=wdencmp('gbl',nx,'db4',2,THR,'h');%sΪ����2ֵ��h��ʾӲ��
value1=SNR(sig1,xt,m)



