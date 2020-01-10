
namespace CALCULATOR {

enum TOKEN_TYPE { INTEGER = 1, OPERATOR_PLUS, OPERATOR_MINUS, OPERATOR_MUL, OPERATOR_DIV, PAR_LEFT, PAR_RIGHT, T_EOF, T_NULL };
class TOKEN {
	private:
	TOKEN_TYPE _typ;
	const char *_val;
	unsigned int _len;

	public:
	TOKEN(TOKEN_TYPE typ = T_NULL) : _typ(typ), _val(0), _len(0) {}
	TOKEN(TOKEN_TYPE type, const char *val, unsigned int len) : _val(val), _typ(type), _len(len) {}
	TOKEN_TYPE getType() const {
		return this->_typ;
	}
	const char *getValue() const {
		return this->_val;
	}
	unsigned int getLength() const {
		return this->_len;
	}
	~TOKEN() {}
};

int toInteger(const char *val, unsigned int len) {
	int res = 0;
	for(unsigned int i = 0; i < len; i++) res = res * 10 + val[i] - '0';
	return res;
}

unsigned int toString(int val, char *res) {
	unsigned int len = 0;
	int val2 = val;
	while(val2) ++len, val2 /= 10;
	unsigned int len2 = len;
	while(val) res[--len2] = '0' + val % 10, val /= 10;
	if(len == 0) res[len = 1] = '0';
	return len;
}

bool isNumber(char ch) {
	return ch >= '0' && ch <= '9';
}

bool isSpacer(char ch) {
	return ch == ' ' || ch == '\n' || ch == '\t';
}

class LEXER {
	private:
	const char *_text;
	unsigned int _len;
	unsigned int _pos;
	char _ch;
	void nextChar() {
		this->_ch = (this->_pos >= this->_len ? 0 : this->_text[++this->_pos]);
		return;
	}
	void skipSpace() {
		while(this->_ch != 0 && isSpacer(this->_ch)) nextChar();
		return;
	}
	unsigned int skipNumber() {
		unsigned int res = 0;
		while(this->_ch != 0 && isNumber(this->_ch)) ++res, nextChar();
		return res;
	}
	const char *getPosString() const {
		return _text + _pos;
	}

	public:
	LEXER(const char *text, unsigned int len) : _text(text), _len(len), _pos(0) {
		this->_ch = (this->_pos >= this->_len ? 0 : this->_text[this->_pos]);
	}
	~LEXER() {}
	TOKEN getNextToken() {
		while(this->_ch != 0) {
			if(isSpacer(this->_ch)) {
				skipSpace();
				continue;
			}
			if(isNumber(this->_ch)) {
				const char *pos = getPosString();
				return TOKEN(INTEGER, pos, skipNumber());
			}
			if(this->_ch == '+') {
				nextChar();
				return TOKEN(OPERATOR_PLUS);
			}
			if(this->_ch == '-') {
				nextChar();
				return TOKEN(OPERATOR_MINUS);
			}
			if(this->_ch == '*') {
				nextChar();
				return TOKEN(OPERATOR_MUL);
			}
			if(this->_ch == '/') {
				nextChar();
				return TOKEN(OPERATOR_DIV);
			}
			if(this->_ch == '(') {
				nextChar();
				return TOKEN(PAR_LEFT);
			}
			if(this->_ch == ')') {
				nextChar();
				return TOKEN(PAR_RIGHT);
			}
			return TOKEN(T_NULL);
		}
		return TOKEN(T_EOF);
	}
};  // namespace CALCULATOR

class BASENODE {
	protected:
	TOKEN _token;

	public:
	BASENODE() : _token() {}
	BASENODE(TOKEN token) : _token(token) {}
	virtual ~BASENODE() {}
	virtual int getValue() const {
		return 0;
	}
};
class CONSTANT : public BASENODE {
	public:
	CONSTANT(TOKEN token) : BASENODE(token) {}
	~CONSTANT() {}
	virtual int getValue() const override {
		return toInteger(this->_token.getValue(), this->_token.getLength());
	}
};
class UNARYOPER : public BASENODE {
	private:
	BASENODE *_expr1;

