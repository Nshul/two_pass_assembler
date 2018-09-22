#include <iostream>
#include <cstdio>

using namespace std;

/*
    This Class is used to perform
    Hashing using Chaining for Opcodes
    and corresponding Machine codes and 
    Type of instruction
*/
struct Opcode{
    /*
        opcode refers to Mnemonic
        machineCode refers to corresponding Machine Code
        addressFormat refers to whether
            rri -> Register Register Immediate Addr.
            rrr -> Register Register Register
            ri -> Register Immediate Addr.
            a -> Addr.
            z -> Zero i.e. Implicit
    */
    char opcode[10];
    char machineCode[35];
    char addressFormat[5];
    
    // Pointer to next node in LL of Bucket
    Opcode *next;
};

class HashMapSymbol{
    int bucketSize;
    Opcode *Hashmap;
    public:
    HashMapSymbol(int s = 13){
        bucketSize = s;
        Hashmap = new Opcode[13];
    }
};

int main(){
    freopen("Hello.txt","w",stdout);
    cout<<"U";
    return 0;
}