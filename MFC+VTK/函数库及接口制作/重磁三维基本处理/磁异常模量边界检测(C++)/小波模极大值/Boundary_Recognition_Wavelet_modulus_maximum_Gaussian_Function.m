
clear; 
clc;

%����С��ģ����ֵ����λ���߽�ʶ����ȡ���Խṹ
% 1 ʲô��ģ����ֵ��һ���źŵ���Ҫ��Ϣ���ɹյ㣨���׵���Ϊ��ĵ㣩ȷ����������������Ӱ�죬ֱ����յ���Ȼ���ѡ����ǣ�������һ�׵�����ģ�ļ���ֵ��
% 
% 2 ʲô��С��ģ����ֵ�������Ƚ�С��������ԭ�źž��������С���任����Ȼ��Խ��ȡģ������ҵ�����ֵ���������裬Ҳ�͵ȼ��ڣ��Ȱ�ĳһ�⻬�����󵼣��󵼺��������Ϊ���������ΪС����������Ȼ����Դ�źţ�����ȡģ������ּ���ֵ��
% 
% 3 ͼ����Ĳ�����
% 
%     a������ĳһ�߶ȣ������ά��˹��Phi_y������x����y����ĵ���Phi_x,�����������͵ȼ���С��������
% 
%     b����Phi_x,Phi_y�ֱ���ͼ�����õ�Gx��Gy��
% 
%     c�����ÿһ�����ص���ݶȴ�СG=(Gx*Gx+Gy*Gy).^(1/2)���÷��������ݶȷ�����߳Ʒ���atan(Gy/Gx)�����ע����Ƿ�����ֻ�����һ�������޵ĽǶȣ���������Ҫ�ֱ�����GxΪһ����С����ֵʱ��ҲҪ����
% 
%     d������÷��ǣ��ֳ����ַ��򡣵�һ��0��180����ˮƽ�����ڶ���90��270���򣨴�ֱ����������45��225�������Խ��ߣ���������135��315���򣨸��Խ��ߣ���Ҳ����˵��������������ǵĴ�С��������ĸ�������ӽ���
% 
%     e�����μ��ÿһ�����ص㣬����������Ӧ��������ӽ��ķ����ϡ��Ƿ��Ǽ���ֵ������ǣ���¼���ݶ�ֵ�������ǣ����ݶ�ֵ���㡣
% 
%     f���ҵ���¼�ݶ�ֵ�е����ֵ��Ȼ���Ը�ֵ����һ�����Ƚ�ÿһ�����ع�һ�����ݶ�ֵ�������ݶ�ֵ����ĳ����ֵ��ʱ�򣬾���������Ե��������Ϊ��α��Ե��
% 
% 4 ʵ��������㷨��canny���ӱ����ϵȼ۵ġ������������ع�canny���˾����ԭ����������Ե��ȡ��Ŀ�굽����ʲô��
% 
%     a���õļ�����ܡ���©����ʵ��Ե��Ҳ���ѷǱ�Ե����Ϊ��Ե������ʹ�������������
% 
%     b���õĶ�λ���ܡ���⵽�ı�Ե����ʵ�ʱ�Ե��λ�������
% 
%     c��Ψһ�ԡ����ڵ�����Ե�����һ����Ӧ��

tic;
filename='�ֲ��쳣.grd'; %��ȡ�ļ�
fname=filename(1:size(filename,2)-4);

% �򿪲���ȡGRD�ļ�
[XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Z_MIN,Z_MAX,data]=open_grd(filename);

[SIZE_Y,SIZE_X]=size(data);% ��ȡ�źŴ�С
X_grd= (X_MAX-X_MIN)/(XN-1); % x������
Y_grd= (Y_MAX-Y_MIN)/(YN-1); % y������

% ���޸Ĳ�����
% m ; �˲�������N; ��ֵ��threshold

% ��λ���߽�ʶ���У�m,N���趨ĳһ�̶�����ֵ��ֻ��ı���ֵthreshold����ֵ

% ��߶�
m=0;               % �״�,�ɾ������ԣ�����ֵ�ɱ��ֲ���
delta=2^m;

