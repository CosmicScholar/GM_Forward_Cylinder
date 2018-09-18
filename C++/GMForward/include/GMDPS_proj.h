
//�ش����ݴ���ϵͳ�õ��Ĺ��������ݽṹ��ͷ�ļ���

#ifndef GMDPS_PROJ
#define GMDPS_PROJ

//#include <comdef.h>
#include "math.h"
#include <afx.h>
#include <atlstr.h>
#include <windows.h>
#include <vector>
using namespace std;

//���峣��
#define G 6.67E-11
#define PI 3.1415926535897932384626433832795
#define U0 (4.0*PI*1E-7)
#define EPS 1E-10
//------------------------------------------���ݽṹ����------------------------------------------------------------
//���߷���
#define EXTENBOUNDARY_COS	0		//����˥����0����
#define EXTENBOUNDARY_MinCurvature	1	//��С��������
#define EXTENBOUNDARY_Poly	2		//�ֲ�����ʽ����


//����ԭʼ�������ͺ�ת����������
#define MAG_ORIGINAL_DT	0
#define MAG_ORIGINAL_DZ	1

#define MAG_TRANS_DX	0
#define MAG_TRANS_DY	1
#define MAG_TRANS_DZ	2
#define MAG_TRANS_GRAV	3
#define MAG_TRANS_MODULE_Ta	4
#define MAG_TRANS_MODULE_R	5
#define MAG_TRANS_MODULE_E	6
#define MAG_TRANS_MODULE_Q	7
#define MAG_TRANS_MODULE_L	8

//���ݴ����ų�����������Ϣ���ݽṹ��
struct MagneticComponentTransStruct
{
	int OriginDataType, TransDataType;			//ԭʼ�������ͣ���ת����������
	double MagAngle_D_Earth, MagAngle_I_Earth;//�ش�ƫ�Ǻ���ǣ��ȣ�
};
//���ݴ�����������Ϣ�ṹ��
#define DERIVATIVE_NORTH	3
#define DERIVATIVE_EAST	2
#define DERIVATIVE_VERTICAL1	0
#define DERIVATIVE_VERTICAL2	1
#define DERIVATIVE_HORIZONTAL	4
struct DerivativeInfoStruct
{
	int DerivativeType;			//������
	int DerivativeOrder;		//�󵼽���
	double aerfa;				//�󵼷�����X�ᣨ����������ļн�
};
//��ά�ش�������
/*ʹ�������֮ǰ������г�ʼ����Ȼ������push������Ϊdata��ֵ*/
class CGM_GRDDATA
{
public:
	CGM_GRDDATA()
	{
		m_number_x = 0;
		m_number_y = 0;
		height_data = 0;
		for (int i = 0; i < 6; i++)
		{
			m_bounds[i] = 0;
		}
		m_data = new double[m_number_y*m_number_x];
	};
	~CGM_GRDDATA()
	{
		
	};

private:
	double* m_data;
	double m_bounds[6];
	int m_number_x, m_number_y;
	double height_data;//�������ڸ߶ȣ��۲�߶ȣ�z������Ϊ����
public:
	int Initialize(int number_x, int number_y, double* bounds)
	{
		/*�����ͷ��ϵ�ָ��*/
		if (m_data)
		{
			delete m_data;
		}
		/*Ϊ������ֵ*/
		m_number_x = number_x;
		m_number_y = number_y;
		for (int i = 0; i < 6; i++)
		{
			m_bounds[i] = bounds[i];
		}
		/*������������*/
		m_data = new double[number_y*number_x];
		return 0;
	}

	int SetData(int rows, int cols,double data)
	{
		m_data[rows*m_number_x+cols] = data;
		return 0;
	}
	int GetHeight()
	{
		return height_data;
	}
	double* GetBounds()
	{
		return m_bounds;
	}

	double* GetData()
	{
		return m_data;
	}

	int GetDimension(int& number_x, int& number_y)
	{
		number_x = m_number_x;
		number_y = m_number_y;
		return 0;
	}

