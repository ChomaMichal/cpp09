#include <iostream>
#include <stack>
#include <string>

int main(int argc, char **argv){
	if (argc != 2){
		std::cerr << "Ivalid amount of arguments" << std::endl;
		return 1;
	}

	std::string	str = argv[1];
	std::string::iterator let = str.begin();
	bool	was_space = true;

	std::stack<int> pile;

	for (; let != str.end(); let ++){
		if (was_space == true){
			was_space = false;
			if (*let >= '0' && *let <= '9'){
				pile.push(*let - '0');
			} else{
				int	a = pile.top();
				pile.pop();
				int b = pile.top();
				pile.pop();
				switch (*let){
					case '/':
						pile.push(b / a);
						break;
					case '*':
						pile.push(b * a);
						break;
					case '+':
						pile.push(b + a);
						break;
					case '-':
						pile.push(b - a);
						break;
					default:
						std::cerr << "Invalid argument" << std::endl;
						return 1;
				}

			}
		} else if (*let == ' '){
			was_space = true;
		} else {
			std::cerr << "Invalid argument" << std::endl;
			return 1;
		}
	}
	int res = pile.top();
	pile.pop();
	if (pile.empty()){
		std::cout << res << std::endl;
		return 0;
	} else {
		std::cerr << "Invalid argument" << std::endl;
	}
}
