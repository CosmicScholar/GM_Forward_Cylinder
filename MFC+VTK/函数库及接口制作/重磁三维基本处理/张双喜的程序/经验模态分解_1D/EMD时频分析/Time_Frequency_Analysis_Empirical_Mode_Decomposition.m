
clear ;
clc;

%ģ���ź�
N=2048;%��������
t=linspace(0,1,N);
sampFreq=N/(1-0);%����Ƶ��
n=0:N-1;T=n*sampFreq/N;

% ģ���ź�
x01=chirp(t,50,1,500);
x02=chirp(t,10,1,200);
x0=x01+x02;

x0_length=length(x0); % ԭʼ�źų���

% �ź�����
K=x0_length+1024; % ���ߺ���źų���
[x,k1,k2]=Signal_Extension_1D(x0,x0_length,K);

[imf,ort,nbits]=emd(x);

% �ź�����
imfsize=size(imf);
imf_length=imfsize(1);
for i=1:imf_length
    [imf_cut(i,:)]=Signal_Cut_1D(imf(i,:),k1,k2);  
end
imf=imf_cut;

figure;
subplot(311)
plot(t,x01);title('y1');
subplot(312)
plot(t,x02);title('y2');
subplot(313)
plot(t,x0);title('y1+y2');

%{
%ԭʼ�źŵĻ���
figure;
plot(t,x);title('ģ���ź�');ylabel('��ֵ');xlabel('ʱ��  t/s');

%IMF������
figure;
imfsize=size(imf);
i=imfsize(1);
for j=1:i
    [imf_cut(j,:)]=Signal_Cut_1D(imf(j,:),k1,k2);
    subplot(i/2+1,2,j);plot(t,imf(j,:));
    if(j<i) ylabel(sprintf('IMF%d', j));
    else ylabel('Res');
    end
end

imf=imf_cut
%�ֽ��IMFʣ�����
figure;
newrdxn=x;
for k=1:i
    newrdxn=newrdxn-imf(k,:);
    subplot(i/2+1,2,k);plot(t,newrdxn);title(sprintf('IMF%d��ʣ���ź�', k));
end 

%����ԭʼ�źŵ�Ƶ��
figure;
plot(T,abs(fft(x)));
title('Ƶ��ͼ');ylabel('��ֵ');xlabel('Ƶ��/HZ');
axis([0,sampFreq/2,0,1000]);%�����������ȡֵ��Χ
%}
%ϣ��������  ��ͼ�ε����Ͻ���ӱ���磨a��
freq_resol=500;
[A,f,tt] = hhspectrum(imf(1:end,:));%�޸�imf(1:end-2,:)������ʾĳһ��Ƶ��
[im,ttt,ff] = toimage(A,f,tt,length(tt),freq_resol);
[T,IM]=disp_hhs(im,[],N);%������ʵƵ�ʣ�NΪ����Ƶ��  ====IMΪ���صĲ���====
colormap(flipud(gray));% �ڰ���ʾ,��ӡ�Ƚ�����
set(gca,'ytick',(0:100:N/2),'yticklabel',(0:100:N/2));%����y���꣬ǰ������Ҫһ��
set(gca,'FontName','Times New Roman');

