function savegrd(xmin,xmax,ymin,ymax,z,filename)
%�������ܣ����������ļ�Ϊ.grd��ʽ
%����������x�������ֵ����Сֵ��y�������ֵ����Сֵ��z���ļ���
%savegrd(xmin,xmax,ymin,ymax,z,filename)
sizez=size(z);
h=sizez(1,1);
l=sizez(1,2);
str=strcat(filename,'.grd');
fid=fopen(str,'w');
cdumx='DSAA';
fprintf(fid,'%s\r\n',cdumx);
g_head=zeros(3,2);
g_head(1,1)=l;
g_head(1,2)=h;
g_head(2,1)=xmin;
g_head(2,2)=xmax;
g_head(3,1)=ymin;
g_head(3,2)=ymax;
for i=1:3
   fprintf(fid,'%d\r\t%d\r\n',g_head(i,:));
end
fprintf(fid,'%12.8f\r\t%12.8f\r\n',min(min(z)),max(max(z)));

str=['д��',filename,'.grd'];
w=waitbar(0,'1','name',str);

for j=1:1:h
    str=['����ɣ�',num2str(j*100/h),'%'];
    waitbar(j/h,w,str);
    for k=1:1:l
        fprintf(fid,'%12.8f ',z(j,k));
    end
    fprintf(fid,'\n');
end
fclose(fid);
close(w);