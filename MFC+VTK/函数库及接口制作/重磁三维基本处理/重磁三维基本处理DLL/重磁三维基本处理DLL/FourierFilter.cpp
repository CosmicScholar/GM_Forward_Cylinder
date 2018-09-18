//#include "stdafx.h"
//#include "proj.h"
#include "FourierFilter.h"

/*================================================
�������ܣ� λ��Ƶ������������
��������� ���������ݶ�ά����ָ�룻���غ�Ķ�ά����ָ�룻
		   ������������dx��dy��
		   ���ظ߶ȣ���λ��m��
==================================================*/
bool UpWardContinuation(double** OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double rph)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i][j];
	
//..�任���̣����Ĵ���
		double h,df,pjg,em,emn,en,tp;
		h=-fabs(rph);
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);
		fft(zr,zi,m1,n1,me,ne,0);
		double u1,u2,v1,v2;
		double AC11,AC12,AC21,AC22;
		double y11,y12,y21,y22,w11,w12,w21,w22;
		int i1,j1;
		for(int i=0;i<(m1/2);i++)
		{	
			u1=(double)i/em+1E-10; u2=(double)(i-m1/2)/em+1E-10; i1=m1/2+i;
			for(int j=0;j<(n1/2);j++)
			{	
				v1=(double)j/en+1E-10; v2=(double)(j-n1/2)/en+1E-10; j1=n1/2+j;
				y11=(double)sqrt(u1*u1+v1*v1); y12=(double)sqrt(u1*u1+v2*v2);
				y21=(double)sqrt(u2*u2+v1*v1); y22=(double)sqrt(u2*u2+v2*v2);
				w11=tp*y11; w12=tp*y12;
				w21=tp*y21; w22=tp*y22;
				AC11=AC12=AC21=AC22=(double)1;	
				//��������
				AC11*=(double)exp(w11*h); AC12*=(double)exp(w12*h);
				AC21*=(double)exp(w21*h); AC22*=(double)exp(w22*h);
				//Ƶ�׳�����������
				zr[i][j]=zr[i][j]*AC11; zi[i][j]=zi[i][j]*AC11;
				zr[i][j1]=zr[i][j1]*AC12; zi[i][j1]=zi[i][j1]*AC12;
				zr[i1][j]=zr[i1][j]*AC21; zi[i1][j]=zi[i1][j]*AC21;
				zr[i1][j1]=zr[i1][j1]*AC22; zi[i1][j1]=zi[i1][j1]*AC22;
				
			}
		}

		//.. ��任
  		fft(zr,zi,m1,n1,me,ne,1);

		//..�任�����ݸ�ֵ
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				TransData[i][j]=zr[i+np][j+nq]+pjg;

		//����ָ��
		delete zr,zi;
		return true;
}	


/*================================================
�������ܣ� λ��Ƶ������������
��������� ����������һά����ָ�룻���غ��һά����ָ�룻������Ԫ��
		   ������������dx��dy��
		   ���ظ߶ȣ���λ��m��
==================================================*/
bool UpWardContinuation(double* OriginalData,double* TransData,const int rows,const int columns,const double dx,const double dy,const double rph)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i*n+j];
	
//..�任���̣����Ĵ���
		double h,df,pjg,em,emn,en,tp;
		h=-fabs(rph);
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);
		fft(zr,zi,m1,n1,me,ne,0);
		double u1,u2,v1,v2;
		double AC11,AC12,AC21,AC22;
		double y11,y12,y21,y22,w11,w12,w21,w22;
		int i1,j1;
		for(int i=0;i<(m1/2);i++)
		{	
			u1=(double)i/em+1E-10; u2=(double)(i-m1/2)/em+1E-10; i1=m1/2+i;
			for(int j=0;j<(n1/2);j++)
			{	
				v1=(double)j/en+1E-10; v2=(double)(j-n1/2)/en+1E-10; j1=n1/2+j;
				y11=(double)sqrt(u1*u1+v1*v1); y12=(double)sqrt(u1*u1+v2*v2);
				y21=(double)sqrt(u2*u2+v1*v1); y22=(double)sqrt(u2*u2+v2*v2);
				w11=tp*y11; w12=tp*y12;
				w21=tp*y21; w22=tp*y22;
				AC11=AC12=AC21=AC22=(double)1;	
				//��������
				AC11*=(double)exp(w11*h); AC12*=(double)exp(w12*h);
				AC21*=(double)exp(w21*h); AC22*=(double)exp(w22*h);
				//Ƶ�׳�����������
				zr[i][j]=zr[i][j]*AC11; zi[i][j]=zi[i][j]*AC11;
				zr[i][j1]=zr[i][j1]*AC12; zi[i][j1]=zi[i][j1]*AC12;
				zr[i1][j]=zr[i1][j]*AC21; zi[i1][j]=zi[i1][j]*AC21;
				zr[i1][j1]=zr[i1][j1]*AC22; zi[i1][j1]=zi[i1][j1]*AC22;
				
			}
		}

		//.. ��任
  		fft(zr,zi,m1,n1,me,ne,1);

		//..�任�����ݸ�ֵ
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				TransData[i*n+j]=zr[i+np][j+nq]+pjg;

		//����ָ��
		delete zr,zi;
		return true;
}

