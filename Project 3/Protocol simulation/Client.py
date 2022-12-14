import socket
import ipaddress
import sys

from packet import Packet


class Httpc:
    host = "127.0.0.1"  # server host
    port = 0  # server port
    router_host = "localhost"
    router_port = 3000
    conn = None
    seq_num = 4  # start with 4 to avoid confusing between the handshaking nak and request nak. 1-3:handshaking nak
    backup_pack = None

    command = ""  # get/post/help
    url = ""
    verbose = False  # -v
    header = ""  # -h
    data = ""  # -d
    file = ""  # -f
    file_name = ""  # -o

    def __init__(self, host, port, command, url, verbose, header, data, file, filename):
        self.host = host
        self.port = port
        self.command = command
        self.url = url
        self.verbose = verbose
        self.header = header
        self.data = data
        self.file = file
        self.file_name = filename

    # three handshake
    def three_way_handshake(self):
        conn = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.conn = conn
        peer_ip = ipaddress.ip_address(socket.gethostbyname(self.host))
        timeout = 5
        try:
            msg = "Hello Server"
            p = Packet(packet_type=1,
                       seq_num=1,
                       peer_ip_addr=peer_ip,
                       peer_port=self.port,
                       payload=msg.encode("utf-8"))
            conn.sendto(p.to_bytes(), (self.router_host, self.router_port))
            print('Send "{}" to router'.format(msg))
            self.backup_pack = p

            # Try to receive a response within timeout
            conn.settimeout(timeout)
            print('Waiting for a response')
            response, sender = conn.recvfrom(1024)
            p = Packet.from_bytes(response)
            print("Message from server: " + p.payload.decode("utf-8"))
            if p.packet_type == 1 and p.seq_num == 2:  # third handshake
                msg = "I am going to send data !"
                p = Packet(packet_type=1,
                           seq_num=3,
                           peer_ip_addr=peer_ip,
                           peer_port=self.port,
                           payload=msg.encode("utf-8"))
                conn.sendto(p.to_bytes(), (self.router_host, self.router_port))
                print('Send "{}" to router'.format(msg))
        except socket.timeout:
            print('No response after {}s'.format(timeout))
            print("reconnecting....\n")
            self.three_way_handshake()

    # get
    def https_get_request(self):
        try:
            peer_ip = ipaddress.ip_address(socket.gethostbyname(self.host))
            timeout = 5
            request = f"""GET {self.url} HTTP/1.0\nHost: {self.host}\r\n{self.header}\n\n"""
            p = Packet(packet_type=0,
                       seq_num=self.seq_num,
                       peer_ip_addr=peer_ip,
                       peer_port=self.port,
                       payload=request.encode("utf-8"))
            self.conn.sendto(p.to_bytes(), (self.router_host, self.router_port))
            print('Send "{}" to router'.format(request))
            self.backup_pack = p

            if not self.verbose:  # -v
                total_response = ""
                self.conn.settimeout(timeout)
                print('Waiting for a response...')
                response, sender = self.conn.recvfrom(1024)
                p = Packet.from_bytes(response)
                if p.packet_type == 2:  # if receive the ack
                    if p.seq_num == self.seq_num:
                        self.seq_num += 1
                        payload = p.payload
                        total_response += payload.decode("utf8")
                        print(total_response[total_response.find("{"):])
            else:
                self.conn.settimeout(timeout)
                print('Waiting for a response...')
                response, sender = self.conn.recvfrom(1024)
                p = Packet.from_bytes(response)
                if p.packet_type == 2:  # if receive the ack
                    if p.seq_num == self.seq_num:
                        self.seq_num += 1
                        payload = p.payload
                        print(payload.decode("utf8"))
        except socket.timeout:
            print('No response after {}s'.format(timeout))
            print("retransmitting the packet!....\n")
            self.https_get_request()

    # -o
    def https_o_request(self):
        try:
            self.conn.connect((self.host, self.port))
            request = f"""GET {self.url} HTTP/1.0\nHost: {self.host}\n\n"""
            self.conn.sendall(request.encode("utf8"))
            total_response = ""
            while True:
                response = self.conn.recv(1024)
                total_response += response.decode("utf8")
                if len(response) < 1:
                    break
                with open(self.file_name, 'w') as f:
                    f.write(total_response[total_response.find("{"):])
        except Exception as error:
            print("Something went wrong: " + repr(error))

    # post
    def https_post_request(self):
        try:
            if self.file != "" and self.data != "":
                sys.exit(0)  # if both -d -f , exit the system
            if self.file != "" and self.data == "":
                with open(self.file) as f:
                    lines = f.readlines()
                for line in lines:
                    self.data += line  # -f
            request = f"""POST {self.url} HTTP/1.0\r\nHost: {self.host}\r\n{self.header}\r\nContent-Length: {len(bytes(self.data, "utf8"))}\r\nConnection: Close\r\n\r\n{self.data}"""

            peer_ip = ipaddress.ip_address(socket.gethostbyname(self.host))
            timeout = 5
            p = Packet(packet_type=0,
                       seq_num=self.seq_num,
                       peer_ip_addr=peer_ip,
                       peer_port=self.port,
                       payload=request.encode("utf-8"))
            self.conn.sendto(p.to_bytes(), (self.router_host, self.router_port))
            print('Send "{}" to router'.format(request))
            self.backup_pack = p

            if not self.verbose:  # -v
                total_response = ""
                print('Waiting for a response...')
                self.conn.settimeout(timeout)
                response, sender = self.conn.recvfrom(1024)
                p = Packet.from_bytes(response)
                if p.packet_type == 2:  # if receive the ack
                    if p.seq_num == self.seq_num:
                        self.seq_num += 1
                        payload = p.payload
                        total_response += payload.decode("utf8")
                        print(total_response[total_response.find("{"):])
            else:
                self.conn.settimeout(timeout)
                print('Waiting for a response...')
                response, sender = self.conn.recvfrom(1024)
                p = Packet.from_bytes(response)
                if p.packet_type == 2:  # if receive the ack
                    if p.seq_num == self.seq_num:
                        self.seq_num += 1
                        payload = p.payload
                        print(payload.decode("utf8"))
        except socket.timeout:
            print('No response after {}s'.format(timeout))
            print("retransmitting the packet!....\n")
            self.data = ''
            self.https_post_request()


