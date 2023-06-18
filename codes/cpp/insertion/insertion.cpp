#include <iostream>

using namespace std;

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
	 ifstream in("../../nomes.txt");
	std::vector

	return 0;
}