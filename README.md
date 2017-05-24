# Gossip
Simple gossip(p,k) protocol has been implemented using CSIM. Here we Use a 20 x 50 grid network topology with degree of 4, 
and assume that the communication range are 5m. We have assumed that the nodes are not mobile. The source node i.e. the node at the 
left upper corner of the mesh network will generate a packet. The inter arrival time of packet generation is assumed to be 1 second. 
The destination node (right and lower) is the node at the right lower corner of the mesh network. <br />
Each node forwards the packet to its nearest 1-hop neighbors who further broadcast that packet. 
Each node checks the sequence number of packet it has received and drops the packet if it has already received the packet else it forwards 
the packet. <br />
When a node receive a packet, it broadcasts the packet with probability p to its neighbor and discard the packet with probability 1 – p.
Also a node broadcasts the packet with probability 1 for the first k hops from the source. This simulation ends when the source node
generates 100 packets. For implementing this protocol we create a mesh network of 20*50. <br />
First we use the source node to generate packets and this node transmits packets to it nearest 1-hop neighbor’s node 1 and node 50
using send functions. Each packet contains the following data like the sequence number and number of hops .
form the source node we implement the send function which determines the nodes nearest neighbors and transmits message to them.<br />
Then after transmitting the message with exponential transmission time to the neighbor. At the receiving node we implement the receive 
function where we check if the node has already received the packet. If it has already received that we discard it and don’t transmit 
the packet. We do this by taking a queue which stores the sequence of the packets which have arrived to the node and go 
through the queue and try to perform a linear search on the elements of the queue. If it’s not in the queue we again perform the
send function if the hop count of the packet is less than 4.else we compare the probability of transmitting the packet with the gossiping
proximity which is a uniform value between 0 and 1.
If the gossiping probability value is more than the original probability we drop the packet else drop the packet.
