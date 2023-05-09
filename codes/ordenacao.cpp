#include <iostream>

using namespace std;

template <class T>
void escreve(T V[], int n)
{
	cout << "[";
	for (int i = 0; i < n; i++)
	{
		cout << V[i];
		if (i < n - 1)
			cout << ", ";
	}
	cout << "]";
}


template <class T>
void InsertionSort(T dados[], int n)
{
   for (int i = 1; i < n; i++)
   {
		T aux = dados[i];
		int j = 0;
      for (j = i; (j > 0) && (aux < dados[j-1]); j--)
         dados[j] = dados[j - 1];
      dados[j] = aux;
   }
}


int main()
{
	return 0;
}