%{
%�߼���
%%%�߼��ױ�ʾ�ź���ĳһƵ���ڸ���ʱ�̵ķ�ֵֵ֮�ͣ�������ʵ�ķ�ӦƵ�����ź����Ƿ����
%������ʱ��ĳһ˲ʱƵ�ʵ���������ֵ�������������ź��и�Ƶ�ʵ����������ܷ�ֵ�������߼����ߵĸ߶�
%%%�ӱ߼����Ͽ��Կ����ź�Ƶ�ʷֲ�����ʵ���

fs=1;
aaa=zeros(length(size(im,1)));
for kkk=1:size(im,1)
    aaa(kkk)=sum(im(kkk,:))*1/fs;
end

figure;
plot(N*ff(1,:),aaa);%��һ��Ƶ�ʳ��ڲ���Ƶ�ʾ�����ʵƵ��,NΪ����Ƶ��
axis tight;
title('�߼���');%��ʾÿ��Ƶ�ʵ������
xlabel('Ƶ��');ylabel('��ֵ');
axis([0,sampFreq/4,0,1000]);%�����������ȡֵ��Χ
%}
%{
%==================================================================================
% �����grapher��surfer�ø�ʽ�����ڻ�ͼ
Sig_length=length(x);
disp('���ڱ��汾��ģ̬�������ݡ���');

% ����ÿһ�ױ���ģ̬������IMF����.dat��ʽ=======
filename1='��һ�ױ���ģ̬����(IMF1).dat';  % ������Ҫ���һ���ļ���
rdxn1=imf(1,:); % ������Ҫ���һ���ļ���
fidD1=fopen(filename1,'wt');

for i=1:Sig_length
    fprintf(fidD1,'%.4f    %.6f',t(i),rdxn1(i)); 
    fprintf(fidD1,'\n');  % ����
end
fclose(fidD1);
disp('����ģ̬�������ݱ�����ɣ�');

% �߽��ױ���===================
disp('������߼������ݡ���');

filename2='�߽���.dat';  
rdxn2=ff(1,:); 
fidD2=fopen(filename2,'wt');

bianji_length=length(ff(1,:));
for j=1:bianji_length
    fprintf(fidD2,'%.4f    %.6f',Sig_length*rdxn2(j),aaa(j)); % Sig_lengthΪԭʼ�źų��ȣ�Ҳ����N
    fprintf(fidD2,'\n');  % ����
end
fclose(fidD2);
disp('�߼������ݱ�����ɣ�');
%}
%{
% ����hilber��===============
% ����һ

disp('������ϣ�����������ݡ���');

[yn,xn]=size(IM);

YN=yn/4;  % xiugai
XN=xn;
% ����Zֵ����ֵ����Сֵ
M=zeros(XN*YN,1);
k=1;
for i0=1:YN
    for j0=1:XN
        if IM(i0,j0)==-Inf
            IM(i0,j0)=0;
        end
        M(k)=IM(i0,j0);
        k=k+1;
    end
end
Z_MAX=max(M);
Z_MIN=min(M);

%XX=[0,(1/sampFreq)*N];
X_MAX=max(T);
X_MIN=min(T);

YY=[0,sampFreq]; % sampFreq ����Ƶ��  xiugai
Y_MAX=max(YY);
Y_MIN=min(YY);

filename3='ϣ��������.grd';
fidD3=fopen(filename3,'wt');
fprintf(fidD3,'%s','DSAA');
fprintf(fidD3,'\n');
fprintf(fidD3,'%d  %d',XN,YN);
fprintf(fidD3,'\n');
fprintf(fidD3,'%f  %f',X_MIN,X_MAX);
fprintf(fidD3,'\n');
fprintf(fidD3,'%f  %f',Y_MIN,Y_MAX);
fprintf(fidD3,'\n');
fprintf(fidD3,'%f  ',Z_MIN,Z_MAX);
fprintf(fidD3,'\n');

for i1=1:YN   %
    for j1=1:XN
        fprintf(fidD3,'%f  ',IM(i1,j1));
    end
    fprintf(fidD3,'\n');
end
fclose(fidD3);
disp('ϣ�����������ݱ�����ɣ�');
%}

%{
% ������  �����dat��ʽ��������
[YN,XN]=size(IM);

% ����Zֵ����ֵ����Сֵ
M=zeros(XN*YN,1);
for i0=1:YN
    for j0=1:XN
        if IM(i0,j0)==-Inf
            IM(i0,j0)=0;
        end
    end
end
% x,y����ʸ����
XX=linspace(0,(1/sampFreq)*N,XN);
YY=linspace(0,0.5*sampFreq,YN);
xx=XX;
yy=YY;

filename3='ϣ��������.dat';  
fidD3=fopen(filename3,'wt');


for i1=1:XN
    for j1=1:YN
        fprintf(fidD3,'%.4f    %.6f    %.6f',xx(i1),yy(j1),IM(j1,i1)); % Sig_lengthΪԭʼ�źų��ȣ�Ҳ����N
    end
    fprintf(fidD3,'\n');  % ����
end
fclose(fidD3);
%}










