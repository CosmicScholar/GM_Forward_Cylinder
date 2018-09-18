function [h,l,xmin,xmax,ymin,ymax,zmin,zmax,z,dx,dy]=opengrd(filename)
%�������ܣ���grd�ļ������������Ϣ
%�������ز���Ϊ��������������x�������ֵ����Сֵ��y�������ֵ����Сֵ��z��Сֵ�����ֵ��z��dx,dy
%[h,l,xmin,xmax,ymin,ymax,zmin,zmax,z,dx,dy]=opengrd(filename)
str=strcat(filename,'.grd');
fidx=fopen(str,'r'); %�����άƽ��grd����
cdumx=fread(fidx,4,'uint8=>char')'; %��ȡ�ļ�ͷDSAA
fscanf(fidx,'\n');
l=fscanf(fidx,'%d',1);%��ȡ�������ݵ�x���������������,y���������������
fp=fseek(fidx,1,0);
h=fscanf(fidx,'%d',1);
fscanf(fidx,'\n');
xmin=fscanf(fidx,'%f',1);%��ȡx�������Сֵ�����ֵ
fseek(fidx,4,1);
xmax=fscanf(fidx,'%f',1);
fscanf(fidx,'\n');
ymin=fscanf(fidx,'%f',1);%��ȡy�������Сֵ�����ֵ
fseek(fidx,4,1);
ymax=fscanf(fidx,'%f',1);
fscanf(fidx,'\n');
zmin=fscanf(fidx,'%f',1);%��ȡz����Сֵ�����ֵ
fseek(fidx,4,1);
zmax=fscanf(fidx,'%f',1);
fscanf(fidx,'\n');
z=zeros(h,l);

fin=['����',filename,'.grd'];
w=waitbar(0,'1','name',fin);
for i=1:h
    str=['����ɣ�',num2str(i*100/h),'%'];
    waitbar(i/h,w,str);
   for m=1:l
     z(i,m)=fscanf(fidx,'%f',1);
     fseek(fidx,4,1);
   end
end
fclose(fidx);
dx=((xmax-xmin)/(l-1));
dy=((ymax-ymin)/(h-1));
close(w);