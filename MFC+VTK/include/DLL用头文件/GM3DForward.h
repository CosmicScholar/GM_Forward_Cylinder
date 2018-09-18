//��ʵ���ڣ������⼰�ӿ�����\�ش���ά����\�ش���ά����DLL Ŀ¼��
//���Ǹ�������dll�õ�ͷ�ļ�
//���򼸺�������ش���ά����

#include "GMDPS_proj.h"
#include "fftw3.h"
#ifndef REGULAR3DFORWARD
#define REGULAR3DFORWARD

#define GMDLL extern "C" _declspec(dllexport)


//���岻ͬ����ģ�͵ı�־ID
#define MODEL_global 1
#define MODEL_cylinder 2
#define MODEL_cube 3

//���岻ͬ����������
#define FORWARD_V 4
#define FORWARD_Vz 5
#define FORWARD_Vx 6
#define FORWARD_Vy 7
#define FORWARD_Vxx 8
#define FORWARD_Vxy 9
#define FORWARD_Vxz 10
#define FORWARD_Vyy 11
#define FORWARD_Vyz 12
#define FORWARD_Vzz 13
#define FORWARD_ERROR_Vxx	19
#define FORWARD_ERROR_Vxy	20
#define FORWARD_ERROR_Vxz	21
#define FORWARD_ERROR_Vyy	22
#define FORWARD_ERROR_Vyz	23
#define FORWARD_ERROR_Vzz	24
#define FORWARD_ERROR_Hax	25

#define FORWARD_Ta 14
#define FORWARD_Hax 15
#define FORWARD_Hay 16
#define FORWARD_Za 17
#define FORWARD_Module 18

//Բ����ģ�ͽṹ��
struct GM_CylinderInfo
{
	double Pos1[3];								//һ���˵�����꣨x��y��z��
	double Pos2[3];								//��һ���˵������(x,y,z)��pos1��pos2��ȫ��������Բ�����λ��
	double Radius;								//�뾶
	double Density;								//�ܶȣ���������ʱʹ��,��λ��k/cm3��
	double CiHuaLv,Angle_I,Angle_D;				//�Ż���,�Ż���ǣ��Ż�ƫ�ǣ��ŷ�����ʱʹ�ã���λ���ȣ�
	double Resolution;							//����vtk��ʾʱ��һ������
	COLORREF Color;								//����VTK��ʾ�ǵı���
};
//������ģ�ͽṹ��
struct GM_CubeInfo
{
	double bounds[6];							//�������귶Χ��xmin��xmax��ymin��ymax��zmin��zmax��z������Ϊ����
	double Density;								//�ܶȣ���������ʱʹ��
	double CiHuaLv,Angle_I,Angle_D;				//�Ż���,�Ż���ǣ��Ż�ƫ�ǣ��ŷ�����ʱʹ�ã���λ���ȣ�
	COLORREF Color;								//����VTK��ʾ�ǵı���
};

//����ģ�ͽṹ��
struct GM_GlobalInfo
{
	double Radius;								//�뾶
	double Center[3];							//����λ�ã�x0��y0��z0��z0�ľ���ֵҲ������������
	double Density;								//�ܶȣ���������ʱʹ��
	double CiHuaLv,Angle_I,Angle_D;				//�Ż���,�Ż���ǣ��Ż�ƫ�ǣ��ŷ�����ʱʹ�ã���λ���ȣ�
	double Resolution;							//����vtk��ʾʱ��һ������
	COLORREF Color;								//����VTK��ʾ�ǵı���
};

//���򼸺���ģ��
struct GM_RegularGeometryInfo
{
	CGM_GRDDATAINFO grddatainfo;				//�������ݵĽṹ�壬������������Ϣ������ϵ��Ϣ
	vector<GM_CylinderInfo> cylinder_vec;		//��¼Բ����ģ�Ͳ���������
	vector<GM_CubeInfo> cube_vec;				//��¼������ģ�Ͳ���������
	vector<GM_GlobalInfo> global_vec;			//��¼����ģ�Ͳ���������
};

