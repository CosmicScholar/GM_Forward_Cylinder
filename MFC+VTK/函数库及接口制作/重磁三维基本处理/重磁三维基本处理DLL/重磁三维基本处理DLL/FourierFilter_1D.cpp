
//#include "stdafx.h"
#include "proj.h"
#include "FourierFilter_1D.h"


/*=============================================
�������ܣ�Ƶ������һλλ��������������
������
	OriginalData/TransData������λ���������飻ת���������
	datanum�����ݸ���
	dx�����
	rph�����ظ߶�
=============================================*/
bool UpWardContinuation(double* OriginalData,double* TransData,const int datanum,const double dx,const double rph)
{

	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	h=-fabs(rph);
	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	//=====����=================================================================================================
	//pjg=(double)0;
	//pjg=(zr[0]+zr[n-1])/(double)2.;
	//
	//for(int j=(n-1);j>=0;j--)
	//{ 
	//	zr[j+nq]=zr[j]-pjg;
	//}

	//for(int j=0;j<nq;j++)
	//	{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
	//		zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
	//	}zr[n1-1]=zr[0];
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	//====================================
		for(int j=0;j<(n1/2);j++)
		{	
			v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
			w11=tp*(double)fabs(v1); w22=tp*(double)fabs((v2));
			AC11=AC22=(double)1;
			AC11*=(double)exp(w11*h); AC22*=(double)exp(w22*h);	
			zr[j]=zr[j]*AC11; zi[j]=zi[j]*AC11;
			zr[j1]=zr[j1]*AC22; zi[j1]=zi[j1]*AC22;
		}
	//����Ҷ��任
	fft1(zr,zi,ne,n1,1);
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
		TransData[j]=zr[j+nq];

	//����ָ��
	delete zr,zi;
	return true;
}


/*=============================================
�������ܣ�Ƶ������һλλ��������������(������ɢ���ұ任��
������
	OriginalData/TransData������λ���������飻ת���������
	datanum�����ݸ���
	dx�����
	rph�����ظ߶�
=============================================*/
bool UpWardContinuation_Dct(double* OriginalData,double* TransData,const int datanum,const double dx,const double rph)
{

	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	h=-fabs(rph);
	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	//=====����=================================================================================================
	//pjg=(double)0;
	//pjg=(zr[0]+zr[n-1])/(double)2.;
	//
	//for(int j=(n-1);j>=0;j--)
	//{ 
	//	zr[j+nq]=zr[j]-pjg;
	//}

	//for(int j=0;j<nq;j++)
	//	{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
	//		zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
	//	}zr[n1-1]=zr[0];
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//��ɢ���ұ任
	dct1(zr,zi,n1);
	//====================================
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		w11=tp*(double)fabs(v1); w22=tp*(double)fabs((v2));
		AC11=AC22=(double)1;
		AC11*=(double)exp(w11*h); AC22*=(double)exp(w22*h);	
		zi[j]=zi[j]*AC11/v1;
		zi[j1]=zi[j1]*AC22/v2;
	}
	//����Ҷ��任
	dct1(zi,zr,n1,false);
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
		TransData[j]=zr[j+nq];

	//����ָ��
	delete zr,zi;
	return true;
}

