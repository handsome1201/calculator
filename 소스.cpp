#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include<string.h>

using namespace std;

struct oper {
    int p; // ������ �켱����
    string o; // ������
};

stack<int> num; // ���� ����
stack<oper> op; // ������ ����

class Strategy
{
public:
    virtual int doOperation(int a, int b) = 0;
};
class OperationAdd : public Strategy {
public:
    int doOperation(int num1, int num2) override {
        return num1 + num2;
    }
};
class OperationSubstract : public Strategy
{
public:
    int doOperation(int num1, int num2) override {
        return num1 - num2;
    }
};
class OperationMultiply : public Strategy
{
public:
    int doOperation(int num1, int num2) override {
        return num1 * num2;
    }
};
class OperationDivide : public Strategy
{
public:
    int doOperation(int num1, int num2) override {
        return num1 / num2;
    }
};
class Context {
public:
    Context(Strategy* strategy) {
        this->strategy = strategy;
    }
    void setStrategy(Strategy* st) {
        if (this->strategy != nullptr) delete this->strategy;
        this->strategy = st;
    }
    int executeStrategy(int num1, int num2) {
        return strategy->doOperation(num1, num2);
    }

private:
    Strategy* strategy;
};
void calc() {
    int a, b, result;
   
    b = num.top();
    num.pop();
    a = num.top();
    num.pop();
    string oper = op.top().o;
    op.pop();

    Context con1 = Context(new OperationAdd());
    Context con2 = Context(new OperationSubstract());
    Context con3 = Context(new OperationMultiply());
    Context con4 = Context(new OperationDivide());
    if (oper == "*")
        result = con3.executeStrategy(a, b);
    else if (oper == "/")
        result = con4.executeStrategy(a, b);
    else if (oper == "+")
        result = con1.executeStrategy(a, b);
    else if (oper == "-")
        result = con2.executeStrategy(a, b);
    // ��� �� ���ÿ� �ٽ� ����
    num.push(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    std::cout.tie(NULL);
    string input;
    std::cout << "���� �Է��Ҷ� ���� ��ĭ ���� �Է��� �ϼ���(�� ó�� ����)" << endl;
    std::cout << "���� �Է��ϼ���:";
    getline(cin, input);
    stringstream ss(input);

    // ������ �켱������ ���� ���ÿ� push
    // 0 : ( )
    // 1 : + -
    // 2 : * /
    string tok;
    while (ss >> tok) {
        // ( �� ������ ������ ���ÿ� push
        if (tok == "(") {
            op.push({ 0, tok });
        } // ) �� ������ ( �� ���� �� ���� ���
        else if (tok == ")") {
            while (op.top().o != "(")
                calc();
            op.pop();
        }
        else if (num.size() != op.size()) {
            exit(0);
        }
        else if (tok == "*" || tok == "/" || tok == "+" || tok == "-") {
            int prior = 0; // ������ �켱����
            if (tok == "*")
                prior = 2;
            else if (tok == "/")
                prior = 2;
            else if (tok == "+")
                prior = 1;
            else if (tok == "-")
                prior = 1;

            // ������ �켱 ���� ������ top���� �� ������ ���
            while (!op.empty() && prior <= op.top().p)
                calc();
            // ���ÿ� ������ push
            op.push({ prior, tok });
        }
        else { // ������ ��� ���� ���ÿ� push
           
            char ch1[100];
            strcpy(ch1, tok.c_str()); //�Է°� char�� �ٲ�
            int distinction2 = 0;
            int distinction16 = 0;
            if (ch1[1] == 'b') {
                for (int i = 2; i < tok.length(); i++) {
                    if (ch1[i] == '0' || ch1[i] == '1') {
                        distinction2 += 1;
                    }
                }
            }
            if (ch1[1] == 'x') {
                for (int i = 2; i < tok.length(); i++) {
                    if (ch1[i] == '0' || ch1[i] == '1' || ch1[i] == '2' || ch1[i] == '3' || ch1[i] == '4' || ch1[i] == '5' || ch1[i] == '6' || ch1[i] == '7' || ch1[i] == '8' || ch1[i] == '9' || ch1[i] == 'a' || ch1[i] == 'b' || ch1[i] == 'c' || ch1[i] == 'd' || ch1[i] == 'e' || ch1[i] == 'f') {
                        distinction16 += 1;
                    }
                }
            } 
            if (ch1[1] == 'x' && distinction16 == 0) {
                exit(0);
            }
            if (ch1[1] == 'b' && distinction2 == 0) {
                exit(0);
            }
            if (ch1[1] == 'x') {
                int result = stoi(tok, nullptr, 16);
                num.push(result);
            }
            else if (ch1[1] == 'b') {
                int result = 0;
                int t = 0;
                int size = tok.length();
                for (int i = size - 1; i > 1; i--) {
                    result += (ch1[i] - 48) * pow(2, t);
                    t++;
                }
                num.push(result);
            }
            else {
                stringstream ssInt(tok);
                num.push(stoi(tok));
            }

        }
    }
    // ���� ������ ���
    while (!op.empty())
        calc();

    std::cout << "���: " << num.top();

    return 0;
}