def help_msg():
    print("httpc is a curl-like application but supports HTTP protocol only.\n"
          "Usage:\n"
          "     httpc command [arguments]\n"
          "The commands are:\n"
          "     get     executes a HTTP GET request and prints the response.\n"
          "     post    executes a HTTP POST request and prints the response.\n"
          "     help    prints this screen.\n\n"
          'Use "httpc help [command]" for more information about a command.\n')


def help_get_msg():
    print("Usage: httpc get [-v] [-h key:value] URL\n\n"
          "Get executes a HTTP GET request for a given URL.\n\n"
          "     -v      Prints the detail of the response such as protocol, status, and headers.\n"
          "     -h      key:value Associates headers to HTTP Request with the format key:value'.\n")


def help_post_msg():
    print("Usage: httpc post [-v] [-h key:value] [-d inline-data] [-f file] URL\n\n"
          "Post executes a HTTP POST request for a given URL with inline data or from file.\n\n"
          "     -v      Prints the detail of the response such as protocol, status, and headers.\n"
          "     -h      key:value Associates headers to HTTP Request with the format 'key:value'.\n"
          "     -d      string Associates an inline data to the body HTTP POST request.\n"
          "     -f      file Associates the content of a file to the body HTTP POST request.\n\n"
          "Either [-d] or [-f] can be used but not both.\n")


def welcome_msg():
    print("Welcome to httpc!\n"
          'Use "httpc help" for more information.\n')


