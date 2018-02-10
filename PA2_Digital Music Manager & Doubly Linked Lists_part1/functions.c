//
//  functions.c
//  PA2_Digital Music Manager & Doubly Linked Lists_part1
//
//  Created by Chingan on 01/02/2018.
//  Copyright © 2018 Chingan. All rights reserved.
//

#include "functions.h"

// make new record
Record *makeRecord(char *strs[7]){
    Record *pMem = NULL;
    pMem = (Record *) malloc(sizeof(Record));
    if (pMem != NULL){
        strcpy(pMem ->artist, strs[0]);
        strcpy(pMem ->albumTitle, strs[1]);
        strcpy(pMem ->songTitle, strs[2]);
        strcpy(pMem ->genre, strs[3]);
        int minute = atoi(strtok(strs[4], ":"));
        int second = atoi(strtok(NULL, "\0"));
        Duration d = {minute, second};
        pMem ->length = d;
        pMem ->numberTimesPlayed = atoi(strs[5]);
        pMem ->rating = atoi(strs[6]);
    }
    
    return pMem;
}

// place the value inside the container
Node *makeNode(Record newRecord){
    Node *pMem = NULL;
    
    pMem = (Node *) malloc(sizeof (Node));
    
    if (pMem != NULL) { // space was allocated
        pMem -> pPrev = NULL; // for doubly linked list
        pMem -> pNext = NULL;
        pMem -> data = newRecord; // we want to make a copy!
    }
    return pMem;
}

// list operation
int insertFront(Node **pList, Record newRecord){
    Node *pMem = NULL;
    int success = 0;
    
    pMem = makeNode(newRecord);
    
    if (pMem != NULL) { // we allocated space for a Node and initialized it
        // connect the new Node/container to the list
        if (*pList != NULL) { // not empty list
            pMem -> pNext = *pList;
            (*pList) -> pPrev = pMem; // doubly linked list
            *pList = pMem;
            success = 1;
        } else { // empty list
            *pList = pMem;
            success = 1;
        }
    }
    return success;
}

// a - z based on name
int insertInOrder(Node **pList, Record newRecord) {
    Node *pMem = NULL;
    int success = 0;
    
    pMem = makeNode(newRecord);
    
    if (*pList != NULL) {
        
        success = 1;
    } else {
        *pList = pMem;
        success = 1;
    }
    
    return success;
}

void printTitle(void) {
    printf("%20s\t%20s\t%20s\t%10s\t%s\t%s\t%s\n","Artist","AlbumTitle","SongTitle","Genre","Duration length","NumberTimesPlayed","Rating");
}

void printTitleWithNumber(void) {
    printf("%s%20s\t%20s\t%20s\t%10s\t%s\t%s\t%s\n","Number","Artist","AlbumTitle","SongTitle","Genre","Duration length","NumberTimesPlayed","Rating");
}

// Print record.
void printRecord(Record r) {
    printf("%20s\t%20s\t%20s\t%10s\t \t%3d:%3d\t \t%10d\t %4d\n", r.artist, r.albumTitle, r.songTitle, r.genre, r.length.minute, r.length.second, r.numberTimesPlayed, r.rating);
}

void printList(Node *pList) {
    if (pList != NULL) {
        Record d = pList -> data;
        printf("%20s\t%20s\t%20s\t%10s\t \t%3d:%3d\t \t%10d\t %4d\n", d.artist, d.albumTitle, d.songTitle, d.genre, d.length.minute, d.length.second, d.numberTimesPlayed, d.rating);
        printList(pList -> pNext);
    }
}

// Print certain artist recursively
void printListByArtist(Node *pList, char *targetArtist) {
    if (pList != NULL){
        Record r = pList ->data;
        if (strcmp(r.artist, targetArtist) == 0){
            printf("%20s\t%20s\t%20s\t%10s\t \t%3d:%3d\t \t%10d\t%4d\n", r.artist, r.albumTitle, r.songTitle, r.genre, r.length.minute, r.length.second, r.numberTimesPlayed, r.rating);
        }
        printListByArtist(pList ->pNext, targetArtist);
    }
}