/*================================================
�������ܣ� λ��Ƶ������������(Tikhonov���򻯷�����
��������� ���������ݶ�ά����ָ�룻���غ�Ķ�ά����ָ�룻
		   ������������dx��dy�����ظ߶ȣ���λ��m��
		   ���򻯲���(Tikhonov Regularization Parameter)
		   �������򻯲���
==================================================*/
bool DownWardContinuation_Tik(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double rph,const double TRP,const double XiGeMe)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i][j];
	
//..�任���̣����Ĵ���
		double h,df,pjg,em,emn,en,tp;
		h=fabs(rph);
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);
		fft(zr,zi,m1,n1,me,ne,0);
		double u1,u2,v1,v2;
		double uv11,uv12,uv21,uv22;
		double AC11,AC12,AC21,AC22;
		double y11,y12,y21,y22,w11,w12,w21,w22;
		int i1,j1;
		for(int i=0;i<(m1/2);i++)
			{	
				u1=(double)i/em+1E-10; u2=(double)(i-m1/2)/em+1E-10; i1=m1/2+i;
				for(int j=0;j<(n1/2);j++)
				{	
					v1=(double)j/en+1E-10; v2=(double)(j-n1/2)/en+1E-10; j1=n1/2+j;
					uv11=u1*u1+v1*v1;uv12=u1*u1+v2*v2;
					uv21=u2*u2+v1*v1;uv22=u2*u2+v2*v2;
					y11=(double)sqrt(uv11); y12=(double)sqrt(uv12);
					y21=(double)sqrt(uv21); y22=(double)sqrt(uv22);
					w11=tp*y11; w12=tp*y12;
					w21=tp*y21; w22=tp*y22;
					//��������
					AC11=AC12=AC21=AC22=(double)1;	
					AC11*=(double)exp(-w11*h)/pow(exp(-2*XiGeMe*w11*h)+TRP,1.0/XiGeMe); AC12*=(double)exp(-w12*h)/pow(exp(-2*XiGeMe*w12*h)+TRP,1.0/XiGeMe);
					AC21*=(double)exp(-w21*h)/pow(exp(-2*XiGeMe*w21*h)+TRP,1.0/XiGeMe); AC22*=(double)exp(-w22*h)/pow(exp(-2*XiGeMe*w22*h)+TRP,1.0/XiGeMe);
					
					/*AC11*=(double)exp(w11*h)/(1+TRP*(uv11)*exp(w11*h)); AC12*=(double)exp(w12*h)/(1+TRP*(uv12)*exp(w12*h));
					AC21*=(double)exp(w21*h)/(1+TRP*(uv21)*exp(w21*h)); AC22*=(double)exp(w22*h)/(1+TRP*(uv22)*exp(w22*h));*/

					/*AC11*=(double)exp(-w11*h)/(exp(-2*w11*h)+TRP*(1+uv11)); AC12*=(double)exp(-w12*h)/(exp(-2*w12*h)+TRP*(1+uv12));
					AC21*=(double)exp(-w21*h)/(exp(-2*w21*h)+TRP*(1+uv21)); AC22*=(double)exp(-w22*h)/(exp(-2*w22*h)+TRP*(1+uv22));*/
					//Ƶ�׳�����������
					zr[i][j]=zr[i][j]*AC11; zi[i][j]=zi[i][j]*AC11;
					zr[i][j1]=zr[i][j1]*AC12; zi[i][j1]=zi[i][j1]*AC12;
					zr[i1][j]=zr[i1][j]*AC21; zi[i1][j]=zi[i1][j]*AC21;
					zr[i1][j1]=zr[i1][j1]*AC22; zi[i1][j1]=zi[i1][j1]*AC22;
				
					}
				}
		//.. ��任
  		fft(zr,zi,m1,n1,me,ne,1);

		//..�任�����ݸ�ֵ
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				TransData[i][j]=zr[i+np][j+nq]+pjg;

		//����ָ��
		delete zi,zr;
		return true;
}	

/*================================================
�������ܣ� λ��Ƶ������������(Tikhonov���򻯷�����,�Զ�ѡ��������򻯲���
��������� ���������ݶ�ά����ָ�룻���غ�Ķ�ά����ָ�룻
		   ������������dx��dy�����ظ߶ȣ���λ��m��
		   ��ʼ���򻯲���(Tikhonov Regularization Parameter)��
		   ���򻯲����仯����ѭ���������������򻯲���
==================================================*/
double AutoDownWardContinuation_Tik(double** OriginalData,double** TransData,const int rows,const int columns,
									const double dx,const double dy,const double rph,const double TRP,
									const double dTRP,const int kmax,const double XiGeMe)
{
	double trp=TRP;
	double FaiD=0,FaiM=0;
	double** transdata2=new double* [rows];
	transdata2[0]=new double [rows*columns]; 
	for(int i=1;i<rows;i++)
	{	
		transdata2[i]=transdata2[i-1]+columns; 
	}
	char* filename="L����.dat";
	FILE* fp;
	if ((fp=fopen(filename,"w"))==NULL)
	{
		printf("��%sʧ��\n",filename);
		return -1;
	}
	for (int k = 0; k < kmax; k++)
	{
		trp+=dTRP;
		DownWardContinuation_Tik(OriginalData,TransData,rows,columns,dx,dy,rph,trp,XiGeMe);
		UpWardContinuation(TransData,transdata2,rows,columns,dx,dy,rph);				//�����ӽ������
		FaiD=0.0;FaiM=0.0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				FaiD+=pow(OriginalData[i][j]-transdata2[i][j],2);
				FaiM+=pow(TransData[i][j],2);
			}
		}
		FaiD=sqrt(FaiD);FaiM=sqrt(FaiM);
		fprintf(fp,"%lf\t%lf\t%lf\n",FaiM,FaiD,trp);
		printf("%d\n",k);//�������
	}
	fclose(fp);

	//����ָ��
	delete transdata2;
	return trp;
}