def get_input(httpc):
    httpc.data = ''
    httpc.file = ''

    data = input()
    lists = (data.split())
    if lists[0] == "httpc":
        if "help" in lists:
            if "get" in lists:
                help_get_msg()
            elif "post" in lists:
                help_post_msg()
            else:
                help_msg()
        else:
            if "-o" in lists:  # need fix
                httpc.file_name = lists[lists.index("-o") + 1]
            if httpc.file_name != "":
                if lists[len(lists) - 3][0:1] == "'":
                    httpc.url = lists[len(lists) - 3][1:len(lists[len(lists) - 3]) - 1]
                else:
                    httpc.url = lists[len(lists) - 3]  # -o url different
            else:
                if lists[len(lists) - 1][0:1] == "'":
                    httpc.url = lists[len(lists) - 1][1:len(lists[len(lists) - 1]) - 1]
                else:
                    httpc.url = lists[len(lists) - 1]  # some with' some does not
            httpc.host = httpc.url[httpc.url.index("/") + 2:len(httpc.url) - 1][
                         0:httpc.url[httpc.url.index("/") + 2:len(httpc.url) - 1].index("/")]
            if ":" in httpc.host:
                httpc.port = int(httpc.host[httpc.host.index(":") + 1:])
                httpc.host = httpc.host[: httpc.host.index(":")]
            if "get" in lists:
                httpc.command = "get"
            if "post" in lists:
                httpc.command = "post"
            if "-v" in lists:
                httpc.verbose = True
            if "-f" in lists:
                httpc.file = lists[lists.index("-f") + 1]
                httpc.data = ""
            if "--d" in lists:
                httpc.data = (lists[lists.index("--d") + 1] + lists[lists.index("--d") + 2])[
                             1:len(lists[lists.index("--d") + 1] + lists[lists.index("--d") + 2]) - 1]
            if "-h" in lists:
                httpc.header = lists[lists.index("-h") + 1]

    else:
        raise Exception('Syntax error.')


welcome_msg()
httpc = Httpc('127.0.0.1', 8007, "", '', False, "", "", "", "")
httpc.three_way_handshake()

while True:
    try:
        get_input(httpc)

        if httpc.command == "get":
            httpc.https_get_request()

        if httpc.command == "post":
            httpc.https_post_request()

        if httpc.verbose == True and httpc.file_name != "":
            httpc.https_o_request()
    except Exception as error:
        print("Something went wrong: " + repr(error) + "\nPlease check your syntax and try again.\n")
    # finally:
    #     httpc.conn.close()

# httpc get "http://127.0.0.1:8007/Base/"
# httpc get -v "http://127.0.0.1:8007/Base/"
# httpc get -v -h Content-Type:application/json "http://127.0.0.1:8007/Base/"
# httpc get -v -h Content-Type:application/json "http://127.0.0.1:8007/Base/B/"

# httpc get "http://127.0.0.1:8007/Base/B/b.txt"
# httpc get -v "http://127.0.0.1:8007/Base/a.txt"
# httpc get -v "http://127.0.0.1:8007/Base/B/b.txt"
# httpc get -v -h Content-Type:application/json "http://127.0.0.1:8007/Base/a.txt"

# httpc post --d '{"Assignment": 1}' http://127.0.0.1:8007/Base/a.txt
# httpc post -f test.txt http://127.0.0.1:8007/Base/a.txt
# httpc post -v -h Content-Type:application/json --d '{"Assignment": 1}' http://127.0.0.1:8007/Base/a.txt
# httpc post -v -h Content-Type:application/json -f test.txt http://127.0.0.1:8007/Base/a.txt

# cd C:\Users\15528\Desktop\Study\COMP 445\LA3\LA3_Router\router\windows
# cd D:\concordia\HYF\Comp course material\comp445
# router --port=3000 --drop-rate=0.2 --max-delay=10ms --seed=1
# router --port=3000 --drop-rate=0 --max-delay=10ms --seed=1
# router --port=3000 --drop-rate=0.4 --max-delay=0ms --seed=1