// Print list with number.
void printListWithNumber(Node *pList) {
    int num = 1;
    while (pList != NULL) {
        Record r = pList ->data;
        printf("%6d\t%20s\t%20s\t%20s\t%10s\t \t%3d:%3d\t \t%10d\t%4d\n", num++, r.artist, r.albumTitle, r.songTitle, r.genre, r.length.minute, r.length.second, r.numberTimesPlayed, r.rating);
        pList = pList ->pNext;
    }
}

// Search nodes by certain artist.
Node **searchByArtist(Node *pList, char *targetArtist, int *size) {
    int index = 0;
    Node **arrayTmp = malloc(50 * sizeof(Node *));
    while (pList != NULL){
        if (strcmp(pList ->data.artist, targetArtist) == 0) {
            arrayTmp[index++] = pList;
        }
        pList = pList ->pNext;
    }
    *size = index + 1;
    Node **array = malloc( *size * sizeof(Node *));
    for (int i = 0; i < index + 1; i++) {
        array[i] = arrayTmp[i];
    }
    free(arrayTmp);
    return array;
}

Node *loadFile(Node *pList) {
//    int success = 0;
    FILE *pFile;
    char *buffer = malloc(255 * sizeof(char));
    char *array[7];
    
    pFile = fopen("/Users/chingan/Documents/Cpts122/PA2,3/musicPlayList.csv", "r");
    while(fgets(buffer, 255, (FILE*) pFile) != NULL) {
        int i = 0;
        char *p;
        //Decide if there is "" in string
        if (strstr(buffer, "\"") != NULL) {
            p = strtok(buffer, "\"");
            while (p != NULL)
            {
                array[i++] = p;
                p = strtok (NULL, ",");
            }
        } else {
            p = strtok(buffer, ",");
            while (p != NULL) {
                array[i++] = p;
                p = strtok (NULL, ",");
            }
        }
        Record r = *makeRecord(array);
        insertFront(&pList, r);
    }
    fclose(pFile);
    printf("\nFile loaded!\n");
    return pList;
//    return success;
}

int storeFile(Node *pList) {
    int success = 0;
    if (pList != NULL) {
        FILE *pFile;
        pFile = fopen("/Users/chingan/Documents/Cpts122/PA2,3/testStore.csv", "w+");
        writeList(pList, pFile);
        fclose(pFile);
        success = 1;
    }

    return success;
}

void writeList(Node *pList, FILE *pFile) {
    if (pList != NULL) {
        Record d = pList -> data;
        if (strstr(d.artist, ",") != NULL) {
            fprintf(pFile, "\"%s\", %s, %s, %s, %d:%d, %d, %d\n", d.artist, d.albumTitle, d.songTitle, d.genre, d.length.minute, d.length.second, d.numberTimesPlayed, d.rating);
        } else {
            fprintf(pFile, "%s, %s, %s, %s, %d:%d, %d, %d\n", d.artist, d.albumTitle, d.songTitle, d.genre, d.length.minute, d.length.second, d.numberTimesPlayed, d.rating);
        }
        
        writeList(pList -> pNext, pFile);
    }
}

// Display list
void displayList(Node *pList) {
    int input = 0;
    char *inputStr = malloc(50 * sizeof(char));
    do {
        printf("\n1.Print all records.\n2.Print all records that match an artist.\n3.Previous step.\n >");
        scanf("%d", &input);
        switch (input) {
            case 1:
                printTitle();
                printList(pList);
                input = 3;
                break;
                
            case 2:
                printf("\nPlease input artist: >");
                scanf("%s", inputStr);
                printf("\n");
                printTitle();
                printListByArtist(pList, inputStr);
                input = 3;
                free(inputStr);
                break;
                
            case 3:
                break;
                
            default:
                printf("\nInput error!\n");
                break;
        }
    } while (input != 3);
    
    free(inputStr);
}

