package main

import "fmt"

import "bytes"

const body string = `{
	"grid": [%s]
}
`

func FromRawToJSON(grid []byte) []byte {
	var buffer bytes.Buffer
	buffer.WriteRune('[')
	for i := 0; i < len(grid); i++ {
		if grid[i] == 10 {
			buffer.Truncate(buffer.Len() - 1)
			buffer.WriteString("],[")
			continue
		}

		buffer.WriteByte(grid[i])
		buffer.WriteRune(',')
	}
	buffer.Truncate(buffer.Len() - 1)
	buffer.WriteRune(']')

	return []byte(fmt.Sprintf(body, buffer.String()))
}
