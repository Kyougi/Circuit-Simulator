#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct chararray{
    char listOfReadyGates[20];
} Strings;

typedef struct node{
    char inouttype[20];
    int assocNumber;
    struct node* next;
} InOutVars;

typedef struct gate{
    char whatInputItNeeds[20];
    struct gate* next;
} Gates;

typedef struct ListOfGates{
    InOutVars * input;
    InOutVars * output;
    InOutVars * tempInputs;
    Gates * conveyerOutput;
    Gates * and;
    Gates * or;
    Gates * xor;
    Gates * not;
    Gates * decoder;
    Gates * multiplexer;
    Gates * selector;
    int numOfInputs;
    int numOfOutputs; 
} OpenTheGate;

void initializingInOut(InOutVars ** initializing, char * position){
    InOutVars * temp = malloc(sizeof(InOutVars));
        strcpy(temp->inouttype, position);
    temp->next = NULL;
    InOutVars * ptr = *initializing;
    if(ptr == NULL){
        *initializing = temp;
        return;
    }
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = temp;
    return;
}


void initializingGates(Gates ** initializing, char * giveMeInputs){
    Gates * temp = (Gates*)malloc(sizeof(Gates));
        strcpy(temp->whatInputItNeeds, giveMeInputs);
    temp->next = NULL;
    Gates * ptr = *initializing;
    if(ptr == NULL){
        *initializing = temp;
        return;
    }
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = temp;
    return;
}

int andCal(int andOne, int andTwo){
    int andResult = (andOne & andTwo);
    return andResult;
}

int orCal(int orOne, int orTwo){
    int orResult = (orOne | orTwo);
    return orResult;
}

int xorCal(int xorOne, int xorTwo){
    int xorResult = (xorOne ^ xorTwo);
    return xorResult;
}

int notCal(int notOne){
    int notResult = !(notOne);
    return notResult;
}

void submittingOutputs(InOutVars ** output, char * subject, int results){
    InOutVars * ptr = *output;
    if(ptr == NULL){
        printf("You didn't label your outputs, yet.\n");
        return;
    }
    while(ptr != NULL){
        if(strcmp(ptr->inouttype, subject) == 0){
            ptr->assocNumber = results;
        }
        ptr = ptr->next;
    }
    return;
}

int searchInt(char * needInput, InOutVars ** inTemps){
    InOutVars * ptr = *inTemps;
    int results = 0;
    while(ptr != NULL){
        if(strcmp(ptr->inouttype, needInput) == 0){
            results = ptr->assocNumber;
            break;
        }
        ptr = ptr->next;
    }
    return results;
}

void fillingIntegerNumbers(int * submit, int currentIndex, int num){
    submit[currentIndex] = num;
    return;
}

void submittingIns(InOutVars ** inputList, int size, int mainNumber){
    int bitNumbers[size];
    for(int i = 0; i < size; i++){
        if(mainNumber == 0 && i < size){
            bitNumbers[i] = 0;
            continue;
        }
        bitNumbers[i] = (mainNumber % 2);
        mainNumber = mainNumber / 2;
    }
    InOutVars * ptr = *inputList;
    for(int i = size - 1; i >= 0; i--){
        ptr->assocNumber = bitNumbers[i];
        ptr = ptr->next;
    }
    return;
}

void printOutput(InOutVars ** output){
    InOutVars * ptr = *output;
    while(ptr != NULL){
        printf("%d ", ptr->assocNumber);
        ptr = ptr->next;
    }
    printf("\n");
    return;
}

void freeNodes(InOutVars * nodes){
    if(nodes != NULL){
        freeNodes(nodes->next);
        free(nodes);
    }
    return;
}

void freeGates(Gates * nodes){
    if(nodes != NULL){
        freeGates(nodes->next);
        free(nodes);
    }
}

int inverseCode(int num){
    int inverse = 0;
    while(num > 0){
        inverse = inverse ^ num;
        num = num >> 1;
    }
    return inverse;
}



