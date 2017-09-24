package main

import (
	"unicode/utf8"
)

type distFunc func(string, string) int

//Min returns min of two elements
func Min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

//LevenshteinDistance returns Levenshtein Distance between two words
func LevenshteinDistance(iMainWord, iAnotherWord string) int {
	N := utf8.RuneCountInString(iMainWord)
	M := utf8.RuneCountInString(iAnotherWord)
	if N == 0 {
		return M
	}
	if M == 0 {
		return N
	}
	var D = make([][]int, N+1)
	for i := range D {
		D[i] = make([]int, M+1)
	}

	for i := 0; i <= N; i++ {
		D[i][0] = i
	}
	for j := 0; j <= M; j++ {
		D[0][j] = j
	}

	var SubstutitionCost int
	for i := 1; i <= N; i++ {
		for j := 1; j <= M; j++ {
			if iMainWord[i-1] == iAnotherWord[j-1] {
				SubstutitionCost = 0
			} else {
				SubstutitionCost = 1
			}
			D[i][j] = Min(D[i-1][j]+1,
				Min(D[i][j-1]+1,
					D[i-1][j-1]+SubstutitionCost))
		}
	}
	return D[N][M]
}

//DamerauLevenshteinDistance returns Damerau-Levenshtein Distance between two words
func DamerauLevenshteinDistance(iMainWord, iAnotherWord string) int {
	N := utf8.RuneCountInString(iMainWord)
	M := utf8.RuneCountInString(iAnotherWord)
	if N == 0 {
		return M
	}
	if M == 0 {
		return N
	}
	var D = make([][]int, N+1)
	for i := range D {
		D[i] = make([]int, M+1)
	}

	for i := 0; i <= N; i++ {
		D[i][0] = i
	}
	for j := 0; j <= M; j++ {
		D[0][j] = j
	}

	var cost int
	for i := 1; i <= N; i++ {
		for j := 1; j <= M; j++ {
			if iMainWord[i-1] == iAnotherWord[j-1] {
				cost = 0
			} else {
				cost = 1
			}
			D[i][j] = Min(D[i-1][j]+1,
				Min(D[i][j-1]+1,
					D[i-1][j-1]+cost))
			if i > 1 && j > 1 && iMainWord[i-1] == iAnotherWord[j-2] && iMainWord[i-2] == iAnotherWord[j-1] {
				D[i][j] = Min(D[i][j], D[i-2][j-2]+cost)
			}
		}
	}
	return D[N][M]
}
