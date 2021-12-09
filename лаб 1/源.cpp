#include<iostream>
#include<algorithm>

using namespace std;

double* Gauss(double** Array_A, double* Array_B, int n)
{
	double* X = new double[n];
	for (int k = 0; k < n; k++)
	{
		for (int i = k + 1; i < n; i++)
		{
			if (abs(Array_A[i][k]) > abs(Array_A[k][k]))
			{
				swap(Array_A[i], Array_A[k]);
				swap(Array_B[i], Array_B[k]);
			}
		}
		double A_Main = Array_A[k][k];
		if (A_Main == 0)
		{
			cout << "error\n";
			system("pause");
			exit(0);
		}
		for (int i = k; i < n; i++)
		{
			Array_A[k][i] /= A_Main;
		}
		Array_B[k] /= A_Main;
		for (int i = k + 1; i < n; i++)
		{
			double s = Array_A[i][k];
			for (int j = k; j < n; j++)
			{
				Array_A[i][j] -= s * Array_A[k][j];
			}
			Array_B[i] -= s * Array_B[k];
		}
	}
	for (int k = n - 1; k >= 0; k--)
	{
		X[k] = Array_B[k];
		for (int i = n - 1; i > k; i--)
		{
			X[k] -= Array_A[k][i] * X[i];
		}
	}
	return X;
}
double* Res_vectorF(double** Array_A, double* Array_B, double* X, int n)
{
	double* result = new double[n];
	for (int i = 0; i < n; i++)
	{
		result[i] = -Array_B[i];
		for (int j = 0; j < n; j++)
		{
			result[i] += Array_A[i][j] * X[j];
		}
	}
	return result;
}

double norma(double* F, int n)
{
	double Norma = abs(F[0]);
	for (int i = 0; i < n; i++)
	{
		Norma = max(F[i], Norma);
	}
	return Norma;
}

double* Vector_B(double** Array_A, double* X, int n)
{
	double* B = new double[n];
	for (int i = 0; i < n; i++)
	{
		B[i] = 0;
		for (int j = 0; j < n; j++)
		{
			B[i] += Array_A[i][j] * X[j];
		}
	}
	return B;
}


double* difference(double* X1, double* X2, int n)
{
	double* x = new double[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = X2[i] - X1[i];
	}
	return x;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int n;
	cout << "n: ";
	do
	{
		cin >> n;
	} while (n < 0);
	double** Array_A = new double* [n];
	double* Array_B = new double[n];
	double** Copy_A = new double* [n];
	double* Copy_B = new double[n];
	
	cout << "Please enter the elements of Array_A:" << endl;
	for (int i = 0; i < n; i++)
	{
		Array_A[i] = new double[n];
		Copy_A[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			cin >> Array_A[i][j];
			Copy_A[i][j] = Array_A[i][j];
		}
	}

	cout << "Please enter the elements of Array_B: " << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> Array_B[i];
		Copy_B[i] = Array_B[i];
	}
	double* X = Gauss(Array_A, Array_B, n);
	
	cout << "result: " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "X[" << i << "]: " << X[i] << " ";
	}
	cout << endl;

	double* F = Res_vectorF(Copy_A, Copy_B, X, n);
	cout << "\nresidual vector F:\n";
	for (int i = 0; i < n; i++)
	{
		cout << "F[" << i << "]: " << F[i] << " ";
	}
	cout << endl;
	cout << "Norma of the residual vector F:";
	double Norma = norma(F, n);
	cout << Norma;
	double* B = Vector_B(Copy_A, X, n);

	double* X2 = Gauss(Copy_A, B, n);

	cout << "Assistant system solution:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "X2["<<i<<"]: "<< X2[i] << " ";
	}
	cout << endl;
	cout  <<"estimates of relative errors:"<< norma(difference(X, X2, n), n) / norma(X, n);
	cout << endl;
	system("pause");
	return 0;
}





