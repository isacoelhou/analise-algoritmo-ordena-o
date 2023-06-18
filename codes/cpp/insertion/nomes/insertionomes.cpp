#include <iostream>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <time.h>
#include <string>
#include <algorithm>

using namespace std;

class Vetor {
public:
    string* V; // Estrutura de armazenamento do Vetor
    int n;     // número de elementos armazenados no Vetor

    Vetor(int tam);           // Construtor com tamanho definido
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
        V = new string[n];
        if (V == NULL)
        {
            cerr << "Erro 1: Não é possível construir um vetor com tamanho\n ";
            cerr << n << ".";
            exit(1);
        }
        else
        {
            for (int i = 0; i < n; i++)
                V[i] = "";
        }
    }
}

int main() {
    double time_spent = 0.0;
    ifstream in("nomes.txt");
    string palavra;
    int trocas, compara;
    Vetor V(100000);
	string aux;
    in.clear();
    in.seekg(0, ios::beg);
    for (int i = 0; i < V.n; i++) {
        getline(in, V.V[i]);
    }
    clock_t begin = clock();


	for (int i = 0; i < V.n - 1; i++)
    {
        for (int j = i + 1; j > 0; j--)
        {
            compara++;
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

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    
    ofstream out("ordenados.txt");

    for (int i = 0; i < V.n; i++) {
        out << V.V[i] << endl;
    }

    out.close(); 

    cout << "Tempo de execução: " << time_spent << " segundos" << endl;

    return 0;
}
