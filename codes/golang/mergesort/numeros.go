package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

type SortStats struct {
	Comparisons int
	Swaps       int
}

func mergeSort(items []int, stats *SortStats) []int {
	if len(items) <= 1 {
		return items
	}

	middle := len(items) / 2
	left := mergeSort(items[:middle], stats)
	right := mergeSort(items[middle:], stats)

	return merge(left, right, stats)
}

func merge(left, right []int, stats *SortStats) []int {
	var result []int
	i, j := 0, 0

	for i < len(left) && j < len(right) {
		if left[i] < right[j] {
			result = append(result, left[i])
			i++
		} else {
			result = append(result, right[j])
			j++
		}

		stats.Comparisons++
	}

	result = append(result, left[i:]...)
	result = append(result, right[j:]...)

	stats.Swaps += len(left) + len(right)

	return result
}

func main() {
	fileName := "numeros 1.txt"

	tempo_total := time.Duration(0)
	var (
		comparação_total int
		swaps_total      int
	)

	in, err := os.Open(fileName)
	out, ferror1 := os.Create("ordenado.txt")
	out2, ferror2 := os.Create("statistics.txt")
	defer in.Close()
	defer out.Close()

	if err != nil || ferror1 != nil || ferror2 != nil {
		fmt.Println("Erro ao abrir o arquivo:", err)
		return
	}

	scanner := bufio.NewScanner(in)
	var numbers []int

	for scanner.Scan() {
		line := scanner.Text()
		numStr := strings.Split(line, " ")

		for _, str := range numStr {
			num, err := strconv.Atoi(str)
			if err != nil {
				fmt.Println("Erro ao converter número:", err)
				return
			}
			numbers = append(numbers, num)
		}
	}

	start := 0
	increment := 1000
	end := increment

	for end <= 100000 {

		subset := numbers[start:end]

		// Inicializar as estatísticas do subset
		stats := &SortStats{}

		// Obter o tempo de início
		startTime := time.Now()

		sortedSubset := mergeSort(subset, stats)

		// Obter o tempo de fim
		endTime := time.Now()

		// Verificar se o subset está totalmente ordenado
		if end == 100000 {
			for _, num := range sortedSubset {
				fmt.Fprintf(out, "%d\n", num)
			}
		} else {
			fmt.Fprintf(out2, "O arquivo não está totalmente ordenado (de %d a %d)\n\n", start, 100000)
		}

		// Calcular a duração da execução
		duration := endTime.Sub(startTime)

		// Exibir os resultados
		fmt.Fprintf(out2, "Estatísticas dos números (de %d a %d):\n", start, end-1)
		fmt.Fprintf(out2, "Tempo de execução: %s\n", formatDuration(duration))
		fmt.Fprintf(out2, "Número de comparações: %d\n", stats.Comparisons)
		fmt.Fprintf(out2, "Número de trocas: %d\n\n", stats.Swaps)

		// Atualizar as estatísticas totais
		tempo_total += duration
		comparação_total += stats.Comparisons
		swaps_total += stats.Swaps

		// Atualizar os índices para o próximo subset
		end += increment
	}

	// Exibir as estatísticas totais
	fmt.Fprintf(out2, "\tEstatísticas da Ordenação do arquivo completo:\n")
	fmt.Fprintf(out2, "Tempo de execução total: %s\n", formatDuration(tempo_total))
	fmt.Fprintf(out2, "Total de comparações: %d\n", comparação_total)
	fmt.Fprintf(out2, "Total de trocas: %d\n", swaps_total)
}

func formatDuration(duration time.Duration) string {
	hours := duration / time.Hour
	duration -= hours * time.Hour

	minutes := duration / time.Minute
	duration -= minutes * time.Minute

	seconds := duration / time.Second
	duration -= seconds * time.Second

	microseconds := duration / time.Microsecond

	return fmt.Sprintf("%dh%dm%ds%dµs", hours, minutes, seconds, microseconds)
}
