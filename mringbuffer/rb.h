#ifndef __RB_H__
#define __RB_H__

struct ringbuffer {
    unsigned char *buf;
    unsigned int cap;
    unsigned int widx;
    unsigned int ridx;
};

void rb_init(struct ringbuffer *p, void *buf, unsigned int cap);
unsigned int rb_put(struct ringbuffer *p, void *buf, unsigned int len);
unsigned int rb_get(struct ringbuffer *p, void *buf, unsigned int len);
unsigned int rb_data_length(struct ringbuffer *p);
unsigned int rb_left_space(struct ringbuffer *p);

#endif