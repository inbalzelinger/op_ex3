#include <stdio.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>
#include <stdlib.h>

#define FIRST_FILE 1
#define SECOND_FILE 2

#define SIZE_TO_READ 1

enum bool{true, false};

int readAndCompare(int firstFd , int secondPd);
int ignoreChar(char* buff);
int checkIfReadSucced(int reader);



int main(int argc, char **argv) {
	int arg = 0;
	char check2[1];
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



int readAndCompare(int firstFd , int secondPd) {
	char buffFirst[SIZE_TO_READ] = {0};
	char buffSec[SIZE_TO_READ]= {0};
	size_t size = SIZE_TO_READ;
	int flagFirst = 0;
	int flagSecond = 0;
	enum bool isEqual = true;
	enum bool isSimilar = true;
	flagSecond = read(secondPd , buffSec , size);
	flagFirst = read(firstFd , buffFirst , size);
	checkIfReadSucced(flagFirst);
	checkIfReadSucced(flagSecond);
	while (flagFirst != 0 || flagSecond != 0) {
		if (buffFirst[0] != buffSec[0]) {
			isEqual = false;
		}
		if (ignoreChar(buffFirst)) {
			do {
				if (!ignoreChar(buffSec)) {
					isEqual = false;
					flagFirst = read(firstFd, buffFirst, size);
					checkIfReadSucced(flagFirst);
				} else {
					if (buffFirst[0] != buffSec[0]) {
						isEqual = false;
					}
					flagFirst = read(firstFd, buffFirst, size);
					checkIfReadSucced(flagFirst);
					flagSecond = read(secondPd, buffSec, size);
					checkIfReadSucced(flagSecond);
				}
			} while (ignoreChar(buffFirst) && flagFirst != 0);
		} else if (ignoreChar(buffSec)) {
			isEqual = false;
			do {
				flagSecond = read(secondPd, buffSec, size);
				checkIfReadSucced(flagSecond);
			} while (ignoreChar(buffSec) && flagSecond != 0);
		}
		///check endPoint case.
		if (buffFirst[0] != buffSec[0] + 32 && buffFirst[0] != buffSec[0] - 32 &&
			buffFirst[0] != buffSec[0]) {
			isSimilar = false;
		}
		buffFirst[0] = 0;
		buffSec[0] = 0;
		flagFirst = read(firstFd, buffFirst, size);
		checkIfReadSucced(flagFirst);
		flagSecond = read(secondPd, buffSec, size);
		checkIfReadSucced(flagSecond);
	}
	if (isEqual == true) {
		return 3;
	} else if (isSimilar == true) {
		return 2;
	} else {
		return 1;
	}
}




int checkIfReadSucced(int reader) {
	if (reader < 0) {
		fprintf(stderr, "Error in system call");
		exit(-1);
	}
}



int ignoreChar(char* buff) {
	if ((buff[0] == '\n')  || (buff[0] == ' ')) {
		return 1;
	} else {
		return 0;
	}
}



//enum bool readsCharAndIgnore(int fileNumber , int secoundFileNumber , char firstBuff[] , char secoundBuff[],
//							 int firstFileFd , int secFilePd) {
//
//	enum bool isEqual = true;
//	do {
//		if (!ignoreChar(secoundBuff)) {
//			isEqual = false;
//			fileNumber = read(firstFileFd, firstBuff, SIZE_TO_READ);
//			checkIfReadSucced(fileNumber);
//		} else {
//			if (firstBuff[0] != secoundBuff[0]) {
//				isEqual = false;
//			}
//			fileNumber = read(firstFileFd, firstBuff, SIZE_TO_READ);
//			checkIfReadSucced(fileNumber);
//			secoundFileNumber = read(secFilePd, secoundBuff, SIZE_TO_READ);
//			checkIfReadSucced(secoundFileNumber);
//		}
//	} while (ignoreChar(firstBuff) && fileNumber != 0);
//	return isEqual;
//}
//
