# Fishing Simulator
A C program to learn about pointers, structs, malloc and free through fishing simulation

## Getting Started

### To Run
For statically allocating fish in arrays
1. ```gcc -o fishingSimulator fishingSimulator.c```
2. ```./fishingSimulator```

For dynamically allocating fish in arrays
1. ```gcc -o dynamicVersion dynamicVersion.c```
2. ```./dynamicVersion``` or ```valgrind --leak-check=yes ./dynamicVersion``` to check for memory leaks

### Contains
```
- fishingSimulator.c
- dynamicVersion.c
- README.md
```