/*================================================
�������ܣ� λ��Ƶ������������(Landweber������
��������� ���������ݶ�ά����ָ�룻���غ�Ķ�ά����ָ�룻
		   ������������dx��dy�����ظ߶ȣ���λ��m��
		   ����a����������n
==================================================*/
bool DownWardContinuation_LandWeber(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double rph,const double a_Land,const double n_Land)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i][j];
	
//..�任���̣����Ĵ���
		double h,df,pjg,em,emn,en,tp;
		h=fabs(rph);
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);
		fft(zr,zi,m1,n1,me,ne,0);
		double u1,u2,v1,v2;
		double AC11,AC12,AC21,AC22;
		double y11,y12,y21,y22,w11,w12,w21,w22;
		int i1,j1;
		for(int i=0;i<(m1/2);i++)
			{	
				u1=(double)i/em+1E-10; u2=(double)(i-m1/2)/em+1E-10; i1=m1/2+i;
				for(int j=0;j<(n1/2);j++)
				{	
					v1=(double)j/en+1E-10; v2=(double)(j-n1/2)/en+1E-10; j1=n1/2+j;
					y11=(double)sqrt(u1*u1+v1*v1); y12=(double)sqrt(u1*u1+v2*v2);
					y21=(double)sqrt(u2*u2+v1*v1); y22=(double)sqrt(u2*u2+v2*v2);
					w11=tp*y11; w12=tp*y12;
					w21=tp*y21; w22=tp*y22;
					//��������
					AC11=AC12=AC21=AC22=(double)1;	
					AC11*=(double)exp(w11*h)*(1-pow(1-a_Land*exp(-2*h*w11),n_Land)); AC12*=(double)exp(w12*h)*(1-pow(1-a_Land*exp(-2*h*w12),n_Land));
					AC21*=(double)exp(w21*h)*(1-pow(1-a_Land*exp(-2*h*w21),n_Land)); AC22*=(double)exp(w22*h)*(1-pow(1-a_Land*exp(-2*h*w22),n_Land));
					//Ƶ�׳�����������
					zr[i][j]=zr[i][j]*AC11; zi[i][j]=zi[i][j]*AC11;
					zr[i][j1]=zr[i][j1]*AC12; zi[i][j1]=zi[i][j1]*AC12;
					zr[i1][j]=zr[i1][j]*AC21; zi[i1][j]=zi[i1][j]*AC21;
					zr[i1][j1]=zr[i1][j1]*AC22; zi[i1][j1]=zi[i1][j1]*AC22;
				
					}
				}
		//.. ��任
  		fft(zr,zi,m1,n1,me,ne,1);

		//..�任�����ݸ�ֵ
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				TransData[i][j]=zr[i+np][j+nq]+pjg;

		//����ָ��
		delete zi,zr;
		return true;
}	

/*===============================================================================
	���쳣��������
	�������:ԭʼ���ݶ�ά���飻�����Ķ�ά����ָ�룻
			 ����������������dx��dy������ǣ��ȣ�����ƫ�ǣ��ȣ���
			 ԭʼ�������ͣ�1��ʾT��2��ʾTx��3��ʾTy��4��ʾZa����
			 �������������ͣ�1��ʾx������2��ʾY������3��ʾZ������4��ʾT��
=================================================================================*/
bool ComponentTransProcess(double** OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double angle_I,const double angle_D,const int OriginalStyle,const int TransStyle)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i][j];
	
