package main

import (
	"testing"
)

func TestMin(t *testing.T) {
	type args struct {
		a int
		b int
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		// TODO: Add test cases.
		{"Test1", args{0, 0}, 0},
		{"Test2", args{0, 1}, 0},
		{"Test3", args{1, 0}, 0},
	}
	for _, tt := range tests {
		if got := Min(tt.args.a, tt.args.b); got != tt.want {
			t.Errorf("%q. Min() = %v, want %v", tt.name, got, tt.want)
		}
	}
}

func TestLevenshteinDistance(t *testing.T) {
	type args struct {
		iMainWord    string
		iAnotherWord string
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		// TODO: Add test cases.
		{"Test1", args{"maxus", "maxus"}, 0},
		{"Test2", args{"maxus", "maxas"}, 1},
		{"Test3", args{"maxus", "maxs"}, 1},
		{"Test4", args{"maxus", "maxuss"}, 1},
		{"Test5", args{"algol", "golang"}, 5},
		{"Test6", args{"maxus", ""}, 5},
		{"Test7", args{"", "golang"}, 6},
	}
	for _, tt := range tests {
		if got := LevenshteinDistance(tt.args.iMainWord, tt.args.iAnotherWord); got != tt.want {
			t.Errorf("%q. LevenshteinDistance() = %v, want %v", tt.name, got, tt.want)
		}
	}
}

func TestDamerauLevenshteinDistance(t *testing.T) {
	type args struct {
		iMainWord    string
		iAnotherWord string
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		// TODO: Add test cases.
		{"Test1", args{"maxus", "maxus"}, 0},
		{"Test2", args{"maxus", "maxas"}, 1},
		{"Test3", args{"maxus", "maxs"}, 1},
		{"Test4", args{"maxus", "maxuss"}, 1},
		{"Test5", args{"algol", "golang"}, 5},
		{"Test6", args{"maxus", ""}, 5},
		{"Test7", args{"", "golang"}, 6},
		{"Test8", args{"maxus", "maxsu"}, 1},
		{"Test9", args{"goalgn", "golang"}, 2},
	}
	for _, tt := range tests {
		if got := DamerauLevenshteinDistance(tt.args.iMainWord, tt.args.iAnotherWord); got != tt.want {
			t.Errorf("%q. DamerauLevenshteinDistance() = %v, want %v", tt.name, got, tt.want)
		}
	}
}
