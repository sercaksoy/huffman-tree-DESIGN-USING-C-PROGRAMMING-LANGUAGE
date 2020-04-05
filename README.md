# huffman-tree-DESIGN-USING-C-PROGRAMMING-LANGUAGE
Hey ! It is my second assignment from "Data Structures and Algorithm" class that I took at Yildiz Technical University. This repository contains; code of program , screenshots while it is processing , and Assignment's description.

# what is huffman tree and huffman coding
  In computer science and information theory, a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. You can find more detailed informations from here https://en.wikipedia.org/wiki/Huffman_coding but I want to describe it basicly;
  Huffman coding takes input and counts frequencies which belong to datas symbols. It can be integers or characters doesn't matter. Then 
it builds a tree which has with more frequent datas are closer to the root. Then the program manipulates the size of characters by their
distance to root. This part important, program keeps the inputs symbols, size of to their distances to the root, not by their data types. So the complete data represented by less bits from now on.
# How to implement
  Usually trees are created by a class which includes two pointers as left and right child to point same type classes. You can create your sorted list by using linked list and if your linked list has tree properties like right and left child. You can create your tree upon linked list. 
# It works like..
Program can take inputs from file or command prompt by User's decision. Input part is using totaly dynamic memory. In the file case, first we are searching for file's memory and then allocating the memory. In the command prompt case, the program is reading string character by character and if characters counter reach the allocated memory , program resizing it by realloc.

You can easily understand program's run logic from comments where is written in the .c file. And there are some paint drawings about functions I coded. After all you can always send me e-mails about this repository.
# Some pictures
I draw some sketches about algortihm before coding and I wanted to attach it here so you can understand how the program works.
<img src="https://github.com/sercfornow/huffman-tree-DESIGN-USING-C-PROGRAMMING-LANGUAGE/blob/master/handsketch/10.jpg">
<img src="https://github.com/sercfornow/huffman-tree-DESIGN-USING-C-PROGRAMMING-LANGUAGE/blob/master/handsketch/20.jpg">

And here you can see the linked list is created step by step.

<img src="https://github.com/sercfornow/huffman-tree-DESIGN-USING-C-PROGRAMMING-LANGUAGE/blob/master/screenshots/fulllist.png">

I used insertionSort to order list after all frequency increment. You can see the function and details below. And after all you can check the main function to understand how to use it.

<img src="https://github.com/sercfornow/huffman-tree-DESIGN-USING-C-PROGRAMMING-LANGUAGE/blob/master/functionsandDescription/insertionSort.png">
