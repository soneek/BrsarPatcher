#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;
char* itoa(int value, char* result, int base);

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        std::cerr << "Universal BRSAR Patcher by soneek\nUsage: " << argv[0] << " filename search_term\n"
            "Prints offsets where search_term is found in file.\nModified to help with patching of brsars.\nThe search term should be the path from the brsar, to the BRSTM file.\nExample of usage with Mario Power Tennis:\nbrsarsearch soundtennis_eng.brsar stream/don-tai.brstm\n";
        return 1;
    }

    const char* filename = argv[1];
    const char* search_term = argv[2];
    size_t search_term_size = strlen(search_term);

    std::ifstream file(filename, std::ios::binary);
    if (file)
    {
        file.seekg(0, std::ios::end);
        size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::string file_content;
        file_content.reserve(file_size);
        char buffer[16384];
        std::streamsize chars_read;
		int brspos = 0;
		
        while (file.read(buffer, sizeof buffer), chars_read = file.gcount())
            file_content.append(buffer, chars_read);

        if (file.eof())
        {
            for (std::string::size_type offset = 0, found_at;
                 file_size > offset &&
                 (found_at = file_content.find(search_term, offset)) !=
                                                            std::string::npos;
                 offset = found_at + search_term_size)
				 brspos = found_at - 28; 
                 std::cout << brspos << std::endl;
				 std::cout << std::hex << brspos << std::endl;
        }
		
		FILE * brstm;
//		FILE * brsar;
		std::ofstream brsar;
		char brstmbuffer [33];
		brstm = fopen ( search_term, "rb" );
		brsar.open( filename, ios::in|ios::out|ios::binary);
		//fputs ( "This is an apple." , pFile );
		fseek ( brstm , 0 , SEEK_END );
		brsar.seekp(brspos);
		std::string brstmsize = ""; 
		brstmsize.insert(0,itoa(ftell(brstm),brstmbuffer,16));		
		while ( brstmsize.length() < 8 )
			brstmsize.insert(0,"0");
		int i;
		int temp;
		unsigned char rbytes[4];
		for( i = 0; i < 4; ++i ) {
        sscanf( brstmsize.c_str() + 2 * i, "%2x", &temp );
        rbytes[i] = temp;
		}	
		brsar.write((char*)rbytes, 4);
//		fwrite(rbytes, 1, sizeof(rbytes), brsar);
		std::cout << rbytes << std::endl;
//		std::cout << search_term + " patched in" << std::endl;
//		fputs ( " sam" , pFile );
		brsar.close();
		fclose ( brstm );
    }
}

char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }
	
		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;
	
		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );
	
		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
}
