#include <iostream>
#include <fstream>
#include <string>
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "MutableListSequence.hpp"
#include "ImmutableListSequence.hpp"

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

void writeOutput(const std::string& message) {
    std::ofstream outputFile(OUTPUT_FILE, std::ios::app);
    if (outputFile) {
        outputFile << message << "\n";
        outputFile.close();
    }
}

int main() {
    // int p[4];
    // p[0] = 111;
    // p[1] = 112;
    // p[2] = 113;
    // p[3] = 114;
    // DynamicArray<int>* a = new DynamicArray<int>(p, 4);
    // MutableArraySequence<int>* ar1 = new MutableArraySequence<int>(*a);
    // // ArraySequence<int>* ar3 = new ArraySequence<int>(*a);
    
    // ar1->Append(0);
    // ar1->Append(1);
    // ar1->Append(2);
    // ar1->Append(3);
    // ar1->Append(4);
    // // MutableArraySequence<int>* ar2 = new MutableArraySequence<int>(*ar1);
    // // ar2->Append(11);
    // // ar2->Append(12);
    // // ar2->Append(13);
    // // ar2->Append(14);
    // // ar2->Append(15);
    // MutableArraySequence<int>* sar = ar1->GetSubsequence(1,3);
    // std::cout<<sar->GetLength();


    std::ifstream inputFile(INPUT_FILE);
    if (!inputFile) {
        writeOutput("Error: Cannot open input file.");
        return 1;
    }

    std::ofstream outputFile(OUTPUT_FILE, std::ios::out);
    if (!outputFile) {
        inputFile.close();
        writeOutput("Error: Cannot open output file.");
        return 1;
    }
    outputFile.close();

    Sequence<int>* seq1 = nullptr;
    Sequence<int>* seq2 = nullptr;
    std::string command;

    while (inputFile >> command) {
        if (command == "NEW") {
            std::string type;
            inputFile >> type;
            if (seq1) {
                delete seq1;
                seq1 = nullptr;
            }
            if (type == "MUTABLE_ARRAY") {
                seq1 = new MutableArraySequence<int>();
                writeOutput("MutableArraySequence created.");
            } else if (type == "IMMUTABLE_ARRAY") {
                seq1 = new ImmutableArraySequence<int>();
                writeOutput("ImmutableArraySequence created.");
            } else if (type == "MUTABLE_LIST") {
                seq1 = new MutableListSequence<int>();
                writeOutput("MutableListSequence created.");
            } else if (type == "IMMUTABLE_LIST") {
                seq1 = new ImmutableListSequence<int>();
                writeOutput("ImmutableListSequence created.");
            } else {
                writeOutput("Error: Invalid sequence type.");
                continue;
            }
        }
        else if (command == "NEW2") {
            std::string type;
            inputFile >> type;
            if (seq2) {
                delete seq2;
                seq2 = nullptr;
            }
            if (type == "MUTABLE_ARRAY") {
                seq2 = new MutableArraySequence<int>();
                writeOutput("MutableArraySequence 2 created.");
            } else if (type == "IMMUTABLE_ARRAY") {
                seq2 = new ImmutableArraySequence<int>();
                writeOutput("ImmutableArraySequence 2 created.");
            } else if (type == "MUTABLE_LIST") {
                seq2 = new MutableListSequence<int>();
                writeOutput("MutableListSequence 2 created.");
            } else if (type == "IMMUTABLE_LIST") {
                seq2 = new ImmutableListSequence<int>();
                writeOutput("ImmutableListSequence 2 created.");
            } else {
                writeOutput("Error: Invalid sequence type.");
                continue;
            }
        }
        else if (command == "APPEND") {
            std::string type;
            int value;
            inputFile >> type >> value;
            Sequence<int>* seq = (type == "SEQ1" && seq1) ? seq1 : (type == "SEQ2" && seq2) ? seq2 : nullptr;
            if (!seq) {
                writeOutput("Error: Sequence not created.");
                continue;
            }
            try {
                if (dynamic_cast<ImmutableArraySequence<int>*>(seq) || dynamic_cast<ImmutableListSequence<int>*>(seq)) {
                    Sequence<int>* newSeq = seq->Append(value);
                    if (type == "SEQ1") {
                        delete seq1;
                        seq1 = newSeq;
                    } else {
                        delete seq2;
                        seq2 = newSeq;
                    }
                } else {
                    seq->Append(value);
                }
                writeOutput("Element " + std::to_string(value) + " appended.");
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "PREPEND") {
            std::string type;
            int value;
            inputFile >> type >> value;
            Sequence<int>* seq = (type == "SEQ1" && seq1) ? seq1 : (type == "SEQ2" && seq2) ? seq2 : nullptr;
            if (!seq) {
                writeOutput("Error: Sequence not created.");
                continue;
            }
            try {
                if (dynamic_cast<ImmutableArraySequence<int>*>(seq) || dynamic_cast<ImmutableListSequence<int>*>(seq)) {
                    Sequence<int>* newSeq = seq->Prepend(value);
                    if (type == "SEQ1") {
                        delete seq1;
                        seq1 = newSeq;
                    } else {
                        delete seq2;
                        seq2 = newSeq;
                    }
                } else {
                    seq->Prepend(value);
                }
                writeOutput("Element " + std::to_string(value) + " prepended.");
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "INSERT") {
            std::string type;
            int value, index;
            inputFile >> type >> value >> index;
            Sequence<int>* seq = (type == "SEQ1" && seq1) ? seq1 : (type == "SEQ2" && seq2) ? seq2 : nullptr;
            if (!seq) {
                writeOutput("Error: Sequence not created.");
                continue;
            }
            try {
                if (dynamic_cast<ImmutableArraySequence<int>*>(seq) || dynamic_cast<ImmutableListSequence<int>*>(seq)) {
                    Sequence<int>* newSeq = seq->InsertAt(value, index);
                    if (type == "SEQ1") {
                        delete seq1;
                        seq1 = newSeq;
                    } else {
                        delete seq2;
                        seq2 = newSeq;
                    }
                } else {
                    seq->InsertAt(value, index);
                }
                writeOutput("Element " + std::to_string(value) + " inserted at index " + std::to_string(index) + ".");
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "CONCAT") {
            std::string type1, type2;
            inputFile >> type1 >> type2;
            if (!seq1 || !seq2) {
                writeOutput("Error: One or both sequences not created.");
                continue;
            }
            try {
                if (dynamic_cast<ImmutableArraySequence<int>*>(seq1) || dynamic_cast<ImmutableListSequence<int>*>(seq1)) {
                    Sequence<int>* newSeq = seq1->Concat(seq2);
                    delete seq1;
                    seq1 = newSeq;
                } else {
                    seq1->Concat(seq2);
                }
                writeOutput("Sequences concatenated. Length: " + std::to_string(seq1->GetLength()));
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "SUBSEQ") {
            std::string type;
            int start, end;
            inputFile >> type >> start >> end;
            Sequence<int>* seq = (type == "SEQ1" && seq1) ? seq1 : (type == "SEQ2" && seq2) ? seq2 : nullptr;
            if (!seq) {
                writeOutput("Error: Sequence not created.");
                continue;
            }
            try {
                Sequence<int>* subseq = seq->GetSubsequence(start, end);
                std::string result = "Subsequence: ";
                for (int i = 0; i < subseq->GetLength(); i++) {
                    result += std::to_string(subseq->Get(i)) + " ";
                }
                writeOutput(result);
                delete subseq;
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "GET") {
            std::string type;
            int index;
            inputFile >> type >> index;
            Sequence<int>* seq = (type == "SEQ1" && seq1) ? seq1 : (type == "SEQ2" && seq2) ? seq2 : nullptr;
            if (!seq) {
                writeOutput("Error: Sequence not created.");
                continue;
            }
            try {
                int value = seq->Get(index);
                writeOutput("Element at index " + std::to_string(index) + ": " + std::to_string(value));
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "GETFIRST") {
            std::string type;
            inputFile >> type;
            Sequence<int>* seq = (type == "SEQ1" && seq1) ? seq1 : (type == "SEQ2" && seq2) ? seq2 : nullptr;
            if (!seq) {
                writeOutput("Error: Sequence not created.");
                continue;
            }
            try {
                int value = seq->GetFirst();
                writeOutput("First element: " + std::to_string(value));
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "GETLAST") {
            std::string type;
            inputFile >> type;
            Sequence<int>* seq = (type == "SEQ1" && seq1) ? seq1 : (type == "SEQ2" && seq2) ? seq2 : nullptr;
            if (!seq) {
                writeOutput("Error: Sequence not created.");
                continue;
            }
            try {
                int value = seq->GetLast();
                writeOutput("Last element: " + std::to_string(value));
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "GETLENGTH") {
            std::string type;
            inputFile >> type;
            Sequence<int>* seq = (type == "SEQ1" && seq1) ? seq1 : (type == "SEQ2" && seq2) ? seq2 : nullptr;
            if (!seq) {
                writeOutput("Error: Sequence not created.");
                continue;
            }
            try {
                int length = seq->GetLength();
                writeOutput("Length: " + std::to_string(length));
            } catch (const std::exception& e) {
                writeOutput("Error: " + std::string(e.what()));
            }
        }
        else if (command == "DELETE") {
            if (seq1) {
                delete seq1;
                seq1 = nullptr;
                writeOutput("Sequence 1 deleted.");
            }
            if (seq2) {
                delete seq2;
                seq2 = nullptr;
                writeOutput("Sequence 2 deleted.");
            }
        }
        else {
            writeOutput("Error: Unknown command.");
        }
    }

    if (seq1) {
        delete seq1;
    }
    if (seq2) {
        delete seq2;
    }
    inputFile.close();
    return 0;
}