/*===============================================================================
�������ܣ�Ƶ������һλλ�����ݹ�һ�����ݶȣ���Ҫ���������ų������д��о���
������
	OriginalData/TransData������λ���������飻ת���������
	datanum�����ݸ���
	dx�����;
	HarmonicWaveNum:г����
	rph�����ظ߶�
===============================================================================*/
bool NormalFullGradient(double* OriginalData,double* TransData,const int datanum,const double dx,const double TRP,const double rph,int NormalizeType)
{
	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	h=fabs(rph);
	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	double* Vxzr=new double[n1],*Vxzi=new double[n1],*Vzzr=new double[n1],*Vzzi=new double[n1];
	double* Vzr=new double[n1],*Vzi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	//=====����=================================================================================================
	//pjg=(double)0;
	//pjg=(zr[0]+zr[n-1])/(double)2.;
	//
	//for(int j=(n-1);j>=0;j--)
	//{ 
	//	zr[j+nq]=zr[j]-pjg;
	//}

	//for(int j=0;j<nq;j++)
	//	{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
	//		zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
	//	}zr[n1-1]=zr[0];
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	//====================================
	double temp;
	double a=1;
	double x11,x22;
	double P=5;
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		x11=tp*(double)v1; x22=tp*(double)v2;
		w11=fabs(x11); w22=fabs(x22);
		AC11=AC22=(double)1;
		//AC11*=(double)pow(exp(-w11*h),P)*pow((4-exp(-w11*h)-2*cos(w11*h)),P); AC22*=(double)pow(exp(-w22*h),P)*pow((4-exp(-w22*h)-2*cos(w22*h)),P);//��ַ��������ػط�
		AC11*=(double)exp(-w11*h)/(exp(-2*w11*h)+TRP); AC22*=(double)exp(-w22*h)/(exp(-2*w22*h)+TRP);	
		////����x������������
		Vxzr[j]=-zi[j]*AC11*x11;Vxzi[j]=zr[j]*AC11*x11;
		Vxzr[j1]=-zi[j1]*AC22*x22;Vxzi[j1]=zr[j1]*AC22*x22;
		////����z������������
		Vzzr[j]=zr[j]*AC11*w11;Vzzi[j]=zi[j]*AC11*w11;
		Vzzr[j1]=zr[j1]*AC22*w22;Vzzi[j1]=zi[j1]*AC22*w22;
		//ֻ��������
		Vzr[j]=-zi[j]*AC11;Vxzi[j]=zr[j]*AC11;
		Vzi[j1]=-zi[j1]*AC22;Vxzi[j1]=zr[j1]*AC22;
	}
	//����Ҷ��任
	fft1(Vxzr,Vxzi,ne,n1,1);
	fft1(Vzzr,Vzzi,ne,n1,1);
	fft1(Vzr,Vzi,ne,n1,1);
	//..����
	for(int j=0;j<n;j++)
	{
		Vxzr[j]=/*Vzzr[j+nq]*1E4*/Vxzr[j+nq];
		Vzzr[j]=/*Vzzr[j+nq]*1E4*/Vzzr[j+nq];
	}
	//�����һ�����ݶ�
	double Gxz=0;
	double *GH=new double[n1],*GH0=new double[n1];
	for (int i = 0; i < n1; i++)
	{
		GH0[i]=sqrt(Vxzr[i]*Vxzr[i]+Vzzr[i]*Vzzr[i]);
		//GH0[i]=Vzr[i];
	}
	//===========���ڹ�һ��===============================
	/*int WindowSize=datanum/2;
	int HalfWindowSize=WindowSize/2;
	double GHmax;
	Gxz=0;
	GHmax=GH0[0];
	for (int j = 0; j < WindowSize; j++)
	{
		if (GHmax<GH0[j])
		{
			GHmax=GH0[j];
		}	
	}
	for (int i = 0; i < HalfWindowSize; i++)
	{
		GH[i]=GH0[i]/GHmax;
	}

	for (int i = 0; i < datanum-WindowSize; i++)
	{
		GHmax=GH0[i];
		for (int j = 0; j < WindowSize; j++)
		{
			if (GHmax<GH0[i+j])
			{
				GHmax=GH0[i+j];
			}	
		}
		GH[i+HalfWindowSize]=GH0[i+HalfWindowSize]/GHmax;
	}

	for (int j = datanum-HalfWindowSize; j < datanum; j++)
	{
		GH[j]=GH0[j]/GHmax;
	}*/
	//===================================================
	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz+=GH0[i];
	//}Gxz=Gxz/(n);//��ֵ
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================

	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz+=1.0/GH0[i];
	//}Gxz=n/Gxz;//
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================

	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz*=GH0[i];
	//}Gxz=pow(Gxz,1.0/n);//
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================
	switch (NormalizeType)
	{
	case 0:			//����ƽ����һ
		{
			for (int i = 0; i < n; i++)
			{
				Gxz+=GH0[i];
			}Gxz=Gxz/(n);//��ֵ
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}

		}
		break;
	case 1:		//��ֵ��һ
		{
			double* GH0sort=new double[datanum];
			for (int k = 0; k < datanum; k++)
			{
				GH0sort[k]=GH0[k];
			}
			Qsort(GH0sort,0,datanum-1);//����
			if (datanum%2==0)			//ȡ��ֵ
			{
				Gxz=(GH0sort[datanum/2]+GH0sort[datanum/2-1])/2.0;
			}else
			{
				Gxz=GH0sort[datanum/2];
			}
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
			delete GH0sort;
		}
		break;
	case 2:
		{
			for (int i = 0; i < n; i++)
			{
				Gxz+=1.0/GH0[i];
			}Gxz=n/Gxz;//
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
		}
	case 3:
		{
			for (int i = 0; i < n; i++)
			{
				Gxz*=GH0[i];
			}Gxz=pow(Gxz,1.0/n);//
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
		}
	default:
		{
			for (int i = 0; i < n; i++)
			{
				Gxz+=1.0/GH0[i];
			}Gxz=n/Gxz;//
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
		}
		break;
	}
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
	{
		TransData[j]=/*Vxzr[j]*1E4*/GH[j];
	}
	//����ָ��
	delete zr,zi,Vzzi,Vzzr,Vxzi,Vxzr,GH,GH0,Vzr,Vzi;
	return true;
}
/*=============================================
�������ܣ�Ƶ������һλλ�����ݹ�һ�����ݶȣ���Ҫ���������ų������д��о���
������
	OriginalData/TransData������λ���������飻ת���������(������originaldata��ͬ������Ϊ���������
	datanum�����ݸ���
	dx�����;
	HarmonicWaveNum_max:г�������ֵ����СֵĬ��Ϊ1��
	h2/dh/h1�������²�z���ꣻ���������ࣻ����z����
=============================================*/
bool NormalFullGradient(double* OriginalData,double* TransData,const int datanum,const double dx,const double TRP,const int hNum,const double dh,const double h1,int NormalizeType)
{
	double *GHdata=new double[datanum];
	double* TransData2=new double[datanum];
	double rph=0;
	double trptemp;
	for (int j = 0; j < hNum; j++)
	{
		trptemp=TRP/**(j+1)*/;
		rph=h1+dh*j;
		NormalFullGradient(OriginalData,GHdata,datanum,dx,trptemp,rph,NormalizeType);
		//================�������ڹ�һ��==============================
		int WinSize=20;
		
	//Separation_EntropyFilter(GHdata,TransData2,datanum,dx,WinSize);
	//=====================================================================
		for (int i = 0; i < datanum; i++)
		{
			TransData[j*datanum+i]=GHdata[i];
		}
	}
	delete GHdata,TransData2;
	return true;
}

