import Server_lib
import socket
import threading
import ipaddress

from packet import Packet

class Httpfs:
    host = "127.0.0.1"
    port = 8007
    directory = "Base"
    client_host = "127.0.0.1"
    client_port = 41830

    current_seq = 4  # the initial sequence number

    def __init__(self, port, directory):
        self.port = port
        self.directory = directory

    def set_port(self, port):
        self.port = port

    def set_dirctory(self, directory):
        self.directory = directory


def help_msg():
    print("httpfs is a simple file server.\n"
          "Usage:\n"
          "     httpfs [-v] [-p PORT] [-d PATH-TO-DIR]\n"
          "     -v Prints debugging messages.\n"
          "     -p Specifies the port number that the server will listen and serve at. Default is 8080.\n"
          "     -d Specifies the directory that the server will use to read/write requested files. Default is the current directory when launching the application.\n"
          )


def welcome_msg():
    print("Welcome to httpf file sever!")


def server_input(httpfs):
    data = input()
    lists = (data.split())
    if lists[0] == "httpfs":
        if "-v" in lists:
            print("\nthe server is listening at the port: " + str(
                httpfs.port) + "\nthe current directory is: " + httpfs.directory)
        if "-p" in lists:
            httpfs.port = lists[lists.index("-p") + 1]
        if "-d" in lists:
            httpfs.directory = lists[lists.index("-d") + 1]


def run_server(httpfs):
    conn = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        httpfs.client_host = ipaddress.ip_address(socket.gethostbyname(httpfs.client_host))
        conn.bind((httpfs.host, httpfs.port)) # maybe needed in the client calso
        print('server is listening at', httpfs.port)
        while True:
            try:
                data, sender = conn.recvfrom(1024)
                handle_client(conn, data, sender, httpfs.directory, httpfs)
            except Exception as error:
                print("Something went wrong: " + repr(error))
    finally:
        conn.close()


def handle_client(conn, data, sender, directory, httpfs):
    try:
        print("waiting for requests...")
        p = Packet.from_bytes(data)
        print("Router: ", sender)
        print("Packet: ", p)
        print("Payload: ", p.payload.decode("utf-8") + "\n")

        # How to send a reply.
        # The peer address of the packet p is the address of the client already.
        # We will send the same payload of p. Thus we can re-use either `data` or `p`.
        if p.packet_type == 1:
            if p.seq_num == 1:
                msg = "Hello Client"
                p.payload = msg.encode("utf-8")
                p.seq_num += 1
                conn.sendto(p.to_bytes(), sender)
            elif p.seq_num == 3:
                print("\nconnection settled\n")
        elif p.packet_type == 0:
            if p.seq_num == httpfs.current_seq:
                httpfs.current_seq += 1
            else:
                httpfs.current_seq = p.seq_num

            request = p.payload.decode("utf-8")
            if not request:
                raise Exception('No data.')
            server_lib = Server_lib.Slib(request, directory)
            server_lib.handle_input()
            responses = server_lib.response
            p.payload = responses.encode("utf-8")
            p.packet_type = 2  # change the type to ack
            print("Sending response...\n")
            conn.sendto(p.to_bytes(), sender)  # send the response
    except Exception as error:
        print("Something went wrong: " + repr(error))


httpfs = Httpfs(8007, "Base")
# welcome_msg()
# help_msg()
# server_input(httpfs)
run_server(httpfs)
