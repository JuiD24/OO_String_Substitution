#include "fstream_wrapper.h"

fstream_wrapper::fstream_wrapper(const char *filename) : fstream{filename, ios::in | ios::out}, getpos{0}, putpos{0},filename{filename}, hit_eof{false}, hit_empty_buffer{false}
{
}

fstream_wrapper::~fstream_wrapper()
{   
    fstream::close();
    truncate(filename, putpos);
}

bool fstream_wrapper::eof() const{
    return hit_eof && hit_empty_buffer;
}

void fstream_wrapper::raw_get(char &c)
{   
    fstream::seekg(getpos);
    fstream::get(c);  //call inherited behavior
    getpos = fstream::tellg(); //essentially ++getpos
    
    if(fstream::eof()){
        fstream::clear();
        hit_eof = true;
    }
}

fstream_wrapper &fstream_wrapper::get(char &c)
{   
    if(buffer.size() > 0){ //buffer not empty
        c = buffer.front();
        buffer.pop_front();
        return *this;
    }
    //buffer empty , call raw_get
    raw_get(c);
    if(hit_eof)
        hit_empty_buffer = true;

    return *this;   
}

fstream_wrapper &fstream_wrapper::put(char c)
{   
    if(getpos == putpos && !hit_eof){
        char ch;
        raw_get(ch);
        if(!hit_eof)
            buffer.push_back(ch);
    }
    fstream::seekp(putpos);
    fstream::put(c);
    putpos = fstream::tellp(); //essentially ++putpos
    return *this;
}

fstream_wrapper &fstream_wrapper::putback(char c){
    buffer.push_front(c);
    return *this;
}
