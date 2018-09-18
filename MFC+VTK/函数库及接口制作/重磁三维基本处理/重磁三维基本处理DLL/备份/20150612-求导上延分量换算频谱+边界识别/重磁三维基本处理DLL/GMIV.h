//3GMIV.CPP
  //�ù����淨�����С��������
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;

#ifndef GMIV
#define GMIV
  class  gmiv
  {
  private: 
           int m, n, ka;
		   double  **a, **u, **v, **aa, *b, *x, eps;
		   double  *s, *e, *w, fg[2], cs[2];
  public:
	       gmiv (int mm, int nn)
		   {
			   int i;
			   m = mm;  n = nn;
	           a = new double*[m];   //��̬�����ڴ�ռ�
	           for (i=0; i<m; i++) a[i] = new double[n];
	           u = new double*[m];
	           for (i=0; i<m; i++) u[i] = new double[m];
	           v = new double*[n];
	           for (i=0; i<n; i++) v[i] = new double[n];
	           aa = new double*[n];
	           for (i=0; i<n; i++) aa[i] = new double[m];
	           b = new double[m];
	           x = new double[n];
               ka = m + 1;
	           if (m < n)  ka = n + 1;
               s = new double[ka];
               e = new double[ka];
               w = new double[ka];
		   }
	       void input ();   //���ļ��������A�볣������B�Լ�eps
		   void input(double** A,double* B,double error);
		   void uav ();          //����ֵ�ֽ�
           void ppp();            //����ֵ�ֽ���ӳ���
           void sss();            //����ֵ�ֽ���ӳ���
		   void ginv ();         //��A�Ĺ�����
		   void a_gmiv ();       //������С���˽�
		   void output ();  //����������Լ���С���˽⵽�ļ�����ʾ
		   void output(double* X);
		   ~gmiv ()
		   {
			   int i;
			   for (i=0; i<m; i++) { delete [] a[i]; }
			   delete [] a;
			   for (i=0; i<m; i++) { delete [] u[i]; }
			   delete [] u;
			   for (i=0; i<n; i++) { delete [] v[i]; }
			   delete [] v;
			   for (i=0; i<n; i++) { delete [] aa[i]; }
			   delete [] aa;
			   delete [] b, x;
			   delete [] s, e, w;
		   }
  };

#endif