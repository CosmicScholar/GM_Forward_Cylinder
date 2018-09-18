#include<iostream.h>
#include<stdio.h>
#include<math.h>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

const double I=45; // ����������� ��λ����
const double A=0;  // ��������ƫ�� ��λ����

string filename; // ԭʼ���쳣
string filename_hax,filename_hay,filename_za;  // ���ڱ�������������Hax��Hay��Za
string filename_Ta,filename_R, filename_E, filename_Q, filename_L; // ���ڱ������ִ��쳣ģ��
string Filename_Ta,Filename_R, Filename_E, Filename_Q, Filename_L; // ���ڱ������ִ��쳣ģ���߽�ʶ����


int XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Z_MIN,Z_MAX;

double open_grd(string Filename1);
double save_grd(string Filename2,,xn,yn,x_min,x_max,y_min,y_max,data[]);
int dew;
int main()
{
	// ��ȡ�ļ�
	[XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Z_MIN,Z_MAX,data]=open_grd("���ֱ��������Delta_T_����ʣ��.grd");
    
	// ����ԭʼ�쳣����������Hax,Hay,Za
	double Hax[YN][XN];
	double Hay[YN][XN];
	double Za[YN][XN];

    Hax=save_grd(filename_hax,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Data[]);
	Hay=save_grd(filename_hay,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Data[]);
	Za=save_grd(filename_za,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Data[]);

    // ��������������������㣬�󵼺����ֱ�Ϊ��
	// Derivative_direction_X��Derivative_direction_Y��Derivative_direction_Z
    
    
    // ������Hax��Hay��Za�ĸ�����ĵ����ֱ�Ϊ:Hax_x��Hax_y��Hax_z
	//                                        Hay_x��Hay_y��Hay_z
	//                                        Za_x��Za_y��Za_z


    // ģ��Ta
	int i,j;
	double Ta[YN][XN];
	for (i=1;i<=YN;i++)
	{
		for (j=1;j<=XN;j++)
		{
			Ta[i][j]=sqrt(Hax[i][j]*Hax[i][j]+Hay[i][j]*Hay[i][j]+Za[i][j]*Za[i][j]);
		}
	}


    // ģ��R
    double Tax[YN][XN];	
	double Tay[YN][XN];
	double Taz[YN][XN];
	double R[YN][XN];
    for (i=1;i<=YN;i++)
	{
		for (j=1;j<=XN;j++)
		{
			Tax[i][j]=(Hax[i][j]*Hax_x[i][j]+Hay[i][j]*Hay_x[i][j]+Za[i][j]*Za_x[i][j])/Ta[i][j];
		    Tay[i][j]=(Hax[i][j]*Hax_y[i][j]+Hay[i][j]*Hay_y[i][j]+Za[i][j]*Za_y[i][j])/Ta[i][j];
			Taz[i][j]=(Hax[i][j]*Hax_z[i][j]+Hay[i][j]*Hay_z[i][j]+Za[i][j]*Za_z[i][j])/Ta[i][j];
			R[i][j]=sqrt(Tax[i][j]*Tax[i][j]+Tay[i][j]*Tay[i][j]+Taz[i][j]*Taz[i][j]);
		}
	}


   // ģ��E
	double Theta_Hx[YN][XN];
    double Theta_Hy[YN][XN];
	double Theta_Za[YN][XN];
	double E[YN][XN];
    for (i=1;i<=YN;i++)
	{
		for (j=1;j<=XN;j++)
		{
			Theta_Hx[i][j]=Hax_x[i][j]*Hax_x[i][j]+Hax_y[i][j]*Hax_y[i][j]+Hax_z[i][j]*Hax_z[i][j];
			Theta_Hy[i][j]=Hay_x[i][j]*Hay_x[i][j]+Hay_y[i][j]*Hay_y[i][j]+Hay_z[i][j]*Hay_z[i][j];
			Theta_Za[i][j]=Za_x[i][j]*Za_x[i][j]+Za_y[i][j]*Za_y[i][j]+Za_z[i][j]*Za_z[i][j];
            E[i][j]=sqrt((Theta_Hx[i][j]+Theta_Hy[i][j]+Theta_Za[i][j])/2);
		}
	}

 
    // ģ��Q
    double Q[YN][XN];
	for (i=1;i<=YN;i++)
	{
		for (j=1;i<=XN;j++)
		{
			Q[i][j]=sqrt(fabs(2*E[i][j]*E[i][j]-R[i][j]*R[i][j]));
		}
	}

   // ģ��L
	double L[YN][XN];
	for (i=1;i<=YN;i++)
	{
		for (j=1;j<=XN;j++)
		{
			L[i][j]=Q[i][j]*Q[i][j]/Ta[i][j];
		}
	}

    // ��ģ���ķ������ֱ�Ϊ��Ta_x��Ta_y��Ta_z; R_x��R_y��R_z
    //                         E_x��E_y��E_z; Q_x��Q_y��Q_z; L_x��L_y��L_z
    
	Ta_x=
    Ta_y=
    Ta_z=

    R_x=
    R_y=
    R_z=

    E_x=
    E_y=
    E_z=

    Q_x=
	Q_y=
	Q_z=

	L_x=
	L_y=
	L_z=

    double Ta_Alplitude[YN][XN];
	double R_Alplitude[YN][XN];
	double E_Alplitude[YN][XN];
	double Q_Alplitude[YN][XN];
	double L_Alplitude[YN][XN];

	double Ta_Tdr_improved[YN][XN]; // �Ľ��͵�Tilt����
	double R_Tdr_improved[YN][XN];
	double E_Tdr_improved[YN][XN];
	double Q_Tdr_improved[YN][XN];
	double L_Tdr_improved[YN][XN];

    for (i=1;i<=YN;i++)
	{
		for (j=1;j<=XN;j++)
		{
			// ��ģ�������ݶ�ģ
			Ta_Alplitude[i][j]=sqrt(Ta_x[i][j]*Ta_x[i][j]+Ta_y[i][j]*Ta_y[i][j]+Ta_z[i][j]*Ta_z[i][j]);
			R_Alplitude[i][j]=sqrt(R_x[i][j]*R_x[i][j]+R_y[i][j]*R_y[i][j]+R_z[i][j]*R_z[i][j]);
			E_Alplitude[i][j]=sqrt(E_x[i][j]*E_x[i][j]+E_y[i][j]*E_y[i][j]+E_z[i][j]*E_z[i][j]);
			Q_Alplitude[i][j]=sqrt(Q_x[i][j]*Q_x[i][j]+Q_y[i][j]*Q_y[i][j]+Q_z[i][j]*Q_z[i][j]);
			L_Alplitude[i][j]=sqrt(L_x[i][j]*L_x[i][j]+L_y[i][j]*L_y[i][j]+L_z[i][j]*L_z[i][j]);
            
			// �Ľ��͵�Tilt���������߽�ʶ����
			Ta_Tdr_improved[i][j]=atan2(Ta_z[i][j],Ta_Alplitude[i][j]);
            R_Tdr_improved[i][j]=atan2(R_z[i][j],R_Alplitude[i][j]);
			E_Tdr_improved[i][j]=atan2(E_z[i][j],E_Alplitude[i][j]);
			Q_Tdr_improved[i][j]=atan2(Q_z[i][j],Q_Alplitude[i][j]);
			L_Tdr_improved[i][j]=atan2(L_z[i][j],L_Alplitude[i][j]);

            // �����ж�
			if Ta_Tdr_improved(i,j)<0
				Ta_Tdr_improved(i,j)=0;
			else if R_Tdr_improved(i,j)<0
				R_Tdr_improved(i,j)=0;
			else if E_Tdr_improved(i,j)<0
				E_Tdr_improved(i,j)=0;
			else if Q_Tdr_improved(i,j)<0
				Q_Tdr_improved(i,j)=0;
			else if L_Tdr_improved(i,j)<0
				L_Tdr_improved(i,j)=0;

		// ������쳣������Hax��Hay��Za ��������
			save_grd;

		// ��������ģ���������ݣ�Ta��R��E��Q��L
			save_grd;
		
		// ��������ģ���߽�ʶ���������ݣ�Ta��R��E��Q��L
            save_grd;


		}
	}


	delete [] obdata;
    return 0;
}