// Edit list.
void editList(Node *pList) {
    int maxStrSize = 50 * sizeof(char), size = 0, editIndex = 0, choose = 0, doWhileOrNot = 1;
    char *inputStr = malloc(maxStrSize);

    printf("\nPlease input artist: >");
    scanf("%s", inputStr);
    
    Node **pT = searchByArtist(pList, inputStr, &size);
    
    if (pT == NULL){
        printf("Input artist nor exist!\n");
        return;
    }
    
    // If there are more than one record, prompt user to choose the record that want to edit.
    if (size > 2) {
        printTitleWithNumber();
        for (int i = 0; i < size - 1; i++) {
            printf("%6d", i + 1);
            printRecord(pT[i]->data);
        }
        printf("\nPlease input number of record that want to edit: >");
        scanf("%d", &editIndex);
        if (editIndex > size - 1)
            return;
        editIndex -= 1;
    }
    
    do {
        printf("\nPlease choose the item you want to edit:\n (1) artist\n (2) album title\n (3) song title\n (4) genre\n (5) song length\n (6) number times played\n (7) rating\n > ");
        scanf("%d", &choose);
        if (choose > 0 && choose < 8) {
            doWhileOrNot = 0;
        } else {
            printf("\nInput error!!\n");
            doWhileOrNot = 1;
        }
    } while(doWhileOrNot != 0);

    switch (choose) {
        case 1:
            printf("\nPlease input new artist: > ");
            strcpy(inputStr, "");
            while (strcmp(inputStr, "") == 0 || strcmp(inputStr, "\n") == 0) {
                fgets(inputStr, maxStrSize, stdin);
            }
            /* Remove trailing newline, if there. */
            if ((strlen(inputStr) > 0) && (inputStr[strlen (inputStr) - 1] == '\n'))
                inputStr[strlen (inputStr) - 1] = '\0';

            pT[editIndex] = editArtist(pT[editIndex], inputStr);
            break;
            
        case 2:
            printf("\nPlease input new album title: > ");
            strcpy(inputStr, "");
            while (strcmp(inputStr, "") == 0 || strcmp(inputStr, "\n") == 0) {
                fgets(inputStr, maxStrSize, stdin);
            }
            /* Remove trailing newline, if there. */
            if ((strlen(inputStr) > 0) && (inputStr[strlen (inputStr) - 1] == '\n'))
                inputStr[strlen (inputStr) - 1] = '\0';
            pT[editIndex] = editAlbumTitle(pT[editIndex], inputStr);
            break;
            
        case 3:
            printf("\nPlease input new song title: > ");
            strcpy(inputStr, "");
            while (strcmp(inputStr, "") == 0 || strcmp(inputStr, "\n") == 0) {
                fgets(inputStr, maxStrSize, stdin);
            }
            /* Remove trailing newline, if there. */
            if ((strlen(inputStr) > 0) && (inputStr[strlen (inputStr) - 1] == '\n'))
                inputStr[strlen (inputStr) - 1] = '\0';
            pT[editIndex] = editSongTitle(pT[editIndex], inputStr);
            break;
            
        case 4:
            printf("\nPlease input new genre: > ");
            strcpy(inputStr, "");
            while (strcmp(inputStr, "") == 0 || strcmp(inputStr, "\n") == 0) {
                fgets(inputStr, maxStrSize, stdin);
            }
            /* Remove trailing newline, if there. */
            if ((strlen(inputStr) > 0) && (inputStr[strlen (inputStr) - 1] == '\n'))
                inputStr[strlen (inputStr) - 1] = '\0';
            pT[editIndex] = editAlbumTitle(pT[editIndex], inputStr);
            break;
            
        case 5: {
            int minute, second;
            printf("\nPlease input minute: > ");
            scanf("%d", &minute);
            printf("\nPlease input second: > ");
            scanf("%d", &second);
            pT[editIndex] = editDuration(pT[editIndex], minute, second);
            break;
        }
        case 6: {
            int number;
            printf("\nPlease input new number times played: >");
            scanf("%d", &number);
            pT[editIndex] = editNumberTimesPlayed(pT[editIndex], number);
            break;
        }

        default: {
            int number;
            printf("\nPlease input new rating: >");
            scanf("%d", &number);
            pT[editIndex] = editRating(pT[editIndex], number);
            break;
        }
    }
    
    free(inputStr);

}

