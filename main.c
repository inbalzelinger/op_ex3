#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include <stdlib.h>

#define FIRST_FILE 1
#define SECOND_FILE 2

#define SIZE_TO_READ 1

enum bool{true, false};

int readAndCompare(int firstFd , int secondFd);
//int ignoreChar(char* buff);
int checkIfReadSucced(int reader);



int main(int argc, char **argv) {
	int arg = 0;
	//check this if on the U2~~!!!! because of the arguments number.
	if (argc < 3 || argc > 3) {
		printf("the arguments are illegal please try again\n");
		return -1;
	}
	int firstFile = open(argv[FIRST_FILE] , O_RDONLY);
	checkIfReadSucced(firstFile);
	int secondFile = open(argv[SECOND_FILE] , O_RDONLY);
	checkIfReadSucced(secondFile);
	arg = readAndCompare(firstFile , secondFile);
	close(firstFile);
	close(secondFile);
	printf("%d" , arg);
	return arg;
}



/**
* function name: readAndCompare
* the function reads the files it gets (throgh the files Fd) and return
 * if the files are equals / similar / different.
 * @param firstFd - the first file pointer , secondFd - the second file pointer
* @return -  int - 3 to equals , 2 to similar , 1 to different.
**/


int readAndCompare(int firstFd , int secondFd) {
	char buffFirst[SIZE_TO_READ] = {0};
	char buffSec[SIZE_TO_READ]= {0};
	size_t size = SIZE_TO_READ;
	int flagFirst = 0;
	int flagSecond = 0;
	enum bool isEqual = true;
	enum bool isSimilar = true;
	flagFirst = read(firstFd , buffFirst , size);
	flagSecond = read(secondFd , buffSec , size);
	checkIfReadSucced(flagFirst);
	checkIfReadSucced(flagSecond);
	while (flagFirst != 0 || flagSecond != 0) {
		if (buffFirst[0] != buffSec[0]) {
			isEqual = false;
		}
		if (flagFirst == 0) {
			buffFirst[0] = '\0';
		} else if (flagSecond == 0) {
			buffSec[0] = '\0';
		}
		if (buffFirst[0] == ' ' || buffFirst[0] == '\n') {
			flagFirst = read(firstFd, buffFirst, size);
			checkIfReadSucced(flagFirst);
			if (buffSec[0] == ' ' || buffSec[0] == '\n') {
				flagSecond = read(secondFd, buffSec, size);
				checkIfReadSucced(flagSecond);
			}
		} else if (buffSec[0] == ' ' || buffSec[0] == '\n') {
			flagSecond = read(secondFd, buffSec, size);
			checkIfReadSucced(flagSecond);
		} else {
			if (buffFirst[0] != buffSec[0] + 32 && buffFirst[0] != buffSec[0] - 32 &&
				buffFirst[0] != buffSec[0]) {
				isSimilar = false;
			}
			flagFirst = read(firstFd, buffFirst, size);
			checkIfReadSucced(flagFirst);
			flagSecond = read(secondFd, buffSec, size);
			checkIfReadSucced(flagSecond);
		}
	}
		if (isEqual == true) {
		return 3;
	} else if (isSimilar == true) {
		return 2;
	} else {
		return 1;
	}
}




/**
* function name: checkIfReadSucced
* the function checks if a read was successful
 * @param reader.
* @return -  int - 1 if the read didn't failed.
**/



int checkIfReadSucced(int reader) {
	if (reader < 0) {
		fprintf(stderr, "Error in system call");
		exit(-1);
	}
	return 1;
}




