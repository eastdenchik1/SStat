
#include "SStat.h"
#include "str_switch.h" 



string implode(const vector<string>& elems, char delim);
vector<string> split(const string &s, char delim);
int decimalToOctal(int decimalNumber);
string removeSpaces(string input);
string numToStr(int num);

SStat::SStat(char * file_name){
    struct stat buf;
    stat(file_name, &buf);
    _FileName = file_name;
    _FileSize = buf.st_size;
    _FileBlks = buf.st_blocks;
    _FileBB = buf.st_blksize;
    _FileDevDec = buf.st_dev;
    _FileIno = buf.st_ino;
    _FileLnks = buf.st_nlink;
    _UID = buf.st_uid;
    _GID = buf.st_gid;
    _ModTime = buf.st_mtime;
    _ChangTime = buf.st_ctime;
    _AccTime = buf.st_atime;
    _FileMode = buf.st_mode;
}

void SStat::GetAll(){
    passwd *__uid = getpwuid(_UID);
    passwd *__gid = getpwuid(_GID);
    int access_int = decimalToOctal(_FileMode);
    
    string rights;
    rights = this->getRightStr(access_int);

    string UID = __uid->pw_gecos;
    string GID = __gid->pw_gecos;

    printf("  Файл: %s\n", _FileName);
    printf("  Размер: %d             Блоков: %d    Блок В/В: %d   %s\n",_FileSize,_FileBlks, _FileBB, __file_type);
    printf("Устройство: %xh/%dd        Inode: %d     Ссылки: %d\n",_FileDevDec,_FileDevDec,_FileIno,_FileLnks);
    printf("Доступ: (%d/%s)   UID: ( %d/%s )      GID: ( %d/%s )      \n",access_int%10000,rights.c_str(), _UID, UID.substr(0, UID.size()-3).c_str(), _GID, GID.substr(0, GID.size()-3).c_str());
    tm *aTm = gmtime(&_AccTime);
    printf("Доступ: %.4i-%.2i-%.2i %.2i:%.2i:%.2i +0300 \n",
                    (aTm->tm_year % 100 + 2000),
                    (aTm->tm_mon + 1),
                     aTm->tm_mday,
                     (aTm->tm_hour + 3)%24,
                     aTm->tm_min,
                     aTm->tm_sec
                     );
    
    tm *mTm = gmtime(&_ModTime);
    printf("Модифицирован: %.4i-%.2i-%.2i %.2i:%.2i:%.2i +0300 \n",
                    (mTm->tm_year % 100 + 2000),
                    (mTm->tm_mon + 1),
                     mTm->tm_mday,
                     (mTm->tm_hour + 3)%24,
                     mTm->tm_min,
                     mTm->tm_sec);
    
    tm *cTm = gmtime(&_ChangTime);
    printf("Изменен: %.4i-%.2i-%.2i %.2i:%.2i:%.2i +0300 \n",
                    (cTm->tm_year % 100 + 2000),
                    (cTm->tm_mon + 1),
                     cTm->tm_mday,
                     (cTm->tm_hour + 3)%24,
                     cTm->tm_min,
                     cTm->tm_sec);
    printf(" Создан: -\n");    

}