/*=============================================
�������ܣ�̩�ռ�����������ȡ��һ�����ݶ�
������
	OriginalData/TransData������λ���������飻ת���������(������originaldata��ͬ������Ϊ���������
	datanum�����ݸ���
	dx�����;
	N/L/K��г������չ����������������
	h2/dh/h1�������²�z���ꣻ���������ࣻ����z����
=============================================*/
bool NormalFullGradient_TSI(double* OriginalData,double* TransData,const int datanum,const double dx,const int N,const int L,const int K,const double rph)
{
	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	h=fabs(rph);
	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	double* Vxzr=new double[n1],*Vxzi=new double[n1],*Vzzr=new double[n1],*Vzzi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	//=====����=================================================================================================
	//pjg=(double)0;
	//pjg=(zr[0]+zr[n-1])/(double)2.;
	//
	//for(int j=(n-1);j>=0;j--)
	//{ 
	//	zr[j+nq]=zr[j]-pjg;
	//}

	//for(int j=0;j<nq;j++)
	//	{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
	//		zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
	//	}zr[n1-1]=zr[0];
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	//====================================
	double pn1,pn2;
	double temp;
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		pn1=pow(sin(v1*en*PI/N)/(v1*en*PI/N),2);pn2=pow(sin(v2*en*PI/N)/(v2*en*PI/N),2);
		w11=tp*(double)fabs(v1); w22=tp*(double)fabs((v2));
		AC11=AC22=(double)1;
		AC11*=(double)exp(w11*pn1*h)*pow(1-exp(-w11*pn1*h),K+1); AC22*=(double)exp(w22*pn2*h)*pow(1-exp(-w22*pn2*h),K+1);	
		////����x������������
		temp=zr[j];Vxzr[j]=-zi[j]*AC11*w11;Vxzi[j]=temp*AC11*w22;
		temp=zr[j1];Vxzr[j1]=-zi[j1]*AC22*w11;Vxzi[j1]=temp*AC22*w22;
		////����z������������
		Vzzr[j]=zr[j]*AC11*w11;Vzzi[j]=zi[j]*AC11*w22;
		Vzzr[j1]=zr[j1]*AC22*w11;Vzzi[j1]=zi[j1]*AC22*w22;
	}
	//����Ҷ��任
	fft1(Vxzr,Vxzi,ne,n1,1);
	fft1(Vzzr,Vzzi,ne,n1,1);

	//�����һ�����ݶ�
	double Gxz=0;
	double *GH=new double[n1];
	for (int i = 0; i < n1; i++)
	{
		Gxz+=sqrt(Vxzr[i]*Vxzr[i]+Vzzr[i]*Vzzr[i]);
	}Gxz=Gxz/(n1);//��ֵ
	for (int i = 0; i < n1; i++)
	{
		GH[i]=sqrt(Vxzr[i]*Vxzr[i]+Vzzr[i]*Vzzr[i])/Gxz;
	}
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
		TransData[j]=GH[j+nq];

	//����ָ��
	delete zr,zi,Vzzi,Vzzr,Vxzi,Vxzr,GH;
	return true;
}
bool NormalFullGradient_TSI(double* OriginalData,double* TransData,const int datanum,const double dx,const int N,const int L,const int K,const int hNum,const double dh,const double h1)
{
	return true;
}


/*=============================================
�������ܣ�Ƶ������һλλ��������������-����ŵ������
������
	����λ���������飻ת���������
	datanum�����ݸ���
	dx�����
	rph�����ظ߶�
	TRP�����򻯲���
=============================================*/
bool DownWardContinuation_Tik(double* OriginalData,double* TransData,const int datanum,const double dx,const double rph,double TRP)
{

	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	h=fabs(rph);
	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	//=====����=================================================================================================
	//pjg=(double)0;
	//pjg=(zr[0]+zr[n-1])/(double)2.;
	//
	//for(int j=(n-1);j>=0;j--)
	//{ 
	//	zr[j+nq]=zr[j]-pjg;
	//}

	//for(int j=0;j<nq;j++)
	//	{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
	//		zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
	//	}zr[n1-1]=zr[0];
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	int nn=100;
	//====================================
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		w11=tp*(double)fabs(v1); w22=tp*(double)fabs((v2));
		AC11=AC22=(double)1;
		AC11*=(double)exp(-w11*h)/(exp(-2*w11*h)+TRP); AC22*=(double)exp(-w22*h)/(exp(-2*w22*h)+TRP);	
		//AC11*=(double)exp(w11*h)*(1-pow(TRP/exp(-2*w11*h)+TRP,nn)); AC22*=(double)exp(w22*h)*(1-pow(TRP/exp(-2*w22*h)+TRP,nn));	
		zr[j]=zr[j]*AC11; zi[j]=zi[j]*AC11;
		zr[j1]=zr[j1]*AC22; zi[j1]=zi[j1]*AC22;
	}
	//����Ҷ��任
	fft1(zr,zi,ne,n1,1);
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
		TransData[j]=zr[j+nq];

	//����ָ��
	delete zr,zi;
	return true;
}

/*=============================================
�������ܣ�Ƶ������һλλ������z����һ�׵���
������
	����λ���������飻ת���������
	datanum�����ݸ���
	dx�����
=============================================*/
bool Derivative_Z(double* OriginalData,double* TransData,const int datanum,const double dx)
{

	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,pjg,tp;
	double v1,v2;
	double x11,x22;
	int j1;

	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	for(int j=0;j<n1;j++)
	{ 
		zi[j]=(double)0; 
	}
	//=====����=================================================================================================

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	double temp;
	int order=1;
	//====================================
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		x11=tp*fabs(v1);x22=tp*fabs(v2);
		zr[j]=zr[j]*pow(x11,order); zi[j]=zi[j]*pow(x11,order);
		zr[j1]=zr[j1]*pow(x22,order); zi[j1]=zi[j1]*pow(x22,order);
	}
	//����Ҷ��任
	fft1(zr,zi,ne,n1,1);
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
		TransData[j]=zr[j+nq]*1E4;

	//����ָ��
	delete zr,zi;
	return true;
}

