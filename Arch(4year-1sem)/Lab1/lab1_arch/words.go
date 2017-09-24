package main

type word struct {
	name     string
	distance int
}

type words []word

func (s words) Len() int           { return len(s) }
func (s words) Swap(i, j int)      { s[i], s[j] = s[j], s[i] }
func (s words) Less(i, j int) bool { return s[i].distance < s[j].distance }

//CreateWordsWithDistanceFromLines returns array of word struct
func CreateWordsWithDistanceFromLines(lines []string, MainWord string, fn distFunc) words {
	var tmpWords words
	for _, line := range lines {
		tmpWords = append(tmpWords, word{line, fn(MainWord, line)})
	}
	return tmpWords
}
