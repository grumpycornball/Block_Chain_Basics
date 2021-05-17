#include <bits/stdc++.h>
#include <openssl/sha.h> //for sha hash
using namespace std;

struct block{

    int index;      // Block number
    string timestamp;   // Obvious
    int proof;      // Also called nonce
    string previousHash; // contain hash of previous block
};

string timestamp()
{
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    return asctime( localtime(&ltime) ) ;
}

void sha256_string(char *string, char outputBuffer[65])     //function courtesy of https://stackoverflow.com/a/2458382/5340585 
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, string, strlen(string));
    SHA256_Final(hash, &sha256);
    int i = 0;
    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

// Function to create hash
string create_hash(int proof, string previousHash){

    char hash[65];
    char *input = new char[(to_string(proof)+previousHash).length() + 1];
    strcpy(input, (to_string(proof)+previousHash).c_str());
    sha256_string(input,hash);
    
    return hash;
    
}

// Function to mine for proof
int mineBlock(string previousHash){

    int nonce=0;
    bool keepMining=true;
    while(keepMining){

        if( create_hash(nonce, previousHash).substr(0,4) == "0000" ){     //You can increase complexity of problem here by increasing leading 0's 
            keepMining=false;
            break;
        }
        nonce++;
    }
    return nonce;
}

// Function to add block in the chain
void addBlock(struct block *chain[], int *i){

    struct block *temp = new block();
    temp->index=*(i)+1;
    temp->timestamp=timestamp();
    temp->previousHash=create_hash(chain[*(i)-1]->proof,chain[*(i)-1]->previousHash);
    temp->proof=mineBlock(temp->previousHash);
    
    chain[*(i)]=temp;
    *(i)=*(i)+1;

}

// Funcion to print chain
void printChain(struct block *chain[], int i){

    cout<<"--------------Length:"<<i<<"----------------\n";
    int j=0;
    while(j<i){

        cout<<"Index        : "<<chain[j]->index<<endl;
        cout<<"Timestamp    : "<<chain[j]->timestamp;
        cout<<"Proof        : "<<chain[j]->proof<<endl;
        cout<<"previousHash : "<<chain[j]->previousHash<<endl;
        j++;
        cout<<"------------------------------\n";        
    }

    cout<<"------------------------------\n";
}

// Function to verify chain
bool check_chain(struct block *chain[], int i){

    for (int j = i-1; j>0; j--)
    {
        if(create_hash(chain[j-1]->proof,chain[j-1]->previousHash) == chain[j]->previousHash ){
                // All good
        }else{
                // Fishy
            cout<<"Chain is tampered at "<<j<<"th block"<<endl;
            return false;
        }
    }
    cout<<"Chain is all good"<<endl;
    return true;
}

// Function to tamper chain
void tamper_chain(struct block *chain[], int i){

    if(i<=3){
        cout<<" Chain is not long enough "<<endl;
    }else{
        chain[3]->proof=123;
    }

}

int main(){

    struct block *chain[10]; // Can change size if you want
    int i=0;
    // Lets create genesis block
    struct block *genesis = new block();
    genesis->index=i+1;
    genesis->timestamp=timestamp();
    genesis->proof=1;
    genesis->previousHash="0";
    chain[i]=genesis;
    i++;

    while(true){
        cout<<"\nWhat do you want to do?  \n 1. View All Blocks \n 2. Add Block \n 3. Verify Chain \n 4. Tamper chain\n";
        int ans;
        cin>>ans;
        switch(ans){
            case 1:
            printChain(chain, i);
            break;
            case 2:
            addBlock(chain, &i);
            break;
            case 3:
            check_chain(chain, i);
            break;
            case 4:
            tamper_chain(chain, i);
            break;
            default:
            cout<<"Wrong choice \n";
            break;
        }

        cout<<"#############################\n";
    }

    // Operations
    return 0;
}