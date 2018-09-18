
/////Proj.h



#include <cmath>
#include "Ext.h"
#include "Filter.h"
#include "�ļ�����.h"
#include "FourierFilter.h"
#include "FourierFilter_1D.h"
#include "��˹��Ԫ�ⷽ����.h"
//#include "ContinuationInSpace.h"
#include "GMQR.h"
#include "GMIV.h"

#ifndef proj
#define proj

//#define PI 3.1415926
#define GRAV_CONSTANT 6.667		//������������


//������Ϣ
//struct MESHINFO
//{
//	int M,N,L;		//x,y,z�����ϵ��������
//	double dx,dy,dz;	//x,y,z�����ϵ�������
//	double initx,inity,initz;	//��ʼ����
//};

//struct MODELINFO					//ģ���ʷ���Ϣ
//{
//	double initx,inity,initz;		//��ʼ����
//	double dx,dy,dz;				//ģ��x,y,z����ļ��
//	int M,N,L;						//X,Y,Z�����ϵ�ģ�͸���
//	double z0;						//�۲���߶ȣ���ȼ�Ȩ�����е�z0
//};
double arctg(double v);
//{
//	double ang;
//	if(v>=0)
//	{
//		ang=atan(v);
//	}
//	else if(v<0)
//	{
//		ang=atan(v)+3.1415926535897932384626433832795;
//	}
//	return ang;
//}
//////////////////////////////����GPUKernal.cu�еĺ���//////////////////////////////////////////////////
// declaration, forward
extern "C" 
	void GetGPUProperty();
extern "C"
	void GPU_GetAdk(int numElements,double* h_A,double* h_B,double* h_C,GridDataInfo datainfo);

#endif
////////////////////////////////////////////////////////////////////////////////