struct Word {
   char* letters;
   char unique[5];
   int counts[5];
   char* hint1;
   char* hint2;
} word;  

Word dictionary[30] = {
    {(char*)"frame", {'f', 'r', 'a', 'm', 'e'}, {1,1,1,1,1}, (char*)"activation ___", (char*)"memory layout"},
    {(char*)"stack", {'s', 't', 'a', 'c', 'k'}, {1,1,1,1,1}, (char*)"LIFO structure", (char*)"used in recursion"},
    {(char*)"cache", {'c', 'a', 'c', 'h', 'e'}, {1,1,1,1,1}, (char*)"memory type", (char*)"speed booster"},
    {(char*)"fault", {'f', 'a', 'u', 'l', 't'}, {1,1,1,1,1}, (char*)"page ___", (char*)"segmentation error"},
    {(char*)"ascii", {'a', 's', 'c', 'i', 'i'}, {1,1,1,1,1}, (char*)"character encoding", (char*)"text format"},
    {(char*)"shift", {'s', 'h', 'i', 'f', 't'}, {1,1,1,1,1}, (char*)"bitwise operation", (char*)"arithmetic type"},
    {(char*)"debug", {'d', 'e', 'b', 'u', 'g'}, {1,1,1,1,1}, (char*)"fix errors", (char*)"code troubleshooting"},
    {(char*)"align", {'a', 'l', 'i', 'g', 'n'}, {1,1,1,1,1}, (char*)"memory boundary", (char*)"data structure"},
    {(char*)"flush", {'f', 'l', 'u', 's', 'h'}, {1,1,1,1,1}, (char*)"pipeline", (char*)"clear stage"},
    {(char*)"timer", {'t', 'i', 'm', 'e', 'r'}, {1,1,1,1,1}, (char*)"measure time", (char*)"system clock"},
    {(char*)"cycle", {'c', 'y', 'c', 'l', 'e'}, {1,1,1,1,1}, (char*)"instruction ___", (char*)"execution loop"},
    {(char*)"mutex", {'m', 'u', 't', 'e', 'x'}, {1,1,1,1,1}, (char*)"thread safety", (char*)"exclusive lock"},
    {(char*)"adder", {'a', 'd', 'd', 'e', 'r'}, {1,1,1,1,1}, (char*)"arithmetic unit", (char*)"logic circuit"},
    {(char*)"xorai", {'x', 'o', 'r', 'a', 'i'}, {1,1,1,1,1}, (char*)"XOR operation", (char*)"boolean logic"},
    {(char*)"array", {'a', 'r', 'r', 'a', 'y'}, {2,2,1,1,1}, (char*)"data structure", (char*)"indices required"},
    {(char*)"input", {'i', 'n', 'p', 'u', 't'}, {1,1,1,1,1}, (char*)"from user", (char*)"or external device"},
    {(char*)"trace", {'t', 'r', 'a', 'c', 'e'}, {1,1,1,1,1}, (char*)"debugging", (char*)"program analysis"},
    {(char*)"flags", {'f', 'l', 'a', 'g', 's'}, {1,1,1,1,1}, (char*)"status bits", (char*)"conditional checks"},
    {(char*)"loops", {'l', 'o', 'o', 'p', 's'}, {1,1,1,1,1}, (char*)"iteration", (char*)"control construct"},
    {(char*)"clock", {'c', 'l', 'o', 'c', 'k'}, {1,1,1,1,1}, (char*)"oscillator", (char*)"system timing"},
    {(char*)"logic", {'l', 'o', 'g', 'i', 'c'}, {1,1,1,1,1}, (char*)"boolean algebra", (char*)"circuit design"},
    {(char*)"input", {'i', 'n', 'p', 'u', 't'}, {1,1,1,1,1}, (char*)"data stream", (char*)"from external source"},
    {(char*)"store", {'s', 't', 'o', 'r', 'e'}, {1,1,1,1,1}, (char*)"write operation", (char*)"to memory"},
    {(char*)"branch", {'b', 'r', 'a', 'n', 'c'}, {1,1,1,1,1}, (char*)"control flow", (char*)"jump instruction"},
    {(char*)"carry", {'c', 'a', 'r', 'r', 'y'}, {1,1,1,1,1}, (char*)"arithmetic", (char*)"overflow bit"},
    {(char*)"trace", {'t', 'r', 'a', 'c', 'e'}, {1,1,1,1,1}, (char*)"execution", (char*)"tracking tool"},
    {(char*)"fetch", {'f', 'e', 't', 'c', 'h'}, {1,1,1,1,1}, (char*)"instruction phase", (char*)"CPU cycle"},
    {(char*)"write", {'w', 'r', 'i', 't', 'e'}, {1,1,1,1,1}, (char*)"data transfer", (char*)"to memory"},
    {(char*)"level", {'l', 'e', 'v', 'e', 'l'}, {1,2,1,1,1}, (char*)"cache hierarchy", (char*)"organization"},
    {(char*)"loops", {'l', 'o', 'o', 'p', 's'}, {1,1,1,1,1}, (char*)"iteration", (char*)"repeated execution"}
};

struct Word1 {
   char* letters;
   char unique[7];
   int counts[7];
   char* hint1;
   char* hint2;
} word1;  

Word1 hard_dictionary[10] = {
    {(char*)"vector", {'v', 'e', 'c', 't', 'o', 'r'}, {1,1,1,1,1,1}, (char*)"data structure", (char*)"dynamic array"},
    {(char*)"kernel", {'k', 'e', 'r', 'n', 'e', 'l'}, {1,1,1,1,1,1}, (char*)"OS core", (char*)"system manager"},
    {(char*)"binary", {'b', 'i', 'n', 'a', 'r', 'y'}, {1,1,1,1,1,1}, (char*)"base-2", (char*)"low-level data"},
    {(char*)"buffer", {'b', 'u', 'f', 'f', 'e', 'r'}, {1,1,2,1,1,1}, (char*)"temporary storage", (char*)"data queue"},
    {(char*)"branch", {'b', 'r', 'a', 'n', 'c', 'h'}, {1,1,1,1,1,1}, (char*)"control flow", (char*)"jump statement"},
    {(char*)"output", {'o', 'u', 't', 'p', 'u', 't'}, {1,1,1,1,1,1}, (char*)"result", (char*)"data display"},
    {(char*)"stream", {'s', 't', 'r', 'e', 'a', 'm'}, {1,1,1,1,1,1}, (char*)"data flow", (char*)"file or socket"},
    {(char*)"module", {'m', 'o', 'd', 'u', 'l', 'e'}, {1,1,1,1,1,1}, (char*)"program component", (char*)"independent unit"},
    {(char*)"loader", {'l', 'o', 'a', 'd', 'e', 'r'}, {1,1,1,1,1,1}, (char*)"linker process", (char*)"program starter"},
    {(char*)"syntax", {'s', 'y', 'n', 't', 'a', 'x'}, {1,1,1,1,1,1}, (char*)"code rules", (char*)"grammar in programming"}
};