//..�任���̣����Ĵ���
		double df,pjg,em,emn,en,tp;
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);
		fft(zr,zi,m1,n1,me,ne,0);
		double u1,u2,v1,v2;
		//double AC11,AC12,AC21,AC22;
		double y11,y12,y21,y22,w11,w12,w21,w22;
		double p11,p12,p21,p22,q11,q12,q21,q22;		//��������ʱʹ��
		double kx1,kx2,ky1,ky2,kz11,kz22,kz12,kz21;
		double angleI=angle_I/180.0*PI,angleD=angle_D/180*PI;
		double aerfa0=cos(angleI)*cos(angleD),beta0=cos(angleI)*sin(angleD),gama0=sin(angleI);
		double temp;
		int i1,j1;

		for(int i=0;i<(m1/2);i++)
			{	
				u1=(double)i/em+1E-10; u2=(double)(i-m1/2)/em+1E-10; i1=m1/2+i;
				for(int j=0;j<(n1/2);j++)
				{	
					v1=(double)j/en+1E-10; v2=(double)(j-n1/2)/en+1E-10; j1=n1/2+j;
					y11=(double)sqrt(u1*u1+v1*v1); y12=(double)sqrt(u1*u1+v2*v2);
					y21=(double)sqrt(u2*u2+v1*v1); y22=(double)sqrt(u2*u2+v2*v2);
					w11=tp*y11; w12=tp*y12;
					w21=tp*y21; w22=tp*y22;
					//AC11=AC12=AC21=AC22=(double)1;	
					//��������
					if (OriginalStyle==1)		//��T����Tx��Ty��Tz
					{
						
						kx1=aerfa0*u1,kx2=aerfa0*u2;
						ky1=beta0*v1,ky2=beta0*v2;
						kz11=gama0*sqrt(u1*u1+v1*v1),kz22=gama0*sqrt(u2*u2+v2*v2),kz12=gama0*sqrt(u1*u1+v2*v2),kz21=gama0*sqrt(u2*u2+v1*v1);
						switch (TransStyle)
						{
						case 1:			//X����
							q11=kx1*kz11/aerfa0/(pow(kx1+ky1,2.0)+pow(kz11,2.0));
							q12=kx1*kz12/aerfa0/(pow(kx1+ky2,2.0)+pow(kz12,2.0));
							q21=kx2*kz21/aerfa0/(pow(kx2+ky1,2.0)+pow(kz21,2.0));
							q22=kx2*kz22/aerfa0/(pow(kx2+ky2,2.0)+pow(kz22,2.0));
							p11=kx1*(kx1+ky1)/aerfa0/(pow(kx1+ky1,2.0)+pow(kz11,2.0));
							p12=kx1*(kx1*ky2)/aerfa0/(pow(kx1+ky2,2.0)+pow(kz12,2.0));
							p21=kx2*(kx2*ky1)/aerfa0/(pow(kx2+ky1,2.0)+pow(kz21,2.0));
							p22=kx2*(kx2*ky2)/aerfa0/(pow(kx2+ky2,2.0)+pow(kz22,2.0));
							break;
						case 2:			//Y����
							q11=ky1*kz11/beta0/(pow(kx1+ky1,2.0)+pow(kz11,2.0));
							q12=ky1*kz12/beta0/(pow(kx1+ky2,2.0)+pow(kz12,2.0));
							q21=ky2*kz21/beta0/(pow(kx2+ky1,2.0)+pow(kz21,2.0));
							q22=ky2*kz22/beta0/(pow(kx2+ky2,2.0)+pow(kz22,2.0));
							p11=ky1*(kx1+ky1)/beta0/(pow(kx1+ky1,2.0)+pow(kz11,2.0));
							p12=ky1*(kx1*ky2)/beta0/(pow(kx1+ky2,2.0)+pow(kz12,2.0));
							p21=ky2*(kx2*ky1)/beta0/(pow(kx2+ky1,2.0)+pow(kz21,2.0));
							p22=ky2*(kx2*ky2)/beta0/(pow(kx2+ky2,2.0)+pow(kz22,2.0));
							break;
						default:		//Z����
							p11=kz11*kz11/gama0/(pow(kx1+ky1,2.0)+pow(kz11,2.0));
							p12=kz12*kz12/gama0/(pow(kx1+ky2,2.0)+pow(kz12,2.0));
							p21=kz21*kz21/gama0/(pow(kx2+ky1,2.0)+pow(kz21,2.0));
							p22=kz22*kz22/gama0/(pow(kx2+ky2,2.0)+pow(kz22,2.0));
							q11=-kz11*(kx1+ky1)/gama0/(pow(kx1+ky1,2.0)+pow(kz11,2.0));
							q12=-kz12*(kx1*ky2)/gama0/(pow(kx1+ky2,2.0)+pow(kz12,2.0));
							q21=-kz21*(kx2*ky1)/gama0/(pow(kx2+ky1,2.0)+pow(kz21,2.0));
							q22=-kz22*(kx2*ky2)/gama0/(pow(kx2+ky2,2.0)+pow(kz22,2.0));
							break;
						}
						temp=zr[i][j]; zr[i][j]=(temp*p11-zi[i][j]*q11); zi[i][j]=temp*q11+zi[i][j]*p11;
						temp=zr[i][j1]; zr[i][j1]=(temp*p12-zi[i][j1]*q12); zi[i][j1]=temp*q12+zi[i][j1]*p12;
						temp=zr[i1][j]; zr[i1][j]=(temp*p21-zi[i1][j]*q21); zi[i1][j]=temp*q21+zi[i1][j]*p21;
						temp=zr[i1][j1]; zr[i1][j1]=(temp*p22-zi[i1][j1]*q22); zi[i1][j1]=temp*q22+zi[i1][j1]*p22;
					}
				
				}
			}

		//.. ��任
  		fft(zr,zi,m1,n1,me,ne,1);
		//..�任�����ݸ�ֵ
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				TransData[i][j]=zr[i+np][j+nq]+pjg;
		return true;
}

