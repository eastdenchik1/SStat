/*
Название: Системная утилита SStat на С++.
Разработал: Свиридов Денис.
ВУЗ: РУТ (МИИТ).
Группа: УИБ-411.
*/

#include "SStat.h"



int main(int argc, char ** argv){
   // Проверка на наличие операндов
   if (argc == 1){
      cout << argv[0] << ": пропущен операнд.\nПо команде '" << argv[0] << " --help' можно получить доп. информацию." << endl;
      return 0;
   } else if (argc == 2) {
         if (strcmp(argv[1],"--help")==0){
            cout << "Раздел помощи. " << endl;
            const char fname[36] = "stat.file";
            string line;
            ifstream fin(fname, ios::in);
            
            while (getline(fin,line)){
               cout << line << endl;
            }
            fin.close(); // закрываем файл
            return 0;
         } else if (strcmp(argv[1],"--version")==0) {
            cout << argv[0] << " version - 1.0" << endl; return 0;
         } else { 
            SStat obj = SStat(argv[1]);
            obj.GetAll();   
         }
      } else if (argc == 3) {
         SStat obj = SStat(argv[2]);
         obj.GetConrete(argv[1]);
      }
      
   }