// ���ڶ�ȡgrd�ļ�
double open_grd(filename1)
{
	ifstream infile;
	FILE *fp;
	if ((fp=fopen(filename1,"rb"))==NULL)
	{
		cout<<"�򲻿��ļ�����"<<endl;
		return 0;
	}
    
	string filehead; // �洢ͷ�ļ�DSAA
	getline(infile,filehead);  // ��ȡgrd�����ļ�ͷDSAA
	infile>>XN>>YN>>X_MIN>>X_MAX>>Y_MIN>>Y_MAX>>Z_MIN>>Z_MAX;
    double *obdata=new double [XN*YN];
	for (i=1;i<XN*YN;i++)
	{
		infile>>obdata[i];
	}
	infile.close();

	return 0;
}


// ���ڱ���grd�ļ�
double save_grd(filename2,XN,YN,X_MIN,X_MAX,Y_MIN,Y_MAX,Data[])
{
	ifstream outGrid;
	FILE *fp;
	if ((fp=fopen(filename2,"w"))==NULL)
	{
		cout<<"�򲻿��ļ�����"<<endl;
		return 0;
	}
    outGrid<<"DSAA"<<endl;
	outGrid<<XN<<"  "<<YN<<endl;
	outGrid<<X_MIN<<"  "<<X_MAX<<endl;
    outGrid<<Y_MIN<<"  "<<Y_MAX<<endl;
    
	// ���������еļ���ֵ�ͼ�Сֵ
	double Z_MIN,Z_MAX;
	Z_MIN=Z_MAX=data[0];

    for(i=1;i<XN*YN;i++)
    {
       if(obdata[i]>MAX)
           MAX=obdata[i];
	   else if(obdata[i]<MIN)
		   MIN=obdata[i];
	}

    outGrid<<MIN<<"  "<<MAX<<endl; // �����Сֵ�ͼ���ֵ
	for(i=0;i<datanum;i++)
	{
         outGrid<<obdata[i]<<"  "; // ����۲�����
	}
    outGrid.close();

	return 0;
}
