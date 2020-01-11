#include <stdio.h>
namespace CALCULATOR {
enum TOKEN_TYPE {
	INTEGER = 1,
	OPERATOR_PLUS,
	OPERATOR_MINUS,
	OPERATOR_LT,
	OPERATOR_GT,
	OPERATOR_LE,
	OPERATOR_GE,
	OPERATOR_EQ,
	OPERATOR_NEQ,
	PAR_LEFT,
	PAR_RIGHT,
	BRACKET_LEFT,
	BRACKET_RIGHT,
	BLOCK_LEFT,
	BLOCK_RIGHT,
	PROGRAM,
	BLOCK,
	VARIABLE_NAME,
	VARIABLE_TYPE,
	VARS,
	YOSORO,
	OPERATOR_ASSIGN,
	IHU,
	HOR,
	WHILE,
	T_DOT,
	T_EOF,
	T_NULL,
	T_COLON,
	T_COMMA
};

bool equalString(const char *a, const char *b, unsigned int len) {
	for(unsigned int i = 0; i < len; i++)
		if(a[i] != b[i]) return 0;
	return 1;
}
class VAR {
	private:
	const char *_name;
	unsigned int _len;
	VAR *_nxt;
	int *_mem;
	int _s, _t;

	public:
	VAR() : _name(), _len(), _nxt(), _mem(), _t(), _s() {}
	VAR(const char *name, unsigned int len) : _name(name), _len(len), _nxt(), _mem(), _t(), _s() {}
	VAR(const char *name, unsigned int len, int s, int t) : _name(name), _len(len), _nxt(), _mem(), _t(t), _s(s) {
		this->_mem = new int[this->_t - this->_s]();
	}
	unsigned int getLen() const {
		return this->_len;
	}
	void setValue(int x, int v) {
		this->_mem[x - this->_s] = v;
		return;
	}
	const char *getName() const {
		return this->_name;
	}
	VAR *getNext() const {
		return this->_nxt;
	}
	void setNext(VAR *v) {
		this->_nxt = v;
	}
	int getValue(int x) {
		return this->_mem[x - this->_s];
	}

} var_first;
VAR *getVar(const char *name, unsigned int len) {
	VAR *p = &var_first;
	while(p) {
		if(p->getLen() == len && equalString(p->getName(), name, len)) return p;
		p = p->getNext();
	}
	return 0;
}
void setVar(VAR *nxt) {
	VAR *p = &var_first;
	while(p->getNext()) p = p->getNext();
	p->setNext(nxt);
	return;
}
class TOKEN {
	private:
	TOKEN_TYPE _typ;
	const char *_val;
	unsigned int _len;

