#include <iostream>

// vetor p c++ 
// class Vetor {	
// 	private:
// 		// atributos
// 		int *V; // Estrutura de armazenamanto do Vetor
// 		int n;	// número de elementos armazenados no Vetor
// // void Vetor::merge(int low, int mid, int high)
// // {
// 	int n1 = mid - low + 1; 
// 	int n2 = high - mid;          
// 	int left[n1 + 1], right[n2 + 1];
// 	int i = 0, j = 0; // i e j locais à função
// 	for (int i = 0; i < n1; i++) // i local ao laço
// 		left[i] = this->V[low + i];
// 	for (int j = 0; j < n2; j++) // j local ao laço
// 		right[j] = this->V[mid + 1 + j];
// 	left[n1] = INT_MAX;
// 	right[n2] = INT_MAX;
	
// 	for (int k = low; k <= high; k++)
// 		if (left[i] <= right[j])
// 			this->V[k] = left[i++];
// 		else
// 		{
// 			this->V[k] = right[j++];
// 		}
// }

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