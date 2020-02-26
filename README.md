First run the server: ./server <Server's IP> <Server's port>
Run the client: ./client <8 bit binary no> <probability> <Server's IP> <Server's port>

Problem Description:
In this assignment, you will implement a data link layer channel between two nodes A and B using socket API, where node A and node B are the client and the server of the socket interface. Data link layer protocol should use the following Error handling technique using hamming code.

Single bit Error Correction using Hamming Code:

Node A before sending a data item computes the codeword using hamming code. The generated codeword may be corrupted with single bit error (to simulate erroneous channel) before transmission. The receiver corrects the error in the received codeword (if any) and prints the data item. You must incorporate the error generating code based on a given BER (Bit Error Rate) or probability (random no).

For simulation of Bit Error, you have to use random number generators as follows:-

Suppose, the probability of error, p, is given as 0.4 (p should be always ≤ 1.0). You must use a random number generator, R1, which generates a random number in the range [0, 9]. If R1 generates a number in [0, 3], then Bit Error should be introduced in the data frame. Otherwise, (i.e. if R1 generates any number in [4, 9]) no Bit Error should be introduced in the data frame.
In the case, when Bit Error is to be introduced, you have to use another random number generator to generate a number between 0 and 11 (assuming no of bits in the resultant codeword is 12) to decide on the bit position b, in the codeword, which is to be corrupted (or flipped).

Assume that the sender is going to send one ASCII character at a time and receiver will print both the corrupted and corrected ASCII characters.
