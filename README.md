# Block_Chain_Basics
Practising blockchain basics

This repository will contain code varying from basic blockchain model to advanced one.

# Makefile added :
To build, use make command. For Help use 'make help'. Rest is obvious.

# basic_bitcoin.py : 
python script to host api and allows basic blockchain operations (Non persistent one)
- Visit 127.0.0.1:5000/mine_block     : Hit this url to mine block (genesis block is already present when server is hosted)
- Visit 127.0.0.1:5000/view_chain     : Hit this url to view the chain
- Visit 127.0.0.1:5000/is_chain_ok    : Hit this url to check if the chain is tampered with i.e. data is changed/altered
- Visit 127.0.0.1:5000/tamper_chain   : Hit this url to tamper the block, by default you'll temper 3rd block you can change code to tamper any other.

# basic_bitcoin.cpp :
Lets see if the mining is faster in cpp rest is self explanatory.  
