package main


import(
"runtime"
)


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
    var numCPU=runtime.NumCPU()
    if( len(lines) < 4 ){
        numCPU = 1
    } 
    
    for _, line := range lines {
		tmpWords = append(tmpWords, word{line, 0})
	}
    
    sem := make (chan int, len(lines));
    
    for i := 0; i < numCPU; i++ {
       go func (i int, num int) {
        for j, _ := range tmpWords[i*len(tmpWords)/numCPU :(i+1)*len(tmpWords)/numCPU] {
            tmpWords[j].distance = fn(MainWord, tmpWords[j].name)
        }            
            sem <- 0;
        } (i, numCPU);
    }

   for i := 0; i < numCPU; i++ { 
   <-sem 
   }

	return tmpWords
}
