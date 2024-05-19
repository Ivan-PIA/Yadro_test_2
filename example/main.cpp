#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <regex>
#include <chrono>
#include <queue>
#include <algorithm>  
#include <set>


#include <C:\Users\Ivan\Desktop\lerning\YADRO\Yadro_test_2\src\ComputerClub.hpp>

using namespace std;



int run(ifstream &file){

    ComputerClub info;
    string line;

    int i = 0;

    while(getline(file, line)){
        
        if (i == 0){
            info.set_count_table(line);
            //cout << info.get_count_table() << endl;
        }

        else if(i == 1){
            info.set_open_close_time(line);
            tm time_open = info.get_time_open();
            cout <<(time_open.tm_hour < 10 ? "0" : "") << time_open.tm_hour << ":"<<
            (time_open.tm_min < 10 ? "0" : "") << time_open.tm_min << endl;
        }

        else if (i == 2){
            info.set_price(line);
            //cout << info.get_price() << endl;
        }   

        else{
            cout << line << endl;
            info.set_ivent(line);
        }
        

        
        i++;
    }

    //info.print_client_in_club();
    info.close_club();
    
    tm time_close = info.get_time_close();


    cout <<(time_close.tm_hour < 10 ? "0" : "") << time_close.tm_hour << ":"<<
    (time_close.tm_min < 10 ? "0" : "") << time_close.tm_min << endl;

    info.count_money_day();


}


int main(int argc, char* argv[]){

    if (argc < 2) {
        cout << "Пожалуйста, укажите путь к файлу в качестве аргумента программы." << endl;
        return 1;
    }
    
    const char* file_name = argv[1];
    ifstream file(file_name);

    if (!file.is_open()){
        cout << "Error open file!" << endl;
        return 1;
    }


    run(file);

}