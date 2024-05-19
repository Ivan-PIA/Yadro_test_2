
#include <C:\Users\Ivan\Desktop\lerning\YADRO\Yadro_test_2\src\Client.hpp>
#include <C:\Users\Ivan\Desktop\lerning\YADRO\Yadro_test_2\src\Billing.hpp>


class ComputerClub {
    
    private:

        int count_table;
        int price_hour;
        tm time_open {};
        tm time_close {};
        vector <string> client_in_club;
        vector <Client> client_at_table;
        vector <Client> waiting_clients;
        vector <Billing> billing_vector;


    public:
        

        void print_client_in_club(){
            for (string &cl : client_in_club)
                cout << "name " << cl<< endl;
        }


        void set_count_table(string &line){

            regex formatRegex(R"(^\d+$)");
            if (!regex_match(line, formatRegex)) {
                cout << "Error at line " << line << endl;
                exit(0);
            }

            // string to char
            char buf[line.size() + 1];
            strcpy(buf,line.c_str()); 
            
            int err_form = sscanf(buf, "%d", &count_table);

            
        }

        int get_count_table(){
            return count_table;
        }

        void set_open_close_time(string &line){
            
            regex formatRegex(R"(^([01][0-9]|2[0-3]):([0-5][0-9])\s([01][0-9]|2[0-3]):([0-5][0-9])$)");
            if (!regex_match(line, formatRegex)) {
                cout << "Error at line " << line << endl;
                exit(0);
            }

            // string to char
            char buf[line.size() + 1];
            strcpy(buf,line.c_str());

            int err_form = sscanf(buf, "%d:%d %d:%d", &time_open.tm_hour, &time_open.tm_min, &time_close.tm_hour, &time_close.tm_min);    
    
        }

        tm get_time_open(){
            return time_open;
        }

        tm get_time_close(){
            return time_close;
        }

        void set_price(string& line){

            regex formatRegex(R"(^\d+$)");
            if (!regex_match(line, formatRegex)) {
                cout << "Error at line: " << line << endl;
                exit(0);
            }

            // string to char
            char buf[line.size() + 1];
            strcpy(buf,line.c_str()); 
            
            int err_form = sscanf(buf, "%d", &price_hour);

            
        }

        int get_price(){
            return price_hour;
        }

        void print_time(tm time){
            cout <<(time.tm_hour < 10 ? "0" : "") << time.tm_hour << ":"<<
            (time.tm_min < 10 ? "0" : "") << time.tm_min;
        }

        void add_client(string &name, tm time){

            bool exists = false;
            

            for (string& el : client_in_club) {
                
                if (name.data() == el){

                    exists = true;
                    break;
                }
            }
            
            if (exists) {
                print_time(time);
                cout << " 13 YouShallNotPass" << endl;
            } 
            else {
                client_in_club.push_back(name.data());
                
            }
            
           
        }

        int check_error_time(tm time){
            
            if (time.tm_hour < time_open.tm_hour){
                print_time(time);
                cout << " 13 NotOpenYet" << endl;
                return 0;
            }

        }


        int check_client_in_club(string name, tm time){
            
            int flag = 1;

            for (const string& el : client_in_club) {
                if (el == name.data()) {
                    flag = 0;
                    break;
                }    
            }

            if (flag){
                print_time(time);
                cout << " 13 ClientUnknown" << endl;
                return 0;
            }

            return 1;
        }

        int check_size_queue(Client client){
            if (waiting_clients.size() == count_table ){

                ivent_ID_11(client);
                return 0;
            }
            else {
                return 1;
            }
        }

        int check_free_table(Client client){
            
            int tables = get_count_table();
            if (client.get_table() > tables){
                cout << "There's no such table." << endl;
                return 0;
            }
            else {
                for (Client obj : client_at_table){
                    if (obj.get_table() == client.get_table()){
                        
                        if (check_size_queue(client)){
                            waiting_clients.push_back(client);
                        }
                        
                        
                        print_time(client.get_time());
                        cout << " 13 PlaceIsBusy" << endl;
                        return 0;
                    }
                }
                return 1;
            }
        }




