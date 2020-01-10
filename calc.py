# Token types
#
# EOF (end-of-file) token is used to indicate that
# there is no more input left for lexical analysis
INTEGER,PLUS,MINUS,MULT, DIV,LPAR,RPAR,EOF = 'INTEGER','PLUS','MINUS', 'MULT','DIV','LPAR','RPAR','EOF'


class Token(object):
    def __init__(self, type, value):
        # token type: INTEGER, PLUS, or EOF
        self.type = type
        # token value: 0, 1, 2. 3, 4, 5, 6, 7, 8, 9, '+', or None
        self.value = value

    def __str__(self):
        """String representation of the class instance.
        Examples:
            Token(INTEGER, 3)
            Token(PLUS '+')
        """
        return 'Token({type}, {value})'.format(
            type=self.type,
            value=repr(self.value)
        )

    def __repr__(self):
        return self.__str__()

class Lexer(object):
    def __init__(self,text):
        self.text=text
        self.current_pos=0
        self.current_char=self.text[self.current_pos]

    def error(self):
        raise Exception('Invalid character!')
    def advance(self):
        self.current_pos+=1
        if self.current_pos > len(self.text)-1 :
            self.current_char=None
        else:
            self.current_char=self.text[self.current_pos]

    def skip_whitespace(self):
        while self.current_char is not None and self.current_char.isspace():
            self.advance()

    def integer(self):
        result=''
        while self.current_char is not None and self.current_char.isdigit():
            result+=self.current_char
            self.advance()
        return int(result)

    def get_next_token(self):
        while self.current_char is not None:
            #print('get_next_token---->'+self.current_char)
            if self.current_char.isspace():
                self.skip_whitespace()
                continue
            if self.current_char.isdigit():
                return Token(INTEGER,self.integer())
            if self.current_char=='+':
                self.advance()
                return Token(PLUS,'+')
            if self.current_char=='-':
                self.advance()
                return Token(MINUS,'-')
            if self.current_char=='*':
                self.advance()
                return Token(MULT,'*')
            if self.current_char=='/':
                self.advance()
                return Token(DIV,'/')
            if self.current_char=='(':
                self.advance()
                return Token(LPAR,'(')
            if self.current_char==')':
                self.advance()
                return Token(RPAR,')')
            self.error()

        return Token(EOF,None)

class AST(object):
    pass

class BinOp(AST):
    def __init__(self,left,op,right):
        self.left=left
        self.token=self.op=op
        self.right=right

class Num(AST):
    def __init__(self,token):
        self.token=token
        self.value=token.value

class UnaryOp(AST):
    def __init__(self,op,expr):
        self.token=self.op=op
        self.expr=expr

class Parser(object):
    def __init__(self,lexer):
        self.lexer=lexer
        self.current_token=self.lexer.get_next_token()

    def error(self):
        raise Exception('Invalid syntax')

    def eat(self,token_type):
        #print('eat---->'+self.current_token.type)
        if self.current_token.type==token_type:
            self.current_token=self.lexer.get_next_token()
        else:
            self.error()

    def factor(self):
        """factor : (PLUS | MINUS) factor | INTEGER | LPAREN expr RPAREN"""
        token=self.current_token
        if token.type==INTEGER:
            self.eat(INTEGER)
            return Num(token)
        elif token.type==LPAR:
            self.eat(LPAR)
            result=self.expr()
            self.eat(RPAR)
            return result
        elif token.type == PLUS:
            self.eat(PLUS)
            node=UnaryOp(token,self.factor())
            return node
        elif token.type == MINUS:
            self.eat(MINUS)
            node=UnaryOp(token,self.factor())
            return node
        else:
            self.error()
        #self.eat(INTEGER)
        #return token.value
        #return result

    def term(self):
        r=self.factor()
        #print('term---->'+self.current_token.type)
        while self.current_token.type != EOF :
            if self.current_token.type==MULT:
                self.eat(MULT)
                #r=r*self.factor()
                r=BinOp(r,Token(MULT,'*'),self.factor())
            elif self.current_token.type==DIV:
                self.eat(DIV)
                #r=r/self.factor()
                r=BinOp(r,Token(DIV,'/'),self.factor())
            else:
                #?????
                break
                #print("term error....."+self.current_token.type)
        return r

    def expr(self):
        t=self.term()
        #print('expr---->'+str(t))
        #print('expr2---->'+self.current_token.type)
        while self.current_token.type != EOF :
            #print('expr3---->'+self.current_token.type)
            if self.current_token.type==PLUS:
                self.eat(PLUS)
                #t=t+self.term()
                t=BinOp(t,Token(PLUS,'+'),self.term())
            elif self.current_token.type==MINUS:
                self.eat(MINUS)
                #t=t-self.term()
                t=BinOp(t,Token(MINUS,'-'),self.term())
            else:
                break
        return t

    def parse(self):
        return self.expr()

class NodeVisitor(object):
    def visit(self,node):
        method_name='visit_'+type(node).__name__
        visitor=getattr(self,method_name,self.generic_visit)
        return visitor(node)

    def generic_visit(self,node):
        raise Exception('No visit_{} method'.format(type(node).__name__))

class Interpreter(NodeVisitor):
    def __init__(self,parser):
        self.parser=parser

    def visit_BinOp(self,node):
        if node.op.type == PLUS:
            return self.visit(node.left)+self.visit(node.right)
        elif node.op.type == MINUS:
            return self.visit(node.left)-self.visit(node.right)
        elif node.op.type == MULT:
            return self.visit(node.left)*self.visit(node.right)
        elif node.op.type == DIV:
            return self.visit(node.left)/self.visit(node.right)
        else:
            pass

    def visit_Num(self,node):
        #print(node.value)
        return node.value

    def visit_UnaryOp(self,node):
        op=node.op
        if op.type == PLUS:
            return +self.visit(node.expr)
        elif op.type == MINUS:
            return -self.visit(node.expr)
        else:
            pass

    def interprete(self):
        tree=self.parser.parse()
        return self.visit(tree)

def main():
    while True:
        try:
            try:
                text = raw_input('spi> ') #python 2
            except NameError:
                text = input('spi>') #python 3
        except EOFError:
            break
        if not text:
            continue

        lexer=Lexer(text)
        parser = Parser(lexer)
        interpreter=Interpreter(parser)
        result=interpreter.interprete()
        print(result)


if __name__ == '__main__':
    main()