// Edit artist.
Node *editArtist(Node *pNode, char *newArtist) {
//    Record r = pNode ->data;
    strcpy(pNode ->data.artist, newArtist);
    
    return pNode;
}

// Edit album title.
Node *editAlbumTitle(Node *pNode, char *newAlbumTitle){
    Record r = pNode ->data;
    strcpy(r.albumTitle, newAlbumTitle);
    
    return pNode;
}

// Edit song title.
Node *editSongTitle(Node *pNode, char *newSongTitle) {
    Record r = pNode ->data;
    strcpy(r.songTitle, newSongTitle);
    return pNode;
}

// Edit genre.
Node *editGenre(Node *pNode, char *newGenre) {
    Record r = pNode ->data;
    strcpy(r.genre, newGenre);
    return pNode;
}

// Edit duration.
Node *editDuration(Node *pNode, int newMinute, int newSecond) {
//    Record r = pNode ->data;
    pNode ->data.length.minute = newMinute;
    pNode ->data.length.second = newSecond;
    return pNode;
}

// Edit number times played.
Node *editNumberTimesPlayed(Node *pNode, int newTimes) {
    pNode ->data.numberTimesPlayed = newTimes;
    return pNode;
}

// Edit rating.
Node *editRating(Node *pNode, int newRating) {
    pNode ->data.rating = newRating;
    return pNode;
}

// Play list.
void playList(Node *pList) {
    if (pList == NULL)
        return;
    int index = 0, size = 0, startNum = 0, playedTimes = 0;
    Node **arrayTmp = malloc(50 * sizeof(Node *));
    while (pList != NULL){
        arrayTmp[index++] = pList;
        pList = pList ->pNext;
    }
//    size = index + 1;
    size = index;
    Node **array = malloc( size * sizeof(Node *));
    printTitleWithNumber();
    for (int i = 0; i < size; i++) {
        array[i] = arrayTmp[i];
        printf("%6d", i + 1);
        printRecord(array[i] ->data);
    }
    
    printf("\nPlease input number you want to start with: >");
    scanf("%d", &startNum);
    if (startNum > size)
        startNum = 0;
    else
        startNum -= 1;
    
    while (playedTimes < size) {
        // Clear the screen
        
        printRecord(array[(startNum + playedTimes) % size]->data);
        playedTimes++;
        sleep(3);
    }
    free(array);
    free(arrayTmp);
}

// Insert new record.
Node *insertNewRecord(Node *pList) {
    // The prompt must request the artist name, album title, song title, genre, song length, number of times played, and rating.
    char *array[7];
    for (int i = 0; i < 7; i++) {
        array[i] = malloc(50  * sizeof(char));
    }
    int minute = 0, second = 0;
    
    printf("\nPlease input artist: >");
    strcpy(array[0], "");
    while (strcmp(array[0], "") == 0 || strcmp(array[0], "\n") == 0) {
        fgets(array[0], 256, stdin);
    }
    if ((strlen(array[0]) > 0) && (array[0][strlen (array[0]) - 1] == '\n'))
        array[0][strlen (array[0]) - 1] = '\0';
    
    printf("\nPlease input album title: >");
    strcpy(array[1], "");
    while (strcmp(array[1], "") == 0 || strcmp(array[1], "\n") == 0) {
        fgets(array[1], 256, stdin);
    }
    if ((strlen(array[1]) > 0) && (array[1][strlen (array[1]) - 1] == '\n'))
        array[1][strlen (array[1]) - 1] = '\0';
    
    printf("\nPlease input song title: >");
    strcpy(array[2], "");
    while (strcmp(array[2], "") == 0 || strcmp(array[2], "\n") == 0) {
        fgets(array[2], 256, stdin);
    }
    if ((strlen(array[2]) > 0) && (array[2][strlen (array[2]) - 1] == '\n'))
        array[2][strlen (array[2]) - 1] = '\0';
    
    printf("\nPlease input genre: >");
    strcpy(array[3], "");
    while (strcmp(array[3], "") == 0 || strcmp(array[3], "\n") == 0) {
        fgets(array[3], 256, stdin);
    }
    if ((strlen(array[3]) > 0) && (array[3][strlen (array[3]) - 1] == '\n'))
        array[3][strlen (array[3]) - 1] = '\0';
    
    printf("\nPlease input minute of song length: >");
    scanf("%d", &minute);
    
    printf("\nPlease input second of song length: >");
    scanf("%d", &second);
    
    sprintf(array[4], "%d:%d", minute, second);
    
    printf("\nPlease input number of times played: >");
    fgets(array[5], 256, stdin);
    fgets(array[5], 256, stdin);
    
    printf("\nPlease input rating: >");
    fgets(array[6], 256, stdin);
    
    Record r = *makeRecord(array);
    insertFront(&pList, r);
    
    return pList;
}