/*=============================================
�������ܣ�Ƶ������һλλ������x����һ�׵���
������
	����λ���������飻ת���������
	datanum�����ݸ���
	dx�����
=============================================*/
bool Derivative_X(double* OriginalData,double* TransData,const int datanum,const double dx,int Order)
{
	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,pjg,tp;
	double v1,v2;
	double x11,x22;
	int j1;

	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	for(int j=0;j<n1;j++)
	{ 
		zi[j]=(double)0; 
	}
	//=====����=================================================================================================

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	double temp;
	//====================================
	/*switch (Order%4)
	{
	case 1:
		{
			for(int j=0;j<(n1/2);j++)
			{	
				v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
				x11=pow(tp*v1,Order);x22=pow(tp*v2,Order);
				temp=zr[j];zr[j]=zi[j]*x11; zi[j]=temp*x11;
				temp=zr[j1];zr[j1]=zi[j1]*x22; zi[j1]=temp*x22;
			}
		}
		break;
	case 2:
		{
			for(int j=0;j<(n1/2);j++)
			{	
				v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
				x11=pow(tp*v1,Order);x22=pow(tp*v2,Order);
				temp=zr[j];zr[j]=zi[j]*x11; zi[j]=temp*x11;
				temp=zr[j1];zr[j1]=zi[j1]*x22; zi[j1]=temp*x22;
			}
		}
		break;
	case 0:
		{
			for(int j=0;j<(n1/2);j++)
			{	
				v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
				x11=pow(tp*v1,Order);x22=pow(tp*v2,Order);
				zr[j]=zi[j]*x11; zi[j]*=x11;
				zr[j1]=zi[j1]*x22; zi[j1]=zi[j1]*x22;
			}
		}
		break;
	default:
		break;
	}*/
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		x11=pow(tp*v1,Order);x22=pow(tp*v2,Order);
		temp=zr[j];zr[j]=-zi[j]*x11; zi[j]=temp*x11;
		temp=zr[j1];zr[j1]=-zi[j1]*x22; zi[j1]=temp*x22;
	}
	//����Ҷ��任
	fft1(zr,zi,ne,n1,1);
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
		TransData[j]=zr[j+nq]*1E4;

	//����ָ��
	delete zr,zi;
	return true;
}

/*=============================================
�������ܣ���ַ��������ػط��������ݳ�Դ���
������
	OriginalData/TransData������λ���������飻ת���������
	datanum�����ݸ���
	dx�����;
	P:�ط�����
	rph�����ظ߶�
	�ο����ף���Եȣ�1999���������쳣������˲���Ӧ��
=============================================*/
bool SourceDepthInversion(double* OriginalData,double* TransData,const int datanum,const double dx,const double P,const double rph)
{
	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	h=fabs(rph);
	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	//=====����=================================================================================================
	//pjg=(double)0;
	//pjg=(zr[0]+zr[n-1])/(double)2.;
	//
	//for(int j=(n-1);j>=0;j--)
	//{ 
	//	zr[j+nq]=zr[j]-pjg;
	//}

	//for(int j=0;j<nq;j++)
	//	{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
	//		zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
	//	}zr[n1-1]=zr[0];
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	//====================================
	double temp;
	double x11,x22;
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		x11=tp*(double)v1; x22=tp*(double)v2;
		w11=fabs(x11); w22=fabs(x22);
		AC11=AC22=(double)1;
		AC11*=(double)pow(exp(-w11*h),P)*pow((4-exp(-w11*h)-2*cos(w11*h)),P+1); AC22*=(double)pow(exp(-w22*h),P)*pow((4-exp(-w22*h)-2*cos(w22*h)),P+1);

		zr[j]=zr[j]*AC11;zi[j]=zi[j]*AC11;
		zr[j1]=zr[j1]*AC22;zi[j1]=zi[j1]*AC22;
	}
	//����Ҷ��任
	fft1(zr,zi,ne,n1,1);


	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
	{
		TransData[j]=/*Vxzr[j]*1E4*/zr[j+nq];
	}
	//����ָ��
	delete zr,zi;
	return true;
}

/*=============================================
�������ܣ���ַ���������
������
	OriginalData/TransData������λ���������飻ת���������(������originaldata��ͬ������Ϊ���������
	datanum�����ݸ���
	dx�����;
	HarmonicWaveNum_max:г�������ֵ����СֵĬ��Ϊ1��
	h2/dh/h1�������²�z���ꣻ���������ࣻ����z����
=============================================*/
bool SourceDepthInversion(double* OriginalData,double* TransData,const int datanum,const double dx,const double P,const int hNum,const double dh,const double h1)
{
	double *GHdata=new double[datanum];
	double rph=0;
	for (int j = 0; j < hNum; j++)
	{
		rph=h1+j*dh;
		SourceDepthInversion(OriginalData,GHdata,datanum,dx,P,rph);
		for (int i = 0; i < datanum; i++)
		{
			TransData[j*datanum+i]=GHdata[i];
		}
	}
	delete GHdata;
	return true;
}


