#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN {
private:
	RPN(const RPN &copy);
	RPN &operator=(const RPN &copy);

public:
	RPN();
	~RPN();

	int evaluate(const std::string &expression);
};

#endif