        int client_waiting(Client client){
            if (client_in_club.size() < count_table){
                print_time(client.get_time());
                cout << " 13 ICanWaitNoLonger!" << endl;
                return 0;
            }
            else {
                for(Client cl : waiting_clients){
                    if(cl.get_name() != client.get_name()){
                        waiting_clients.push_back(client);
                    }
                }   
                
            }
        }
        
        
        int biling(tm time_start, tm time_end){
            int hour = time_end.tm_hour - time_start.tm_hour;
            int min =  time_end.tm_min - time_start.tm_min;

            if (min < 0){
                min = (time_end.tm_min + 60) - time_start.tm_min;
                hour-=1;
            }

            if (min > 0){
                hour +=1;
            }

            return hour ;
        }
        
        void count_money_day(){
            map <int, int > dif_time;
            map <int, int > sum_map;
            for (int i = 0; i < billing_vector.size(); ++i) {
                int flag = 0;
                for (int j = i; j < billing_vector.size(); ++j) {
                    if (billing_vector[i].number_table == billing_vector[j].number_table ){
                        if(billing_vector[i].start_end == 1){

                            if (billing_vector[i].start_end != billing_vector[j].start_end && flag == 0){

                                dif_time[billing_vector[i].number_table] += biling(billing_vector[i].time, billing_vector[j].time);

                                //cout << billing_vector[i].number_table << "  " << dif_time[billing_vector[i].number_table] << endl;
                                flag = 1;
                            }
                        }
                    }


                }
            }
            for (const auto& pair : dif_time) {
                sum_map[pair.first] += pair.second;
                cout << pair.first << " " << sum_map[pair.first] * price_hour << " " << (sum_map[pair.first] < 10 ? "0" : "") << sum_map[pair.first] << ":" << "00" << endl;
            }

            
        }

        int ivent_ID_11(Client client){
            if(check_client_in_club(client.get_name(),client.get_time())){
                auto iter = client_at_table.cbegin();
                for (int i = 0; i < client_at_table.size(); i ++){

                    if (client.get_name() == client_at_table[i].get_name()){
                        client_at_table.erase(iter+i);
                    }
                }  

                auto iter2 = client_in_club.cbegin();
                for (int i = 0; i < client_in_club.size(); i ++){

                    if (client.get_name() == client_in_club[i]){
                        client_in_club.erase(iter2+i);
                    }
                }
            }

        }


        int sit_client_table(Client new_client){

            //new_client.print_client();
            //cout << "name :: " << new_client.get_name().data() << endl;

            if (check_client_in_club(new_client.get_name(),new_client.get_time()) && check_free_table(new_client)){
                  
                client_at_table.push_back(new_client);

                Billing input(new_client.get_table(),new_client.get_time(), true);
                billing_vector.push_back(input);

                //client_in_club.erase(remove(client_in_club.begin(), client_in_club.end(), new_client.get_name()), client_in_club.end());

            }
            
        }

        void print_queue(){
            for(Client cl : waiting_clients){
                cout <<"queue : "<< cl.get_name()<< " ";

            }
            cout << endl;

        }

        int check_queue_client(int table_free, tm time){
            
            //print_queue();

            if( !waiting_clients.empty()){
                
                Client client = waiting_clients.front();
                waiting_clients.erase(waiting_clients.begin());

                client.set_table(table_free);
                client.set_time(time);

                if (client_at_table.size() < count_table){
                    
                    sit_client_table(client);
                    print_time(time);
                    cout << " 12 " << client.get_name() << " " << client.get_table() << endl;
                    client_in_club.push_back(client.get_name());
                    //print_time(time);
                    //cout << endl;

                }   

            }
            
        }

        void print_client_table(){
            for(Client cl : client_at_table){
                cout<< cl.get_name()<< " " << cl.get_table() << " | " ;

            }
            cout << endl;

        }