/*=============================================
�������ܣ����������
������
	OriginalData/TransData������λ���������飻ת���������(������originaldata��ͬ������Ϊ���������
	datanum�����ݸ���
	dx�����;
	HarmonicWaveNum_max:г�������ֵ����СֵĬ��Ϊ1��
	h2/dh/h1�������²�z���ꣻ���������ࣻ����z����
=============================================*/
bool AmplitudeSpectrum(double* OriginalData,const int datanum,const double dx,char* outfilename)
{
	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	//Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);
	//=====����=================================================================================================
	pjg=(double)0;
	pjg=(zr[0]+zr[n-1])/(double)2.;
	
	for(int j=(n-1);j>=0;j--)
	{ 
		zr[j+nq]=zr[j]-pjg;
	}

	for(int j=0;j<nq;j++)
		{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
			zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
		}zr[n1-1]=zr[0];
	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	//fft1(zr,zi,ne,n1,1);
	//====================================
	double f=0,Amplitude;
	FILE* fp;
	if ((fp=fopen(outfilename,"w"))==NULL)
	{
		printf("��%sʧ��\n");
		return false;
	}
	for(int j=0;j<n1/2;j++)
	{
		f=j/en+1E-10; 
		Amplitude=sqrt(zr[j]*zr[j]+zi[j]*zi[j]);
		fprintf(fp,"%lf\t%lf\n",f,log(Amplitude));
	}fclose(fp);

	//����ָ��
	delete zr,zi;
	return true;
}

bool Derivative_X_space(double* OriginalData,double* TransData,const int datanum,const double dx,int Order)
{
	double *temptransdata=new double[datanum],*ExtensionData=new double[datanum];
	int extennum=datanum+20;
	int halfextennum=(extennum-datanum)/2;
	Extension_Polynomial_1D(OriginalData,ExtensionData,dx,datanum,extennum,2);
	for (int k = 0; k < Order; k++)
	{
		for (int i = 0; i < extennum-1; i++)
		{
			temptransdata[i]=(ExtensionData[i+1]-ExtensionData[i])/dx;
		}
		for (int i = 0; i < extennum-1; i++)
		{
			ExtensionData[i]=temptransdata[i];
		}
	}
	
	for (int i = 0; i < datanum; i++)
	{
		TransData[i]=temptransdata[i];
	}
	return true;
}

bool Derivative_Z(double* OriginalData,double* TransData,const int datanum,const double dx,const int hNum,const double dh,const double h1)
{
	double *GHdata=new double[datanum],*contidata=new double[datanum];
	double rph=0;
	for (int j = 0; j < hNum; j++)
	{
		rph=h1+j*dh;
		UpWardContinuation(OriginalData,contidata,datanum,dx,rph);
		//DownWardContinuation_Tik(OriginalData,contidata,datanum,dx,rph,0.001);
		//Derivative_Z(contidata,GHdata,datanum,dx);
		Derivative_X(contidata,GHdata,datanum,dx,1);
		for (int i = 0; i < datanum; i++)
		{
			TransData[j*datanum+i]=GHdata[i];
		}
	}
	delete GHdata;
	return true;
}

/*===============================================================================
�������ܣ�Ƶ������һλλ�����ݹ�һ����ǿ�Ľ����ź��������Ҫ���������ų������д��о���
������
	OriginalData/TransData������λ���������飻ת���������
	datanum�����ݸ���
	dx�����;
	HarmonicWaveNum:г����
	rph�����ظ߶�
===============================================================================*/
bool NormalEAS(double* OriginalData,double* TransData,const int datanum,const double dx,const double TRP,const double rph,int NormalizeType)
{
	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	h=fabs(rph);
	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	double* Vxzr=new double[n1],*Vxzi=new double[n1],*Vzzr=new double[n1],*Vzzi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	//=====����=================================================================================================
	//pjg=(double)0;
	//pjg=(zr[0]+zr[n-1])/(double)2.;
	//
	//for(int j=(n-1);j>=0;j--)
	//{ 
	//	zr[j+nq]=zr[j]-pjg;
	//}

	//for(int j=0;j<nq;j++)
	//	{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
	//		zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
	//	}zr[n1-1]=zr[0];
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	//====================================
	double temp;
	double x11,x22;
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		x11=tp*(double)v1; x22=tp*(double)v2;
		w11=fabs(x11); w22=fabs(x22);
		AC11=AC22=(double)1;
		AC11*=(double)exp(-w11*h)/(exp(-2*w11*h)+TRP); AC22*=(double)exp(-w22*h)/(exp(-2*w22*h)+TRP);	
		////����x������������
		temp=zr[j];Vxzr[j]=-zi[j]*AC11*x11*pow(w11,2);Vxzi[j]=temp*AC11*x11*pow(w11,2);
		temp=zr[j1];Vxzr[j1]=-zi[j1]*AC22*x22*pow(w22,2);Vxzi[j1]=temp*AC22*x22*pow(w22,2);
		////����z������������
		Vzzr[j]=zr[j]*AC11*w11;Vzzi[j]=zi[j]*AC11*w11;
		Vzzr[j1]=zr[j1]*AC22*w22;Vzzi[j1]=zi[j1]*AC22*w22;
	}
	//����Ҷ��任
	fft1(Vxzr,Vxzi,ne,n1,1);
	fft1(Vzzr,Vzzi,ne,n1,1);

	//..����
	for(int j=0;j<n;j++)
	{
		Vxzr[j]=/*Vzzr[j+nq]*1E4*/Vxzr[j+nq];
		Vzzr[j]=/*Vzzr[j+nq]*1E4*/Vzzr[j+nq];
	}
	//�����һ�����ݶ�
	double Gxz=0;
	double *GH=new double[n1],*GH0=new double[n1];
	for (int i = 0; i < n1; i++)
	{
		GH0[i]=sqrt(Vxzr[i]*Vxzr[i]+Vzzr[i]*Vzzr[i]);
	}
	//===========���ڹ�һ��===============================
	/*int WindowSize=datanum/2;
	int HalfWindowSize=WindowSize/2;
	double GHmax;
	Gxz=0;
	GHmax=GH0[0];
	for (int j = 0; j < WindowSize; j++)
	{
		if (GHmax<GH0[j])
		{
			GHmax=GH0[j];
		}	
	}
	for (int i = 0; i < HalfWindowSize; i++)
	{
		GH[i]=GH0[i]/GHmax;
	}

	for (int i = 0; i < datanum-WindowSize; i++)
	{
		GHmax=GH0[i];
		for (int j = 0; j < WindowSize; j++)
		{
			if (GHmax<GH0[i+j])
			{
				GHmax=GH0[i+j];
			}	
		}
		GH[i+HalfWindowSize]=GH0[i+HalfWindowSize]/GHmax;
	}

	for (int j = datanum-HalfWindowSize; j < datanum; j++)
	{
		GH[j]=GH0[j]/GHmax;
	}*/
	//===================================================
	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz+=GH0[i];
	//}Gxz=Gxz/(n);//��ֵ
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================

	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz+=1.0/GH0[i];
	//}Gxz=n/Gxz;//
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================

	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz*=GH0[i];
	//}Gxz=pow(Gxz,1.0/n);//
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================
	switch (NormalizeType)
	{
	case 0:			//����ƽ����һ
		{
			for (int i = 0; i < n; i++)
			{
				Gxz+=GH0[i];
			}Gxz=Gxz/(n);//��ֵ
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
		}
		break;
	case 1:		//����ƽ����һ
		{
			for (int i = 0; i < n; i++)
			{
				Gxz+=1.0/GH0[i];
			}Gxz=n/Gxz;//
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
		}
		break;
	default:
		{
			for (int i = 0; i < n; i++)
			{
				Gxz+=1.0/GH0[i];
			}Gxz=n/Gxz;//
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
		}
		break;
	}
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
	{
		TransData[j]=/*Vxzr[j]*1E4*/GH0[j];
	}
	//����ָ��
	delete zr,zi,Vzzi,Vzzr,Vxzi,Vxzr,GH,GH0;
	return true;
}

