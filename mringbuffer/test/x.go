package main

/*
#include "../rb.c"
*/
import "C"
import (
	"fmt"
	"reflect"
	"unsafe"
)

type RB struct {
	rb  C.struct_ringbuffer
	buf []byte
}

func NewRb(size uint) *RB {
	n := &RB{}
	n.buf = make([]byte, size)
	C.rb_init(&n.rb, unsafe.Pointer(C.CBytes(n.buf)), C.uint(size))

	return n
}

func (r *RB) Put(buf []byte) uint {
	pHdr := (*reflect.SliceHeader)(unsafe.Pointer(&buf))
	realSize := C.rb_put(&r.rb, unsafe.Pointer(pHdr.Data), C.uint(pHdr.Len))

	return uint(realSize)
}

func (r *RB) Get(buf []byte) uint {
	pHdr := (*reflect.SliceHeader)(unsafe.Pointer(&buf))
	realSize := C.rb_get(&r.rb, unsafe.Pointer(pHdr.Data), C.uint(pHdr.Len))
	return uint(realSize)
}

func (r *RB) Left() uint {
	return uint(C.rb_left_space(&r.rb))
}

func (r *RB) Dlen() uint {
	return uint(C.rb_data_length(&r.rb))
}

func main() {
	rb := NewRb(26)
	rb.Put([]byte{1, 2, 3})
	rb.Put([]byte{4, 5, 6, 7})

	fmt.Println(rb.Left())
	fmt.Println(rb.Dlen())

	_buf := make([]byte, 16)
	l := rb.Get(_buf)
	_buf = _buf[:l]
	fmt.Println(_buf)
}
