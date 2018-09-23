#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

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
    }

    Opcode(){
        next = NULL;
    }
};

struct Symbol{
    /*
        labelName refers to the Label in Code
        address gives the address of Label
    */
    char labelName[100];
    int address;
    Symbol *next;

    Symbol(char label[],int addr){
        strcpy(labelName,label);
        address = addr;
        next = NULL;
    }
};

/*
    This Class is used to perform
    Hashing using Chaining for Opcodes
    and corresponding Machine codes and 
    Type of instruction
*/
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
    /*
        Constructor for class with default Bucket Size as 13
    */
    HashMapForOpcode(int s = 13){
        bucketSize = s;
        Hashmap = new Opcode*[s];
    }

    /*
        Insert Opcode into HashMap
    */
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

    /*
        Returns Value from HashMap
    */
    Opcode* returnValue(char opcode[]){
        int tempVal = getHashValue(opcode);
        Opcode *tempPtr = Hashmap[tempVal];
        while(strcmp(tempPtr->opcode,opcode)!=0){
            tempPtr=tempPtr->next;
        }
        return tempPtr;
    }

    /*
        Print HashMap
    */
    void printHashMap(){
        Opcode *tempPtr;
        for(int i=0;i<bucketSize;i++){
            cout<<i<<":\n";
            tempPtr = Hashmap[i];
            while(tempPtr!=NULL){
                cout<<tempPtr->opcode<<" "<<tempPtr->machineCode<<" "<<tempPtr->addressFormat<<"\n";
                tempPtr = tempPtr->next;
            }
        }
    }
};

class HashMapForSymbol{
    /*
        bucketSize -> Holds the current bucket size of HashMap
        Hashmap -> pointer to the the HashMap with LL
    */
    int bucketSize;
    Symbol **Hashmap;

    /*
        Calculates Hash Value corresponding to Opcode
    */
    int getHashValue(char label[]){
        int value =0;
        for(int i=0;label[i]!='\0';i++){
            value = (value+(int)label[i])%bucketSize;
        }
        return value;
    }
    
    public:
    /*
        Constructor for class with default Bucket Size as 13
    */
    HashMapForSymbol(int s = 13){
        bucketSize = s;
        Hashmap = new Symbol*[s];
    }

    /*
        Insert Opcode into HashMap
    */
    void insertIntoMap(char label[],int addr){
        Symbol *temp = new Symbol(label, addr);
        int hashValue = getHashValue(label);
        if(Hashmap[hashValue]==NULL){
            Hashmap[hashValue] = temp;
        }else{
            Symbol *ptr = Hashmap[hashValue];
            while(ptr->next!=NULL){
                ptr = ptr->next;
            }
            ptr->next = temp;
        }
    }

    /*
        Returns Value from HashMap
    */
    int returnAddr(char label[]){
        int tempVal = getHashValue(label);
        Symbol *tempPtr = Hashmap[tempVal];
        while(strcmp(tempPtr->labelName,label)!=0){
            tempPtr=tempPtr->next;
        }
        return tempPtr->address;
    }

    /*
        Print HashMap
    */
    void printHashMap(){
        Symbol *tempPtr;
        for(int i=0;i<bucketSize;i++){
            cout<<i<<":\n";
            tempPtr = Hashmap[i];
            while(tempPtr!=NULL){
                cout<<tempPtr->labelName<<" "<<tempPtr->address<<"\n";
                tempPtr = tempPtr->next;
            }
        }
    }

    /*
        This prints symbol table to text file
    */
    void publishMap(){
        ofstream symbolTableFile;
        symbolTableFile.open("symbolTable.txt",ios::out);
        Symbol *tempPtr;
        for(int i=0;i<bucketSize;i++){
            tempPtr = Hashmap[i];
            while(tempPtr!=NULL){
                symbolTableFile<<tempPtr->labelName<<" "<<tempPtr->address<<"\n";
                tempPtr = tempPtr->next;
            }
        }
    }
};

/*
    This function generates Machine Code
    for registers used
*/
string outputCodeForRegister(char reg[]){
    if(strcmp("A",reg)==0){
        return "001";
    }else if(strcmp("B",reg)==0){
        return "010";
    }else if(strcmp("C",reg)==0){
        return "011";
    }else if(strcmp("D",reg)==0){
        return "100";
    }else if(strcmp("H",reg)==0){
        return "101";
    }else if(strcmp("L",reg)==0){
        return "110";
    }
}

void numToBin(char numStr[],char conv[]){
    int num=0;
    int itr=0;
    while(numStr[itr]!='\0'){
        num=num*10+(numStr[itr]-'0');
        itr++;
    }
    // cout<<"num is:"<<num<<"\n";
    char ans[33];
    for(int i=0;i<32;i++){
        if(num&1){
            ans[31-i]='1';
        }else{
            ans[31-i]='0';
        }
        num/=2;
    }
    ans[32]='\0';
    // cout<<"ans is:"<<ans<<"\n";
    strcpy(conv,ans);
}