/*=============================================
�������ܣ�Ƶ������һλλ�����ݹ�һEAS����Ҫ���������ų������д��о���
������
	OriginalData/TransData������λ���������飻ת���������(������originaldata��ͬ������Ϊ���������
	datanum�����ݸ���
	dx�����;
	HarmonicWaveNum_max:г�������ֵ����СֵĬ��Ϊ1��
	h2/dh/h1�������²�z���ꣻ���������ࣻ����z����
=============================================*/
bool NormalEAS(double* OriginalData,double* TransData,const int datanum,const double dx,const double TRP,const int hNum,const double dh,const double h1,int NormalizeType)
{
	double *GHdata=new double[datanum];
	double rph=0;
	for (int j = 0; j < hNum; j++)
	{
		rph=h1+j*dh;
		NormalEAS(OriginalData,GHdata,datanum,dx,TRP,rph,NormalizeType);
		for (int i = 0; i < datanum; i++)
		{
			TransData[j*datanum+i]=GHdata[i];
		}
	}
	delete GHdata;
	return true;
}


/*=============================================
�������ܣ�����Hilbert�任��һάλ������z����һ�׵���
������
	����λ���������飻ת���������
	datanum�����ݸ���
	dx�����
=============================================*/
bool Derivative_Z_DHT(double* OriginalData,double* TransData,const int datanum,const double dx)
{

	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,pjg,tp;
	double v1,v2;
	double x11,x22;
	int j1;

	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	for(int j=0;j<n1;j++)
	{ 
		zi[j]=(double)0; 
	}
	//=====����=================================================================================================

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	double temp;
	int order=1;
	//====================================
	//��z��������Ƶ��
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		x11=tp*fabs(v1);x22=tp*fabs(v2);
		zr[j]=zr[j]*pow(x11,order); zi[j]=zi[j]*pow(x11,order);
		zr[j1]=zr[j1]*pow(x22,order); zi[j1]=zi[j1]*pow(x22,order);
	}
	//����Ƶ�׺�DHT����X������
	double* HilbertTemp=new double[n1];
	for(int j=0;j<(n1);j++)
	{	
		HilbertTemp[j]=0;
		for (int i = 0; i < (n1/2); i++)
		{
			v1=i/en+1E-10; 
			x11=tp*fabs(v1);
			HilbertTemp[j]+=zi[i]*cos(x11*j*dx)+zr[i]*sin(x11*j*dx);
		}
	}
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
		TransData[j]=HilbertTemp[j+nq]*1E4;

	//����ָ��
	delete zr,zi,HilbertTemp;
	return true;

}


