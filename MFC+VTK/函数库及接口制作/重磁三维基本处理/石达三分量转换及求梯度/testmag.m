

clear;
clc;

filename='��������쳣.grd';
% [h,l,ymin,ymax,xmin,xmax,zmin,zmax,z,dx,dy]=opengrd(filename);%��DeltaT�ļ�

I0=45;%�����شų�����
A0=0;
%���ú���
savepath='E:\Study\�ش����ݴ������ϵͳ����\����ģ�鼰ϵͳ\�����⼰�ӿ�����\�ش���ά��������\ʯ��������ת�������ݶ�';
cal_mag_trans_new_ext(filename,I0,A0,2,savepath,'grd',1);