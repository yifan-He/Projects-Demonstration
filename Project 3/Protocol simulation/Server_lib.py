import copy
import os


class Slib:
    request = ""
    directory = ''
    response = ""

    def __init__(self, request, directory):
        self.request = request
        self.directory = directory

    def get_file_lists(self):
        files = os.listdir(self.directory)
        self.response = normal_case()
        self.response += "{\n"
        for x in files:
            if os.path.isdir(self.directory + '/' + x):
                files.remove(x)
            else:
                self.response += x
        header = self.request.split("\r\n")[-1]
        header = header.split("\n\n")[0]
        if header != "":
            self.response += "\n" + header
        self.response += "\n}"

    def get_file_content(self, filename):
        files = os.listdir(self.directory)
        self.response += normal_case()
        self.response += "{\n"
        if filename in files:
            with open(self.directory + '/' + filename) as f:
                lines = f.readlines()
            for line in lines:
                self.response += line
            header = self.request.split("\r\n")[-1]
            header = header.split("\n\n")[0]
            if header != "":
                self.response += "\n" + header
            self.response += "\n}"
            # print(self.response)
        else:
            self.response = error_404()
            # print(self.response)

    def post_file_content(self, filename, content):
        with open(self.directory + '/' + filename, 'w') as f:
            f.write(content)
        header = self.request.split("\r\n")[2]
        if header != "":
            self.response = normal_case() + "{\nFile created or overwritten.\n" + header + "\n}"
        else:
            self.response = normal_case() + "{\nFile created or overwritten.\n}"

    def handle_input(self):
        body = copy.deepcopy(self.request)
        lists = self.request.split()
        detail = lists[1]
        der1 = detail[detail.index("/") + 2:]
        der2 = der1[der1.index("/") + 1: len(der1) - 1]
        der = der2[:der2.index("/")]  # find the directory base
        if der != self.directory:
            self.response = error_403()  # secure
        else:
            if "GET" in lists and der2[-1] == "/":  # if it is get and not request file name
                self.directory = der2[:der2.rindex("/")]
                self.get_file_lists()
            # print(self.response)
            elif "GET" in lists and der2[der2.index("/") + 1:] != "":  # if it is get and have request file name
                filename = detail[detail.rindex("/") + 1:len(detail) - 1]
                self.directory = der2[:der2.rindex("/")]
                self.get_file_content(filename)  # go to the path and load response
                # print(self.response)
            if "POST" in lists:
                filename = detail[detail.rindex("/") + 1:]
                self.directory = der2[:der2.rindex("/")]
                body = body.split("\r\n\r\n")[-1]
                content = body
                self.post_file_content(filename, content)


def normal_case():
    return ('HTTP/1.0 200 OK\nContent-Type: text/html\n\n')


# not found
def error_404():
    return ('HTTP/1.0 404 Not Found\nContent-Type: text/html\n\n{\nThe file not found!\n}')


# request deny
def error_403():
    return ('HTTP/1.0 403 request deny\nContent-Type: text/html\n\n{\nYou are trying to access outside of the directory!\n}')

# slib = Slib("get http://localhost:8080/Base/","Base")
# slib = Slib("get http://localhost:8080/Base/B/b.txt","Base")
# slib = Slib("post 12345 http://localhost:8080/Base/B/b.txt","Base")

# slib.handle_input()
