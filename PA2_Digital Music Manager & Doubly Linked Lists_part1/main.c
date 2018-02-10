 //
//  main.c
//  PA2_Digital Music Manager & Doubly Linked Lists_part1
//
//  Created by Chingan on 30/01/2018.
//  Copyright © 2018 Chingan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, const char * argv[]) {
    Node *pList = NULL;
    int isLoadFile = 0;
    int input = 0;
    int success;
    char *menu = "\nPlease input option:\n( 1) load\n( 2) store\n( 3) display\n( 4) insert\n( 5) delete\n( 6) edit\n( 7) sort\n( 8) rate\n( 9) play\n(10) shuffle\n(11) exit\n";
    // Start operation flow
    do {
        printf("%s > ", menu);
        scanf("%d", &input);
        
        if (isLoadFile == 0 && input != 1) {
            printf("\nPlease load file at first!\n");
        } else {
            switch (input) {
                case 1:
                    pList = loadFile(pList);
                    isLoadFile = 1;
                    break;
                    
                case 2:
                    success = storeFile(pList);
                    if (success == 0) {
                        printf("File store failure!");
                    } else {
                        printf("File store success!");
                    }
                    break;
                    
                case 3:
                    displayList(pList);
                    break;
                    
                case 4:
                    pList = insertNewRecord(pList);
                    break;
                case 5:
                    pList = deleteRecordBySong(pList);
                    break;
                    
                case 6:
                    editList(pList);
                    break;
                    
                case 7:
                    pList = sortList(pList);
                    break;
                    
                case 8:
                    
                    break;
                case 9:
                    playList(pList);
                    break;
                    
                case 10:
                    shuffle(pList);
                    break;
                case 11:
                    printf("\nBye!\n");
                    break;
                    
                default:
                    printf("\nInput error!\n");
                    break;
            }
        }
    } while (input != 11);

    
//    printTitle();
//    printList(pList);
//    printf("-----------------------------------------------------------------------------------\n");
//    printTitleWithNumber();
//    int size = 0;
//    Node **pT = searchByArtist(pList, "Swift, Taylor", &size);
//    for (int i = 0; i < size - 1; i++){
//        printf("%6d\t", i + 1);
//        printRecord(pT[i]->data);
//    }
//    pT[0] = editArtist(pT[0], "testEdit");

//    printListWithNumber(pT);
//    storeFile(pList);
    
    


//    printList(pList);

    return 0;
}