void SStat::GetConrete(char * mode){
    SWITCH (mode)
    {
        CASE("-c%A"):{
            int access_int = decimalToOctal(_FileMode);
            string rights;
            rights = this->getRightStr(access_int);
			printf("%s\n", rights.c_str());
            break;
        }
        CASE("-c%a"):{
            int access_int = decimalToOctal(_FileMode);
            cout << access_int%10000 << endl;
            break;
        }
        CASE("-c%B"):{
            cout << _FileBB/_FileBlks << endl;
            break;
        }
        CASE("-c%b"):{
            cout << _FileBlks << endl;
            break;
        }
        CASE("-c%d"):{
            cout << _FileDevDec << endl;
            break;
        }
        CASE("-c%D"):{
            cout << hex << _FileDevDec << endl;
            break;
        }
        CASE("-c%F"):{
            switch (_FileMode & S_IFMT) {
                case S_IFBLK:  __file_type = "Блочное устройство";break;
                case S_IFCHR:  __file_type = "Символьное устройство";break;
                case S_IFDIR:  __file_type = "Каталог";break;
                case S_IFIFO:  __file_type = "FIFO";break;
                case S_IFLNK:  __file_type = "Символьная ссылка";break;
                case S_IFREG:  __file_type = "Обычный файл";break;
                case S_IFSOCK: __file_type = "Сокет";break;
                default:      __file_type = "unknown?";break;
            }
            cout << __file_type << endl;
            break;
        }
        CASE("-c%f"):{
			cout << hex << _FileMode << endl;
            break;
        }
        CASE("-c%g"):{
            cout << _GID << endl;
            break;
        }
        CASE("-c%G"):{
            passwd *__gid = getpwuid(_GID);
            cout << __gid->pw_gecos << endl;
            break;
        }
        CASE("-c%h"):{
            cout << _FileLnks << endl;
            break;
        }
        CASE("-c%i"):{
            cout << _FileIno << endl;
            break;
        }
        CASE("-c%m"):{
            char resolved_path[PATH_MAX]; 
            realpath(_FileName, resolved_path); 
            string path;
            path.push_back(resolved_path[0]);
            path.erase(0,1);
            // cout << path;
            vector<string> Words = split(path, '/');
            // for (vector<string>::iterator it = Words.begin() ; it!=Words.end() ; ++it)
            //     cout<<*it;
            cout << endl;
        }
        CASE("-c%n"):{
			printf("%s \n",_FileName);
            break;
        }
        CASE("-c%N"):{
			printf("'%s' \n",_FileName);
            break;
        }
        CASE("-c%o"):{
			printf("%d \n",_FileBB);
            break;
        }
        CASE("-c%s"):{
			printf("%d \n",_FileSize);
            break;
        }
        CASE("-c%T"):{
			cout << 0 << endl;
            break;
        }
        CASE("-c%u"):{
			cout << _UID << endl;
            break;
        }
        CASE("-c%U"):{
            passwd *__uid = getpwuid(_UID);
            cout << __uid->pw_gecos << endl;
            break;
        }
        
    }

}


string SStat::getRightStr(int num){
    vector<string> rightsVec(4);
    int num1, num2, num3;
    switch (_FileMode & S_IFMT) {
        case S_IFBLK:  __file_type = "Блочное устройство";break;
        case S_IFCHR:  __file_type = "Символьное устройство";break;
        case S_IFDIR:  __file_type = "Каталог";break;
        case S_IFIFO:  __file_type = "FIFO";break;
        case S_IFLNK:  __file_type = "Символьная ссылка";break;
        case S_IFREG:  __file_type = "Обычный файл";break;
        case S_IFSOCK: __file_type = "Сокет";break;
        default:      __file_type = "unknown?";break;
    }
        
    if (__file_type=="Каталог"){
      	rightsVec.push_back("d");
      	num1 = ((num%1000)/100);
       	num2 = ((num%1000)/10)%10;
       	num3 = ((num%1000)%10);
        rightsVec.push_back(numToStr(num1));
        rightsVec.push_back(numToStr(num2));
        rightsVec.push_back(numToStr(num3)); 
    } else {
      	rightsVec.push_back("-");
       	num1 = ((num%1000)/100);
       	num2 = ((num%1000)/10)%10;
       	num3 = ((num%1000)%10);
        	
        rightsVec.push_back(numToStr(num1));
        rightsVec.push_back(numToStr(num2));
        rightsVec.push_back(numToStr(num3)); 
        }   
    
        string s;

        s = implode(rightsVec,' ');
        s = removeSpaces(s); 
        return s;
    }

string numToStr(int num){
    switch (num)
    {
       	case 0: return "---"; break;
    	case 1: return "--x"; break;
        case 2: return "-w-"; break;
        case 3: return "-wx"; break;
        case 4: return "r--"; break;
        case 5: return "r-x"; break;
        case 6: return "rw-"; break;
        case 7: return "rwx"; break;
    }
}


// Function to convert decimal number to octal
int decimalToOctal(int decimalNumber)
{
    int rem, i = 1, octalNumber = 0;
    while (decimalNumber != 0)
    {
        rem = decimalNumber % 8;
        decimalNumber /= 8;
        octalNumber += rem * i;
        i *= 10;
    }
    return octalNumber;
}


string& implode(const vector<string>& elems, char delim, string& s)
{
    for (vector<string>::const_iterator ii = elems.begin(); ii != elems.end(); ++ii)
    {
        s += (*ii);
        if ( ii + 1 != elems.end() ) {
            s += delim;
        }
    }

    return s;
}

string implode(const vector<string>& elems, char delim)
{
    string s;
    return implode(elems, delim, s);
}


vector<string> &split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}



string removeSpaces(string input)
{
  input.erase(std::remove(input.begin(),input.end(),' '),input.end());
  return input;
}