// Delete node.
Node *deleteNode(Node *nodeToDelete, Node *pList) {
    if (nodeToDelete == NULL || pList == NULL)
        return pList;
    
    // If node to delete is the first node.
    if (pList == nodeToDelete){
        // If there are only one node in list.
        if (nodeToDelete ->pNext == NULL)
            pList = NULL;
        else {
            nodeToDelete ->pNext ->pPrev = NULL;
            pList = nodeToDelete ->pNext;
        }
    } else {
        nodeToDelete ->pPrev ->pNext = nodeToDelete ->pNext;
        nodeToDelete ->pNext ->pPrev = nodeToDelete ->pPrev;
    }
    free(nodeToDelete);
    return pList;
}

// Delete record.
Node *deleteRecordBySong(Node *pList) {
    char *targetSongTitle = malloc(50 * sizeof(char));
    printf("\nPlease input song title of record you want to delete: >");
    strcpy(targetSongTitle, "");
    while (strcmp(targetSongTitle, "") == 0 || strcmp(targetSongTitle, "\n") == 0) {
        fgets(targetSongTitle, 256, stdin);
    }
    if ((strlen(targetSongTitle) > 0) && (targetSongTitle[strlen (targetSongTitle) - 1] == '\n'))
        targetSongTitle[strlen (targetSongTitle) - 1] = '\0';
    
    Node *pMem = pList, *pTarget = NULL;
    
    while (pMem != NULL) {
        if (strcmp(pMem ->data.songTitle, targetSongTitle) == 0) {
            pTarget = pMem;
            break;
        }
        pMem = pMem ->pNext;
    }
    
    if (pTarget != NULL) {
        pList = deleteNode(pTarget, pList);
        printf("\nRecord deleted!\n");
    } else {
        printf("\nInput not found!");
    }
    
    return pList;
}

// Sort the list.
Node *sortList(Node *pList) {
    int number;
    if (pList != NULL) {
        printf("\nPlease choose method to sort the list:\n (1)Sort based on artist (A-Z)\n (2)Sort based on album title (A-Z)\n (3)Sort based on rating (1-5)\n (4)Sort based on times played (largest-smallest)\n > ");
        scanf("%d", &number);
        if (number >= 1 && number <= 4)
            pList = doSort(pList, number);
        else
            printf("\nWrong input!!");
    }
    
    return pList;
}

