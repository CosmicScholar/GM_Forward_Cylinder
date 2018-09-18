//��ʵ���ڣ������⼰�ӿ�����\�ش���ά����\�ش���ά����DLL Ŀ¼��
//���Ǹ�������dll�õ�ͷ�ļ�

//�ش���ά���ݴ���

#include "GMDPS_proj.h"
#ifndef GM3DPROCESS
#define GM3DPROCESS

#define GMDLL extern "C" _declspec(dllexport)
namespace GM3DProcess
{
	/*-----------------------//
	����
	//------------------------*/
	/*����CGM_GRDDATA������������Ϣ���������������*/
	/*Orientation��ʾ�������ҷֱ�Ϊx����y����z����*/
	GMDLL int DerivativeX(CGM_GRDDATA indata, CGM_GRDDATA* processdata);
	GMDLL int DerivativeY(CGM_GRDDATA indata, CGM_GRDDATA* processdata);
	GMDLL int DerivativeHorizontal(CGM_GRDDATA indata, double* Orientation, CGM_GRDDATA* processdata);		//OrientationԪ�طֱ�Ϊcosx��cosy
	GMDLL int DerivativeHorizontal2(CGM_GRDDATA indata, double aerfa_x, CGM_GRDDATA* processdata);			//aerfa_x��ʾ�󵼷�����x������ļн�(˳ʱ��):��
	GMDLL int DerivativeVertical(CGM_GRDDATA indata, CGM_GRDDATA* processdata);
	GMDLL int Derivative(CGM_GRDDATA indata, double* Orientation, CGM_GRDDATA* processdata);				//OrientationԪ�طֱ�Ϊcosx��cosy��cosz
	GMDLL int Derivative2(CGM_GRDDATA indata, double* Angle, CGM_GRDDATA* processdata);						//AngleԪ�طֲ�Ϊƫ�Ǻ���ǣ��ȣ�
	
	/*-----------------------//
	Ƶ��
	//------------------------*/
	GMDLL int AmplitudeSpectrum(CGM_GRDDATA indata, CGM_GRDDATA* processdata);
	GMDLL double* MeanRadialPowerSpectrum(CGM_GRDDATA indata, int& frequenceNum);							//ƽ����������
	GMDLL int DeleteArray1D(double* array1d);

	/*-----------------------//
	����
	//------------------------*/
	GMDLL int UpwardContinuation(CGM_GRDDATA indata, double height, CGM_GRDDATA* processdata);				//height:���ظ߶ȣ�m��

	/*-----------------------//
	���쳣ת��
	//------------------------*/
	GMDLL int MagComponentTransT2X(CGM_GRDDATA indata, MagneticComponentTransStruct*, CGM_GRDDATA* processdata);//�����и�xy����ϵ�����⣬��������xy��Ӧ����
	GMDLL int MagComponentTransT2X_ext(CGM_GRDDATA indata, MagneticComponentTransStruct* magdatainfo, CGM_GRDDATA* processdata);//�������ڼ��������ߣ�ò�������⣬�Ժ����޸İ�
	GMDLL int MagComponentTransT2Y(CGM_GRDDATA indata, MagneticComponentTransStruct*, CGM_GRDDATA* processdata);//
	GMDLL int MagComponentTransT2Z(CGM_GRDDATA indata, MagneticComponentTransStruct*, CGM_GRDDATA* processdata);//
	//ģ��
	GMDLL int MagComponentTransT2Ta(CGM_GRDDATA indata, MagneticComponentTransStruct* magdatainfo, CGM_GRDDATA* processdata);
	GMDLL int MagComponentTransT2R(CGM_GRDDATA indata, MagneticComponentTransStruct* magdatainfo, CGM_GRDDATA* processdata);
	GMDLL int MagComponentTransT2E(CGM_GRDDATA indata, MagneticComponentTransStruct* magdatainfo, CGM_GRDDATA* processdata);
	GMDLL int MagComponentTransT2Q(CGM_GRDDATA indata, MagneticComponentTransStruct* magdatainfo, CGM_GRDDATA* processdata);
	GMDLL int MagComponentTransT2L(CGM_GRDDATA indata, MagneticComponentTransStruct* magdatainfo, CGM_GRDDATA* processdata);

	/*-----------------------//
	�߽�ʶ��
	//------------------------*/
	GMDLL int EdgeDetective_ImprovedTiltDerivative(CGM_GRDDATA indata, CGM_GRDDATA* processdata);//�Ľ���Tilt����

	/*-----------------------//
	����
	//------------------------*/
	GMDLL int ExtenBoundary(CGM_GRDDATA indata, CGM_GRDDATA* processdata, int method = EXTENBOUNDARY_COS);//processdata�ں���������г�ʼ����Ҳ����˵�Ѿ�֪��Ҫ���߶����ˣ��˺���ֻ����ֵ����
}


#endif