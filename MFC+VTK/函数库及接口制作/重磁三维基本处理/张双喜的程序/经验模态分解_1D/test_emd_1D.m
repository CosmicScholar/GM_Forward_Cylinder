
clear;
clc;
% ��ȡ�ı������ļ�

filename='model_two_TAHG.dat'; % ��ȡ�ļ���
fname=filename(1:size(filename,2)-4);
data=load(filename);
ts=data(:,1); % ��ȡ�ı���ȡ��1��
rdxn=data(:,2);

N=length(rdxn); % �źŵĳ���
D1=zeros(N,2); % �Ե�һ�׸�Ƶ���ٿռ�N��2�У�����ĵ�һ�����ڴ洢ʱ������
D2=zeros(N,2); % �ڶ��׸�Ƶ
D3=zeros(N,2); % �����׸�Ƶ
D4=zeros(N,2); % ���Ľ׸�Ƶ
A=zeros(N,2); % ���Ľ׵�Ƶ

% EMD�ֽ�
[imf,ort,nbits]=emd(rdxn);
imfsize=size(imf);
m=imfsize(1);% �ֽ�״�

figure(1);
plot(ts,rdxn,'k');title('ԭʼ�쳣');

figure(2);
newrdxn=rdxn';
for j=1:m
    subplot(m/2+1,2,j);plot(imf(j,:));% Ylabel('IMF');
     ylabel(sprintf('IMF%d', j));
    newrdxn=newrdxn-imf(j,:);
end

%{
% �ع��쳣
figure(3);
subplot(311)
plot(ts,rdxn,'b');
subplot(312)
plot(ts,imf(1,:)+imf(2,:)+imf(3,:),'b');
subplot(313)
plot(ts,imf(4,:)+imf(5,:),'b');
%}

for k=1:m
    t=imf(k,:);  
    for j=1:N
        NUM=k;
        switch NUM
            case 1
            D1(j,1)=ts(j);% �ļ��ĵ�һ�����ʱ������
            D1(j,2)=t(j);
            case 2
            D2(j,1)=ts(j);
            D2(j,2)=t(j);
            case 3
            D3(j,1)=ts(j);
            D3(j,2)=t(j);   
            case 4
            D4(j,1)=ts(j);
            D4(j,2)=t(j);  
            case 5
            A(j,1)=ts(j);
            A(j,2)=t(j);            
        end
    end
end


filename1=strcat(fname,'_EMD_1','.txt');
filename2=strcat(fname,'_EMD_2','.txt');
filename3=strcat(fname,'_EMD_3','.txt');
filename4=strcat(fname,'_EMD_4','.txt');
filename5=strcat(fname,'_EMD_5','.txt');

% �������ļ�����д���ļ� 
fidD1=fopen(filename1,'wt');
fidD2=fopen(filename2,'wt');
fidD3=fopen(filename3,'wt');
fidD4=fopen(filename4,'wt');
fidA=fopen(filename5,'wt');

% ���ı��д�������
disp('�ı�������̣�');
for j0=1:N
   disprog(j0,N,10); % �������� 10Ϊ��ʾ����
   for i0=1:2
       fprintf(fidD1,'%.4f   ',D1(j0,i0)); % ������λ��Ч����
       fprintf(fidD2,'%.4f   ',D2(j0,i0)); 
       fprintf(fidD3,'%.4f   ',D3(j0,i0));
       fprintf(fidD4,'%.4f   ',D4(j0,i0));
       fprintf(fidA,'%.4f   ',A(j0,i0)); 
   end
       % ÿ�������������л���
       fprintf(fidD1,'\n');
       fprintf(fidD2,'\n');
       fprintf(fidD3,'\n');
       fprintf(fidD4,'\n');
       fprintf(fidA,'\n');
end
fclose(fidD1);
fclose(fidD2);
fclose(fidD3);
fclose(fidD4);
fclose(fidA);


% ͼ����ʾ
%{
figure ;
subplot(611)
plot(ts,rdxn);
subplot(612);
plot(ts,D1(:,2));%1�׸�Ƶ
subplot(613);
plot(ts,D2(:,2));%2�׸�Ƶ
subplot(614);
plot(ts,D3(:,2));%3�׸�Ƶ
subplot(615);
plot(ts,D4(:,2));%4�׸�Ƶ
subplot(616);
plot(ts,A(:,2));%4�׵�Ƶ
%}

% �ع��쳣
%{
rdxn_new=imf(3,:)+imf(4,:)+imf(5,:);
%��������
filename7=strcat(fname,'_����ģ̬�ֽ�(EMD)_(3+4+5)','.txt');
fidD7=fopen(filename7,'wt');
 
for m=1:N
       fprintf(fidD7,'%.4f   %.6f',ts(m),rdxn_new(m));%������λ��Ч����
       fprintf(fidD7,'\n');
end      
fclose(fidD7);
%}

figure ;
subplot(211)
plot(ts,rdxn);title('ԭʼ�ź�');
subplot(212)
plot(ts,imf(4,:)+imf(5,:));title('ȥ�����ź�');

%{
figure ;
plot(ts,rdxn,'k',ts,rdxn_new,'r');title('ԭʼ�ź�');
%}