// Do sorting.
Node *doSort(Node *pList, int method) {
    if (method < 1 || method > 4)
        return pList;
    
    Node *pNewList = NULL;
    Node *pCurrent = pList, *pTmp;
    while (pList != NULL) {
        pTmp = pCurrent;
        while (pCurrent != NULL) {
            switch (method) {
                case 1:
                    if (strcmp(pCurrent ->data.artist, pTmp ->data.artist) > 0)
                        pTmp = pCurrent;
                    break;
                    
                case 2:
                    if (strcmp(pCurrent ->data.albumTitle, pTmp ->data.albumTitle) > 0)
                        pTmp = pCurrent;
                    break;
                    
                case 3:
                    if (pCurrent ->data.rating > pTmp ->data.rating)
                        pTmp = pCurrent;
                    break;
                    
                case 4:
                    if (pCurrent ->data.numberTimesPlayed < pTmp ->data.numberTimesPlayed)
                        pTmp = pCurrent;
                    break;
            }

            
            pCurrent = pCurrent ->pNext;
        }
        
        Node *newNode = makeNode(pTmp ->data);
        // Insert pTmp to new list.
        if (pNewList == NULL)
            pNewList = newNode;
        else {
            pNewList -> pPrev = newNode;
            newNode -> pNext = pNewList;
            pNewList = newNode;
        }
        
        // Remove pTmp from pList.
        if (pTmp == pList) {
            if (pTmp -> pNext == NULL) {
                pList = NULL;
            } else {
                pTmp -> pNext -> pPrev = NULL;
                pList = pTmp -> pNext;
            }
        } else if (pTmp -> pNext == NULL) {
            pTmp -> pPrev -> pNext = NULL;
        } else {
            pTmp -> pPrev -> pNext = pTmp -> pNext;
            pTmp -> pNext -> pPrev = pTmp -> pPrev;
        }
        
        free(pTmp);
        pCurrent = pList;
    }
    if (pNewList != NULL) {
        printf("\nDone!");
    }
    return pNewList;
}

// Sort by artist.
Node *sortByArtist(Node *pList) {
    Node *pNewList = NULL;
    Node *pCurrent = pList, *pTmp;
    while (pList != NULL) {
        pTmp = pCurrent;
        while (pCurrent != NULL) {
            if (strcmp(pCurrent ->data.artist, pTmp ->data.artist) > 0)
                pTmp = pCurrent;
            
            pCurrent = pCurrent ->pNext;
        }
        
        Node *newNode = makeNode(pTmp ->data);
        // Insert pTmp to new list.
        if (pNewList == NULL)
            pNewList = newNode;
        else {
            pNewList -> pPrev = newNode;
            newNode -> pNext = pNewList;
            pNewList = newNode;
        }
        
        // Remove pTmp from pList.
        if (pTmp == pList) {
            if (pTmp -> pNext == NULL) {
                pList = NULL;
            } else {
                pTmp -> pNext -> pPrev = NULL;
                pList = pTmp -> pNext;
            }
        } else if (pTmp -> pNext == NULL) {
            pTmp -> pPrev -> pNext = NULL;
        } else {
            pTmp -> pPrev -> pNext = pTmp -> pNext;
            pTmp -> pNext -> pPrev = pTmp -> pPrev;
        }
        
        free(pTmp);
        pCurrent = pList;
    }
    if (pNewList != NULL) {
        printf("\nDone!");
    }
    return pNewList;
}

// Sort by album title.
Node *sortByAlbumTitle(Node *pList) {
    Node *pNewList = NULL;
    Node *pCurrent = pList, *pTmp;
    while (pList != NULL) {
        pTmp = pCurrent;
        while (pCurrent != NULL) {
            if (strcmp(pCurrent ->data.albumTitle, pTmp ->data.albumTitle) > 0)
                pTmp = pCurrent;
            
            pCurrent = pCurrent ->pNext;
        }
        
        Node *newNode = makeNode(pTmp ->data);
        // Insert pTmp to new list.
        if (pNewList == NULL)
            pNewList = newNode;
        else {
            pNewList -> pPrev = newNode;
            newNode -> pNext = pNewList;
            pNewList = newNode;
        }
        
        // Remove pTmp from pList.
        if (pTmp == pList) {
            if (pTmp -> pNext == NULL) {
                pList = NULL;
            } else {
                pTmp -> pNext -> pPrev = NULL;
                pList = pTmp -> pNext;
            }
        } else if (pTmp -> pNext == NULL) {
            pTmp -> pPrev -> pNext = NULL;
        } else {
            pTmp -> pPrev -> pNext = pTmp -> pNext;
            pTmp -> pNext -> pPrev = pTmp -> pPrev;
        }
        
        free(pTmp);
        pCurrent = pList;
    }
    if (pNewList != NULL) {
        printf("\nDone!");
    }
    return pNewList;
}

