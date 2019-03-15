/* 20141264 information communication Engineer*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

void Dictionary();
void fileRead(char *fileName);
void wordStore(char *line);
void search(char *target);
int find(char *target, int begin, int end);
void search_same(int n);
void print(int n);

string word[200000];
string wordClass[200000];
string account[200000];
int index = 0;

int main() {
	Dictionary();
}

void Dictionary() {
	char Text[30];
	while (1) {
		printf("$ ");
		cin.getline(Text, sizeof(Text));
		char *command = strtok(Text, " ");

		if (strcmp(command, "\0") == 0)
			continue;

		else if (strcmp(command, "read") == 0) {
			command = strtok(NULL, "\0");
			fileRead(command);
		}
		else if (strcmp(command, "size") == 0) {
			cout << index << '\n';
		}
		else if (strcmp(command, "find") == 0) {
			command = strtok(NULL, "\0");
			search(command);
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		}
	}
}

void fileRead(char *fileName) {
	FILE *fp = fopen(fileName, "r");
	char line[5000];

	while (fgets(line, sizeof(line), fp)) {
		if (fp == NULL) {
			cout << "Not found file" << endl;
			break;
		}
		if (strcmp(line, "\n") == 0)
			continue;
		wordStore(line);
	}
	fclose(fp);
	cout << "Open File" << endl;
}

void wordStore(char *line) {
	char *context = NULL;
	char *tok_Word = strtok_s(line, "(", &context);

	while (tok_Word != NULL) {
		word[index] = tok_Word;
		//find할때 단어를 비교하기위해 공백제거
		word[index] = word[index].substr(0, word[index].length() - 1);
		if (context[0] == ')')
			wordClass[index] = " ";
		else {
			tok_Word = strtok_s(NULL, ")", &context);
			wordClass[index] = tok_Word;
		}
		//단어설명 공백일 경우 체크
		if (context[1] == '\0')
			account[index] = " ";
		else {
			tok_Word = strtok_s(NULL, "\0", &context);
			account[index] = tok_Word;
		}
		index++;
		tok_Word = strtok(NULL, " ");
	}
}

void search(char *target) {
	int i = find(target, 0, index - 1);
	char *index_word = (char *)word[i].c_str();
	if (_stricmp(index_word, target) != 0)
		print(i);
	else
		search_same(i);
}

void print(int n) {
	cout << "Not found.\n" << word[n] << "(" << wordClass[n] << ")" << account[n] << "- - - - -\n";
	cout << word[n + 1] << "(" << wordClass[n + 1] << ")" << account[n + 1] << '\n';
}

void search_same(int n) {
	string same_word[30];
	int count = 0;
	int tmp = n;
	same_word[count++] = word[n] + "(" + wordClass[n] + ")" + account[n];
	while (1) {
		if (n != index && word[n] == word[n + 1]) {
			same_word[count++] = word[n + 1] + "(" + wordClass[n + 1] + ")" + account[n + 1];
			n++; continue;
		}break;
	}
	n = tmp;
	while (1) {
		if (n != 0 && word[n] == word[n - 1]) {
			same_word[count++] = word[n - 1] + "(" + wordClass[n - 1] + ")" + account[n - 1];
			n--; continue;
		}break;
	}
	cout << "Found " << count << " item\n";
	for (int i = 0; i < count; i++)
		cout << same_word[i];
}

int find(char *target, int begin, int end) {
	int middle = (begin + end) / 2;

	if (begin > end)
		return middle;
	else {
		char *element = (char *)word[middle].c_str();
		int compare = _stricmp(element, target);
		if (compare <0) {
			return find(target, middle + 1, end);
		}
		else if (compare > 0) {
			return find(target, begin, middle - 1);
		}
		else {
			return middle;
		}
	}
}