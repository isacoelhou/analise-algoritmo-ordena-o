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

    void merge(int low, int mid, int high); // algoritmo de recombinação para MergeSort
    Vetor(int tam);           // Construtor com tamanho definido
    ~Vetor();                // Destruidor

    void MergeSort(int low, int high);    // ordenação pelo algoritmo MergeSort
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

Vetor::~Vetor()
{
    delete[] V;
}

// Algoritmo de partição merge
void Vetor::merge(int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    string* left = new string[n1 + 1];
    string* right = new string[n2 + 1];
    int i = 0, j = 0; // i e j locais à função
    for (int i = 0; i < n1; i++) // i local ao laço
        left[i] = this->V[low + i];
    for (int j = 0; j < n2; j++) // j local ao laço
        right[j] = this->V[mid + 1 + j];
    left[n1] = "~"; 
    right[n2] = "~";

    for (int k = low; k <= high; k++)
    {
        if (left[i] <= right[j])
            this->V[k] = left[i++];
        else
            this->V[k] = right[j++];
    }

    delete[] left;
    delete[] right;
}

// Algoritmo de ordenação mergesort
void Vetor::MergeSort(int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSort(low, mid);
        MergeSort(mid + 1, high);
        merge(low, mid, high);
    }
}

int main() {
    double time_spent = 0.0;
    ifstream in("nomes.txt");
    string palavra;
    
    Vetor V(100000);
    in.clear();
    in.seekg(0, ios::beg);
    for (int i = 0; i < V.n; i++) {
        getline(in, V.V[i]);
    }
    clock_t begin = clock();
    V.MergeSort(0, V.n - 1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    
    ofstream out("nomesordenados.txt");
    for (int i = 0; i < V.n; i++) {
        out << V.V[i] << endl;
    }

    cout << "Tempo de execução: " << time_spent << " segundos" << endl;

    return 0;
}
