#include <iostream>
#include <cctype>

enum TokenType {
    ALPHANUM,
    EQUALS,
    NUMBER,
    SEMICOLON,
    END
};
//34an e5zn 2emt eltoken
struct Token {
    TokenType type;
    std::string value;
};

Token getNextToken(const std::string& input, size_t& position) {
    if (position >= input.length()) {
        return {END, ""};
    }

    while (position < input.length() && std::isspace(input[position])) {
        position++;
    }

    if (input[position] == ';') {
        position++;
        return {SEMICOLON, ";"};
    }

    if (input[position] == '=') {
        position++;
        return {EQUALS, "="};
    }

    std::string tokenValue;
    while (position < input.length() && !std::isspace(input[position]) && input[position] != ';' && input[position] != '=') {
        tokenValue += input[position];
        position++;
    }

    return {ALPHANUM, tokenValue};
}

bool parseStatement(const std::string& input) {
    size_t position = 0;

    Token token = getNextToken(input, position);

    // Expecting an alphanumeric token
    if (token.type != ALPHANUM) {
        return false;
    }

    token = getNextToken(input, position);

    // Expecting an equals sign
    if (token.type != EQUALS) {
        return false;
    }

    token = getNextToken(input, position);

    // Expecting a number
    if (token.type != ALPHANUM || !std::isdigit(token.value[0])) {
        return false;
    }

    token = getNextToken(input, position);

    // Expecting a semicolon
    if (token.type != SEMICOLON) {
        return false;
    }

    return true; // All checks passed
}

int main() {
    std::string input;
    std::cout << "Enter a statement: ";
    std::getline(std::cin, input);

    if (parseStatement(input)) {
        std::cout << "Syntax is correct." << std::endl;
    } else {
        std::cout << "Syntax error." << std::endl;
    }

    return 0;
}