/*===============================================================================
�������ܣ�Ƶ������һλλ�����ݹ�һ���ֲ�����
������
	OriginalData/TransData������λ���������飻ת���������
	datanum�����ݸ���
	dx�����;
	HarmonicWaveNum:г����
	rph�����ظ߶�
===============================================================================*/
bool NormalLocalWaveNumber(double* OriginalData,double* TransData,const int datanum,const double dx,const double TRP,const double rph,int NormalizeType)
{
	int n=datanum;
	int ne,n1,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		
	ne=4; n1=(int)(pow(2,ne)+.001);
	while(n>=(n1-12))
	{   ne++; n1=(int)(pow(2,ne)+.001);
	}
	nq=(int)((n1-n)/2+.001);//���������
		
	int nj=n1;		//���ߺ������
	double en,h,pjg,tp;
	double AC11,AC22;
	double v1,v2;
	double w11,w22;
	int j1;

	h=fabs(rph);
	en=dx*(double)(n1-1); 
	tp=(double)(2*PI);

	//---
	double* zr=new double[n1],*zi=new double[n1];
	//double* Vxzr=new double[n1],*Vxzi=new double[n1],*Vzzr=new double[n1],*Vzzi=new double[n1];
	double *Txzr=new double[n1],*Txzi=new double[n1],*Txr=new double[n1],*Txi=new double[n1],*Txxr=new double[n1],
		*Txxi=new double[n1],*Tzr=new double[n1],*Tzi=new double[n1],*Tzzr=new double[n1],*Tzzi=new double[n1];
	double* Kx=new double[n1],*Kz=new double[n1];
	for (int i = 0; i < datanum; i++)
	{
		zr[i]=OriginalData[i];
	}
	//=====����=================================================================================================
	//pjg=(double)0;
	//pjg=(zr[0]+zr[n-1])/(double)2.;
	//
	//for(int j=(n-1);j>=0;j--)
	//{ 
	//	zr[j+nq]=zr[j]-pjg;
	//}

	//for(int j=0;j<nq;j++)
	//	{   zr[j]=zr[nq]*(double)(1-cos(((double)PI*(double)j/(double)nq)))/(double)2;
	//		zr[j+n+nq]=zr[n+nq-1]*(double)(1+cos(((double)PI*(double)(j+1)/(double)(n1-n-nq))))/(double)2;
	//	}zr[n1-1]=zr[0];
	for(int j=0;j<n1;j++)
		{ 
			zi[j]=(double)0; 
		}

	Extension_Polynomial_1D(OriginalData,zr,dx,datanum,nj,2);

	//==========================================================================================================
	//����Ҷ�任
	fft1(zr,zi,ne,n1,0);
	//====================================
	double temp;
	double a=1;int IterationNum=100;
	double x11,x22;
	for(int j=0;j<(n1/2);j++)
	{	
		v1=j/en+1E-10; v2=(j-n1/2)/en+1E-10; j1=n1/2+j;
		x11=tp*(double)v1; x22=tp*(double)v2;
		w11=fabs(x11); w22=fabs(x22);
		AC11=AC22=(double)1;
		AC11*=(double)exp(-w11*h)/(exp(-2*w11*h)+TRP); AC22*=(double)exp(-w22*h)/(exp(-2*w22*h)+TRP);	
		//AC11*=(double)exp(w11*h)*(1-pow(1-a*exp(-2*h*w11),IterationNum)); AC22*=(double)exp(w22*h)*(1-pow(1-a*exp(-2*h*w22),IterationNum));
		////����x������������
		temp=zr[j];Txzr[j]=-zi[j]*AC11*x11*w11;Txzi[j]=temp*AC11*x11*w11;
		temp=zr[j1];Txzr[j1]=-zi[j1]*AC22*x22*w22;Txzi[j1]=temp*AC22*x22*w22;

		temp=zr[j];Txr[j]=-zi[j]*AC11*x11;Txi[j]=temp*AC11*x11;
		temp=zr[j1];Txr[j1]=-zi[j1]*AC22*x22;Txi[j1]=temp*AC22*x22;

		temp=zr[j];Txxr[j]=-zi[j]*AC11*x11*x11;Txxi[j]=temp*AC11*x11*x11;
		temp=zr[j1];Txxr[j1]=-zi[j1]*AC22*x22*x22;Txxi[j1]=temp*AC22*x22*x22;
		////����z������������
		Tzr[j]=zr[j]*AC11*w11;Tzi[j]=zi[j]*AC11*w11;
		Tzr[j1]=zr[j1]*AC22*w22;Tzi[j1]=zi[j1]*AC22*w22;

		Tzzr[j]=zr[j]*AC11*w11*w11;Tzzi[j]=zi[j]*AC11*w11*w11;
		Tzzr[j1]=zr[j1]*AC22*w22*w22;Tzzi[j1]=zi[j1]*AC22*w22*w22;
	}
	//����Ҷ��任
	fft1(Txzr,Txzi,ne,n1,1);
	fft1(Txr,Txi,ne,n1,1);
	fft1(Txxr,Txxi,ne,n1,1);
	fft1(Tzr,Tzi,ne,n1,1);
	fft1(Tzzr,Tzzi,ne,n1,1);

	//..����
	for(int j=0;j<n;j++)
	{
		Txzr[j]=/*Vzzr[j+nq]*1E4*/Txzr[j+nq];
		Txr[j]=/*Vzzr[j+nq]*1E4*/Txr[j+nq];
		Txxr[j]=/*Vzzr[j+nq]*1E4*/Txxr[j+nq];
		Tzr[j]=/*Vzzr[j+nq]*1E4*/Tzr[j+nq];
		Tzzr[j]=/*Vzzr[j+nq]*1E4*/Tzzr[j+nq];
	}
	//����ֲ�����
	double Gxz=0;
	double *GH=new double[n1],*GH0=new double[n1];
	for (int i = 0; i < n1; i++)
	{
		Kx[i]=(Txzr[i]*Txr[i]-Txxr[i]*Tzr[i])/sqrt(Txr[i]*Txr[i]+Tzr[i]*Tzr[i]);
		Kz[i]=-(Txzr[i]*Tzr[i]-Tzzr[i]*Txr[i])/sqrt(Txr[i]*Txr[i]+Tzr[i]*Tzr[i]);
		GH0[i]=sqrt(Kx[i]*Kx[i]+Kz[i]*Kz[i]);
	}
	//===========���ڹ�һ��===============================
	/*int WindowSize=datanum/2;
	int HalfWindowSize=WindowSize/2;
	double GHmax;
	Gxz=0;
	GHmax=GH0[0];
	for (int j = 0; j < WindowSize; j++)
	{
		if (GHmax<GH0[j])
		{
			GHmax=GH0[j];
		}	
	}
	for (int i = 0; i < HalfWindowSize; i++)
	{
		GH[i]=GH0[i]/GHmax;
	}

	for (int i = 0; i < datanum-WindowSize; i++)
	{
		GHmax=GH0[i];
		for (int j = 0; j < WindowSize; j++)
		{
			if (GHmax<GH0[i+j])
			{
				GHmax=GH0[i+j];
			}	
		}
		GH[i+HalfWindowSize]=GH0[i+HalfWindowSize]/GHmax;
	}

	for (int j = datanum-HalfWindowSize; j < datanum; j++)
	{
		GH[j]=GH0[j]/GHmax;
	}*/
	//===================================================
	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz+=GH0[i];
	//}Gxz=Gxz/(n);//��ֵ
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================

	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz+=1.0/GH0[i];
	//}Gxz=n/Gxz;//
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================

	//=========����ƽ����һ��==================================
	//for (int i = 0; i < n; i++)
	//{
	//	Gxz*=GH0[i];
	//}Gxz=pow(Gxz,1.0/n);//
	//for (int i = 0; i < n; i++)
	//{
	//	GH[i]=GH0[i]/Gxz;
	//	//GH[i]=atan2(Vxzr[i],Vzzr[i]);
	//}
	//====================================================
	switch (NormalizeType)
	{
	case 0:			//����ƽ����һ
		{
			//int WindowSize=n/2;//�ܳ��ȵ�ʮ��֮һ
			//int HalfWindowSize=WindowSize/2;
			//WindowSize=HalfWindowSize*2;
			//for (int i = 0; i < n; i++)
			//{
			//	Gxz+=GH0[i];
			//}Gxz=Gxz/(n);//��ֵ
			////��߹�һ
			//for (int i = 0; i < HalfWindowSize; i++)
			//{
			//	GH[i]=0;
			//}
			////�ұ߹�һ
			//for (int i = n-HalfWindowSize; i < n; i++)
			//{
			//	GH[i]=0;
			//}
			////�м们�����ڹ�һ
			//for (int i = HalfWindowSize; i < n-HalfWindowSize; i++)
			//{
			//	Gxz=0;
			//	for (int k = i-HalfWindowSize; k < i+HalfWindowSize; k++)
			//	{
			//		Gxz+=GH0[k];
			//	}Gxz=Gxz/(WindowSize);
			//	GH[i]=GH0[i]/Gxz;
			//}

			for (int i = 0; i < n; i++)
			{
				Gxz+=GH0[i];
			}Gxz=Gxz/(n);//��ֵ
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}

		}
		break;
	case 1:		//����ƽ����һ
		{
			for (int i = 0; i < n; i++)
			{
				Gxz+=1.0/GH0[i];
			}Gxz=n/Gxz;//
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
		}
		break;
	default:
		{
			for (int i = 0; i < n; i++)
			{
				Gxz+=1.0/GH0[i];
			}Gxz=n/Gxz;//
			for (int i = 0; i < n; i++)
			{
				GH[i]=GH0[i]/Gxz;
				//GH[i]=atan2(Vxzr[i],Vzzr[i]);
			}
		}
		break;
	}
	//..�任�����ݸ�ֵ
	for(int j=0;j<n;j++)
	{
		TransData[j]=/*Vxzr[j]*1E4*/Kz[j];
	}
	//����ָ��
	delete zr,zi,Txr,Txi,Txxr,Txxi,Txzr,Txzi,Tzr,Tzi,Tzzr,Tzzi,GH,GH0;
	return true;
}