void numToBin(int num,char conv[]){
    char ans[33];
    for(int i=0;i<32;i++){
        if(num&1){
            ans[31-i]='1';
        }else{
            ans[31-i]='0';
        }
        num/=2;
    }
    ans[32]='\0';
    // cout<<"ans is:"<<ans<<"\n";
    strcpy(conv,ans);
}

int main(){
    ifstream opcode_machineCode, inputCodeFile;
    ofstream outputCodeFile;
    
    /*
        Here We are making HashMap of Opcodes
    */
    opcode_machineCode.open("Opcode_MachineCode.txt");
    HashMapForOpcode OpcodeMap;
    char opcode[10],machineCode[35],addressFormat[5];
    while(!opcode_machineCode.eof()){
        opcode_machineCode>>opcode;
        opcode_machineCode>>machineCode;
        opcode_machineCode>>addressFormat;
        OpcodeMap.insertIntoMap(opcode,machineCode,addressFormat);
    }
    // OpcodeMap.printHashMap();
    opcode_machineCode.close();
    /*
        HashMap is constructed Now
    */

    // FIRST PASS
    inputCodeFile.open("inputCode.txt",ios::in);
    HashMapForSymbol SymbolTable;
    char Input[100];int itr=0;
    int addr=200;
    while(inputCodeFile.getline(Input,sizeof(Input))){
        for(itr=0;Input[itr]!='\0';itr++);
        cout<<addr<<":"<<Input<<"\n";
        if(Input[itr-1]==':'){
            //This Input is Label
            Input[itr-1]='\0';
            SymbolTable.insertIntoMap(Input,addr);
            addr--;
        }
        addr++;
    }
    // SymbolTable.printHashMap();

    // SECOND PASS
    inputCodeFile.clear();
    inputCodeFile.seekg(0,ios::beg);
    outputCodeFile.open("outputCode.txt",ios::out);
    Opcode *tempOpcode;
    char reg1[20];
    char reg2[20];
    char reg3[20];
    int itr1,itr2,itr3;
    while(inputCodeFile>>Input){
        itr=0;
        for(itr=0;Input[itr]!='\0';itr++);
        if(Input[itr-1]==':'){
            //This Input is Label
            outputCodeFile<<"\n";
        }else{
            tempOpcode = OpcodeMap.returnValue(Input);
            outputCodeFile<<tempOpcode->machineCode;
            if(strcmp(tempOpcode->addressFormat,"rr")==0){
                inputCodeFile>>reg3;
                itr1=itr3=0;
                while(reg3[itr3]!=','){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                itr3++;
                outputCodeFile<<outputCodeForRegister(reg1);
                itr1=0;
                while(reg3[itr3]!='\0'){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                outputCodeFile<<outputCodeForRegister(reg1);
                outputCodeFile<<"\n";
            }else if(strcmp(tempOpcode->addressFormat,"rrr")==0){
                inputCodeFile>>reg3;
                itr1=itr3=0;
                while(reg3[itr3]!=','){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                itr3++;
                outputCodeFile<<outputCodeForRegister(reg1);
                itr1=0;
                while(reg3[itr3]!=','){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                itr3++;
                outputCodeFile<<outputCodeForRegister(reg1);
                itr1=0;
                while(reg3[itr3]!='\0'){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                outputCodeFile<<outputCodeForRegister(reg1);
                outputCodeFile<<"\n";
            }else if(strcmp(tempOpcode->addressFormat,"ri")==0){
                inputCodeFile>>reg3;
                itr1=itr3=0;
                while(reg3[itr3]!=','){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                itr3++;
                outputCodeFile<<outputCodeForRegister(reg1);
                itr1=0;
                while(reg3[itr3]!='\0'){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                numToBin(reg1,reg2);
                // cout<<"conv is:"<<reg2<<"\n";
                outputCodeFile<<reg2;
                outputCodeFile<<"\n";
            }else if(strcmp(tempOpcode->addressFormat,"rri")==0){
                inputCodeFile>>reg3;
                itr1=itr3=0;
                while(reg3[itr3]!=','){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                itr3++;
                outputCodeFile<<outputCodeForRegister(reg1);
                itr1=0;
                while(reg3[itr3]!=','){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                itr3++;
                outputCodeFile<<outputCodeForRegister(reg1);
                itr1=0;
                while(reg3[itr3]!='\0'){
                    reg1[itr1++]=reg3[itr3++];
                }
                reg1[itr1]='\0';
                numToBin(reg1,reg2);
                outputCodeFile<<reg2;
                outputCodeFile<<"\n";
            }else if(strcmp(tempOpcode->addressFormat,"r")==0){
                inputCodeFile>>reg3;
                outputCodeFile<<outputCodeForRegister(reg1);
                outputCodeFile<<"\n";
            }else if(strcmp(tempOpcode->addressFormat,"z")==0){
                outputCodeFile<<"\n";
            }else if(strcmp(tempOpcode->addressFormat,"a")==0){
                inputCodeFile>>reg3;
                outputCodeFile<<" ";
                int addr = SymbolTable.returnAddr(reg3);
                numToBin(addr,reg2);
                outputCodeFile<<reg2<<"\n";
            }
        }
    }
    inputCodeFile.close();
    outputCodeFile.close();

    SymbolTable.publishMap();
    return 0;
}