int main(int argc, char * argv[argc + 1]){
    FILE * circuitFile = fopen(argv[1], "r");
    if(circuitFile == NULL){
        printf("There's nothing to extract from here.\n");
        return 0;
    }
    int booleanCounter = 0;
    fscanf(circuitFile, "%d", &booleanCounter);
    int beltSize = booleanCounter - 2;
    Strings gateList[beltSize];
    int decNum[100];
    int multi[100];
    int sel[100];
    int decOut[100];
    
    int decNumCount = 0; 
    int decNumOut = 0; 
    int multiCount = 0; 
    int selectCount = 0;
    OpenTheGate section;
    section.input = NULL;
    section.output = NULL;
    section.tempInputs = NULL;
    section.and = NULL;
    section.or = NULL;
    section.not = NULL;
    section.xor = NULL;
    section.decoder = NULL;
    section.multiplexer = NULL;
    section.selector = NULL;
    section.conveyerOutput = NULL;
    char type[20];
    int index = 0;
    for(int i = 0; i < booleanCounter; i++){
        fscanf(circuitFile, "%s ", type);
        if(strcmp(type, "INPUTVAR") == 0){
            int numOfIns = 0;
            fscanf(circuitFile, "%d ", &numOfIns);
            char inPos[20];
            for(int i = 0; i < numOfIns; i++){
                if(i == numOfIns - 1){
                    fscanf(circuitFile, "%s", inPos);
                    initializingInOut(&section.input, inPos);
                    break;
                }
                fscanf(circuitFile, "%s ", inPos);
                initializingInOut(&section.input, inPos);
            }
            section.numOfInputs = numOfIns;
            continue;
        }
        if(strcmp(type, "OUTPUTVAR") == 0){
            int numOfOuts = 0;
            fscanf(circuitFile, "%d ", &numOfOuts);
            char outPos[20];
            for(int i = 0; i < numOfOuts; i++){
                if(i == numOfOuts - 1){
                    fscanf(circuitFile, "%s", outPos);
                    initializingInOut(&section.output, outPos);
                    break;
                }
                fscanf(circuitFile, "%s ", outPos);
                initializingInOut(&section.output, outPos);
            }
            section.numOfOutputs = numOfOuts;
            continue; 
        }
        if(strcmp(type, "AND") == 0){
            strcpy(gateList[index].listOfReadyGates, type);
            index++;
            char theInputs[20];
            for(int i = 0; i < 2; i++){
                fscanf(circuitFile, "%s ", theInputs);
                initializingGates(&section.and, theInputs);
            }
            fscanf(circuitFile, "%s", theInputs);
            initializingGates(&section.conveyerOutput, theInputs);
            continue;
        }
        if(strcmp(type, "OR") == 0){
            strcpy(gateList[index].listOfReadyGates, type);
            index++;
            char theInputs[20];
            for(int i = 0; i < 2; i++){
                fscanf(circuitFile, "%s ", theInputs);
                initializingGates(&section.or, theInputs);
            }
            fscanf(circuitFile, "%s", theInputs);
            initializingGates(&section.conveyerOutput, theInputs);
            continue;
        }
        if(strcmp(type, "NOT") == 0){
            strcpy(gateList[index].listOfReadyGates, type);
            index++;
            char theInputs[20];
            fscanf(circuitFile, "%s ", theInputs);
            initializingGates(&section.not, theInputs);
            fscanf(circuitFile, "%s", theInputs);
            initializingGates(&section.conveyerOutput, theInputs);
            continue;
        }
        if(strcmp(type, "XOR") == 0){
            strcpy(gateList[index].listOfReadyGates, type);
            index++;
            char theInputs[20];
            for(int i = 0; i < 2; i++){
                fscanf(circuitFile, "%s ", theInputs);
                initializingGates(&section.xor, theInputs);
            }
            fscanf(circuitFile, "%s", theInputs);
            initializingGates(&section.conveyerOutput, theInputs);
            continue;
        }
        if(strcmp(type, "DECODER") == 0){
            strcpy(gateList[index].listOfReadyGates, type);
            index++;
            int decInputs = 0;
            fscanf(circuitFile, "%d ", &decInputs);
            decNum[decNumCount] = decInputs;
            decNumCount = decNumCount + 1;
            char theInputs[20];
            for(int i = 0; i < decInputs; i++){
                fscanf(circuitFile, "%s ",theInputs);
                initializingGates(&section.decoder, theInputs);
            }
            int outputNum = pow(2, decInputs);
            decOut[decNumOut] = outputNum;
            decNumOut = decNumOut + 1;
            for(int i = 0; i < outputNum; i++){
                if(i == (outputNum - 1)){
                    fscanf(circuitFile, "%s", theInputs);
                    initializingGates(&section.conveyerOutput, theInputs);
                    break;
                }
                fscanf(circuitFile, "%s ", theInputs);
                initializingGates(&section.conveyerOutput, theInputs);
            }
            continue;
        }
        if(strcmp(type, "MULTIPLEXER") == 0){
            strcpy(gateList[index].listOfReadyGates, type);
            index++;
            int theInputs = 0;
            fscanf(circuitFile, "%d ", &theInputs);
            multi[multiCount] = theInputs;
            multiCount = multiCount + 1;
            char dude[20];
            for(int i = 0; i < theInputs; i++){
                fscanf(circuitFile, "%s ", dude);
                initializingGates(&section.multiplexer, dude);
            }
            int selects = log2(theInputs);
            sel[selectCount] = selects;
            selectCount = selectCount + 1;
            for(int i = 0; i < selects; i++){
                fscanf(circuitFile, "%s ", dude);
                initializingGates(&section.selector, dude);
            }
            fscanf(circuitFile, "%s", dude);
            initializingGates(&section.conveyerOutput, dude);
        }
    }
    Gates * temper = section.conveyerOutput;
    while(temper != NULL){
        char something = temper->whatInputItNeeds[0];
        if(something == 't'){
            initializingInOut(&section.tempInputs, temper->whatInputItNeeds);
        }
        temper = temper->next;
    }
    int mainNumber = 0;
    while(fscanf(circuitFile, "%d", &mainNumber) != EOF){
        submittingIns(&section.input, section.numOfInputs, mainNumber);
        int decIn = 0, decOu = 0, multCount = 0, selCount = 0;
        Gates * conPtr = section.conveyerOutput;
        Gates * andPtr = section.and;
        Gates * orPtr = section.or;
        Gates * xorPtr = section.xor;
        Gates * notPtr = section.not;
        Gates * decPtr = section.decoder;
        Gates * mulPtr = section.multiplexer;
        Gates * selPtr = section.selector;
        for(int i = 0; i < beltSize; i++){
            if(strcmp(gateList[i].listOfReadyGates, "AND") == 0){
                int andNumbers[2];
                int results = 0;
                for(int i = 0; i < 2; i++){
                    char inning = andPtr->whatInputItNeeds[0];
                    if(inning == 'I'){
                        andNumbers[i] = searchInt(andPtr->whatInputItNeeds, &section.input);
                    } else if(inning == 't'){
                        andNumbers[i] = searchInt(andPtr->whatInputItNeeds, &section.tempInputs);
                    } else {
                        sscanf(andPtr->whatInputItNeeds, "%d", &andNumbers[i]);
                    }
                    andPtr = andPtr->next;
                }
                results = andCal(andNumbers[0], andNumbers[1]);
                char outting = conPtr->whatInputItNeeds[0];
                if(outting == 'O'){
                    submittingOutputs(&section.output, conPtr->whatInputItNeeds, results);
                } else if(outting == 't'){
                    submittingOutputs(&section.tempInputs, conPtr->whatInputItNeeds, results);
                }
                conPtr = conPtr->next; 
                continue;
            } else if(strcmp(gateList[i].listOfReadyGates, "OR") == 0){
                int orNumbers[2];
                int results = 0;
                for(int i = 0; i < 2; i++){
                    char inning = orPtr->whatInputItNeeds[0];
                    if(inning == 'I'){
                        orNumbers[i] = searchInt(orPtr->whatInputItNeeds, &section.input);
                    } else if(inning == 't'){
                        orNumbers[i] = searchInt(orPtr->whatInputItNeeds, &section.tempInputs);
                    } else {
                        sscanf(andPtr->whatInputItNeeds, "%d", &orNumbers[i]);
                    }
                    orPtr = orPtr->next;
                }
                results = orCal(orNumbers[0], orNumbers[1]);
                char outting = conPtr->whatInputItNeeds[0];
                if(outting == 'O'){
                    submittingOutputs(&section.output, conPtr->whatInputItNeeds, results);
                } else if(outting == 't'){
                    submittingOutputs(&section.tempInputs, conPtr->whatInputItNeeds, results);
                }
                conPtr = conPtr ->next; 
                continue;
            } else if(strcmp(gateList[i].listOfReadyGates, "XOR") == 0){
                int xorNumbers[2];
                int results = 0;
                for(int i = 0; i < 2; i++){
                    char inning = xorPtr->whatInputItNeeds[0];
                    if(inning == 'I'){
                        xorNumbers[i] = searchInt(xorPtr->whatInputItNeeds, &section.input);
                    } else if(inning == 't'){
                        xorNumbers[i] = searchInt(xorPtr->whatInputItNeeds, &section.tempInputs);
                    } else {
                        sscanf(xorPtr->whatInputItNeeds, "%d", &xorNumbers[i]);
                    }
                    xorPtr = xorPtr->next;
                }
                results = xorCal(xorNumbers[0], xorNumbers[1]);
                char outting = conPtr->whatInputItNeeds[0];
                if(outting == 'O'){
                    submittingOutputs(&section.output, conPtr->whatInputItNeeds, results);
                } else if(outting == 't'){
                    submittingOutputs(&section.tempInputs, conPtr->whatInputItNeeds, results);
                }
                conPtr = conPtr ->next; 
                continue;
            } else if(strcmp(gateList[i].listOfReadyGates, "NOT") == 0){
                int theNumber = 0;
                char inning = notPtr->whatInputItNeeds[0];
                if(inning == 'I'){
                        theNumber = searchInt(notPtr->whatInputItNeeds, &section.input);
                } else if(inning == 't'){
                        theNumber = searchInt(notPtr->whatInputItNeeds, &section.tempInputs);
                } else {
                    sscanf(notPtr->whatInputItNeeds, "%d", &theNumber);
                }
                int theResult = 0; 
                theResult = notCal(theNumber);
                char outting = conPtr->whatInputItNeeds[0];
                if(outting == 'O'){
                    submittingOutputs(&section.output, conPtr->whatInputItNeeds, theResult);
                } else if(outting == 't'){
                    submittingOutputs(&section.tempInputs, conPtr->whatInputItNeeds, theResult);
                }
                conPtr = conPtr ->next; 
                continue;
            } else if(strcmp(gateList[i].listOfReadyGates, "DECODER") == 0){
                int inputting[decNum[decIn]];
                int size = decNum[decIn];
                for(int i = 0; i < size; i++){
                    char something = decPtr->whatInputItNeeds[0];
                    if(something == 'I'){
                        inputting[i] = searchInt(decPtr->whatInputItNeeds, &section.input);
                    }else if(something == 't'){
                        inputting[i] = searchInt(decPtr->whatInputItNeeds, & section.tempInputs);
                    } else {
                        sscanf(decPtr->whatInputItNeeds, "%d", &inputting[i]);
                    }
                    decPtr = decPtr->next;
                }
                int reference = 0, square = 1;
                for(int i = size - 1; i >= 0; i--){
                    int multiply = inputting[i];
                    int product = multiply * square;
                    reference = reference + product;
                    square = square * 2;
                }
                int outputSize = decOut[decOu];
                decIn = decIn + 1;
                decOu = decOu + 1;
                for(int i = 0; i < outputSize; i++){
                    int equal = i ^(i >> 1);
                    int results = 0;
                    char outting = conPtr->whatInputItNeeds[0];
                    if(reference==equal){
                        results = 1;
                    }
                    if(outting == 'O'){
                        submittingOutputs(&section.output, conPtr->whatInputItNeeds, results);
                    } else if(outting == 't') {
                        submittingOutputs(&section.tempInputs, conPtr->whatInputItNeeds, results);
                    }
                    conPtr = conPtr->next;
                }
                continue;
            } else if(strcmp(gateList[i].listOfReadyGates, "MULTIPLEXER") == 0){
                int inputting[multi[multCount]];
                int size = multi[multCount];
                for(int i = 0; i < size; i++){
                    char something = mulPtr->whatInputItNeeds[0];
                    if(something == 'I'){
                        inputting[i] = searchInt(mulPtr->whatInputItNeeds, &section.input);
                    } else if(something == 't'){
                        inputting[i] = searchInt(mulPtr->whatInputItNeeds, & section.tempInputs);
                    } else {
                        sscanf(mulPtr->whatInputItNeeds, "%d", &inputting[i]);
                    }
                    mulPtr = mulPtr->next; 
                }
                int select[sel[selCount]];
                int selSize = sel[selCount];
                for(int i = 0; i < selSize; i++){
                    char stupid = selPtr->whatInputItNeeds[0];
                    if(stupid == 'I'){
                        select[i] = searchInt(selPtr->whatInputItNeeds, &section.input);
                    } else if(stupid == 't'){
                        select[i] = searchInt(selPtr->whatInputItNeeds, & section.tempInputs);
                    } else {
                        sscanf(selPtr->whatInputItNeeds, "%d", &select[i]);
                    }
                    selPtr = selPtr->next;
                }
                
                int selectingSize = log2(size);
                int square = 1, selGray = 0;
                for(int i = selectingSize - 1; i >= 0; i--){
                    int multiply = select[i];
                    int product = multiply * square;
                    selGray = selGray + product;
                    square = square * 2;
                }
                int newIndex = selGray ^ (selGray >> 1);
                int results = inputting[newIndex];
                selCount = selCount + 1;
                multCount = multCount + 1;
                
                char outting = conPtr->whatInputItNeeds[0];
                if(outting == 'O'){
                    submittingOutputs(&section.output, conPtr->whatInputItNeeds, results);
                } else if(outting == 't'){
                    submittingOutputs(&section.tempInputs, conPtr->whatInputItNeeds, results);
                }
                conPtr = conPtr->next;
                continue;
            }
        }
        
        printOutput(&section.output);
    }
    fclose(circuitFile);
    freeNodes(section.input);
    freeNodes(section.output);
    freeNodes(section.tempInputs);
    freeGates(section.and);
    freeGates(section.or);
    freeGates(section.xor);
    freeGates(section.not);
    freeGates(section.decoder);
    freeGates(section.multiplexer);
    freeGates(section.selector);
    freeGates(section.conveyerOutput);
    return EXIT_SUCCESS;
}