/*================================================
�������ܣ� λ��Ƶ������������(������
��������� ���������ݶ�ά����ָ�룻���غ�Ķ�ά����ָ�룻
		   ������������dx��dy�����ظ߶ȣ���λ��m��
		   ���򻯲���(Tikhonov Regularization Parameter)
		   �������򻯲���
==================================================*/
bool DownWardContinuation_Compensation(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double rph,const int kmax,const double TRP,const double XiGeMe)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i][j];
	
//..�任���̣����Ĵ���
		double h,df,pjg,em,emn,en,tp;
		h=fabs(rph);
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);
		fft(zr,zi,m1,n1,me,ne,0);
		double u1,u2,v1,v2;
		double uv11,uv12,uv21,uv22;
		double AC11,AC12,AC21,AC22;
		double y11,y12,y21,y22,w11,w12,w21,w22;
		double HD11,HD12,HD21,HD22,HU11,HU12,HU21,HU22;
		int i1,j1;
		for(int i=0;i<(m1/2);i++)
			{	
				u1=(double)i/em+1E-10; u2=(double)(i-m1/2)/em+1E-10; i1=m1/2+i;
				for(int j=0;j<(n1/2);j++)
				{	
					v1=(double)j/en+1E-10; v2=(double)(j-n1/2)/en+1E-10; j1=n1/2+j;
					uv11=u1*u1+v1*v1;uv12=u1*u1+v2*v2;
					uv21=u2*u2+v1*v1;uv22=u2*u2+v2*v2;
					y11=(double)sqrt(uv11); y12=(double)sqrt(uv12);
					y21=(double)sqrt(uv21); y22=(double)sqrt(uv22);
					w11=tp*y11; w12=tp*y12;
					w21=tp*y21; w22=tp*y22;
					//��������
					AC11=AC12=AC21=AC22=(double)1;	
					HU11=(double)exp(-w11*h);HU12=(double)exp(-w12*h);
					HU21=(double)exp(-w21*h);HU22=(double)exp(-w22*h);
					HD11=HU11/pow(exp(-2*XiGeMe*w11*h)+TRP,1.0/XiGeMe);HD12=HU12/pow(exp(-2*XiGeMe*w12*h)+TRP,1.0/XiGeMe);
					HD21=HU21/pow(exp(-2*XiGeMe*w21*h)+TRP,1.0/XiGeMe);HD22=HU22/pow(exp(-2*XiGeMe*w22*h)+TRP,1.0/XiGeMe);
					//AC11*=(double)exp(-w11*h)/pow(exp(-2*XiGeMe*w11*h)+TRP,1.0/XiGeMe); AC12*=(double)exp(-w12*h)/pow(exp(-2*XiGeMe*w12*h)+TRP,1.0/XiGeMe);
					//AC21*=(double)exp(-w21*h)/pow(exp(-2*XiGeMe*w21*h)+TRP,1.0/XiGeMe); AC22*=(double)exp(-w22*h)/pow(exp(-2*XiGeMe*w22*h)+TRP,1.0/XiGeMe);
					AC11=HD11;AC12=HD12;AC21=HD21;AC22=HD22;
					for (int k = 0; k < kmax; k++)
					{
						AC11=HD11+(1-HD11*HU11)*AC11;AC12=HD12+(1-HD12*HU12)*AC12;
						AC21=HD21+(1-HD21*HU21)*AC21;AC22=HD22+(1-HD22*HU22)*AC22;
					}
					
					
					/*AC11=2-exp(-w11*h)+tp*tp*uv11*h*h;AC12=2-exp(-w12*h)+tp*tp*uv12*h*h;
					AC21=2-exp(-w21*h)+tp*tp*uv21*h*h;AC22=2-exp(-w22*h)+tp*tp*uv22*h*h;*/
					//Ƶ�׳�����������
					zr[i][j]=zr[i][j]*AC11; zi[i][j]=zi[i][j]*AC11;
					zr[i][j1]=zr[i][j1]*AC12; zi[i][j1]=zi[i][j1]*AC12;
					zr[i1][j]=zr[i1][j]*AC21; zi[i1][j]=zi[i1][j]*AC21;
					zr[i1][j1]=zr[i1][j1]*AC22; zi[i1][j1]=zi[i1][j1]*AC22;
				
					}
				}
		//.. ��任
  		fft(zr,zi,m1,n1,me,ne,1);

		//..�任�����ݸ�ֵ
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				TransData[i][j]=zr[i+np][j+nq]+pjg;

		//����ָ��
		delete zi,zr;
		return true;
}

/*================================================
�������ܣ� ��άλ�����������׼���
��������� OriginalData/PowerSpectrumAmp��ԭʼ����/������
		   ������������dx��dy��
		   mr:Ƶ�ʵ���������������ͼ�������ݸ�����
		   ����GDPS-Match����
==================================================*/
bool PowerSpectrum(double** OriginalData,double* PowerSpectrumAmp,int mr,const int rows,const int columns,const double dx,const double dy)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		/*for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i][j];*/
	
//..�任���̣����Ĵ���
		/*double df,pjg,em,emn,en,tp;
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);
		fft(zr,zi,m1,n1,me,ne,0);*/

//To determine the size of arrays for FFT ///////////////////////////////////////

//////////////////////////////////////////////////////////////
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)
			zr[i][j]=OriginalData[i][j];
