# cuckoo-hash-implementation
Cuckoo Hashing algorithm implemented in C++, focusing on fast lookup, insertion, and efficient collision management using dual hash tables.

Cuckoo Hashing in C++
*A simple and efficient implementation of the Cuckoo Hashing algorithm using the C programming language.
*This project demonstrates collision handling in hash tables using multiple hash functions and relocation (rehashing) of elements.

About Cuckoo Hashing
*Cuckoo Hashing is a collision resolution technique where:
*Two hash tables (or hash functions) are used.
*If a collision occurs, the existing element is “kicked out” and moved to another position.
*This process continues until a free slot is found.

 This ensures:
✔ Fast lookup
✔ Efficient collision handling
✔ Constant average search time

 Features
*Implementation in pure C++ language
*Dual hash function concept
*Collision handling using displacement strategy
*Insert, search, and display operations
*Simple logic suitable for learning and academic purposes

Technologies Used
*C++ Programming Language
*Standard C++ Libraries
