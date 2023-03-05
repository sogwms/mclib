#include "rb.h"

#undef NULL
#define NULL 0

#undef MIN
#define MIN(a, b) ((a) < (b) ? a : b)

#define _rb_data_length(p) ((unsigned int)(p->widx - p->ridx))
#define _rb_left_space(p) (p->cap - _rb_data_length(p))

static void _mem_cpy(void *dst, void *src, unsigned int len);

void rb_init(struct ringbuffer *p, void *buf, unsigned int cap) {
    if ((p == NULL) || (buf == NULL) || (cap == 0)) {
        return;
    }

    p->buf = buf;
    p->cap = cap;
    p->widx = 0;
    p->ridx = 0;
}

int rb_put(struct ringbuffer *p, void *buf, unsigned int len) {
    unsigned int idx;
    unsigned int ltoe;
    if ((p == NULL) || (buf == NULL)) {
        return 0;
    }

    // cal the real size of data can be written
    len = MIN(_rb_left_space(p), len);
    if (len == 0) {
        return 0;
    }
    // get real index
    idx = p->widx % p->cap;

    // cal length to len from index without crossing end
    ltoe = MIN(p->cap - idx, len);

    // write first part (from index)
    _mem_cpy(p->buf + idx, buf, ltoe);
    // write left if have (from beginning)
    if (len != ltoe) {
        _mem_cpy(p->buf, buf + ltoe, len - ltoe);
    }

    p->widx += len;

    return len;
}

int rb_get(struct ringbuffer *p, void *buf, unsigned int len) {
    unsigned int idx;
    unsigned int ltoe;
    if ((p == NULL) || (buf == NULL)) {
        return 0;
    }

    // cal the real size of data can be read
    len = MIN(_rb_data_length(p), len);
    if (len == 0) {
        return 0;
    }
    // get real index
    idx = p->ridx % p->cap;

    // cal length to len from index without crossing end
    ltoe = MIN(p->cap - idx, len);

    // read first part (from index)
    _mem_cpy(buf, p->buf + idx, ltoe);
    // read left if have (from beginning)
    if (len != ltoe) {
        _mem_cpy(buf + ltoe, p->buf, len - ltoe);
    }

    p->ridx += len;

    return len;
}

unsigned int rb_data_length(struct ringbuffer *p) {
    if (p == NULL) {
        return 0;
    }
    return _rb_data_length(p);
}

unsigned int rb_left_space(struct ringbuffer *p) {
    if (p == NULL) {
        return 0;
    }
    return _rb_left_space(p);
}

#include <string.h>
static void _mem_cpy(void *dst, void *src, unsigned int len) {
    memcpy(dst, src, len);
}