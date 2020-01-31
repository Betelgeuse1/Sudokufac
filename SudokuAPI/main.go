package main

import (
	"net/http"
	"regexp"
)

var (
	sudokuPathRegexp *regexp.Regexp = regexp.MustCompile("^sudoku/(?:easy|medium|hard)$")
)

func main() {
	http.HandleFunc("/", PathHandler)
	http.ListenAndServe(":8080", nil)
}

func PathHandler(resp http.ResponseWriter, req *http.Request) {
	// Remove the '/' at the beginning of the path
	path := req.URL.Path[1:]
	switch {
	case path == "":
		http.ServeFile(resp, req, "./static/index.html")
	case path == "sandie":
		http.ServeFile(resp, req, "./static/sandie.html")
	case sudokuPathRegexp.MatchString(path):
		SudokuHandler(resp, req)
	default:
		http.ServeFile(resp, req, "./static/error.html")
	}
}
