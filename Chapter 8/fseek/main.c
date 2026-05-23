#include <fcntl.h>
#include <io.h>
#include <stdlib.h>

#define NULL 0
#define EOF  (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct m_iobuf {
    int cnt;       /* characters left */
    char *ptr;     /* next character position */
    char *base;    /* location of buffer */
    int flag;      /* mode of file access */
    int fd;        /* file descriptor */
} m_FILE;

#define _READ   01
#define _WRITE  02
#define _UNBUF  04
#define _EOF    010
#define _ERR    020

m_FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, _READ, 0 },
    { 0, NULL, NULL, _WRITE, 1 },
    { 0, NULL, NULL, _WRITE | _UNBUF, 2 }
};

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(m_FILE *);
int _flushbuf(int, m_FILE *);

#define getc(p)     (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p)  (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

m_FILE *fopen(char *name, char *mode)
{
    int fd;
    m_FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;

    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = _creat(name, 0666);
    else if (*mode == 'a') {
        if ((fd = _open(name, O_WRONLY)) == -1)
            fd = _creat(name, 0666);
        _lseek(fd, 0L, 2);
    } else
        fd = _open(name, O_RDONLY);

    if (fd == -1)
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;

    return fp;
}

int _fillbuf(m_FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL)
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;

    fp->ptr = fp->base;
    fp->cnt = _read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

int min_fseek(m_FILE *stream, long int offset, int whence)
{
    if(stream->flag & _WRITE) {
        int n = stream->ptr - stream->base;
        write(stream->fd, stream->base, n);
    }
    if(lseek(stream->fd, offset, whence) == -1)
        return -1;
    if(feof(stream))
        stream->flag = stream->flag & ~_EOF;
    stream->cnt = 0;
    stream->ptr = stream->base;
    return 0;
}

#define MAX_SIZE        8

int main(int argc, char *argv[])
{
    return 0;
}

