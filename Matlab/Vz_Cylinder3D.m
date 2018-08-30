function [ Vz,x,y ] = Vz_Cylinder3D( Radius,Length,Density,CenterPosition,AxisRange,DXDY )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
%   有限长水平圆柱体重力位垂向一阶导数正演函数
%   输入参数：半径（m），长度（m），密度（g/cm3），中心位置 （x0,y0,D）,坐标范围（xmin,xmax,ymin,ymax）,点距线距(dx,dy)
%   输出参数：重力位——二维数组（）
%   郭志馗，中国地质大学（武汉），2014.12.31
%   zhikuiguo@live.cn

G=6.67*10^-11;
R=Radius;%半径
den=Density;%g/cm3
S=pi*R^2;
LinDen=den*S;%线密度
L=Length/2;
D=CenterPosition(3);%中心埋深
y0=CenterPosition(2);%中心水平位置y
x0=CenterPosition(1);%中心水平位置x
xmin=AxisRange(1);xmax=AxisRange(2);
ymin=AxisRange(3);ymax=AxisRange(4);
dx=DXDY(1);dy=DXDY(2);
x=xmin:dx:xmax;
y=ymin:dy:ymax;

for i=1:length(y)
    yy=y(i)-y0;
    for j=1:length(x)
        xx=x(j)-x0;
        Vz(i,j)=10^8*G*LinDen*D*((L-yy)/sqrt(xx^2+D^2+(L-yy)^2)+...
            (L+yy)/sqrt(xx^2+D^2+(L+yy)^2))/(xx^2+D^2);%重力异常mGal
    end
end

end
