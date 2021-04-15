
import datetime # Required for timestamp
import hashlib # Required for calculating hash
import json # We'll return data in Json
from flask import Flask,jsonify # Will help us create API to interact with blockchain
import logging

class Blockchain:
    
    # Constructor, create list for chain and genesis block
    def __init__(self):
        self.chain = []
        self.create_block(proof=1,previous_block_hash='0')
    
    # Define create_block function, Block will contain index,timestamp,proof and previous block 
    def create_block(self,proof,previous_block_hash):
        block= { "index":len(self.chain)+1,
                "timestamp":str(datetime.datetime.now()),
                "proof":proof,
                "previous_block_hash":previous_block_hash }
        self.chain.append(block)
        return block
    
    # Define function to get last block from chain
    def last_chain_block(self):
        return self.chain[-1]
    
    # Calculate Proof of work i.e. nonce
    def calculate_proof(self, previous_hash):
        current_proof=1
        keep_going=True
        while keep_going is True:
            current_hash=hashlib.sha256(str(str(current_proof)+previous_hash).encode()).hexdigest()
            if current_hash[:4] == "0000":
                keep_going=False
            else:
                current_proof+=1
        return current_proof
    
    # Function to create hash
    def create_hash(self,proof,previous_block_hash):
        return hashlib.sha256(str(str(proof)+previous_block_hash).encode()).hexdigest()
    
    # Function to verify if chain is valid
    def is_chain_good(self, app):
        looping_variable=len(self.chain)-1
        while looping_variable > 0:
            block=self.chain[looping_variable]
            previous_block=self.chain[looping_variable-1]
            if block['previous_block_hash'] != self.create_hash(previous_block['proof'],previous_block['previous_block_hash']):
                return "Chain is not intact, block"+str(looping_variable)+" has been tampered | \n"
            looping_variable=looping_variable-1
        return "chain is fine"
    
    #This function will mess up the data in chain, to test if is_chain_good is working
    def mess_up_chain(self):
        index_to_mess_up=3
        if index_to_mess_up >= len(self.chain):
            return "Chain is still not big enough, try mining more"
        self.chain[index_to_mess_up]['proof']=123               # You can insert any random value here
        return "Chain is meesed up at index "+str(index_to_mess_up)
    


# Initializing webapp
app=Flask("Blockchain_app")

blockChain= Blockchain()

# Define functions

@app.route('/mine_block', methods= ['GET'])
def mine_it():
    previous_block=blockChain.last_chain_block()
    previous_hash=blockChain.create_hash(previous_block["proof"],previous_block["previous_block_hash"])
    current_proof=blockChain.calculate_proof(previous_hash)
    current_block=blockChain.create_block(current_proof,previous_hash)
    data_to_return= { "message":"Block created sucessfully",
        "block": current_block}
    return jsonify(data_to_return),200
    
    
    
@app.route('/view_chain', methods= ['GET'])
def display_it():
    data_to_return={ "length_of_chain":len(blockChain.chain), 
                    "block": blockChain.chain}
    return jsonify(data_to_return),200


@app.route('/is_chain_ok', methods= ['GET'])
def is_chain_okay():
    data_to_return={'message':blockChain.is_chain_good(app)}
    return jsonify(data_to_return),200

@app.route('/tamper_chain', methods= ['GET'])
def tamper_chain():
    data_to_return={'message':blockChain.mess_up_chain()}
    return jsonify(data_to_return),200
# Start webapp

app.run(host="0.0.0.0",port=5000)