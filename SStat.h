


#include <dirent.h>      
#include <linux/limits.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <algorithm>    
#include <vector>   
#include <sstream>    
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

class SStat {

    private:
        char * _FileName;
        int  _FileSize;
        int  _FileBlks;
        int  _FileBB;
        char * _FileType;
        int  _FileDevDec;
        int  _FileIno;
        int  _FileLnks;
        char * _FileAcc;
        int  _UID;
        int  _GID;
        __time_t _AccTime;
        __time_t _ModTime;
        __time_t _ChangTime;
        __mode_t _FileMode;


        const char * __file_type;
    public:
        SStat (char * file_name);
        void GetAll();
        void GetConrete(char * mode);
        string getRightStr(int num);

};
