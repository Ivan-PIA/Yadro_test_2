

class Billing{
    public:
        int number_table;
        tm time;
        bool start_end;

        Billing(int num_t, tm timer, bool tf_start) : number_table(num_t), time(timer), start_end(tf_start) {}
        
};