	public:
	TOKEN(TOKEN_TYPE typ = T_NULL) : _typ(typ), _val(), _len() {}
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

bool isLetter(char ch) {
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
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
	unsigned int skipWord() {
		unsigned int res = 0;
		while(this->_ch != 0 && isLetter(this->_ch)) ++res, nextChar();
		return res;
	}
	const char *getPosString() const {
		return _text + _pos;
	}

	public:
	LEXER(const char *text, unsigned int len) : _text(text), _len(len), _pos() {
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
			if(isLetter(this->_ch)) {
				const char *pos = getPosString();
				unsigned int len = skipWord();
				if(len == 2 && equalString("lt", pos, len)) return TOKEN(OPERATOR_LT);
				if(len == 2 && equalString("gt", pos, len)) return TOKEN(OPERATOR_GT);
				if(len == 2 && equalString("le", pos, len)) return TOKEN(OPERATOR_LE);
				if(len == 2 && equalString("ge", pos, len)) return TOKEN(OPERATOR_GE);
				if(len == 2 && equalString("eq", pos, len)) return TOKEN(OPERATOR_EQ);
				if(len == 3 && equalString("neq", pos, len)) return TOKEN(OPERATOR_NEQ);
				if(len == 3 && equalString("set", pos, len)) return TOKEN(OPERATOR_ASSIGN);
				if(len == 3 && equalString("ihu", pos, len)) return TOKEN(IHU);
				if(len == 3 && equalString("hor", pos, len)) return TOKEN(HOR);
				if(len == 3 && equalString("int", pos, len)) return TOKEN(VARIABLE_TYPE, pos, len);
				if(len == 4 && equalString("vars", pos, len)) return TOKEN(VARS);
				if(len == 5 && equalString("while", pos, len)) return TOKEN(WHILE);
				if(len == 5 && equalString("array", pos, len)) return TOKEN(VARIABLE_TYPE, pos, len);
				if(len == 6 && equalString("yosoro", pos, len)) return TOKEN(YOSORO);
				return TOKEN(VARIABLE_NAME, pos, len);
			}
			if(this->_ch == '+') {
				nextChar();
				return TOKEN(OPERATOR_PLUS);
			}
			if(this->_ch == '-') {
				nextChar();
				return TOKEN(OPERATOR_MINUS);
			}
			if(this->_ch == '(') {
				nextChar();
				return TOKEN(PAR_LEFT);
			}
			if(this->_ch == ')') {
				nextChar();
				return TOKEN(PAR_RIGHT);
			}
			if(this->_ch == '.') {
				nextChar();
				nextChar();
				return TOKEN(T_DOT);
			}
			if(this->_ch == ',') {
				nextChar();
				return TOKEN(T_COMMA);
			}
			if(this->_ch == ':') {
				nextChar();
				return TOKEN(T_COLON);
			}
			if(this->_ch == '[') {
				nextChar();
				return TOKEN(BRACKET_LEFT);
			}
			if(this->_ch == ']') {
				nextChar();
				return TOKEN(BRACKET_RIGHT);
			}
			if(this->_ch == '{') {
				nextChar();
				return TOKEN(BLOCK_LEFT);
			}
			if(this->_ch == '}') {
				nextChar();
				return TOKEN(BLOCK_RIGHT);
			}
			return TOKEN(T_NULL);
		}
		return TOKEN(T_EOF);
	}
};

class NODE {
	private:
	TOKEN _token;
	NODE **_list;
	bool _multi;
	unsigned int _siz, _msiz;
	bool _flag;
	int getConstantValue() {
		if(this->_token.getType() == INTEGER) return toInteger(this->_token.getValue(), this->_token.getLength());
		if(this->_token.getType() == VARS && this->_flag == 0) return this->_flag = 1;
		if(this->_token.getType() == BLOCK && this->_flag == 0) return this->_flag = 1;
		return 0;
	}
	int getUnaryValue() {
		if(this->_token.getType() == OPERATOR_PLUS) return +this->_list[0]->getValue();
		if(this->_token.getType() == OPERATOR_MINUS) return -this->_list[0]->getValue();
		if(this->_token.getType() == YOSORO) return printf("%d ", this->_list[0]->getValue()), 0;
		if(this->_token.getType() == VARIABLE_NAME) return getVar(this->_token.getValue(), this->_token.getLength())->getValue(this->_list[0]->getValue());
		if(this->_token.getType() == IHU && this->_flag == 0) return this->_flag = 1, this->_list[0]->getValue();
		if(this->_token.getType() == WHILE) return this->_list[0]->getValue();
		return 0;
	}
	int getBinValue() {
		if(this->_token.getType() == OPERATOR_PLUS) return this->_list[0]->getValue() + this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_MINUS) return this->_list[0]->getValue() - this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_LT) return this->_list[0]->getValue() < this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_GT) return this->_list[0]->getValue() > this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_LE) return this->_list[0]->getValue() <= this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_GE) return this->_list[0]->getValue() >= this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_EQ) return this->_list[0]->getValue() == this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_NEQ) return this->_list[0]->getValue() != this->_list[1]->getValue();
		if(this->_token.getType() == OPERATOR_ASSIGN) return this->_list[0]->setValue(this->_list[1]->getValue());
		return 0;
	}
	int getMultiValue() {
		if(this->_token.getType() == T_COLON) {
			if(this->_siz == 1) {
				this->_list[0]->registerVar(0, 1);
			}
			else {
				this->_list[0]->registerVar(this->_list[1]->getValue(), this->_list[2]->getValue());
			}
			return 0;
		}
		if(this->_token.getType() == BLOCK) {
			while(this->_list[0]->getValue()) {
				for(unsigned int i = 1; i < this->_siz; i++) {
					this->_list[i]->getValue();
				}
				this->_list[0]->setValue(0);
			}
			this->clearST();
		}
		if(this->_token.getType() == HOR) {
			if(this->_flag == 0) {
				this->_list[0]->setValue(this->_list[1]->getValue());
				this->_flag = 1;
			}
			return this->_list[0]->getValue() <= this->_list[2]->getValue();
		}
		return 0;
	}
	int registerVar(int s, int t) {
		VAR *p = new VAR(this->_token.getValue(), this->_token.getLength(), s, t);
		setVar(p);
		return 0;
	}
	int setValue(int v) {
		if(this->_token.getType() == VARIABLE_NAME) {
			VAR *p = getVar(this->_token.getValue(), this->_token.getLength());
			p->setValue(this->_list[0]->getValue(), v);
		}
		if(this->_token.getType() == HOR) {
			this->_list[0]->setValue(this->_list[0]->getValue() + 1);
		}
		return 0;
	}
	void clearST() {
		if(this->_siz == -1) return;
		for(unsigned int i = 0; i < this->_siz; i++) this->_list[i]->_flag = 0, this->_list[i]->clearST();
	}

	public:
	NODE(bool multi = 0) : _token(T_NULL), _list(), _siz(-1), _multi(multi), _msiz(), _flag() {
		if(this->_multi) this->_siz = 0;
	}
	NODE(TOKEN token) : _token(token), _list(), _siz(), _multi(), _msiz(), _flag() {}
	NODE(TOKEN token, NODE *expr0) : _token(token), _siz(1), _multi(), _msiz(1), _flag() {
		this->_list = new NODE *[this->_siz]();
		this->_list[0] = expr0;
	}
	NODE(TOKEN token, NODE *expr0, NODE *expr1) : _token(token), _siz(2), _multi(), _msiz(2), _flag() {
		this->_list = new NODE *[this->_siz]();
		this->_list[0] = expr0;
		this->_list[1] = expr1;
	}
	~NODE() {
		if(this->_list)
			for(unsigned int i = 0; i < this->_siz; i++) delete this->_list[i];
	}
	int getValue() {
		if(this->_multi) return getMultiValue();
		switch(_siz) {
			case 0: return getConstantValue();
			case 1: return getUnaryValue();
			case 2: return getBinValue();
			default: break;
		}
		return 0;
	}
	void setToken(const TOKEN &token) {
		this->_token = token;
		return;
	}
	void push(NODE *expr0) {
		if(this->_siz >= this->_msiz) {
			unsigned int lmsiz = this->_msiz;
			this->_msiz = (this->_siz + 1) * 2;
			NODE **list = new NODE *[this->_msiz]();
			for(unsigned int i = 0; i < this->_siz; i++) list[i] = this->_list[i];
			if(this->_list) {
				delete[] this->_list;
			}
			this->_list = list;
		}
		this->_list[this->_siz++] = expr0;
		return;
	}
	int getSize() const {
		return this->_siz;
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
	NODE *parserThird() {
		TOKEN token = this->_tok;
		if(token.getType() == INTEGER) {
			nextToken(INTEGER);
			return new NODE(token);
		}
		if(token.getType() == PAR_LEFT) {
			nextToken(PAR_LEFT);
			NODE *res = parserSecond();
			nextToken(PAR_RIGHT);
			return res;
		}
		if(token.getType() == VARIABLE_NAME) {
			nextToken(VARIABLE_NAME);
			NODE *res;
			if(this->_tok.getType() == BRACKET_LEFT) {
				nextToken(BRACKET_LEFT);
				res = parserSecond();
				nextToken(BRACKET_RIGHT);
			}
			else {
				res = new NODE();
			}
			return new NODE(token, res);
		}
		if(token.getType() == OPERATOR_PLUS || token.getType() == OPERATOR_MINUS) {
			nextToken(token.getType());
			return new NODE(token, parserThird());
		}

		return new NODE();
	}
	NODE *parserSecond() {
		NODE *res = parserThird();
		while(this->_tok.getType() != T_EOF) {
			TOKEN token = this->_tok;
			if(token.getType() == OPERATOR_PLUS || token.getType() == OPERATOR_MINUS) {
				nextToken(token.getType());
				res = new NODE(token, res, parserThird());
			}
			else {
				break;
			}
		}
		return res;
	}
	NODE *parserCall() {
		TOKEN token = this->_tok;
		if(token.getType() == YOSORO) {
			nextToken(YOSORO);
			return new NODE(token, parserSecond());
		}
		if(token.getType() == OPERATOR_ASSIGN) {
			nextToken(OPERATOR_ASSIGN);
			NODE *res = parserThird();
			nextToken(T_COMMA);
			return new NODE(token, res, parserSecond());
		}
		return new NODE();
	}
	NODE *parserVar() {
		NODE *res = new NODE(1);
		res->push(new NODE(this->_tok));
		nextToken(VARIABLE_NAME);
		res->setToken(this->_tok);
		nextToken(T_COLON);
		if(this->_tok.getLength() == 5) {
			nextToken(VARIABLE_TYPE);
			nextToken(BRACKET_LEFT);
			nextToken(VARIABLE_TYPE);
			nextToken(T_COMMA);
			res->push(new NODE(this->_tok));
			nextToken(INTEGER);
			nextToken(T_DOT);
			nextToken(T_DOT);
			res->push(new NODE(this->_tok));
			nextToken(INTEGER);
			nextToken(BRACKET_RIGHT);
		}
		else {
			nextToken(VARIABLE_TYPE);
		}
		return res;
	}
	NODE *parserIhu() {
		NODE *res;
		nextToken(IHU);
		TOKEN token = this->_tok;
		if(token.getType() == OPERATOR_LT || token.getType() == OPERATOR_GT || token.getType() == OPERATOR_LE || this->_tok.getType() == OPERATOR_GE || this->_tok.getType() == OPERATOR_EQ || token.getType() == OPERATOR_NEQ) {
			nextToken(token.getType());
			nextToken(T_COMMA);
			NODE *res1 = parserSecond();
			nextToken(T_COMMA);
			NODE *res2 = parserSecond();
			res = new NODE(token, res1, res2);
		}
		else {
			res = new NODE();
		}
		return new NODE(TOKEN(IHU), res);
	}
	NODE *parserHor() {
		NODE *res = new NODE(1);
		res->setToken(this->_tok);
		nextToken(HOR);
		res->push(parserSecond());
		nextToken(T_COMMA);
		res->push(parserSecond());
		nextToken(T_COMMA);
		res->push(parserSecond());
		return res;
	}
	NODE *parserWhile() {
		NODE *res;
		nextToken(WHILE);
		TOKEN token = this->_tok;
		if(token.getType() == OPERATOR_LT || token.getType() == OPERATOR_GT || token.getType() == OPERATOR_LE || this->_tok.getType() == OPERATOR_GE || this->_tok.getType() == OPERATOR_EQ || token.getType() == OPERATOR_NEQ) {
			nextToken(token.getType());
			nextToken(T_COMMA);
			NODE *res1 = parserSecond();
			nextToken(T_COMMA);
			NODE *res2 = parserSecond();
			res = new NODE(token, res1, res2);
		}
		else {
			res = new NODE();
		}
		return new NODE(TOKEN(WHILE), res);
	}
	NODE *parserFirst() {
		NODE *res = new NODE(1);
		res->setToken(TOKEN(BLOCK));
		while(this->_tok.getType() != T_EOF) {
			TOKEN token = this->_tok;
			if(token.getType() == VARS) {
				nextToken(VARS);
				res->push(new NODE(TOKEN(VARS)));
			}
			else if(token.getType() == IHU) {
				res->push(parserIhu());
			}
			else if(token.getType() == HOR) {
				res->push(parserHor());
			}
			else if(token.getType() == WHILE) {
				res->push(parserWhile());
			}
			else if(token.getType() == VARIABLE_NAME) {
				if(res->getSize() == 0) res->push(new NODE(TOKEN(BLOCK)));
				res->push(parserVar());
			}
			else if(token.getType() == T_COLON) {
				if(res->getSize() == 0) res->push(new NODE(TOKEN(BLOCK)));
				nextToken(T_COLON);
				res->push(parserCall());
			}
			else if(token.getType() == BLOCK_LEFT) {
				if(res->getSize() == 0) res->push(new NODE(TOKEN(BLOCK)));
				nextToken(BLOCK_LEFT);
				res->push(parserFirst());
				nextToken(BLOCK_RIGHT);
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
	NODE *parser() {
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
string str, str2;

int main() {
	while(getline(cin, str2)) {
		str += str2;
	}
	CALCULATOR::calc(str.c_str(), str.size());
	return 0;
}

/*
{ vars
	chika:int
	you:int
	ruby:array[int, 1..2]
	i:int
}
:yosoro 2
:set chika, 1
:set you, 2
:yosoro chika + you
{ ihu eq, chika, 1
	:set you, 3
	:yosoro 1
}
{ hor i, 1, you
	:yosoro i
}
:set i, 1
{ while le, i, 2
	:yosoro i
	:set ruby[i], i+1
	:yosoro ruby[i]
	:set i, i+1
}

*/

/*
{ vars
	chika:int
	you:int
	ruby:array[int, 1..2]
	i:int
}
:set i, 1
{ while le, i, 2
	:yosoro i
	:set ruby[i], i+1
	:yosoro ruby[i]
	:set i, i+1
}
*/