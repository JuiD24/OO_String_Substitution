
#include <cstring>
#include <string>
#include "StreamSource.h"


int main(int argc, char **argv)
{   
    int matchCount =0;
    StreamSource ss(argv[1], argv[2], argv[3]);
    const char* search_word = argv[1];
    
    char ch;

    while(!ss.get(ch).eof()){

        if(!ss.currently_replacing() && ch == search_word[matchCount]){
            ++matchCount;
            if(matchCount < strlen(search_word))
                continue;
        }

        if(matchCount == strlen(search_word)){ //its a match
            ss.match_search_string();
        }else if(matchCount > 0){  //its a failed match
            ss.found_partial_match(matchCount, ch);
        }
        else{
            ss.put(ch);
        }
        matchCount = 0;
    }

}