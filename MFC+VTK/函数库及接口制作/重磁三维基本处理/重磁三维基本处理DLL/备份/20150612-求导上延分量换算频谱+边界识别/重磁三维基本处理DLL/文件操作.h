
//#include "stdafx.h"
#include "vector"
using namespace std;

#ifndef FILE2
#define FILE2
typedef struct tagGridDataInfo
{
	char*	Description;							//���ݵ�����
	double	gridXmin, gridXmax, gridYmin, gridYmax;	//������Χ
	double	gridZmin, gridZmax;						//�쳣��ֵ��С�����
	double	deltX, deltY, ExGridX, ExGridY;			//�����㡢�߾�, �����Ĵ�С
	int		rows, columns, ExRows, ExColumns;		//���ݵ�����
	double	DirectProfile, DirectBaseline;			//�������ߡ����߷�λ��
	double	dTI0, dTD0;								//�شų���λ�ǣ���ǡ�ƫ�ǣ�
}GridDataInfo;


vector<double> ReadGrd(char* infile,GridDataInfo& datainfo);
void WriteGrd(char *filename,double* z,const int dataNumber,int m,int n,double xmin,double xmax,double ymin,double ymax);
void ReadDat(char* filename,vector<double>& x,vector<double>& y,double& dx);
void WriteDat(char* filename,vector<double> x,double* y);
void WriteDat(char* filename,const int datanum,double* x,double* y);
void WriteDat(char* filename,const int datanum,double xmin,double dx,double* y);
void WriteDat(char* filename,vector<double>x,vector<double> y);
void ShinkGrd(char* filename,const int ShinkXnum1,const int ShinkXnum2,const int ShinkYnum1,const int ShinkYnum2);

#endif