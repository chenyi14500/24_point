#include <iostream>
#include <string.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define TARGET 24
#define NUMBER_COUNT 4

enum OPERATION {FAIL = 0, EQUAL,  ADD, SUBSTRACT, MULTIPLY, DIVIDE};

char OPS[] = {'?', '?', '+', '-', '*', '/'};

/*
number operation number_set = target
number operation number = target
*/
void getOperations(list<int> nums, int target, char *exps)
{
	if(nums.size() < 2) {
	} else if(nums.size() == 2) {
		int num1 = nums.front();
		nums.pop_front();
		int num2 = nums.front();
		nums.pop_front();

		if( (num1 - num2) == target) {
			sprintf(exps, "%d %c %d", num1, OPS[SUBSTRACT], num2);
		} else if((num2 - num1) == target) {
			sprintf(exps, "%d %c %d", num2, OPS[SUBSTRACT], num1);
		} else if ( (num1 + num2) == target) {
			sprintf(exps, "%d %c %d", num1, OPS[ADD], num2);
		} else if( (num1 * num2) == target) {
			sprintf(exps, "%d %c %d", num1, OPS[MULTIPLY], num2);
		} else if( (num1 % num2) == 0 && (num1 / num2) == target) {
			sprintf(exps, "%d %c %d", num1, OPS[DIVIDE], num2);
		} else if((num2 % num1) == 0 && (num2 / num1) == target) {
			sprintf(exps, "%d %c %d", num1, OPS[DIVIDE], num2);
		} 

	} else {
		char subExps[256] = { 0 };
		int num = nums.front();
		nums.pop_front();

		int i, subTargets[] = {(target - num), (target + num),  (target * num),  (num - target), (num/target), (target/num)};
		OPERATION ops[] = {ADD, SUBSTRACT, DIVIDE, SUBSTRACT, DIVIDE, MULTIPLY};

		// for (num/target), (target/num) case, it need check they can be divide first.
		for(i = 0; i < sizeof(subTargets)/sizeof(subTargets[0]); i++) {

			// the value of (num/target) maybe same as others, so use the index
			if(i == 4 && (num % target) != 0) {
				continue;
			} else if(i == 5 && (target % num) != 0) {
				continue;
			}

			memset(subExps, 0, 256);
			getOperations(nums, subTargets[i], subExps);
			if(strlen(subExps) != 0) {
				sprintf(exps, "%d %c (%s)", num, OPS[ops[i]], subExps);
				return;
			}
		}
		
	}
}

int main(int argc, char *argv[]) {
	int i, target = TARGET;
	list<int> numList;
	char exps[256] = { 0 };

	if(argc != (NUMBER_COUNT + 1)) {
		cout << "please input " << NUMBER_COUNT << " numbers for make the " << TARGET << " point !" << endl;
		return 0;
	} else {
		for(i = 1; i < NUMBER_COUNT +1; i++) {
			numList.push_back(atoi(argv[i]));
		}
	}

	getOperations(numList, target, exps);

	if(strlen(exps) > 0) {
		cout<< "expresion:" << exps << endl;
	} else {
		cout << "these numbers can't make the " << TARGET << " !" << endl;
	}

	return 0;
}
