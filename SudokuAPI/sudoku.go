package main

import (
	"log"
	"net/http"
	"os/exec"
)

const lengthPath uint = uint(len("/sudoku/"))

func SudokuHandler(resp http.ResponseWriter, req *http.Request) {
	path := req.URL.Path[lengthPath:]
	rawGrid := GetSudokuGrid(path)

	gridJSON := FromRawToJSON(rawGrid)

	resp.Header().Add("Content-Type", "application/json")
	resp.Write(gridJSON)
}

func GetSudokuGrid(difficulty string) []byte {
	cmd := exec.Command("./bin/commands/sudoku_gen", difficulty)
	result, err := cmd.Output()
	if err != nil {
		log.Fatal(err)
	}
	return result
}
