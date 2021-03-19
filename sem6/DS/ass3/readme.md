# Assignment 3
Roll No : 2018113003

## Installing Dependencies
The dependencies are located in requirements.txt and can be installed as follows :
pip install -r requirements.txt

Or if it does not work:
pip3 install -r requirements.txt

## Executing the code
The server has to be started first, which will provide a uri, which is used as the argument in the client, as follows:
python3 server.py

This will print the following output:

Object <class '__main__.GraphActions'>:
    uri = PYRO:example.graphactions@localhost:38461
Pyro daemon running.

The following part has to be copied : PYRO:example.graphactions@localhost:38461

The client has to be started as follows:
python3 client.py PYRO:example.graphactions@localhost:38461 < sample.txt