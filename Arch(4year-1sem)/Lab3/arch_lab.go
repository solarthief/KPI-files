package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"runtime"
	"runtime/pprof"
	"sort"
	"strconv"
	"time"
)

var cpuprofile = flag.String("cpuprofile", "", "write cpu profile to `file")
var memprofile = flag.String("memprofile", "", "write memory profile to `file`")

//ProcessFiles reads dictionaty from dictPath and calculate 10 closest words to words
//from wordPath file; writes results to outputPath file
func ProcessFiles(dictPath, wordPath, outputPath string) bool {
	dictLines, err := ReadLinesFromFile(dictPath)
	if err != nil {
		log.Fatalf("ReadLinesFromFile: %s", err)
	}

	mainwordLines, err := ReadLinesFromFile(wordPath)
	if err != nil {
		log.Fatalf("ReadLinesFromFile: %s", err)
	}

	for index, mainword := range mainwordLines {
		if index%100 == 0 {
			fmt.Println("Processed " + strconv.Itoa(index) + " words")
		}
		var sWords = CreateWordsWithDistanceFromLines(dictLines, mainword, LevenshteinDistance)
		var outStrings []string
		outStrings = append(outStrings, "\nWord # "+strconv.Itoa(index)+"\nList of top 10 nearest words by Levenstein Distance to word "+mainword)
		sort.Sort(sWords)
		for i, sWord := range sWords[:10] {
			outStrings = append(outStrings, "\n#"+strconv.Itoa(i)+"\t"+sWord.name+"\t"+strconv.Itoa(sWord.distance))
		}

		err := WriteLinesToFile(outputPath, outStrings)
		if err != nil {
			log.Fatalf("WriteLinesToFile: %s", err)
		}
	}
	return true
}

func main() {
	var dictPath = "20k.txt"
	var wordPath = "1-1000.txt"
	var outputPath = "find_lev_" + time.Now().String() + ".txt"

	flag.Parse()
	if *cpuprofile != "" {
		f, err := os.Create(*cpuprofile)
		if err != nil {
			log.Fatal("could not create CPU profile: ", err)
		}
		if err := pprof.StartCPUProfile(f); err != nil {
			log.Fatal("could not start CPU profile: ", err)
		}
		defer pprof.StopCPUProfile()

	}

	var isProcessed = ProcessFiles(dictPath, wordPath, outputPath)
	if isProcessed {
		fmt.Println("Work finished!!")
	}

	if *memprofile != "" {
		f1, err := os.Create(*memprofile)
		if err != nil {
			log.Fatal("could not create memory profile: ", err)
		}
		runtime.GC() // get up-to-date statistics
		if err := pprof.WriteHeapProfile(f1); err != nil {
			log.Fatal("could not write memory profile: ", err)
		}
		f1.Close()
	}
}
