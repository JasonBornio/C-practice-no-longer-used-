class Sign_Extend {
    public:
        Sign_Extend();

        void extend_byte(bool arr[8]);
        void extend_half(bool arr[16]);
        void get_output(bool arr[32]);

    private:
        bool output[32] = {};

};

Sign_Extend::Sign_Extend(){

}

void Sign_Extend::extend_byte(bool arr[8]){
    if(arr[0]){
        for(int i = 0; i < 24; i++){
            output[i] = true;
        }
    }
    else{
        for(int i = 0; i < 24; i++){
            output[i] = false;
        }
    }
    for(int i = 0; i < 8; i++){
        output[i + 24] = arr[i];
    }
}

void Sign_Extend::extend_half(bool arr[16]){
    if(arr[0]){
        for(int i = 0; i < 16; i++){
            output[i] = true;
        }
    }
    else{
        for(int i = 0; i < 16; i++){
            output[i] = false;
        }
    }
    for(int i = 0; i < 16; i++){
        output[i + 16] = arr[i];
    }
}

void Sign_Extend::get_output(bool arr[32]){
    for(int i = 0; i < 32; i++){
        arr[i] = output[i];
    }
}