        void print_client_billing(){
            for(Billing cl : billing_vector){
                cout << cl.number_table << " " << cl.time.tm_hour << ":" << cl.time.tm_min << " " << cl.start_end << " | "  ;

            }
            cout << endl;

        }

        int client_leaves(Client client){
            
            int table_free;
            tm time {};
            //print_queue();
            
            if(check_client_in_club(client.get_name(),client.get_time())){
                auto iter = client_at_table.cbegin();
                for (int i = 0; i < client_at_table.size(); i ++){

                    if (client.get_name() == client_at_table[i].get_name()){
                        table_free = client_at_table[i].get_table();
                        time = client.get_time();
                        Billing output(client_at_table[i].get_table(),time, false);
                        billing_vector.push_back(output);
                        client_at_table.erase(iter+i);
                    }
                }  

                auto iter2 = client_in_club.cbegin();
                for (int i = 0; i < client_in_club.size(); i ++){

                    if (client.get_name() == client_in_club[i]){
                        client_in_club.erase(iter2+i);
                    }
                }
                //print_client_in_club();  
                //cout << table_free<<endl; 
                check_queue_client(table_free,time);
            
            }
           // print_client_table();

        }



        void close_club(){
            
            // if (client_in_club.size() > 0){
            //     auto iter2 = client_in_club.cbegin();
            //     for (int i = 0; i < client_in_club.size(); i++){
            //         print_time(time_close);
            //         cout << " 11 " << client_in_club[i] << endl;
            //         client_in_club.erase(iter2+i);
            //     }
            // }

            if (client_in_club.size() > 0){
                for (string &cl : client_in_club){
                    print_time(time_close);
                    cout << " 11 " << cl << endl;
                    
                
                } 
            }

            if (client_at_table.size() > 0){
                auto iter = client_at_table.cbegin();
                for (int i = 0; i < client_at_table.size()+1; i ++){
                    //print_time(time_close);
                    //cout << " 11 " << client_at_table[i].get_name().data() << endl;

                    Billing output(client_at_table[i].get_table(),time_close, false);
                    billing_vector.push_back(output);
                    client_at_table.erase(iter+i);

                }                
            }

            //check free vector
            if(0){
                cout << "Debag : " << endl;
                cout << "client in club : " << endl;
                print_client_in_club();
                cout << "client at table : " << endl;
                print_client_table();
                cout << "client billing : " << endl;
                print_client_billing();
            }



        }


        void set_ivent(string& line){

            int id, number_table;
            tm current_time {};
            char  name_char[20];

            

            regex formatRegex(R"(^([01][0-9]|2[0-3]):([0-5][0-9])\s(\d+)\s([a-z0-9_-]+)$)");
            regex formatRegex2(R"(^([01][0-9]|2[0-3]):([0-5][0-9])\s(\d+)\s([a-z0-9_-]+)\s(\d+)$)");

            int form1 = regex_match(line, formatRegex);
            int form2 = regex_match(line, formatRegex2);

            

            if (!regex_match(line, formatRegex) && !regex_match(line, formatRegex2)) {

                cout << "Error at line " << line << endl;
                exit(0);
            }

            char buf[line.size() + 1];
            strcpy(buf,line.c_str());

            
            if (form1){

                int err = sscanf(buf, "%d:%d %d %s", &current_time.tm_hour, &current_time.tm_min, &id, name_char);
                string name(name_char);
                
                Client new_client(1 + rand()%3, name, current_time);

                if (check_error_time(current_time)){
                     
                    switch (id)
                    {
                    case 1: 
                        add_client(name, current_time);
                        break;

                    case 3:
                        client_waiting(new_client);
                        break;
                       
                    case 4:{
                        client_leaves(new_client);
                        break;
                    }
                    default:
                        break;

                    }
                }
            }
            
            else if (form2){

                sscanf(buf, "%d:%d %d %s %d", &current_time.tm_hour, &current_time.tm_min, &id, name_char, &number_table);
                string name(name_char);

                Client new_client(number_table, name, current_time);
                
                sit_client_table(new_client);

            }



        }


};