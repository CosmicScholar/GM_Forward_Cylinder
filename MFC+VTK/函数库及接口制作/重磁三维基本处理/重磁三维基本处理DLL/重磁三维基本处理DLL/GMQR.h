//3GMQR.CPP
  //��Householder�任���������С��������
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;

#ifndef GMQR
#define GMQR

  class  gmqr
  {
  private: 
           int m, n;
		   double  **a, **q, *b;
  public:
	       gmqr (int mm, int nn)
		   {
			   int i;
			   m = mm; n = nn;
	           a = new double*[m];   //��̬�����ڴ�ռ�
	           for (i=0; i<m; i++) a[i] = new double[n];
	           q = new double*[m];
	           for (i=0; i<m; i++) q[i] = new double[m];
	           b = new double[m];
		   }
	       void input ();    //���ļ�����ϵ������A�볣������B
		   void input(double** A,double* B);
		   void qr ();       //QR�ֽ�
		   void a_gmqr ();   //������С���˽�
           void output ();   //���Q��R�����Լ���С���˽⵽�ļ�����ʾ
		   void output(double* X);
		   ~gmqr ()
		   {
			   int i;
			   for (i=0; i<m; i++) { delete [] a[i]; }
			   delete [] a;
			   for (i=0; i<m; i++) { delete [] q[i]; }
			   delete [] q;
			   delete [] b;
		   }
  };

#endif