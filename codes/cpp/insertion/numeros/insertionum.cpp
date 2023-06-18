#include <iostream>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <time.h>

using namespace std;

class Vetor {	
	public:
		int *V; // Estrutura de armazenamanto do Vetor
		int n;	// número de elementos armazenados no Vetor

		Vetor(int tam);

};


Vetor::Vetor(int tam)
{
	if (tam < 0)
	{
		n = 0;
		V = NULL;
	}
	else
	{
		n = tam;
    	V = new int[n];
    	if (V == NULL)
    	{
			cerr << "Erro 1: Não é possível construir um vetor com tamanho\n ";
			cerr << n << ".";
	 		exit(1);
      	}
      	else
      	{
	 		for (int i = 0; i < n; i++)
	    	V[i] = 0;
      	}
   	}
}


int main() {
    double time_spent = 0.0;
    ifstream in("numeros.txt");
    Vetor V(100000);
	int aux, trocas, comapara;

    for (int i = 0; i < V.n; i++) {
        in >> V.V[i];
    }
    clock_t begin = clock();   	

	for (int i = 0; i < 100000; i++)
    {
        for (int j = i + 1; j > 0; j--)
        {   
            comapara++;
            if (V.V[j] < V.V[j - 1])
            {
                aux = V.V[j];
                V.V[j] = V.V[j - 1];
                V.V[j - 1] = aux;
                trocas++;
            }
            else
                break;
        }
    }


	ofstream out("numerosordenados.txt");
	for( int i = 0; i < 100000; i++){
		out << V.V[i] << endl;
	}

	clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << time_spent;


    return 0;
}

    

	