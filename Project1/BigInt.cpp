#include <iostream>

#pragma warning(disable:4996)
class CbigInt {

public:
    char* p;

    //p指向的空间存储数据 (实现构造函数)
    CbigInt(const char* str) {
        p = new char[strlen(str) + 1];
        strcpy(p, str);
    }

    //拷贝构造函数
    CbigInt(const CbigInt& other) {
        p = new char[strlen(other.p) + 1];
        strcpy(p, other.p);
    }
    
    //等号赋值
    CbigInt& operator=(const CbigInt& other) {
        if (this != &other) {
            delete[] p;
            p = new char[strlen(other.p) + 1];
            strcpy(p, other.p);
        }
        return *this;
    }

    //加功能
    CbigInt operator+(const CbigInt& other) const {
        const int maxLength = std::max(strlen(p), strlen(other.p)) + 1; // +1 为了储存有可能的进位
        char *sum = new char[maxLength + 1]; // +1 为了储存空值终止符

        //初始化sum
        char *temp = sum;
        for (int i = 0; i < maxLength; i++)
            *temp++ = '0';

        //进位
        int carry = 0;
        int index = maxLength - 1;

        //加法
        for (int i = strlen(p) - 1, j = strlen(other.p) - 1; i >= 0 || j >= 0 || carry > 0; i--, j--, index--) {
            int digit1 = (i >= 0) ? p[i] - '0' : 0;
            int digit2 = (j >= 0) ? other.p[j] - '0' : 0;
            int total = digit1 + digit2 + carry;

            sum[index] = total % 10 + '0';
            carry = total / 10;
        }

        //加空值终止符
        sum[maxLength] = '\0';


        CbigInt result(sum);
        delete[] sum;
        return result;
    }

    //减功能
    CbigInt operator-(const CbigInt& other) const {
        const int maxLength = std::max(strlen(p), strlen(other.p));
        char* diff = new char[maxLength + 1]; // +1 为了储存空值终止符

        //初始化diff
        char* temp = diff;
        for (int i = 0; i < maxLength; i++)
            *temp++ = '0';

        int borrow = 0;
        int index = maxLength - 1;

        //减法
        for (int i = strlen(p) - 1, j = strlen(other.p) - 1; i >= 0 || j >= 0 || borrow > 0; i--, j--, index--) {
            int digit1 = (i >= 0) ? p[i] - '0' : 0;
            int digit2 = (j >= 0) ? other.p[j] - '0' : 0;

            digit1 = digit1 - borrow;

            if (digit1 < digit2) {
                digit1 += 10;
                borrow = 1;
            }
            else {
                borrow = 0;
            }
            diff[i] = (digit1 - digit2) + '0';
        }

        diff[maxLength] = '\0';

        CbigInt result(diff);
        delete[] diff;
        return result;
    }

    //相等函数
    bool operator==(const CbigInt& other) const {
        return strcmp(p, other.p) == 0;
    }

    //不相等函数
    bool operator!=(const CbigInt& other) const {
        return strcmp(p, other.p) != 0;
    }
};

int main() {
    CbigInt a("12344556");
    CbigInt b("54656");
    CbigInt c("");
    c = a - b;

    std::cout << c.p;
    return 0;
}