////////////////////////////////////////////////
	double df,pjg,em,emn,en,tp,s,u,v,r,amp0,fmax;
	int kk;
	pjg=prep(zr,zi,m,n,m1,n1,np,nq);
	fft(zr,zi,m1,n1,me,ne,0);
	em=dx*(m1-1); en=dy*(n1-1);
	df=(double)sqrt(1/(em*em)+1/(en*en));	   /// frequency interval  ////
	fmax=(double)(sqrt(dx*dx+dy*dy)/dx/dy/2.);   /// maxmum of frequency ////
	mr=(int)(fmax/df+.5);              /// number of f-points  ////
	for(int k=1;k<mr;k++)
	{	
		PowerSpectrumAmp[k]=(double)0;s=(double)0; kk=0;
		for(int i=0;i<m1/2;i++)
		{	u=i/em;
			for(int j=0;j<n1/2;j++)
			{ 
				v=j/en;
				r=(double)sqrt(u*u+v*v);
				if((r>df*(k-1))&&(r<=df*k))
				{
					s+=zr[i][j]*zr[i][j]+zi[i][j]*zi[i][j];
					kk+=1;
				}
			}
		}
		if(kk!=0)
		{	
			PowerSpectrumAmp[k]=(double)((s)/kk);	
		}
	}
	////////////////////////////////////
	//PowerSpectrumAmp[0]=amp0=(double)log(zr[0][0]*zr[0][0]+zi[0][0]*zi[0][0]);
	PowerSpectrumAmp[0]=amp0=(double)((zr[0][0]*zr[0][0]+zi[0][0]*zi[0][0]));
	//Zmin=Zmax=(double)0;
	//for(int i=0;i<mr;i++)
	{	
		//PowerSpectrumAmp[i]=PowerSpectrumAmp[i]-amp0;
		//if(PowerSpectrumAmp[i]<Zmin) Zmin=PowerSpectrumAmp[i];
		//else if(PowerSpectrumAmp[i]>Zmax) Zmax=PowerSpectrumAmp[i];
	}
	return true;
}

/*================================================
�������ܣ� ��ά����Ҷ�任Ԥ������ȡ�������������ȣ�
��������� grd������Ϣ
		   m1/me:���ߺ��������ǰ����2��������������2��m1�η��Ľ��
		   m1/me:���ߺ��������ǰ����2��������������2��n1�η��Ľ��
		   ����GDPS-Match����
==================================================*/
bool InitFFT(GridDataInfo datainfo,int& m1,int& me,int& n1,int& ne)
{
	int m=datainfo.rows; int n=datainfo.columns;
	int np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
	return true;
}

/*================================================
�������ܣ� ����QR�ֽⷨ��ⷽ����
��������� A��ϵ������B������������X����
==================================================*/
bool SolveEquation(double** A,double* X,double* B,int rows,int columns)
{
	//gmqr gmqr0(rows,columns);
	//gmqr0.input(A,B);
	//gmqr0.a_gmqr();
	//gmqr0.output(X);
	gmiv gmiv0(rows,columns);
	gmiv0.input(A,B,0.000001);
	gmiv0.a_gmiv();
	gmiv0.output(X);

	/*for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%lf\t",A[i][j]);
		}
		printf("\t\t%lf\n",B[i]);
	}*/
	return true;
}

/*================================================
�������ܣ� ����QR�ֽⷨ��ⷽ���������С���˷ֶ���϶���������
��������� PSA�������ף�DX����ࣻmr�������׵�����df��Ƶ�ʼ����
			fstart/fend����ι����׵���ʼƵ�ʺ���ֹƵ��
			path�������ļ���·��
		�����/�����أ�2000��-��15,16,17��ʽ
==================================================*/
double SelectFrequenceSegment(double* PSA,double DX,int mr,double df,double fstart,double fend,char* path)
{
	vector<double>segment1,f1;
	for (int i = 0; i < mr; i++)
	{
		double f=df*i;
		if (f<fend && f>fstart)
		{
			f1.push_back(f);
			segment1.push_back(PSA[i]);
		}
	}
	char outfile1[300];
	sprintf(outfile1,"%s\\����������%.2E-%.2E.dat",path,fstart,fend);
	WriteDat(outfile1,f1,segment1);
	//��ϵ�һ��
	int rows=segment1.size(),columns=2;
	double** A=new double*[rows],*B=new double[rows],*X=new double[2];
	for (int i = 0; i < rows; i++)
	{
		A[i]=new double[2];
	}
	for (int i = 0; i < rows; i++)
	{
		A[i][0]=f1[i];
		A[i][1]=1.0;
		B[i]=segment1[i];
	}
	SolveEquation(A,X,B,rows,columns);
	//�������ֱ��ɢ��
	for (int i = 0; i < f1.size(); i++)
	{
		segment1[i]=X[0]*f1[i]+X[1];
	}
	char outfile2[300];
	sprintf(outfile2,"%s\\����������%.2E-%.2E���.dat",path,fstart,fend);
	WriteDat(outfile2,f1,segment1);

	//���������ߵ�б�ʺͽؾ�
	char outfile3[300];
	sprintf(outfile3,"%s\\����������%.2E-%.2E��ϲ���.dat",path,fstart,fend);
	FILE* fpLineInfo;
	if ((fpLineInfo=fopen(outfile3,"w"))==NULL)
	{
		printf("�� %s ʧ��\n");return -1;
	}
	fprintf(fpLineInfo,"б��:\t%lf\n�ؾ�:\t%lf\n���:%lf",X[0],X[1],df);
	fclose(fpLineInfo);
	//����ֱ��б�ʼ����Ч���ʼ���
	double h=0;
	h=fabs(X[0])/(4*PI)*DX;
	//�ͷ��ڴ�
	for (int i = 0; i < rows; i++)
	{
		delete A[i];
	}
	delete B,X,A;
	return h;
}

