package main

import (
	"reflect"
	"testing"
)

func TestCreateWordsWithDistanceFromLines(t *testing.T) {
	type args struct {
		lines    []string
		MainWord string
		fn       distFunc
	}
	tests := []struct {
		name string
		args args
		want words
	}{
		// TODO: Add test cases.
		{"Test1", args{[]string{"abc", "aaa"}, "", LevenshteinDistance}, words{word{"abc", 3}, word{"aaa", 3}}},
		{"Test2", args{[]string{"abc", "aaa"}, "a", LevenshteinDistance}, words{word{"abc", 2}, word{"aaa", 2}}},
		{"Test3", args{[]string{"abc", "aaa"}, "ab", LevenshteinDistance}, words{word{"abc", 1}, word{"aaa", 2}}},
		{"Test4", args{[]string{"marcus", "marx"}, "marcuus", LevenshteinDistance}, words{word{"marcus", 1}, word{"marx", 4}}},
	}
	for _, tt := range tests {
		if got := CreateWordsWithDistanceFromLines(tt.args.lines, tt.args.MainWord, tt.args.fn); !reflect.DeepEqual(got, tt.want) {
			t.Errorf("%q. CreateWordsWithDistanceFromLines() = %v, want %v", tt.name, got, tt.want)
		}
	}
}