	int Delete()
	{
		if (m_data)
		{
			delete m_data;
		}
		return 0;
	}
};
//��ά�ش�������Ϣ��ƽ��grd���ݣ���
class CGM_GRDDATAINFO
{
public:
	CGM_GRDDATAINFO()
	{
		m_AxisBounds[0]=0;
		m_AxisBounds[1]=1000;
		m_AxisBounds[2]=0;
		m_AxisBounds[3]=1200;
		m_AxisBounds[4]=-300;
		m_AxisBounds[5]=0;
		m_Ranges[0]=0;
		m_Ranges[1]=1;
		m_Number_x=128;
		m_Number_y=128;
		m_Height_data=0;
		UpdateDxDy();
	};
	~CGM_GRDDATAINFO(){};
public:
	char m_Discription[40];						//��¼����������ݵ��й����������磺����Vz-����-���� �ȵ�
	double m_AxisBounds[6];						//��¼xmin,xmax,ymin,ymax,zmin,zmax
	double m_Ranges[2];							//��¼������Сֵ�����ֵ
	double m_Height_data;							//���ݸ߶ȣ�һ��涨��������ϵ������Ϊ��
	double m_Dx,m_Dy;								//x��y����ļ��
private:
	int m_Number_x,m_Number_y;
public:
	int GetNumber_x()
	{
		//UpdateNumber();
		return m_Number_x;
	};
	int AutoGetNumber_x()
	{
		UpdateNumber();
		return m_Number_x;
	};
	int GetNumber_y()
	{
		//UpdateNumber();
		return m_Number_y;
	}
	int AutoGetNumber_y()
	{
		UpdateNumber();
		return m_Number_y;
	}
	void SetNumber(int number_x,int number_y)
	{
		m_Number_x=number_x;
		m_Number_y=number_y;
		UpdateDxDy();
	};
private:
	void UpdateNumber(void)
	{
		m_Number_x=(int)((m_AxisBounds[1]-m_AxisBounds[0])/m_Dx+1);
		m_Number_y=(int)((m_AxisBounds[3]-m_AxisBounds[2])/m_Dy+1);
		m_AxisBounds[1]=m_AxisBounds[0]+m_Dx*(m_Number_x-1);
		m_AxisBounds[3]=m_AxisBounds[2]+m_Dy*(m_Number_y-1);
	};
	void UpdateMax()
	{
		m_AxisBounds[1]=m_AxisBounds[0]+(m_Number_x-1)*m_Dx;
		m_AxisBounds[3]=m_AxisBounds[2]+(m_Number_y-1)*m_Dy;
	};
	void UpdateDxDy()
	{
		m_Dx=(m_AxisBounds[1]-m_AxisBounds[0])/(m_Number_x-1);
		m_Dy=(m_AxisBounds[3]-m_AxisBounds[2])/(m_Number_y-1);
	};

};

//�����С
struct MatrixSize
{
	int rows;
	int cols;
};


//---------------------------���õ�һЩ�����ĺ���---------------------------------------------------------------------
//Ϊһ����ά���鸳ֵΪ����
void Assign_Array2(double** data,int rows,int cols,int indata=0);
//���ź���
int Sign(double number);
//�����ά����
double** CreateArray2(int rows,int cols);
//�ͷŶ�ά�����ڴ�
void DeleteArray2(double** array2,int rows,int cols);
//��ȡ�������ݵ����ֵ��Сֵ
void GetGrdMinMax(double** data,CGM_GRDDATAINFO & grdinfo);

//M��N�������Nά����:C=AB
void Mat_Multiply(double* A,double* B,double* C,int rows,int cols);
//����֮��ľ���
double Distance(double* point1,double *point2,int dims);
double Length_Vector(double* vector0,const int dims);
//���������ֵ,��Сֵ
double GetMax(double* data,const int dims);
double GetMin(double* data,const int dims);
//�����ˣ���ά���꣩
double* Cross(double* a,double* b);
//�������ĵ��(��ά����)
double VectorDot(double *a,double *b,int dims=3);

#endif