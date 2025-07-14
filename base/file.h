#ifndef _FILEREADWRITER_H_
#define _FILEREADWRITER_H_

#include "common.h"
#include "exception.h"

namespace siberia::base {
class FileReadWriter {
private:
    Exception *ex;

    FILE *fp;
    int size_;
    FileReadWriter(const FileReadWriter &other) = delete;
    FileReadWriter(FileReadWriter &&other) = delete;
    FileReadWriter &operator=(const FileReadWriter &other) = delete;
    FileReadWriter &operator=(FileReadWriter &&other) = delete;
    class FilePos {
    private:
        FileReadWriter *parent;
        FILE *fp;
        Exception *ex;
        int pos;
    public:
        FilePos(FileReadWriter *parent, Exception *ex, FILE *fp, int pos) : parent(parent), ex(ex), fp(fp), pos(pos) {}
        ~FilePos() {}
        operator uint8_t() {
            if (!fp) return -1;
            if (pos == parent->size()) {
                THROW("The position at the end of the file is only writable");
                return -1;
            }
            fseek(fp, pos, SEEK_SET);
            char buf = 0;
            fread(&buf, 1, 1, fp);
            return buf;
        }
        uint8_t operator=(const uint8_t &byte) {
            if (!fp) return byte;
            fseek(fp, pos, SEEK_SET);
            char buf = byte;
            fwrite(&buf, 1, 1, fp);
            fflush(fp);
            parent->updateSize();
            return byte;
        }
        uint8_t operator=(const FilePos &other) {
            uint8_t wtf = (FilePos) other;
            return operator=(wtf);
        }
    };
    void updateSize() {
        fseek(fp, 0, SEEK_END);
        size_ = ftell(fp);
    }
public:
    FileReadWriter(Exception *ex, const char *filename) : ex(ex) {
        fp = fopen(filename, "rb+");
        if (!fp) {
            THROW(String("file opening error: ") + filename);
        } else updateSize();
    }
    ~FileReadWriter() {
        fclose(fp);
    }
    FilePos operator[](int pos) {
        if (pos > size_ || pos < 0) {
            String err_msg = "invalid position: ";
            err_msg += pos;
            err_msg += ", where size is ";
            err_msg += size_;
            THROW(err_msg);
            return FileReadWriter::FilePos(this, ex, NULL, -1);
        }
        return FileReadWriter::FilePos(this, ex, fp, pos);
    }
    int size() { return size_; }
};
}

#endif