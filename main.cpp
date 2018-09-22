#include <iostream>
#include <fstream>
#include <string.h>

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

    Opcode(char opcode_arg[],char machineCode_arg[],char addressFormat_arg[]){
        strcpy(opcode,opcode_arg);
        strcpy(machineCode,machineCode_arg);
        strcpy(addressFormat,addressFormat_arg);
        next = NULL;
        cout<<"Creating for "<<opcode<<"*"<<machineCode<<"*"<<addressFormat<<"\n";
    }
};

class HashMapForOpcode{
    /*
        bucketSize -> Holds the current bucket size of HashMap
        Hashmap -> pointer to the the HashMap with LL
    */
    int bucketSize;
    Opcode **Hashmap;

    /*
        Calculates Hash Value corresponding to Opcode
    */
    int getHashValue(char opcode[]){
        int value =0;
        for(int i=0;opcode[i]!='\0';i++){
            value = (value+(int)opcode[i])%bucketSize;
        }
        return value;
    }
    
    public:
    // Constructor for class with default Bucket Size as 13
    HashMapForOpcode(int s = 13){
        bucketSize = s;
        Hashmap = new Opcode*[13];
    }

    void insertIntoMap(char opcode[],char machineCode[],char addressFormat[]){
        Opcode *temp = new Opcode(opcode,machineCode,addressFormat);
        int hashValue = getHashValue(opcode);
        if(Hashmap[hashValue]==NULL){
            Hashmap[hashValue] = temp;
        }else{
            Opcode *ptr = Hashmap[hashValue];
            while(ptr->next!=NULL){
                ptr = ptr->next;
            }
            ptr->next = temp;
        }
    }

};

int main(){
    ifstream opcode_machineCode;
    
    /*
        Here We are making HashMap of Opcodes
    */
    opcode_machineCode.open("Opcode_MachineCode.txt");
    HashMapForOpcode HMap;
    char opcode[10],machineCode[35],addressFormat[5];
    while(!opcode_machineCode.eof()){
        opcode_machineCode>>opcode;
        opcode_machineCode>>machineCode;
        opcode_machineCode>>addressFormat;
        HMap.insertIntoMap(opcode,machineCode,addressFormat);
    }

    opcode_machineCode.close();
    return 0;
}