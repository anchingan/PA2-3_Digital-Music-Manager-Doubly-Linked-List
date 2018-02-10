//
//  functions.h
//  PA2_Digital Music Manager & Doubly Linked Lists_part1
//
//  Created by Chingan on 01/02/2018.
//  Copyright © 2018 Chingan. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc()
#include <unistd.h> // sleep()

#ifndef functions_h
#define functions_h

typedef struct {
    int minute;
    int second;
} Duration;

typedef struct {
    char artist[100];
    char albumTitle[100];
    char songTitle[100];
    char genre[100];
    Duration length;
    int numberTimesPlayed;
    int rating;
} Record;

typedef struct node{
    Record data;
    struct node *pPrev;
    struct node *pNext;
} Node;

// Parse string into [string] for create Record.
//char *parseString(char *); ---------need to be finished.*****

// Create record.
Record *makeRecord(char *strs[7]);

// place the value inside the container
Node *makeNode(Record newRecord);

// list operation
int insertFront(Node **pList, Record newRecord);
// a - z based on name
int insertInOrder(Node **pList, Record newRecord);
// Print title
void printTitle(void);
// Print title with number
void printTitleWithNumber(void);
// Print record.
void printRecord(Record r);
// Print list recursively
void printList(Node *pList);
// Print certain artist recursively
void printListByArtist(Node *pList, char *targetArtist);
// Print list with number recursively
void printListWithNumber(Node *pList);

// Search nodes by certain artist.
Node **searchByArtist(Node *pList, char *targetArtist, int *size);

//File input
Node *loadFile(Node *pList);

// Store file
int storeFile(Node *pList);
// Write record to file, called int storeFile.
void writeList(Node *pList, FILE *pFile);

// Display list
void displayList(Node *pList);

// Edit list.
void editList(Node *pList);
// Edit artist.
Node *editArtist(Node *pNode, char *newArtist);
// Edit album title.
Node *editAlbumTitle(Node *pNode, char *newAlbumTitle);
// Edit song title.
Node *editSongTitle(Node *pNode, char *newSongTitle);
// Edit genre.
Node *editGenre(Node *pNode, char *newGenre);
// Edit duration.
Node *editDuration(Node *pNode, int newMinute, int newSecond);
// Edit number times played.
Node *editNumberTimesPlayed(Node *pNode, int newTimes);
// Edit rating.
Node *editRating(Node *pNode, int newRating);

// Play list.
void playList(Node *pList);

// Insert new record.
Node *insertNewRecord(Node *pList);

// Delete node.
Node *deleteNode(Node *nodeToDelete, Node *pList);

// Delete record.
Node *deleteRecordBySong(Node *pList);

// Sort the list.
Node *sortList(Node *pList);

// Do sorting.
Node *doSort(Node *pList, int method);

// Sort by artist.
Node *sortByArtist(Node *pList);

// Sort by album title.
Node *sortByAlbumTitle(Node *pList);

// Sort by rating.
Node *sortByRating(Node *pList);

// Sort by times played.
Node *sortByTimesPlayed(Node *pList);

// Shuffle and play.
void shuffle(Node *pList);
#endif /* functions_h */
