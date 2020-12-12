#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>

bool game_over(const std::vector<int>& v);
bool proc_num(std::vector<int>& v, int bi, int ei);
void print(std::vector<int>& v);
void rotate_anti_clock(std::vector<int>& v);
int twod_to_oned(int row, int col, int rowlen);
void randomGen(std::vector<int>&v);
void up(std::vector<int>&v);
void down(std::vector<int>&v);
void left(std::vector<int>&v);
void right(std::vector<int>&v);
void merge(std::vector<int>& v);

void print(std::vector<int>& v){
    int side = sqrt(v.size());
    for (int j = 0; j < side; j ++) {
        for (int i = 0; i < side; i++) {
            int index = twod_to_oned(j,i,side);
            int length = std::to_string(v[index]).length();
            std::cout << v[index] << std::string(7 - length, ' ');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool proc_num(std::vector<int>& v, int bi, int ei){
    std::vector<int> result(v);
    std::vector<int> original(v);
    std::vector<int> transform;
    std::vector<int> numbers;
    for (int i = bi; i < ei; i++){
        if (v[i] != 0) {
            numbers.push_back(v[i]);
        }
        result[i] = 0;
    }
    for (int i = 0; i < numbers.size(); i++){
        if ( i == (numbers.size()-1)){
            transform.push_back(numbers[i]);
        }
        else if (numbers[i] == numbers[i+1]){
            transform.push_back(numbers[i]*2);
            i++;
            continue;
        } else {
            transform.push_back(numbers[i]);
        }
    }
    for (int i = 0; i < transform.size(); i++) {
        result[bi+i] = transform[i];
    }
    v = result;
    return (result != original);
}

void rotate_anti_clock(std::vector<int>& v) {
    std::vector<int> temp (v.size(),-1);
    int side = sqrt(v.size());
    for (int i = 0; i < side; i ++) {
        for (int j = 0; j < side; j++) {
            temp[twod_to_oned(-i + side - 1, j, side)] = v[twod_to_oned(j, i, side)];
        }
    }
    v = temp;
}

bool game_over(const std::vector<int>& v){
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 0) {
            return false;
        }
    }
    std::vector<int>rotated(v);
    rotate_anti_clock(rotated);
    int side = sqrt(v.size());
    for (int j = 0; j < side; j ++) {
        for (int i = 0; i < (side - 1); i++) {
            int index1 = twod_to_oned(j, i, side);
            int index2 = twod_to_oned(j, i+1, side);
            if (v[index1] == v[index2] || rotated[index1] == rotated[index2]){
                return false;
            }
        }
    }
    return true;
}

int twod_to_oned(int row, int col, int rowlen){
    return row*rowlen+col;
}

void randomGen(std::vector<int>&v){
    bool zeroPresent=false;
    for(int i=0; i<v.size(); i++){
        if(v[i]==0){
            zeroPresent=true;
        }
    }
    if(zeroPresent){
        int randomIndex = rand() % v.size();
        while(v[randomIndex] != 0 ){
            randomIndex = rand() % v.size();
        }
        v[randomIndex] = 2;
    }
}

void merge(std::vector<int>& v){
    int side = sqrt(v.size());
    bool change = false;
    for(int i=0; i<v.size()-side+1; i=i+side){
        
        change = proc_num(v, i, i + side) || change;
    }
    if (change){
        randomGen(v);
    }
}

void left(std::vector<int>& v){
    merge(v);
}
void up(std::vector<int>& v){
    rotate_anti_clock(v);
    merge(v);
    rotate_anti_clock(v);
    rotate_anti_clock(v);
    rotate_anti_clock(v);
}
void right(std::vector<int>& v){
    rotate_anti_clock(v);
    rotate_anti_clock(v);
    merge(v);
    rotate_anti_clock(v);
    rotate_anti_clock(v);
}
void down(std::vector<int>& v){
    rotate_anti_clock(v);
    rotate_anti_clock(v);
    rotate_anti_clock(v);
    merge(v);
    rotate_anti_clock(v);
}


int main(){

    std::vector<int> s;
    std::vector<int> temp;
    std::string filename;
    
    std::cout << "enter initial configuration file name:" << std::endl;
    std::cout<<std::endl;
    std::cin >> filename;
    std::cout<<std::endl;
    
    std::ifstream infile;
    infile.open(filename.c_str());

    if(infile.is_open()) {
        int tmp;
        while (infile >> tmp) {
            s.push_back(tmp);
        }
    } else {
        std::cout << "file not found, using default start configuration" << std::endl;
        for (int i = 0; i < 15; i++) {
            s.push_back(0);
        }
        s.push_back(2);
    }

    int side = std::sqrt(s.size());
    for(int i = 0; i < side; i++){
        for(int j = 0; j < side; j++){
            std::cout << s[twod_to_oned(i,j,side)] << " ";
        }
        std::cout << std::endl;
    }

    char input;
    while(game_over(s) == false){
        temp=s;
        std::cin >> input;
        std::cout<<std::endl;
        
        if(input == 'a'){
            left(s);
        }
        else if(input == 'w'){
            up(s);
        }
        else if(input == 'd'){
            right(s);
        }
        else if(input == 's'){
            down(s);
        }
        if  (s != temp) {
            print(s);
        }
    }
    std::cout<<"game over"<<std::endl;

    return 0;
}
