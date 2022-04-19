#include "fstream_wrapper.h"

class StreamSource{
    public:
        StreamSource(const char* search_word, const char* replacement_word, const char *filename);
        bool eof();
        StreamSource &get(char &c);
        StreamSource &put(char c);
        bool currently_replacing();
        void match_search_string();
        void found_partial_match(int matchCount, char mismatched_char);

    private:
        enum {BuffFile, SearchString, ReplacementString} getting_from;
        const char* search_word;
        const char* replacement_word;
        int searchStringCount=0;
        int searchStringIndex=0;
        int replacementStringCount=0;
        int found_partial_method_call=0;
        fstream_wrapper fw; 
};