% �����˹����x,y����ƫ��
N=20;  % �˲������ȣ���Ҫ������������ż��������̫��
A=-1/sqrt(2*pi);  % ����
phi_x=zeros(N,N);
phi_y=zeros(N,N);
for index_y=1:N;
    for index_x=1:N;
        x=index_x-(N+1)/2;
        y=index_y-(N+1)/2;
        phi_x(index_x,index_y)=A*(x/delta^2).*exp(-(x.*x+y.*y)/(2*delta^2));%��xƫ��
        phi_y(index_x,index_y)=A*(y/delta^2).*exp(-(x.*x+y.*y)/(2*delta^2));%��yƫ��
    end
end;

phi_x=phi_x/norm(phi_x);  %  ������һ��
phi_y=phi_y/norm(phi_y);  %  ������һ��

%  �Զ�ά�ź������о��
Gx=conv2(data,phi_x,'same');
Gy=conv2(data,phi_y,'same');% ����"same"���ض�ά����������data��С��ͬ�Ĳ���
%"full"���ض�ά�����ȫ�����
%"valid"�����ھ�������У�δʹ�ñ�Ե�� 0 ���ֽ��м���ľ��������֣�
%�� size(A)>size(B) ʱ��size(C)=[Ma-Mb+1,Na-Nb+1].

% ���ݶ�
Grads=zeros(SIZE_Y,SIZE_X);
for i0=1:SIZE_Y
    for j0=1:SIZE_X
          Grads(i0,j0)=sqrt((Gx(i0,j0)*Gx(i0,j0))+(Gy(i0,j0)*Gy(i0,j0)));
    end
end
M=fix(Grads);% ���ڻ��ֱ��ͼ�Ĳ����������õ������С��ֵ

% ����ǣ��ݶȷ���
angle_array=zeros(SIZE_X,SIZE_Y);  %  �Ƕ�

for i=1:SIZE_Y;
    for j=1:SIZE_X
        if (abs(Gx(i,j))>eps*100)  %  x�ľ���ֵ�㹻��
            p=atan(Gy(i,j)/Gx(i,j))*180/pi;  %  ��������Ƕ�ֵ(1,4����)
            if (p<0)        %  ���ķ��ǣ�4���ޣ�
                p=p+360;
            end;
            if (Gx(i,j)<0 && p>180)     %  2���޵����⴦��
                p=p-180;
            elseif (Gx(i,j)<0 && p<180) %  3���޵����⴦��
                p=p+180;
            end
        else  %  90��270��
            p=90;
        end
        angle_array(i,j)=p;  %  ���Ǹ�ֵ
    end
end;

% �ұ�Ե
edge_array=zeros(SIZE_Y,SIZE_X);

% ����,�����ݶȷ�����С���任ϵ��ģ�ľֲ�����ֵ��
for i=2:SIZE_Y-1
    for j=2:SIZE_X-1
        if ((angle_array(i,j)>=(-22.5) && angle_array(i,j)<=22.5) || ...
            (angle_array(i,j)>=(180-22.5) && angle_array(i,j)<=(180+22.5)))     %  0/180
            if (Grads(i,j)>Grads(i+1,j) && Grads(i,j)>Grads(i-1,j))
                edge_array(i,j)=Grads(i,j);
            end
        elseif ((angle_array(i,j)>=(90-22.5) && angle_array(i,j)<=(90+22.5)) || ...
                (angle_array(i,j)>=(270-22.5) && angle_array(i,j)<=(270+22.5))) %  90/270
            if (Grads(i,j)>Grads(i,j+1) && Grads(i,j)>Grads(i,j-1))
                edge_array(i,j)=Grads(i,j);
            end
        elseif ((angle_array(i,j)>=(45-22.5) && angle_array(i,j)<=(45+22.5)) || ...
                (angle_array(i,j)>=(225-22.5) && angle_array(i,j)<=(225+22.5))) %  45/225
            if (Grads(i,j)>Grads(i+1,j+1) && Grads(i,j)>Grads(i-1,j-1))
                edge_array(i,j)=Grads(i,j);
            end
        else  %  135/215
            if (Grads(i,j)>Grads(i+1,j-1) && Grads(i,j)>Grads(i-1,j+1))
                edge_array(i,j)=Grads(i,j);
            end
        end
    end
end

