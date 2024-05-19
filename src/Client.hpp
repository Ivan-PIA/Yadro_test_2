#include <iostream>
#include <ctime>
using namespace std;

class Client {
    private:
        int number_table;
        string name;
        tm time {};

    public:
        Client(int num, string& name_client, tm time_client) : number_table(num), name(name_client), time(time_client) {}

        void print_client(){
            cout << "Client : "<< number_table << " " <<  name << " " << time.tm_hour << ":"<< time.tm_min <<  endl;
        }

        void set_table(int table){
            number_table = table;
        }
        void set_time(tm set_t){
            time = set_t;
        }

        int get_table(){
            return number_table;
        }

        string get_name(){
            return name;
        }

        tm get_time(){
            return time;
        }
};