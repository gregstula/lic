// Copyright (C) 2015 Gregory D. Stula

package main

import (
	"io/ioutil"
	"os"
	"regexp"
	"fmt"
	"errors"
	"strings"
)


// Reading files requires checking most calls for errors.
// This helper will streamline our error checks below.
func check(e error) {
	if e != nil {
		panic(e)
	}
}


// A Little Stack Implementation
type stack [][]byte


// Returns the size and emptyness of the stack
func (s stack) IsEmpty() (int, bool) {
	l := len(s)
	return l, l == 0
}



func (s stack) Push(b []byte) stack {
    return append(s, b)
}


func (s stack) Pop() (stack) {

	// TODO: HANDLE ERRORS
	l := len(s)
    return s[:l - 1]
}


func (s stack) PopTop() []byte {
	return s[0]
}


// Regex 
func magic() *regexp.Regexp {
	rgx := regexp.MustCompile(`\#\[(.*?)\]`)
	return rgx

}


func personalize(src []byte, settings []byte) []byte {

	config := map[string][]byte {
		"fullname": []byte("Gregory D. Stula"),
		"year": []byte("2015"),
		"project": []byte("lic"),
	}

	rgx := magic()

	lics := rgx.FindAllSubmatch(src, -1)

	fmt.Printf("%q\n",lics)

	var replace [][]byte
	for _, bkey := range lics {
		key := string(bkey[1])
		if value, ok := config[key]; ok {
			println(value)
			replace = append(replace, value)
		}
	}

	fmt.Printf("%q\n",replace)

	size := len(replace)
	index := 0
	newFile := rgx.ReplaceAllFunc(src, func(b []byte) []byte {
		r := replace[index]
		if index < size {
			index++
		}
		return r
	})

	return newFile
}


// TODO: Implment parse and test that it can correctly read settings from
// the comments of a .gitignore file

func parse(src []byte) map[string][]byte {

	var hbstack stack

	rgx := magic()
	lics := rgx.FindAllSubmatch(src, -1)

	for _, b := range lics {
		// push key, push value, push key...etc
			hbstack.Push(b[1])
	}

	l := len(hbstack)

	hbmap := make(map[string][]byte)

	for i := 0; i != l; {
		// Pop value
		hbstack, value := hbstack.Pop()

		// Pop key
		hbstack, bkey := hbstack.Pop()
		key := string(bkey)

		hbmap[key] = value
	}
	return hbmap
}


func main() {

	path := ""

	concatMe := []string{path, os.Args[1]}

	licData, errRead := ioutil.ReadFile(strings.Join(concatMe,""))
	check(errRead)

	gitignore, errNoGi := ioutil.ReadFile(".gitignore")
	check(errNoGi)

	newLicData := personalize(licData, gitignore)

	errWrite := ioutil.WriteFile("LICENSE", newLicData, os.FileMode(0644))
	check(errWrite)
}

