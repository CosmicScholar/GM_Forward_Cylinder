//#include "stdafx.h"
#include "�ļ�����.h"

vector<double> ReadGrd(char* infile,GridDataInfo& datainfo)
{
//	int i;
	FILE* fp=NULL;
	if ((fp=fopen(infile,"r"))==NULL)
	{
		printf("error in ReadGrd\n");
		exit(0);
	}
	vector<double> grav0;
	char dsaa[100];
	//��ȡ�ļ�ͷ
	fscanf(fp,"%s%d%d%lf%lf%lf%lf%lf%lf",dsaa,&datainfo.columns,&datainfo.rows,&datainfo.gridXmin,&datainfo.gridXmax,&datainfo.gridYmin,
		&datainfo.gridYmax,&datainfo.gridZmin,&datainfo.gridZmax);
	double temp;
	while (!feof(fp))
	{
		fscanf(fp,"%lf",&temp);
		grav0.push_back(temp);
	}fclose(fp);
	//�����߾�͵��
	datainfo.deltX=(datainfo.gridXmax-datainfo.gridXmin)/(datainfo.columns-1);
	datainfo.deltY=(datainfo.gridYmax-datainfo.gridYmin)/(datainfo.rows-1);
	
	return grav0;
}

void WriteGrd(char *filename,double* z,const int dataNumber,int m,int n,double xmin,double xmax,double ymin,double ymax)
{
	int i;
	FILE* fp=NULL;
	if ((fp=fopen(filename,"w"))==NULL)
	{
		printf("��%sʧ��\n");
		exit(0);
	}
	//�����Сֵ����
	double zmin,zmax;
	zmax=zmin=z[0];
	for (i=0;i<dataNumber;i++)
	{
		if(zmax<z[i])zmax=z[i];
		if(zmin>z[i])zmin=z[i];
	}
	//д�ļ�ͷ
	fprintf(fp,"DSAA\n%d\t%d\n%lf\t%lf\n%lf\t%lf\n%lf\t%lf\n",n,m,xmin,xmax,ymin,ymax,zmin,zmax);
	for (i=0;i<dataNumber;i++)
	{
		fprintf(fp,"%lf  ",z[i]);
		if (i%n==0)
		{
			fprintf(fp,"\n");
		}
	}fclose(fp);
}
void ReadDat(char* filename,vector<double>& x,vector<double>& y,double& dx)
{
	FILE* fp=NULL;
	if ((fp=fopen(filename,"r"))==NULL)
	{
		printf("error in ReadDat\n");
		exit(0);
	}
	double tempx,tempy;
	while (!feof(fp))
	{
		fscanf(fp,"%lf%lf",&tempx,&tempy);
		x.push_back(tempx);
		y.push_back(tempy);
	}fclose(fp);
	if (x[x.size()-1]==x[x.size()-2])
	{
		x.pop_back();
		y.pop_back();
	}
	dx=fabs(x[2]-x[1]);
}

void WriteDat(char* filename,vector<double> x,double* y)
{
	FILE* fp=NULL;
	if ((fp=fopen(filename,"w"))==NULL)
	{
		printf("error in ReadDat\n");
		exit(0);
	}
	for (int i = 0; i < x.size(); i++)
	{
		fprintf(fp,"%lf\t%lf\n",x[i],y[i]);
	}
	fclose(fp);
}
void WriteDat(char* filename,const int datanum,double* x,double* y)
{
	FILE* fp=NULL;
	if ((fp=fopen(filename,"w"))==NULL)
	{
		printf("�� %s ʧ��\n",filename);
		exit(0);
	}
	for (int i = 0; i < datanum; i++)
	{
		fprintf(fp,"%lf\t%lf\n",x[i],y[i]);
	}
	fclose(fp);
}
void WriteDat(char* filename,const int datanum,double xmin,double dx,double* y)
{
	FILE* fp=NULL;
	if ((fp=fopen(filename,"w"))==NULL)
	{
		printf("�� %s ʧ��\n",filename);
		exit(0);
	}
	for (int i = 0; i < datanum; i++)
	{
		fprintf(fp,"%lf\t%.5E\n",xmin+i*dx,y[i]);
	}
	fclose(fp);
}
void WriteDat(char* filename,vector<double>x,vector<double> y)
{
	FILE* fp=NULL;
	if ((fp=fopen(filename,"w"))==NULL)
	{
		printf("�� %s ʧ��\n",filename);
		exit(0);
	}
	for (int i = 0; i < x.size(); i++)
	{
		fprintf(fp,"%lf\t%lf\n",x[i],y[i]);
	}
	fclose(fp);
}
/*================================================================================================================
��������:��һ��GRD�ļ��������ߴ���Ȼ�󱣴��ļ��滻ԭ�ļ�
����:
	filename����Ҫ���ߵ������ļ���
	ShinkXnum1/ShinkXnum2��x��������������ݸ�����x�����ұ��������ݸ���
	ShinkYnum1/ShinkYnum2��y�����±��������ݸ�����y�����ϱ��������ݸ���
================================================================================================================*/
void ShinkGrd(char* filename,const int ShinkXnum1,const int ShinkXnum2,const int ShinkYnum1,const int ShinkYnum2)
{
	GridDataInfo datainfo;
	FILE* fp=NULL;
	if ((fp=fopen(filename,"r"))==NULL)
	{
		printf("error in ReadGrd\n");
		exit(0);
	}
	vector<double> grav0;
	char dsaa[100];
	//��ȡ�ļ�ͷ
	fscanf(fp,"%s%d%d%lf%lf%lf%lf%lf%lf",dsaa,&datainfo.columns,&datainfo.rows,&datainfo.gridXmin,&datainfo.gridXmax,&datainfo.gridYmin,
		&datainfo.gridYmax,&datainfo.gridZmin,&datainfo.gridZmax);
	double temp;
	while (!feof(fp))
	{
		fscanf(fp,"%lf",&temp);
		grav0.push_back(temp);
	}fclose(fp);
	//�����߾�͵��
	datainfo.deltX=(datainfo.gridXmax-datainfo.gridXmin)/(datainfo.columns-1);
	datainfo.deltY=(datainfo.gridYmax-datainfo.gridYmin)/(datainfo.rows-1);
	
	//���ߴ���
	int m,n;
	double xmin,xmax,ymin,ymax,zmin,zmax;
	m=datainfo.rows-ShinkYnum1-ShinkYnum2;
	n=datainfo.columns-ShinkXnum1-ShinkXnum2;
	xmin=datainfo.gridXmin+ShinkXnum1*datainfo.deltX;
	xmax=datainfo.deltX*n+xmin;
	ymin=datainfo.gridYmin+ShinkYnum1*datainfo.deltY;
	ymax=datainfo.deltY*m+ymin;
	zmin=datainfo.gridZmin;
	zmax=datainfo.gridZmax;
	FILE* fpout=NULL;
	if ((fpout=fopen(filename,"w"))==NULL)
	{
		printf("��%sʧ��\n",filename);
		exit(0);
	}
	//д�ļ�ͷ
	fprintf(fp,"DSAA\n%d\t%d\n%lf\t%lf\n%lf\t%lf\n%lf\t%lf\n",n,m,xmin,xmax,ymin,ymax,zmin,zmax);
	for (int i = ShinkYnum1; i <m+ShinkYnum1; i++)
	{
		for (int j = ShinkXnum1; j < n+ShinkXnum1; j++)
		{
			fprintf(fpout,"%lf ",grav0[i*datainfo.columns+j]);
		}
		fprintf(fpout,"\n");
	}fclose(fpout);
}