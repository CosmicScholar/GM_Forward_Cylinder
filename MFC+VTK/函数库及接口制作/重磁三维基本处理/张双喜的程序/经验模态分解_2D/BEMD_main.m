
clear ;
clc;

% ���ö�ά����ģ̬�ֽ���ж�߶ȷֽ⡢λ������
tic;      % tic toc����������������ʱ��
filename='���������ģ��_with_noise_2.5%.grd'; % ��ȡ�ļ�
fname=filename(1:size(filename,2)-4);% size(filename,2)��ʾ2ά���ݵĳ��ȣ�size(filename,2)-4���ǳ�ȥ.grd���ļ���
[XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Z_MIN,Z_MAX,data]=open_grd(filename);% ��ȡ��������
[ imf_matrix residue YuZhi] = bemd(data);% bemd�ֽ�
M=size(imf_matrix);% ����ֵΪ[57,100,5];����YNΪ57������XNΪ100���ֽ�״�KΪ5
N=M(3);% �ֽ�״�

%  �ֽ�ĸ��״�ϸ�ڣ�����ģ̬����BIMF��
for i=1:(N-1)
filename=strcat(fname,'_��=',num2str(YuZhi),'_BIMF_','D',int2str(i),'.grd'); % 'D'��ʾϸ��Datail
z=(imf_matrix(:,:,i));
zmax=max(z(:));
zmin=min(z(:));
save_grd(filename,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,zmin,zmax ,imf_matrix(:,:,i));
end
%  �ֽ�ĸ��״αƽ�
for j=2:N  % �ֽ�һ�κ����ʣ���źţ�                    
filename=strcat(fname,'_��=',num2str(YuZhi),'_BIMF_','A',int2str(j-1),'.grd'); %��A����ʾApproximate
z1=(residue(:,:,j));
zmax1=max(z1(:));
zmin1=min(z1(:));
save_grd(filename,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,zmin1,zmax1 ,residue(:,:,j));
end  

%
% �Ը�ģ̬���������ع�ʵ�ֳַ�
% ���ֽ�õ���ǰK���쳣���е��ӣ����ӽ����Ϊ�ֲ��쳣
Num1=3; 
filename1=strcat(fname,'_','��=',num2str(YuZhi),'�ֲ��쳣��','BIMF1','��','BIMF',int2str(Num1),'��','.grd');
Z1=zeros(YN,XN);% ����YN��XN�е�������

for i1=1:Num1
    Z1=Z1+(imf_matrix(:,:,i1));
end

%{
% ��ʣ����������ع������ӽ����Ϊ�����쳣
zmax=max(Z1(:));
zmin=min(Z1(:));
save_grd(filename1,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,zmin,zmax,Z1);

Num2=Num1+1;
filename2=strcat(fname,'_','��=',num2str(YuZhi),'�����쳣��','BIMF',int2str(Num2),'��','BIMF',int2str(N),'��','.grd');
Z2=zeros(YN,XN);%����YN��XN�е�������
for j1=Num2:N
     Z2=Z2+(imf_matrix(:,:,j1));
end    
zmax=max(Z2(:));
zmin=min(Z2(:));
save_grd(filename2,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,zmin,zmax,Z2);
%}
toc;