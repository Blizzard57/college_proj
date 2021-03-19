import sys
import Pyro4

uri = sys.argv[1].strip()
graphactions = Pyro4.Proxy(uri)

while True:
    try:
        command = input().strip().split(" ")
        if command[0] == "add_graph":
            if len(command) < 3:
                print("client : insufficient arguments")
                continue
            graphactions.addGraph(command[1],int(command[2]))

        elif command[0] == "add_edge":
            if len(command) < 5:
                print("client : insufficient arguments")
                continue
            graphactions.appendVertex(command[1],int(command[2]) - 1,int(command[3]) - 1,int(command[4]))

        elif command[0] == "get_mst":
            if len(command) < 2:
                print("client : insufficient arguments")
                continue
            print(graphactions.getMst(command[1]))

        else :
            print("client : unknown command")
    except EOFError:
        exit(0)