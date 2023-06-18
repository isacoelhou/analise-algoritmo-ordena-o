#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

class Pessoa
{
public:
    int codigo;
    string name;
    Pessoa(){};
    Pessoa(int cod, string nome)
    {
        codigo = cod;
        name = nome;
    }
    void PrintPessoa()
    {
        cout << codigo << ' ' << name << endl;
    }
};

class Vetor
{
public:
    Pessoa* V; // Estrutura de armazenamento do Vetor
    int n;     // número de elementos armazenados no Vetor

    void merge(int low, int mid, int high); // algoritmo de recombinação para MergeSort
    Vetor(int tam);                         // Construtor com tamanho definido
    ~Vetor();                               // Destruidor

    void MergeSort(int low, int high); // ordenação pelo algoritmo MergeSort
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
        V = new Pessoa[n];
        if (V == NULL)
        {
            cerr << "Erro 1: Não é possível construir um vetor com tamanho\n ";
            cerr << n << ".";
            exit(1);
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                V[i].codigo = 0;
                V[i].name = "";
            }
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
    Pessoa* left = new Pessoa[n1 + 1];
    Pessoa* right = new Pessoa[n2 + 1];
    int i = 0, j = 0; // i e j locais à função
    for (int i = 0; i < n1; i++) // i local ao laço
        left[i] = this->V[low + i];
    for (int j = 0; j < n2; j++) // j local ao laço
        right[j] = this->V[mid + 1 + j];
    left[n1].codigo = INT_MAX; // Usamos INT_MAX para representar um valor infinito no contexto de números inteiros
    right[n2].codigo = INT_MAX;

    for (int k = low; k <= high; k++)
    {
        if (left[i].codigo <= right[j].codigo)
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

int main()
{
    ifstream input("pessoa.txt");

    vector<Pessoa> vetor;
    unsigned long long comp = 0, swap = 0;
    clock_t inicio, fim;

    for (int i = 0; i < 100000; i++)
    {
        int id;
        string nome;

        input >> id;
        getline(input, nome);

        vetor.push_back(Pessoa(id, nome));
    }

    input.close();

    Vetor V(vetor.size());
    for (int i = 0; i < vetor.size(); i++)
    {
        V.V[i] = vetor[i];
    }

    double time_spent = 0.0;
    clock_t begin = clock();
    V.MergeSort(0, V.n - 1);
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    for (int i = 0; i < V.n; i++)
    {
        cout << V.V[i].codigo << " " << V.V[i].name << endl;
    }

    cout << "Tempo de execução: " << time_spent << " segundos" << endl;

    return 0;
}
