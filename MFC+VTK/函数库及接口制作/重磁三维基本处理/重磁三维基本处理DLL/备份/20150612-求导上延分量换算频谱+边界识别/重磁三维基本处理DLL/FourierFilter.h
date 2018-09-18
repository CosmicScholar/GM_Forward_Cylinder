#include "GMDPS_proj.h"
#include <cmath>
#include "Ext.h"
#include "Filter.h"
#include "�ļ�����.h"
#include "FourierFilter_1D.h"
#include "��˹��Ԫ�ⷽ����.h"
//#include "ContinuationInSpace.h"
#include "GMQR.h"
#include "GMIV.h"
//������Ϣ
struct MESHINFO
{
	int M, N, L;		//x,y,z�����ϵ��������
	double dx, dy, dz;	//x,y,z�����ϵ�������
	double initx, inity, initz;	//��ʼ����
};

struct MODELINFO					//ģ���ʷ���Ϣ
{
	double initx, inity, initz;		//��ʼ����
	double dx, dy, dz;				//ģ��x,y,z����ļ��
	int M, N, L;						//X,Y,Z�����ϵ�ģ�͸���
	double z0;						//�۲���߶ȣ���ȼ�Ȩ�����е�z0
};

bool UpWardContinuation(double** OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double rph);
bool UpWardContinuation(double* OriginalData,double* TransData,const int rows,const int columns,const double dx,const double dy,const double rph);
bool ComponentTransProcess(double** OriginalData,double** TransData,const int rows,const int columns,const double dx,
						   const double dy,const double angle_I,const double angle_D,const int OriginalStyle,const int TransStyle);
bool DownWardContinuation_Tik(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double rph,const double TRP,double XiGeMe);
double AutoDownWardContinuation_Tik(double** OriginalData,double** TransData,const int rows,const int columns,
									const double dx,const double dy,const double rph,const double TRP,
									const double dTRP,const int kmax,const double XiGeMe);
bool DownWardContinuation_LandWeber(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double rph,const double a_Land,const double n_Land);
bool DownWardContinuation_Compensation(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double rph,const int kmax,const double TRP,const double XiGeMe);
bool PowerSpectrum(double** OriginalData,double* PowerSpectrumAmp,int mr,const int rows,const int columns,const double dx,const double dy);
bool InitFFT(GridDataInfo datainfo,int& m1,int& me,int& n1,int& ne);
bool SolveEquation(double** A,double* X,double* B,int rows,int columns);
double SelectFrequenceSegment(double* PSA,double DX,int mr,double df,double fstart,double fend,char* path);
double EquivalentLayerModel(double* PSA,int mr,double* S,double* depth,double layernum,double df,char* path);
bool HorizontalGradient(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double Derivangle);
bool VerticalGradient(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy);
bool TitlAngle(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy);