function [XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Z_MIN,Z_MAX,data]=open_grd(filename)
%�򿪲���ȡGRD�ļ�
fid = fopen(filename,'r');
ID=fgets(fid); 
XN=fscanf(fid,'%d',1);%�����ļ�����
YN=fscanf(fid,'%d',1);%�����ļ�����
X_MIN=fscanf(fid,'%f',1);%x,y,z�ı任��Χ
X_MAX=fscanf(fid,'%f',1);
Y_MIN=fscanf(fid,'%f',1);
Y_MAX=fscanf(fid,'%f',1);
Z_MIN=fscanf(fid,'%f',1);
Z_MAX=fscanf(fid,'%f',1);
data=fscanf(fid,'%f',[XN,YN]);%���ٶ�ȡXN*YN��Ԫ��
data=data';
fclose(fid);