package main

import "testing"

func TestProcessFiles(t *testing.T) {
	type args struct {
		dictPath   string
		wordPath   string
		outputPath string
	}
	tests := []struct {
		name string
		args args
		want bool
	}{
	// TODO: Add test cases.
	//{"Test1", args{"/home/max/go/src/lab1_arch/20k.txt", "/home/max/go/src/lab1_arch/1-150.txt", "/home/max/go/src/lab1_arch/tested_lev.txt"}, true},
	}
	for _, tt := range tests {
		if got := ProcessFiles(tt.args.dictPath, tt.args.wordPath, tt.args.outputPath); got != tt.want {
			t.Errorf("%q. ProcessFiles() = %v, want %v", tt.name, got, tt.want)
		}
	}
}

func BenchmarkProcessFiles(b *testing.B) {
	type args struct {
		dictPath   string
		wordPath   string
		outputPath string
	}
	tests := []struct {
		name string
		args args
		want bool
	}{
		// TODO: Add test cases.
		{"Test1", args{"/home/max/go/src/lab1_arch/google-10000-english.txt", "/home/max/go/src/lab1_arch/1-1000.txt", "/home/max/go/src/lab1_arch/bench_tested_lev.txt"}, true},
	}
	for _, tt := range tests {
		if got := ProcessFiles(tt.args.dictPath, tt.args.wordPath, tt.args.outputPath); got != tt.want {
			b.Errorf("%q. ProcessFiles() = %v, want %v", tt.name, got, tt.want)
		}
	}
}