/*================================================================
�������ܣ� ����QR�ֽⷨ����Ч����Ϸ�����
��������� PSA�������ף�mr�������׵�����df��Ƶ�ʼ����
			S����Ч��ǿ��
			depth����ͬ��Ч�����
			layernum����Ч�����
			path�������ļ���·��
		�����/�����أ�2000��-��15,16,17��ʽ
=================================================================*/
double EquivalentLayerModel(double* PSA,int mr,double* S,double* depth,double layernum,double df,char* path)
{
	int rows=mr,columns=layernum;
	double** T=new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		T[i]=new double[columns];
	}
	//ΪT��ֵ
	for (int i = 0; i < rows; i++)
	{
		double f=df*i;
		for (int j = 0; j < columns; j++)
		{
			double h=depth[j];
			T[i][j]=exp(-4*PI*f*h);
		}
	}
	//�ⷽ��
	SolveEquation(T,S,PSA,rows,columns);
	//�����С������ϼ����S
	char outfile3[300];
	sprintf(outfile3,"%s\\����������-��Ч��ǿ��.dat",path);
	FILE* fpLineInfo;
	if ((fpLineInfo=fopen(outfile3,"w"))==NULL)
	{
		printf("�� %s ʧ��\n");return -1;
	}
	for (int i = 0; i < layernum; i++)
	{
		fprintf(fpLineInfo,"S%d:\t%lf\n",i,S[i]);
	}
	fclose(fpLineInfo);
	//����S���¼��㹦����
	for (int i = 0; i < rows; i++)
	{
		double temp=0;
		for (int j = 0; j < layernum; j++)
		{
			temp+=T[i][j]*S[j];
		}
		PSA[i]=temp;
	}
	//�ͷ��ڴ�
	for (int i = 0; i < rows; i++)
	{
		delete T[i];
	}
	delete T;
	return 0;
}


/*================================================
�������ܣ� ˮƽһ�׵���
���������  ԭʼ���ݶ�ά����ָ�룻�󵼺�Ķ�ά����ָ�룻
		   ������������dx��dy��
		   Derivangle������Ƕ�
==================================================*/
bool HorizontalGradient(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy,const double Derivangle)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i][j];
	
//..�任���̣����Ĵ���
		double h,df,pjg,em,emn,en,tp,co,si;
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));
		co=(double)cos(PI*Derivangle/180.); 
		si=(double)sin(PI*Derivangle/180.);

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);

		fft(zr,zi,m1,n1,me,ne,0);
		double u1,u2,v1,v2,x11,x21,x12,x22;
		double AC11,AC12,AC21,AC22;
		double y11,y12,y21,y22,w11,w12,w21,w22,temp;
		int i1,j1;
		for(int i=0;i<(m1/2);i++)
			{	
				u1=(double)i/em+1E-10; u2=(double)(i-m1/2)/em+1E-10; i1=m1/2+i;
				for(int j=0;j<(n1/2);j++)
				{	
					v1=(double)j/en+1E-10; v2=(double)(j-n1/2)/en+1E-10; j1=n1/2+j;
					x11=tp*(u1*co+v1*si); x12=tp*(u1*co+v2*si);
					x21=tp*(u2*co+v1*si); x22=tp*(u2*co+v2*si);
					y11=(double)sqrt(u1*u1+v1*v1); y12=(double)sqrt(u1*u1+v2*v2);
					y21=(double)sqrt(u2*u2+v1*v1); y22=(double)sqrt(u2*u2+v2*v2);
					w11=tp*y11; w12=tp*y12;
					w21=tp*y21; w22=tp*y22;
					AC11=AC12=AC21=AC22=(double)1;	
					
					//========================ˮƽһ�ε���============================
					temp=zr[i][j]; zr[i][j]=-zi[i][j]*x11; zi[i][j]=temp*x11;
					temp=zr[i][j1]; zr[i][j1]=-zi[i][j1]*x12; zi[i][j1]=temp*x12;
					temp=zr[i1][j]; zr[i1][j]=-zi[i1][j]*x21; zi[i1][j]=temp*x21;
					temp=zr[i1][j1]; zr[i1][j1]=-zi[i1][j1]*x22; zi[i1][j1]=temp*x22;
					//====================================================================
				
				}
			}
		//.. ��任
  		fft(zr,zi,m1,n1,me,ne,1);

		//..�任�����ݸ�ֵ
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				TransData[i][j]=zr[i+np][j+nq];

		//����ָ��
		delete zi,zr;
		return true;
}	

