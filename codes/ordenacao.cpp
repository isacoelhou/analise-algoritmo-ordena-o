#include <iostream>
#include <cstdlib>
#include <climits>
#include <fstream>

using namespace std;

class Vetor {
	private:
    	int n;									// O número de elementos do vetor;
    	int *V;									// A estrutura que armazena os elementos
    	void swap(int &a, int &b);				// Método auxiliar para troca
    	void realloc(); 						// método auxiliar para realocar o vetor V.
		void merge(int low, int mid, int high);

	public:
    	// Construtores e destruidores
    	Vetor();				// Construtor default
    	Vetor(int tam);			// Construtor com tamanho definido
    	Vetor(const Vetor &A);	// Construtor de cópia
    	~Vetor();				// Destruidor
		
		// Outros métodos
		int len();						// retorna o número de elementos do vetor
    	void add(int valor);			// Adiciona mais uma posição ao final do vetor e 
				        				// lhe atribui "valor";
		int get(int i);	   				// obtem o valor armazenado na posição i do vetor
		void set(int i, int v);			// seta o valor v na posição i do vetor
		int operator[](int i) const; 	// sobrecarga do operador [] para leitura
		int &operator[](int i); 		// sobrecarga do operador [] para escrita
		void escreve();					// escreve o vetor

		// Métodos de ordenação 
		void InsertionSort();				// ordenação pelo algoritmo de inserção
		void MergeSort(int low, int high); 	// ordenação pelo algoritmo MergeSort
};

Vetor::Vetor()
{
	// construtor default
	cout << "Construtor default construindo vetor...\n";
	n = 0;
	V = NULL;
	cout << "Vetor construido.\n";
}

Vetor::Vetor(int tam)
{
	cout << "Construtor inicializável construindo vetor...\n";
	if (tam < 0)
	{
		cerr << "Erro: o número de elementos não pode ser negativo.\n";
		cerr << "Ajustando número de elementos para zero.\n";
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
   	cout << "Vetor construído\n";
}

Vetor::Vetor(const Vetor &A)
{
	cout << "Construtor de cópia construindo Vetor...\n";
	this->n = A.n;
	V = new int[this->n];
	if (V == NULL)
	{
		cerr << "Erro 2: Não é possível criar a cópia do vetor.";
    	exit(2);
	}
	for (int i = 0; i < this->n; i++)
	{
    	this->V[i] = A.V[i];
	}
	cout << "Vetor construído.";
}

Vetor::~Vetor()
{
	cout << "Destruindo Vetor...\n";
	delete[] V;
	cout << "Vetor destruído\n";
}

void Vetor::realloc()
{
	if (n == 0) // Não há elementos no vetor;
	{
    	V = new int[++n];
    	if (V == NULL) // Alocação falhou
    	{
			cerr << "Erro 3: Não é possível redimensionar o vetor.";
        	exit(3);
    	}
	}
	else
	{
    	int *aux = new int[n];
    	if (aux == NULL)
    	{
        	cerr << "Erro 3: Não é possível redimensionar o vetor.";
        	exit(3);
    	}
    	for (int i = 0; i < (n); i++)
		aux[i] = V[i];
    	delete[] V;
    	V = new int [++n];
    	if (V == NULL)
    	{
        	cerr << "Erro 3: Não é possível redimensionar o vetor.";
        	exit(3);
    	}
    	for (int i = 0; i < (n - 1); i++)
			V[i] = aux[i];
    	
		V[n - 1] = 0;
    	delete[] aux;
	}
	return;
}

int Vetor::len()
{
	return this->n;
}

void Vetor::add(int valor)
{
   realloc();
   V[n-1] = valor;
   return;
}

int Vetor::get(int i)
{
   if ((i < 0) || (i > n))
   {
      cerr << "Erro: Tentativa de acesso fora dos limites do vetor.\n";
      return 0;
   }
   else
      return V[i];
}

void Vetor::set(int i, int v)
{
   if ((i < 0) || (i > n))
   {
      cerr << "Erro: Tentativa de acesso fora dos limites do vetor.\n";
      cerr << "Atribuição abortada.\n";
      return;
   }
   else
   {
      V[i] = v;
   }
}

int Vetor::operator[](int i) const
{
   if ((i < 0) || (i >= n))
   {
      cerr << "\nErro: Tentativa de acesso fora dos limites do vetor.\n";
      exit(5);
   }
   return V[i];
}

int &Vetor::operator[](int i)
{
   if ((i < 0) || (i >= n))
   {
      cerr << "\nErro: Tentativa de acesso fora dos limites do vetor.\n";
      exit (5);
   }
   return V[i];
}

void Vetor::escreve()
{
	cout <<"[";
	for (int i = 0; i < n; i++)
	{
		cout << V[i];
    	if (i < n - 1)
		cout << ", ";
	}
	cout << "]";
}

void Vetor::swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

//METODOS DE ORDENAÇÃO

void Vetor::InsertionSort()
{
	for (int i = 1; i < n; i++)
	{
		int aux = V[i];
    	int j = 0;
			for (j = i; (j > 0) && (aux < V[j-1]); j--)
        		V[j] = V[j - 1];
			
		V[j] = aux;
	}
}

// Algoritmo de particao merge
void Vetor::merge(int low, int mid, int high)
{
	int n1 = mid - low + 1; 
	int n2 = high - mid;          
	int left[n1 + 1], right[n2 + 1];
	int i = 0, j = 0; // i e j locais à função
	for (int i = 0; i < n1; i++) // i local ao laço
		left[i] = this->V[low + i];
	for (int j = 0; j < n2; j++) // j local ao laço
		right[j] = this->V[mid + 1 + j];
	left[n1] = INT_MAX;
	right[n2] = INT_MAX;
	
	for (int k = low; k <= high; k++)
		if (left[i] <= right[j])
			this->V[k] = left[i++];
		else
		{
			this->V[k] = right[j++];
		}
}

// algoritmo de ordencão mergesort
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

int main(){

	ifstream in("numeros1.txt");
	ofstream out_ordena("numeros_ordenados.txt");
	ofstream out_time("time.txt");
	ofstream out_swap("swap.txt");
	ofstream out_comp("comp.txt");

	/***************************
    * Ordena com InsertionSort *
    ****************************/
	//V.escreve();
	//cout << endl;
	//cout << "Ordenando vetor com InsertionSort().\n";
   	//V.InsertionSort();
	//V.escreve();
	//cout << endl;


	/*************************
    * Ordena com MergeSort   *
    *************************/
	cout << "Ordenando vetor com MergeSort().\n";
    //V.MergeSort(0, V.len()-1);
}