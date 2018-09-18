  //3GJDN.CPP
  //ȫѡ��ԪGauss-Jordan��ȥ�����ʵϵ��������
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;

#ifndef GSXY
#define GSXY

  class  gjdn
  {
  private: 
           int n, m;
		   double  **a, **b;
  public:
	       gjdn (int nn, int mm)
		   {
			   int i;
			   n = nn; m = mm;
	           a = new double*[n];   //��̬�����ڴ�ռ�
	           for (i=0; i<n; i++) a[i] = new double[n];
	           b = new double*[n];
	           for (i=0; i<n; i++) b[i] = new double[m];
		   }
	       void input ();        //���ļ�����ϵ������A�Լ�m�鳣������B
		   void gauss_jordan ();      //ִ��Gauss-Jordan��ȥ��
           void output ();       //���������ļ�����ʾ
		   ~gjdn ()
		   {
			   int i;
			   for (i=0; i<m; i++) { delete [] a[i]; }
			   delete [] a;
			   delete [] b;
		   }

		   void InPut(double** A, double* B)
		   {
			   for (int i = 0; i < n; i++)
			   {
				   for (int j = 0; j < n; j++)
				   {
					   a[i][j]=A[i][j];
				   }
				   b[i][0]=B[i];
			   }
		   }

		   void OutPut(double* X)
		   {
			   for(int i=0;i<n;i++)
			   {
				   X[i]=b[i][0];
			   }
		   }
  };

#endif