/*================================================
�������ܣ�����һ�׵���
���������  ԭʼ���ݶ�ά����ָ�룻�󵼺�Ķ�ά����ָ�룻
		   ������������dx��dy��
		   
==================================================*/
bool VerticalGradient(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy)
{
	int m=rows; int n=columns;
	int me,ne,m1,n1,np,nq;
//To determine the size of arrays for FFT ///////////////////////////////////////
		if(m==1)
		{   me=0; m1=1; np=0;	}
		else
		{   me=4; m1=(int)(pow(2,me)+.001);
			while(m>=(m1-12))
			{   me++; m1=(int)(pow(2,me)+.001);	}
		}
		ne=4; n1=(int)(pow(2,ne)+.001);
		while(n>=(n1-12))
		{   ne++; n1=(int)(pow(2,ne)+.001);
		}
		np=(int)((m1-m)/2+.001); nq=(int)((n1-n)/2+.001);

		int mj=m1; int nj=n1;
		double **zr,**zi;
		zr=new double* [mj];	zi=new double* [mj];	
		zr[0]=new double [mj*nj]; zi[0]=new double [mj*nj]; 
		for(int i=1;i<mj;i++)
		{	zr[i]=zr[i-1]+nj; zi[i]=zi[i-1]+nj; }
//////////////////////////////////////////////////////////////
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				zr[i][j]=OriginalData[i][j];
	
//..�任���̣����Ĵ���
		double h,df,pjg,em,emn,en,tp;
		em=dx*(double)(m1-1); en=dy*(double)(n1-1); tp=(double)(2*PI);
		emn=(double)(0.5*sqrt(m1*m1/(em*em)+n1*n1/(en*en)));
		df=(double)(5.*sqrt(1./(em*em)+1./(en*en)));

		pjg=prep(zr,zi,m,n,m1,n1,np,nq);

		fft(zr,zi,m1,n1,me,ne,0);
		double u1,u2,v1,v2,x11,x21,x12,x22;
		double AC11,AC12,AC21,AC22;
		double y11,y12,y21,y22,w11,w12,w21,w22,temp;
		int i1,j1;
		for(int i=0;i<(m1/2);i++)
			{	
				u1=(double)i/em+1E-10; u2=(double)(i-m1/2)/em+1E-10; i1=m1/2+i;
				for(int j=0;j<(n1/2);j++)
				{	
					v1=(double)j/en+1E-10; v2=(double)(j-n1/2)/en+1E-10; j1=n1/2+j;
					y11=(double)sqrt(u1*u1+v1*v1); y12=(double)sqrt(u1*u1+v2*v2);
					y21=(double)sqrt(u2*u2+v1*v1); y22=(double)sqrt(u2*u2+v2*v2);
					w11=tp*y11; w12=tp*y12;
					w21=tp*y21; w22=tp*y22;
					AC11=AC12=AC21=AC22=(double)1;	
					AC11*=w11; AC12*=w12; AC21*=w21; AC22*=w22;
					//========================����һ�ε���============================
					zr[i][j]=zr[i][j]*AC11; zi[i][j]=zi[i][j]*AC11;
					zr[i][j1]=zr[i][j1]*AC12; zi[i][j1]=zi[i][j1]*AC12;
					zr[i1][j]=zr[i1][j]*AC21; zi[i1][j]=zi[i1][j]*AC21;
					zr[i1][j1]=zr[i1][j1]*AC22; zi[i1][j1]=zi[i1][j1]*AC22;
					//====================================================================
				
				}
			}
		//.. ��任
  		fft(zr,zi,m1,n1,me,ne,1);

		//..�任�����ݸ�ֵ
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				TransData[i][j]=zr[i+np][j+nq];

		//����ָ��
		delete zi,zr;
		return true;
}	


/*================================================
�������ܣ�Tit Angle����
���������  ԭʼ���ݶ�ά����ָ�룻б�����Ķ�ά����ָ�룻
		   ������������dx��dy��
		   
==================================================*/
bool TitlAngle(double** const OriginalData,double** TransData,const int rows,const int columns,const double dx,const double dy)
{
	double** GradientX=new double*[rows],**GradientZ=new double*[rows],**GradientY=new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		GradientX[i]=new double[columns];
		GradientY[i]=new double[columns];
		GradientZ[i]=new double[columns];
	}
	//1. ����X������
	HorizontalGradient(OriginalData,GradientX,rows,columns,dx,dy,0);
	//2. ����Y������
	HorizontalGradient(OriginalData,GradientY,rows,columns,dx,dy,90);
	//3. ����Z������
	VerticalGradient(OriginalData,GradientZ,rows,columns,dx,dy);
	//4. ������б��
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			TransData[i][j]=atan2(GradientZ[i][j],sqrt(pow(GradientX[i][j],2)+pow(GradientY[i][j],2)))/PI*180.0;
			//TransData[i][j]=GradientX[i][j];
		}
	}
	//�ͷ��ڴ�ռ�
	for (int i = 0; i < rows; i++)
	{
		delete GradientX[i];
		delete GradientY[i];
		delete GradientZ[i];
	}
	delete GradientX,GradientY,GradientZ;
	return true;
}