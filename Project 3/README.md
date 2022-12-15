Source code: Protocol simulation folder

<h3>Program discription</h3>
This is a simple simulation between a user and a server by sending packets through the router.(use socket to send and receive the packets)<br/><br/> 
It contains two types of message that users can send: get and post. Get is to get the information from the server. Post is to request for a change. Depending on the requests the server and client get, they will process and display the information correctly.


<h3>To run the program</h3>
1.open the cmd, go to the directory of router, type router --port=3000 --drop-rate=0.2 --max-delay=10ms --seed=1(port: where the router listening to, drop rate: the rate that router may drop the packet, max-delay: the maximum delay that may happened to the router)<br/>
2.run the server<br/>
3.run the client(it will automaticlly do the 3-way handshake between the user and the server)<br/>
4.uncomment or write your own instructions like httpc get "http://127.0.0.1:8007/Base/"<br/>

<h3>The meaning of instructions</h3>
get     executes a HTTP GET request and prints the response.<br/>
post    executes a HTTP POST request and prints the response.<br/>
-v      Prints the detail of the response such as protocol, status, and headers.<br/>
-h      key:value Associates headers to HTTP Request with the format 'key:value'<br/>
-d      string Associates an inline data to the body HTTP POST request.<br/>
-f      file Associates the content of a file to the body HTTP POST request.<br/>
Either [-d] or [-f] can be used but not both.<br/>

all of these can be find by typing httpc help after running the client part.

<h3>snap shot time</h3>
Handshake1 send from user to server and get responded from server<br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%203/img/handshake2.png"/><br/>

Handshake2 and 3 send from server to user and get responded from user<br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%203/img/handshake1%2C3.png"/><br/>

If a packet is delayed or dropped by the router, our policy is to send a fetch request after every 5 seconds.<br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%203/img/no%20response.png"/><br/>

You can also see the packets flow in the router from the cmd<br/>
<img src="https://github.com/yifan-He/Projects-Demonstration/blob/main/Project%203/img/cmd%20data.png"/><br/>
