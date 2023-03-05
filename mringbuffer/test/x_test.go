package main

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func Test_RB(t *testing.T) {
	assert := assert.New(t)

	const CAP = uint(1024)
	rb := NewRb(CAP)
	assert.Equal(uint(0), rb.Dlen())
	assert.Equal(CAP, rb.Left())
}

func Benchmark_RB(b *testing.B) {
	const CAP = uint(1024)
	rb := NewRb(CAP)
	wbuf := []byte{1, 2, 3, 4, 5}
	rbuf := make([]byte, len(wbuf)+10)
	b.ResetTimer()

	for i := 0; i < b.N; i++ {
		rb.Put(wbuf)
		rb.Get(rbuf)
	}
}
