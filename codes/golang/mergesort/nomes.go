package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"time"
)

type SortStats struct {
	Comparisons int
	Swaps       int
}

type Person struct {
	Line      string
	FirstName string
	LastName  string
	Suffix    string
}

func mergeSort(items []Person, stats *SortStats) []Person {
	if len(items) <= 1 {
		return items
	}

	middle := len(items) / 2
	left := mergeSort(items[:middle], stats)
	right := mergeSort(items[middle:], stats)

	return merge(left, right, stats)
}

func merge(left, right []Person, stats *SortStats) []Person {
	var result []Person
	i, j := 0, 0

	for i < len(left) && j < len(right) {
		if strings.Compare(left[i].Line, right[j].Line) <= 0 {
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
	fileName := "nomes 1.txt"

	increment := 1000

	tempoTotal := time.Duration(0)
	var (
		comparacaoTotal int
		swapsTotal      int
	)

	in, err := os.Open(fileName)
	out, ferror1 := os.Create("nomes_ordenados.txt")
	out2, ferror2 := os.Create("statistics.txt")
	defer in.Close()
	defer out.Close()

	if err != nil || ferror1 != nil || ferror2 != nil {
		fmt.Println("Erro ao abrir o arquivo:", err)
		return
	}

	scanner := bufio.NewScanner(in)
	var people []Person

	for scanner.Scan() {
		line := scanner.Text()
		person := Person{
			Line: line,
		}
		people = append(people, person)
	}

	start := 0
	end := increment

	for end <= len(people) {
		subset := people[start:end]

		// Ordenar o subconjunto
		stats := &SortStats{}
		startTime := time.Now()

		sortedSubset := mergeSort(subset, stats)

		endTime := time.Now()
		duration := endTime.Sub(startTime)

		if end == 100000 {
			for _, person := range sortedSubset {
				fmt.Fprintln(out, person.Line)
			}
		}

		fmt.Fprintln(out2, "Estatísticas do lote:")
		fmt.Fprintf(out2, "Intervalo de linhas: de %d a %d\n", start, end-1)
		fmt.Fprintf(out2, "Tempo de execução: %s\n", formatDuration(duration))
		fmt.Fprintf(out2, "Número de comparações: %d\n", stats.Comparisons)
		fmt.Fprintf(out2, "Número de trocas: %d\n\n", stats.Swaps)

		end += increment
		tempoTotal += duration
		comparacaoTotal += stats.Comparisons
		swapsTotal += stats.Swaps
	}

	fmt.Fprintln(out2, "Estatísticas da ordenação completa:")
	fmt.Fprintf(out2, "Tempo de execução total: %s\n", formatDuration(tempoTotal))
	fmt.Fprintf(out2, "Total de comparações: %d\n", comparacaoTotal)
	fmt.Fprintf(out2, "Total de trocas: %d\n", swapsTotal)
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
