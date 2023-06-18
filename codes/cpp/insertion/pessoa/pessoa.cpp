#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

class Pessoa
{
public:
    int codigo;
    string name;
    Pessoa() {}
    Pessoa(int cod, string nome)
    {
        codigo = cod;
        name = nome;
    }
};

int main()
{
    ifstream input("pessoa.txt");

    vector<Pessoa> vetor;
    unsigned long long comp = 0, swaps = 0;

    for (int i = 0; i < 20; i++)
    {
        int id;
        string nome;

        input >> id;
        input.ignore(); // Ignore the newline character after reading the integer
        getline(input, nome);

        vetor.push_back(Pessoa(id, nome));
    }

    input.close();
    int compara;

    double time_spent = 0.0;
    clock_t begin = clock();

    for (int i = 1; i < vetor.size(); i++)
    {
        for (int j = i; j > 0 && (vetor[j].codigo < vetor[j - 1].codigo || (vetor[j].codigo == vetor[j - 1].codigo && vetor[j].name < vetor[j - 1].name)); j--)
        {
            compara += 3;
            swap(vetor[j], vetor[j - 1]);
            swaps++;
        }
    }

    clock_t end = clock();
    time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;

    ofstream out("ordenados.txt");
    for (const auto& pessoa : vetor)
    {
        out << pessoa.codigo << " " << pessoa.name << endl;
    }

    cout << "Tempo de execução: " << time_spent << " segundos" << endl;

    return 0;
}
