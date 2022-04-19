#include <iostream>
#include <fstream> // std::fstream
#include <experimental/filesystem>
#include <unistd.h>
#include "TrackingDeque.h"
using namespace std;

//BufferedFile

class fstream_wrapper : public fstream{
    public:
        fstream_wrapper(const char *filename);
        ~fstream_wrapper();
        fstream_wrapper &get(char &c);
        fstream_wrapper &put(char c);
        bool eof() const;
        fstream_wrapper &putback(char c);

    private:
        void raw_get(char& c);
        std::streampos getpos; ///=====1
        std::streampos putpos; ///=====0
        TrackingDeque<char> buffer;
        const char* filename;  //For truncating the file
        bool hit_eof; //set to false in initialisation list
        bool hit_empty_buffer;
};