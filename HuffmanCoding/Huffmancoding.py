import heapq
import math

class Node:

    def __init__(self, letter, weight):
        self.letter = letter
        self.zero = None
        self.one = None
        self.weight = weight


    def __eq__(self, other):
        return (self.weight == other.weight)

    def __ne__(self, other):
        return not (self == other)

    def __lt__(self, other):
        return (self.weight < other.weight)

    def __repr__(self):
        return "Letter:'%s' Weight: %s" % (self.letter, self.weight)


class Huffman:
    def __init__(self):
        self.__lookup = {}
        self.charmap ={} # created a hashmap to store values for the encoding
        self.decodecharmap={} # for decoding and storing values
        self.padding_bits=0 # for encoding and sending the padding bits to the file.
        # Any other variables you would like to add...
#to check the frequency of each character
    def frequency_count(self,word):
        frequency = {} # creating a dictionary
        #print(word)
        for char in word:
            #checking whether character is in the dictionary or not and assigning 0 at the start
            if not char in frequency:
                frequency[char]=0
                #print("char=",char)
            else:
                pass
            frequency[char]+=1
        return frequency
#create each node for a character
    def create_node(self,frequency):
        self.heap=[] # initialized list
        for key in frequency:
            node =Node(key,frequency[key])
            #print(key)
            heapq.heappush(self.heap,node) # to push elements into heap

# to iterate through the heap and merging the two nodes until the length of the heap is 1
    def merge_nodes(self):
        while(len(self.heap)>1):
            firstnode=heapq.heappop(self.heap)
            secondnode=heapq.heappop(self.heap)
            node=firstnode.weight+secondnode.weight
            mergednode=Node("templetter",node)
            mergednode.left=firstnode
            mergednode.right=secondnode
            heapq.heappush(self.heap,mergednode)
            #print("Heap",self.heap)
#to get the node and the value of the node.
    def get_node_and_value(self):
        root_node=heapq.heappop(self.heap)
        node_val=""#initializing the root node value to null
        self.char_encoding(root_node,node_val) # calling function to add values to the map
#to get the value of the node, traverse the tree
    def char_encoding(self,root_node,node_val):
        if(root_node.letter!="templetter"):
            self.charmap[root_node.letter]=node_val
            return
        self.char_encoding(root_node.left, node_val+"0")
        self.char_encoding(root_node.right, node_val+"1")
    #for decoding and getting char for a value
    def get_value_and_node(self):
        for key in self.charmap:
            self.decodecharmap[self.charmap[key]] = key
#to check the encoded word length and add padding
    def get_padded_byteword(self,word):
        encoded_word=""
        #print(word)
        #print(self.charmap)
        for char in word:
            #print("char",char)
            encoded_word =encoded_word+self.charmap[char]
            #print("encl",len(encoded_word))
        self.padding_bits=8-len(encoded_word)%8 #to add the extra 0s if the length is not multiple of 8
        #print(self.padding_bits)
        for i in range(self.padding_bits):
            encoded_word+="1" #adding 1s at the end as padding_bits
            #encoded_word=encoded_word
        #print("padded_encoded_word",encoded_word,len(encoded_word))
        if(len(encoded_word)%8 !=0): # to check whether it is padded properly or not
            print("Not encoded properly")
            exit(0)
        return encoded_word
    def encode(self, inFileName, outFileName):
        """
        inFileName is the uncompressed text file
        outFileName is the resulting compressed file
        """
        txtFile = open(inFileName, "r")
        outFile = open(outFileName, "wb")
        word=txtFile.read();
        frequency=self.frequency_count(word)
        intfreq = len(frequency)
        outFile.write(intfreq.to_bytes(2,byteorder="big",signed=False))#1 number of chars
        #print(frequency)
        for key in frequency:
            intkey=ord(key)#converting char to int
            #print(intkey)
            outFile.write(intkey.to_bytes(1, byteorder='big'))#2 key
            outFile.write(frequency[key].to_bytes(4, byteorder="big", signed=False))#2 frequency
        self.create_node(frequency)
        self.merge_nodes()
        self.get_node_and_value()
        byte_word= self.get_padded_byteword(word)
        bitsequence=len(byte_word)-self.padding_bits
        outFile.write(bitsequence.to_bytes(4,byteorder="big",signed=False))#3 length of bit sequence
        for i in range(0,len(byte_word)):
            if(i%8==0):
                val=byte_word[i:i+8]
                intval=int(val,2)
                i=i+8
                text=intval.to_bytes(1,byteorder="big",signed=False)
                outFile.write(text)#4 encoded data
        #print(len(byte_word),"padding_bits")
        outFile.write(self.padding_bits.to_bytes(1,byteorder="big",signed=False))#last padding bits
        txtFile.close()
        outFile.close()
        print("Encoded to tabFile.dat")
        return outFile
#to remove the padding and decode the word
    def decode_word(self, binstringval,padding_bits):
        encoded_word = binstringval[:-1*padding_bits]
        #print("encode_word",encoded_word)
        decoded_word = ""
        node_val=""
        #reading each bit in the str
        for bit in encoded_word:
                node_val +=bit
                if(node_val in self.decodecharmap):
                        char = self.decodecharmap[node_val]
                        decoded_word += char
                        #print(char)
                        node_val = ""
        return decoded_word

    def decode(self, inFileName, outFileName):

        """
        inFileName is the compressed text file
        outFileName is the resulting uncompressed file
        """

        txtFile = open(inFileName, "rb")
        outFile = open(outFileName, "w")

        charcount = int.from_bytes(txtFile.read(2),"big")#reads the number of characters
        #print(charcount)
        frequency ={} #to get the frequency of characters
        for i in range(charcount):
            key = txtFile.read(1).decode("utf-8") # reads 1 byte,key and decodes
            value = int.from_bytes(txtFile.read(4),"big")# reads the value
            frequency[key] = value
        #print (frequency)
        self.create_node(frequency)
        self.merge_nodes()
        self.get_node_and_value() #to construct the encoding of the chars and values
        self.get_value_and_node() # to reverse the key and value for decoding
        encodedbitlength = int.from_bytes(txtFile.read(4), "big")#reading the number of bits in the encoded sequence
        #print(encodedbitlength)
        bitstring=''
        a=txtFile.tell() # returns the current file pointer position
        stringbinvalue='' # used to get the binary values of the data till the end of the file
        data=True
        while data:
            chunk = txtFile.read(1) # reading from current position(bitsequence) to end of the file including padding bits
            #print(len(chunk))
            if (len(chunk)!=0):
                val=int.from_bytes(chunk,"big")
                binval=f'{val:08b}'
                #print(binval)
                binvalue=binval.rjust(8,'0')
                stringbinvalue+=binvalue
            else:
                data=False
        decoded_padding_bits=int(binvalue,2) # converting last byte, padding bits to integer
        #print("padding_bits",decoded_padding_bits)
        #print("stringbinvalue",stringbinvalue)
        encoded_word_tosend=stringbinvalue[:-8] # encoded word
        #print(encoded_word_tosend)
        decode_word=self.decode_word(encoded_word_tosend,decoded_padding_bits)
        outFile.write(decode_word)
        txtFile.close()
        outFile.close()
        print("Decoded to DecodedText.txt")
def main():
    huff=Huffman()
    inFileName="Text.txt"
    outFile="tabFile.dat"
    encodedfile=Huffman.encode(huff,inFileName,outFile)
    encodedfile='tabFile.dat'
    decodeoutfile="DecodeText.txt"
    huff.decode(encodedfile,decodeoutfile)

if __name__ == "__main__":
        main()
