# calc
A calculator that follows mathematical precedence. This calculator was my first year project.
The MBED is wired up to a 4x4 custom keypad on a piece of breadboard. It had 0-9, the four elementary maths operators and a backspace and equals key.
Until the equals key is pressed the program only listens for key press. When it is pressed the data in the array holding the chars is passed into a function which places the data in OP and Num tokens which are implemented using structs. The structs are recursive and form a binary tree. The tree in traversed and evaluated on a stack again recursively. The function returns and in the original buffer is printed as it now contains and evaluation. A illegal operation is handled by crashing. 