% ȥ��α��Ե
MAX_E=max(max(edge_array).');     % ������ֵ
edge_array=edge_array/MAX_E;      % ��һ��

% ����ֱ��ͼ��ȡ�ߵ���ֵ ͬcanny��������
count=0;% �ۼ�ֱ��ͼͳ�ƿ����Ǳ�Ե��ĸ���
NUM=2048;
hist=zeros(1,NUM);
for k1=1:SIZE_Y
    for k2=1:SIZE_X
        if (edge_array(k1,k2)~=0)
            hist(1,M(k1,k2)+1)=hist(1,M(k1,k2)+1)+1;
            count=count+1;
        end
    end
end
for k3=1:NUM
    if hist(1,k3)~=0
        nmaxmag=k3;
    end
end
p=0.7;
dot=ceil(p*count);
k4=1;
nedgenb=hist(1,1);
while (k4<(nmaxmag-1)&&(nedgenb<dot))
    k4=k4+1;
    nedgenb=nedgenb+hist(1,k4);
end
k41=k4/50; % Ҫ��ø���ϸ����Ϣ���ɽ���ĸ��ֵ����
MAX_threshold=k41;                                       % ����ֵ
MIN_threshold=0.4*MAX_threshold;                         % ����ֵ,һ���Ϊ�͵�2.5��

% ������Ե���ж�
for i5=1:SIZE_Y
    for j5=1:SIZE_X
        if (edge_array(i5,j5)>=MAX_threshold)                 % ���ڸ���ֵһ���Ǳ�Ե
            edge_array(i5,j5)=1;
        elseif (edge_array(i5,j5)<=MIN_threshold)              % ���ڵ���ֵһ�����Ǳ�Ե
            edge_array(i5,j5)=0;
        else                                   % �ߵ���ֵ֮���ж�8�����Ƿ������ֵ�����Ǳ�Ե
            if((edge_array(i5-1,j5)>MAX_threshold)&&(edge_array(i5,j5-1)>MAX_threshold)&&(edge_array(i5+1,j5)>=MAX_threshold)&&(edge_array(i5,j5+1)>=MAX_threshold)...
                    &&(edge_array(i5-1,j5-1)>MAX_threshold)&&(edge_array(i5+1,j5-1)>MAX_threshold)&&(edge_array(i5-1,j5+1)>MAX_threshold)&&(edge_array(i5+1,j5+1)>MAX_threshold))
               edge_array(i5,j5)=1;
            else
               edge_array(i5,j5)=0;
            end
        end
    end
end

% ͼ���ϡ��·�ת
edge_array_new=zeros(SIZE_Y,SIZE_X);
for i0=1:SIZE_Y
    for j0=1:SIZE_X
         edge_array_new(i0,j0)=edge_array(SIZE_Y-i0+1,j0);         
    end        
end

%ͼ����ʾ
figure;
imshow(edge_array_new);
title(strcat('С��ģ����ֵ�߽�ʶ����','��','��ֵ','threshold=',num2str(MIN_threshold),'-',num2str(MAX_threshold),'��'));

%{
% ����GRD����
Z_MIN_NEW=min(min(edge_array_new));
Z_MAX_NEW=max(max(edge_array_new));
%filename1=strcat(fname,'_Boundary_Recognition_Wavelet_modulus_maximum','_threshold=',num2str(MIN_threshold),'-',num2str(MAX_threshold),'.grd');
filename1=strcat(fname,'_threshold=',num2str(MIN_threshold),'-',num2str(MAX_threshold),'.grd');
save_grd(filename1,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Z_MIN_NEW,Z_MAX_NEW,edge_array_new);
%}
% ����.dat���ݣ�����ֵΪ1�ı߽��ȫ�����棩
filename2=strcat(fname,'_�߽�λ��','.dat'); 
fidD=fopen(filename2,'wt'); 
for m=1:SIZE_Y
    for n=1:SIZE_X
        if edge_array(m,n)==1
            fprintf(fidD,'%.6f   %.6f   %.2f',(X_MIN+(n-1)*X_grd),(Y_MIN+(m-1)*Y_grd),edge_array(m,n));
            fprintf(fidD,'\n');
        end
    end
end      
fclose(fidD);
%}
toc;