	public:
	UNARYOPER(TOKEN token, BASENODE *expr1) : BASENODE(token), _expr1(expr1) {}
	~UNARYOPER() {
		if(_expr1) delete _expr1;
	}
	virtual int getValue() const override {
		if(this->_token.getType() == OPERATOR_PLUS) return +this->_expr1->getValue();
		if(this->_token.getType() == OPERATOR_MINUS) return -this->_expr1->getValue();
		return 0;
	}
};
class BINOPER : public BASENODE {
	private:
	BASENODE *_expr1, *_expr2;

	public:
	BINOPER(TOKEN token, BASENODE *expr1, BASENODE *expr2) : BASENODE(token), _expr1(expr1), _expr2(expr2) {}
	~BINOPER() {
		if(_expr1) delete _expr1;
		if(_expr2) delete _expr2;
	}
	virtual int getValue() const override {
		if(this->_token.getType() == OPERATOR_PLUS) return this->_expr1->getValue() + this->_expr2->getValue();
		if(this->_token.getType() == OPERATOR_MINUS) return this->_expr1->getValue() - this->_expr2->getValue();
		if(this->_token.getType() == OPERATOR_MUL) return this->_expr1->getValue() * this->_expr2->getValue();
		if(this->_token.getType() == OPERATOR_DIV) return this->_expr1->getValue() / this->_expr2->getValue();
		return 0;
	}
};
class PARSER {
	private:
	LEXER _lexer;
	TOKEN _tok;
	void nextToken(TOKEN_TYPE typ) {
		if(this->_tok.getType() == typ) this->_tok = this->_lexer.getNextToken();
		return;
	}
	BASENODE *parserThird() {
		TOKEN token = this->_tok;
		if(token.getType() == INTEGER) {
			nextToken(INTEGER);
			return new CONSTANT(token);
		}
		if(token.getType() == PAR_LEFT) {
			nextToken(PAR_LEFT);
			BASENODE *res = parserFirst();
			nextToken(PAR_RIGHT);
			return res;
		}
		if(token.getType() == OPERATOR_PLUS || token.getType() == OPERATOR_MINUS) {
			nextToken(token.getType());
			return new UNARYOPER(token, parserThird());
		}
		return new BASENODE();
	}
	BASENODE *parserSecond() {
		BASENODE *res = parserThird();
		while(this->_tok.getType() != T_EOF) {
			TOKEN token = this->_tok;
			if(token.getType() == OPERATOR_MUL || token.getType() == OPERATOR_DIV) {
				nextToken(token.getType());
				res = new BINOPER(token, res, parserSecond());
			}
			else {
				break;
			}
		}
		return res;
	}
	BASENODE *parserFirst() {
		BASENODE *res = parserSecond();
		while(this->_tok.getType() != T_EOF) {
			TOKEN token = this->_tok;
			if(token.getType() == OPERATOR_PLUS || token.getType() == OPERATOR_MINUS) {
				nextToken(token.getType());
				res = new BINOPER(token, res, parserSecond());
			}
			else {
				break;
			}
		}
		return res;
	}

	public:
	PARSER(LEXER lexer) : _lexer(lexer) {
		this->_tok = this->_lexer.getNextToken();
	}
	BASENODE *parser() {
		return parserFirst();
	}

	~PARSER() {}
};

int calc(const char *exp, unsigned int len) {
	char *_exp = new char[len]();
	for(unsigned int i = 0; i < len; i++) _exp[i] = exp[i];
	int res = PARSER(LEXER(_exp, len)).parser()->getValue();
	delete[] _exp;
	return res;
}

}  // namespace CALCULATOR

#include <stdio.h>
#include <iostream>
using namespace std;
string str;

int main() {
	getline(cin, str);
	cout << CALCULATOR::calc(str.c_str(), str.size()) << endl;
	return 0;
}