package main

import (
	"fmt"
	"os"
	"reflect"
)

type Sorter interface {
	Len() int           // Função que retorna o comprimento do slice de dados a ser ordenado
	Less(i, j int) bool // Função de comparação a ser usada pelos algoritmos
	Swap(i, j int)      // Função de troca a ser usada pelos algoritmos
}

type IntSlice []int

// Definição da função Len() para o slice de inteiros
func (intsl IntSlice) Len() int {
	return len(intsl)
}

// Definição da função Less() para o slice de inteiros
func (intsl IntSlice) Less(i, j int) bool {
	return intsl[i] < intsl[j]
}

// Definição da função Swap para o slice de inteiros
func (intsl IntSlice) Swap(i, j int) {
	intsl[i], intsl[j] = intsl[j], intsl[i]
}

func insertionSort(s Sorter) {
	n := s.Len()
	for i := 1; i < n; i++ {
		for j := i; j > 0 && s.Less(j, j - 1); j-- {
			s.Swap(j, j - 1)
		}
	}
}

func main() {
}