/*===============================================================================
�������ܣ�Ƶ������һλλ���������˲��ֳ�
������
	OriginalData/TransData������λ���������飻ת���������
	datanum�����ݸ���
	dx�����;
	Winsize�����ڴ�С
===============================================================================*/
bool Separation_EntropyFilter(double* OriginalData,double* TransData,const int datanum,const double dx,int WinSize)
{
	int np=datanum+WinSize;
	double* ExtensionData=new double[datanum+np];
	Extension_Polynomial_1D(OriginalData,ExtensionData,dx,datanum,np,1);		//����
	
	double mindata,maxdata,meandata,rmax;
	double *Entropy=new double[WinSize],*EntropyCoe=new double[WinSize];
	double SumEntropy=0,RegData=0;
	for (int i = 0; i < datanum; i++)
	{
		double SumTemp=0;
		mindata=ExtensionData[i],maxdata=ExtensionData[i];
		for (int j = i; j < i+WinSize; j++)		//�����ֵ�����ֵ����Сֵ
		{
			SumTemp+=ExtensionData[j];
			if (ExtensionData[j]>maxdata)
			{
				maxdata=ExtensionData[j];
			}
			if (ExtensionData[j]<mindata)
			{
				mindata=ExtensionData[j];
			}
		}meandata=SumTemp/WinSize;
		rmax=fabs(ExtensionData[i]-meandata);
		for (int j = i; j < i+WinSize; j++)		//����rmax
		{
			if (fabs(ExtensionData[j]-meandata)>maxdata)
			{
				rmax=fabs(ExtensionData[j]-meandata);
			}
		}
		SumEntropy=0;
		for (int j = i; j < i+WinSize; j++)		//������ֵ
		{
			Entropy[j-i]=fabs(ExtensionData[j]-meandata)/rmax;
			printf("%lf\n",Entropy[j-i]);
			SumEntropy+=1-Entropy[j-i];
		}
		RegData=0;
		for (int j = i; j < i+WinSize; j++)		//������ϵ��
		{
			EntropyCoe[j-i]=(1-Entropy[j-i])/SumEntropy;
			RegData+=ExtensionData[j]*EntropyCoe[j-i];
		}
		
		TransData[i]=OriginalData[i]/meandata;
		printf("ԭʼֵ:%lf\nƽ��ֵ:%lf\n���˲�:%lf\n��ϵ��:%lf\n",OriginalData[i],meandata,RegData,SumEntropy);
		return true;
	}

	delete ExtensionData,Entropy;
	return true;
}