//���򼸺���ģ�����ݽṹ��
struct RegularGeometry3DForward
{
	GM_RegularGeometryInfo model;						//ģ����ṹ����
	double EarthMag,EarthAngle_I,EarthAngle_D;			//��¼����ų��ʹ�ƫ�Ǽ�����ǣ����ݴŵ�ʱ��ʹ�ã���λ��nT,�ȣ�
};
/*-----------------------------------------------����������ģ��������ݹ���һ��---------------------------------------------------
	�����Vz��λΪmGal�������ݶȵ�λΪE
	����ģ����������ά���ݣ����ø�������ģ��������ݺ���
	���������grav-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ�����λmGal`m,mGal,mGal/m,mGal/m/m
          forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
          type-��ʾ���ݷ������ͣ�����FORWARD_Vz��ʾVz������
----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DRegularModel_grav(double** grav,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Vz);
GMDLL int _3DRegularModel_mag(double** mag,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Za);
GMDLL int _3DRegularModel_magT(double** mag,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Ta);

/*-----------------------------------------------�����Ǹ��ֹ�����������ݺ���------------------------------------------------------*/
/*------------------
	���޳�ˮƽԲ����
	----------------
	˵����ˮƽԲ�������Ĳ������Բ�������˵�ˣ����Ǳ���ģ�
	λ�ò���ֻ��Ҫ���������˵�����꼴�ɣ�������������Ҫ�ģ��뾶��Ҳ�Ǳ���ģ����ȿ��Բ��������ĵ�����Ҳ����Ҫ
------------------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------
	���޳�ˮƽԲ������������
	-------------------------
���������grav-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ�����λmGal`m,mGal,mGal/m,mGal/m/m
          forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
          type-��ʾ���ݷ������ͣ�����FORWARD_Vz��ʾVz������
-----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DHorizontalCylinder_grav(double** grav,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Vz);

/*
���޳�ˮƽԲ���������������
���������mag-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ���λ��nT
          forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
          type-��ʾ���ݷ������ͣ�����FORWARD_Ta��ʾdaiertaT������
-----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DHorizontalCylinder_mag(double** mag,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Za);

/*
���޳�ˮƽԲ�����Ta��ģ�������ݣ���Ҫ�������������ݺ�������λ��nT
���������mag-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ�
          forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
          type-��ʾ���ݷ������ͣ�����FORWARD_Ta��ʾdaiertaT������
-----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DHorizontalCylinder_magT(double** mag,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Ta);

/*----------------------------
	���޳�ֱ����ģ�͵��ش�����
	--------------------------
���������grav-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ�����λmGal`m,mGal,mGal/m,mGal/m/m
forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
type-��ʾ���ݷ������ͣ�����FORWARD_Vz��ʾVz������
-----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DFiniteVercicalLine_mag(double** mag, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Za);
GMDLL int _3DFiniteVercicalLine_grav(double** grav, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Vz);
GMDLL int _3DFiniteVercicalLine_magT(double** mag, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Ta);

/*----------------------------
���޳�ֱ��Բ����ģ�͵��ش�����
------------------------------
theta_num:0-2Pi�Ļ����ʷָ���
*/
//z������Ϊ�����۲������ڸ߶�����ڵ���֮����Ϊ��ֵ
GMDLL int _3DFiniteVercicalCylinder_grav(double** grav, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Vz, int theta_num = 100);
GMDLL int _3DFiniteVercicalCylinder_mag(double** mag, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Hax, int theta_num = 100);
GMDLL int _3DFiniteVercicalCylinder_magT(double** mag, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Ta, int theta_num = 100);
GMDLL int _3DFiniteCylinder_Grav(double** grav, RegularGeometry3DForward& forwardinfo0, int type = FORWARD_Vz, int theta_num = 100);
GMDLL int _3DFiniteCylinder_mag(double** mag, RegularGeometry3DForward& forwardinfo0, int type = FORWARD_Hax, int theta_num = 100);
GMDLL int _3DFiniteCylinder_magT(double** mag, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Ta, int theta_num = 100);
/*----------------------------
	���޳���б��ģ�͵��ش�����
	--------------------------
���������grav-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ�����λmGal`m,mGal,mGal/m,mGal/m/m
forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
type-��ʾ���ݷ������ͣ�����FORWARD_Vz��ʾVz������
-----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DFiniteLine_Grav(double** grav, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Vz);
GMDLL int _3DFiniteLine_mag(double** mag, RegularGeometry3DForward& forwardinfo, int type=FORWARD_Za);
GMDLL int _3DFiniteLine_magT(double** mag, RegularGeometry3DForward& forwardinfo, int type = FORWARD_Ta);
/*--------
	������
	------
	-------------------------------------------------------------------------------------------------------------------------------*/
/*
��������������
���������grav-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ�����λmGal`m,mGal,mGal/m,mGal/m/m
          forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
          type-��ʾ���ݷ������ͣ�����FORWARD_Vz��ʾVz������
-----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DCube_grav(double** grav,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Vz);

/*
�����������������
���������mag-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ���λ��nT
          forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
          type-��ʾ���ݷ������ͣ�����FORWARD_Ta��ʾdaiertaT������
-----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DCube_mag(double** mag,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Za);

/*
�������Ta��ģ�������ݣ���Ҫ�������������ݺ�������λ��nT
���������mag-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ�
          forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
          type-��ʾ���ݷ������ͣ�����FORWARD_Ta��ʾdaiertaT������
-----------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DCube_magT(double** mag,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Ta);

/*------
	����
	----
-------------------------------------------------------------------------------------------------------------------------------*/
/*
������������
���������grav-����������ݵĶ�ά���飨�ж�Ӧx���ж�Ӧy��00Ԫ�ض�Ӧx��y����С������ֵ��˳�ƣ�����λmGal`m,mGal,mGal/m,mGal/m/m
          forwardinfo-�������֮��Ĺ��ڹ۲�ϵͳ��ģ�Ͳ����Ľṹ����������������õ���ʽ��Ϊ�������ݺ����������ֵ�����ֵ����Сֵ
          type-��ʾ���ݷ������ͣ�����FORWARD_Vz��ʾVz������
-------------------------------------------------------------------------------------------------------------------------------*/
GMDLL int _3DGlobal_grav(double** grav,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Vz);
GMDLL int _3DGlobal_mag(double** mag,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Za);
GMDLL int _3DGlobal_magT(double** mag,RegularGeometry3DForward& forwardinfo,int type=FORWARD_Ta);


#endif