// Sort by rating.
Node *sortByRating(Node *pList) {
    Node *pNewList = NULL;
    Node *pCurrent = pList, *pTmp;
    while (pList != NULL) {
        pTmp = pCurrent;
        while (pCurrent != NULL) {
            if (pCurrent ->data.rating > pTmp ->data.rating)
                pTmp = pCurrent;
            
            pCurrent = pCurrent ->pNext;
        }
        
        Node *newNode = makeNode(pTmp ->data);
        // Insert pTmp to new list.
        if (pNewList == NULL)
            pNewList = newNode;
        else {
            pNewList -> pPrev = newNode;
            newNode -> pNext = pNewList;
            pNewList = newNode;
        }
        
        // Remove pTmp from pList.
        if (pTmp == pList) {
            if (pTmp -> pNext == NULL) {
                pList = NULL;
            } else {
                pTmp -> pNext -> pPrev = NULL;
                pList = pTmp -> pNext;
            }
        } else if (pTmp -> pNext == NULL) {
            pTmp -> pPrev -> pNext = NULL;
        } else {
            pTmp -> pPrev -> pNext = pTmp -> pNext;
            pTmp -> pNext -> pPrev = pTmp -> pPrev;
        }
        
        free(pTmp);
        pCurrent = pList;
    }
    if (pNewList != NULL) {
        printf("\nDone!");
    }
    return pNewList;
}

// Sort by times played.
Node *sortByTimesPlayed(Node *pList) {
    Node *pNewList = NULL;
    Node *pCurrent = pList, *pTmp;
    while (pList != NULL) {
        pTmp = pCurrent;
        while (pCurrent != NULL) {
            if (pCurrent ->data.numberTimesPlayed < pTmp ->data.numberTimesPlayed)
                pTmp = pCurrent;
            
            pCurrent = pCurrent ->pNext;
        }
        
        Node *newNode = makeNode(pTmp ->data);
        // Insert pTmp to new list.
        if (pNewList == NULL)
            pNewList = newNode;
        else {
            pNewList -> pPrev = newNode;
            newNode -> pNext = pNewList;
            pNewList = newNode;
        }
        
        // Remove pTmp from pList.
        if (pTmp == pList) {
            if (pTmp -> pNext == NULL) {
                pList = NULL;
            } else {
                pTmp -> pNext -> pPrev = NULL;
                pList = pTmp -> pNext;
            }
        } else if (pTmp -> pNext == NULL) {
            pTmp -> pPrev -> pNext = NULL;
        } else {
            pTmp -> pPrev -> pNext = pTmp -> pNext;
            pTmp -> pNext -> pPrev = pTmp -> pPrev;
        }
        
        free(pTmp);
        pCurrent = pList;
    }
    if (pNewList != NULL) {
        printf("\nDone!");
    }
    return pNewList;
}

// Shuffle and play.
void shuffle(Node *pList) {
    Node *pMem = pList;
    if (pList == NULL)
        return;
    int index = 0, count = 0, tmp = 0;
    
    while (pMem != NULL) {
        count++;
        pMem = pMem -> pNext;
    }
    
    int order[count];
    for (int i = 0; i < count; i++)
        order[i] = i;
    
    for (int i = 0; i < count; i++) {
        index = rand() % count;
        tmp = order[i];
        order[i] = order[index];
        order[index] = tmp;
    }
    
    printf("\nShuffled list:\n");
    printTitle();
    index = 0;
    pMem = pList;
    for (int i = 0; i < count; i++) {
        while (index != order[i]) {
            if (index < order[i]){
                pMem = pMem -> pNext;
                index++;
            } else {
                pMem = pMem -> pPrev;
                index--;
            }
        }
        
        printRecord(pMem ->data);
    }
    
}

