#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>

int main()
{
	int player_score = 0;
	const int MAX_WRONG = 8;
	std::vector<std::string>words;
	std::ifstream file("words.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string word;
			while (std::getline(ss, word, ' ')) {
				words.push_back(word);
			}
		}
		file.close();
	}
	else {
		std::cerr << "File don't open" << std::endl;
	}
	std::cout << "\nWelcome to Hangman. It is my first cpp game. Good luck and thank you for playing!\n";
	while (true) {
		srand(static_cast<unsigned int>(time(0)));
		random_shuffle(words.begin(), words.end());
		int random_number = rand() % (words.end() - words.begin() + 1);
		const  std::string THE_WORD = words[random_number];
		int cur_mistakes = 0;
		std::string soFar(THE_WORD.size(), '-');
		std::string used = " ";
		while ((cur_mistakes < MAX_WRONG) && (soFar != THE_WORD)) {
			std::cout << "\n\nYou have " << (MAX_WRONG - cur_mistakes);
			std::cout << "incorrect guessed left.\n";
			std::cout << "\nYou've used the following letters:\n" << used << std::endl;
			std::cout << "\nSo far. The word is:\n" << soFar << std::endl;

			char guess;
			std::cout << "\n\nEnter your guess: ";
			std::cin >> guess;
			while (used.find(guess) != std::string::npos) {
				std::cout << "\nYou've already guessed " << guess << std::endl;
				std::cout << "Enter your guess: ";
				std::cin >> guess;
			}
			used += guess;
			if (THE_WORD.find(guess) != std::string::npos) {
				std::cout << "That's right! " << guess << "is in the word.\n";
				for (int i = 0; i < THE_WORD.length(); ++i) {
					if (THE_WORD[i] == guess) {
						soFar[i] = guess;
					}
				}
			}
			else {
				std::cout << "Sorry. " << guess << "is not in the word.\n";
				++cur_mistakes;
			}
		}
		if (cur_mistakes == MAX_WRONG) {
			std::cout << "\nYou've been hanged! It's over...";
		}
		else {
			std::cout << "\nYou guessed it! Contgratulation!";
			player_score = player_score + 1;
		}
		std::cout << "\nThe word was " << THE_WORD << std::endl;
		std::cout << "Your final score is: " << player_score;
		std::cout << "\nWant to play again? y/n ";
		char uAnswer;
		std::cin >> uAnswer;
		if (uAnswer == 'n') { break;}
	}
	return 0;
}

