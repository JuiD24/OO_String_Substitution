#include "StreamSource.h"
#include <cstring>

StreamSource::StreamSource(const char* search_word, const char* replacement_word, const char *filename) : search_word(search_word), replacement_word(replacement_word), fw(filename){
}

StreamSource& StreamSource::get(char &c){

    if(replacementStringCount==0 && searchStringCount==0){
        getting_from = BuffFile;
    }

    if(getting_from == SearchString)
    {
        c = search_word[searchStringIndex];
        searchStringIndex++;
        searchStringCount--;
    }

    if(getting_from == ReplacementString){
        c =replacement_word[strlen(replacement_word) - replacementStringCount];
        replacementStringCount--;
    }
    if(getting_from == BuffFile){
        fw.get(c);
    }
    return *this;
}

StreamSource &StreamSource::put(char c){
    fw.put(c);
    return *this;
}

bool StreamSource::currently_replacing(){
    return getting_from == ReplacementString ;
}

void StreamSource::match_search_string(){
    getting_from = ReplacementString;
    replacementStringCount = strlen(replacement_word);
    //set some variable to # of characters remaining to be gotten from replacement string
}

void StreamSource::found_partial_match(int matchCount, char mismatched_char){
    
    if(getting_from == SearchString){
        put(search_word[found_partial_method_call]);
        searchStringCount = matchCount - (found_partial_method_call+1);
        searchStringIndex = found_partial_method_call + 1;
        found_partial_method_call++;
    }
    else{
        getting_from = SearchString;
        found_partial_method_call = 0;
        put(search_word[0]);//The match failed, so the first character of the mismatch should be output.
        searchStringCount = matchCount - 1; 
        searchStringIndex = 1;
        //set integer variable, noting how many chars must be retrieved from search string
    }
    
    fw.putback(mismatched_char); //should push to front of deque/buffer
}

bool StreamSource::eof(){
    return fw.eof();
}