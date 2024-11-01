struct Bigint {
// representations and structures
    string a; // to store the digits
    int sign; // sign = -1 for negative numbers, sign = 1 otherwise
// constructors
    Bigint() {} // default constructor
    Bigint( string b ) { (*this) = b; } // constructor for string
// some helpful methods
    int size() { // returns number of digits
        return a.size();
    }
    Bigint inverseSign() { // changes the sign
        sign *= -1;
        return (*this);
    }
    Bigint normalize( int newSign ) { // removes leading 0, fixes sign
        for( int i = a.size() - 1; i > 0 && a[i] == '0'; i-- )
            a.erase(a.begin() + i);
        sign = ( a.size() == 1 && a[0] == '0' ) ? 1 : newSign;
        return (*this);
    }
// assignment operator
    void operator = ( string b ) { // assigns a string to Bigint
        a = b[0] == '- ' ? b.substr(1) : b;
        reverse( a.begin(), a.end() );
        this->normalize( b[0] == '- ' ? -1 : 1 );
    }
// conditional operators
    bool operator < ( const Bigint &b ) const { // less than operator
        if( sign != b.sign ) return sign < b.sign;
        if( a.size() != b.a.size() )
            return sign == 1 ? a.size() < b.a.size() : a.size() > b.a.size();
        for( int i = a.size() - 1; i >= 0; i-- ) if( a[i] != b.a[i] )
                return sign == 1 ? a[i] < b.a[i] : a[i] > b.a[i];
        return false;
    }
    bool operator == ( const Bigint &b ) const { // operator for equality
        return a == b.a && sign == b.sign;
    }

    bool operator != ( const Bigint &b ) const {  // operator for not equality
        return a != b.a || sign != b.sign;
    }

    Bigint operator + ( Bigint b ) { // addition operator overloading
        if( sign != b.sign ) return (*this) - b.inverseSign();
        Bigint c;
        for(int i = 0, carry = 0; i<a.size() || i<b.size() || carry; i++ ) {
            carry+=(i<a.size() ? a[i]-48 : 0)+(i<b.a.size() ? b.a[i]-48 : 0);
            c.a += (carry % 10 + 48);
            carry /= 10;
        }
        return c.normalize(sign);
    }
    Bigint operator - ( Bigint b ) { // subtraction operator overloading
        if( sign != b.sign ) return (*this) + b.inverseSign();
        int s = sign; sign = b.sign = 1;
        if( (*this) < b ) return ((b - (*this)).inverseSign()).normalize(-s);
        Bigint c;
        for( int i = 0, borrow = 0; i < a.size(); i++ ) {
            borrow = a[i] - borrow - (i < b.size() ? b.a[i] : 48);
            c.a += borrow >= 0 ? borrow + 48 : borrow + 58;
            borrow = borrow >= 0 ? 0 : 1;
        }
        return c.normalize(s);
    }
    Bigint operator * ( Bigint b ) { // multiplication operator overloading
        Bigint c("0");
        for( int i = 0, k = a[i] - 48; i < a.size(); i++, k = a[i] - 48 ) {
            while(k--) c = c + b; // ith digit is k, so, we add k times
            b.a.insert(b.a.begin(), '0'); // multiplied by 10
        }
        return c.normalize(sign * b.sign);
    }
    Bigint operator / ( Bigint b ) { // division operator overloading
        if( b.size() == 1 && b.a[0] == '0' ) b.a[0] /= ( b.a[0] - 48 );
        Bigint c("0"), d;
        for( int j = 0; j < a.size(); j++ ) d.a += "0";
        int dSign = sign * b.sign; b.sign = 1;
        for( int i = a.size() - 1; i >= 0; i-- ) {
            c.a.insert( c.a.begin(), '0');
            c = c + a.substr( i, 1 );
            while( !( c < b ) ) c = c - b, d.a[i]++;
        }
        return d.normalize(dSign);
    }
    Bigint operator % ( Bigint b ) { // modulo operator overloading
        if( b.size() == 1 && b.a[0] == '0' ) b.a[0] /= ( b.a[0] - 48 );
        Bigint c("0");
        b.sign = 1;
        for( int i = a.size() - 1; i >= 0; i-- ) {
            c.a.insert( c.a.begin(), '0');
            c = c + a.substr( i, 1 );
            while( !( c < b ) ) c = c - b;
        }
        return c.normalize(sign);
    }
    void print() {
        if( sign == -1 ) putchar('-');
        for( int i = a.size() - 1; i >= 0; i-- ) putchar(a[i]);
    }
};

Bigint gcd(Bigint a,Bigint b) {
    while((a % b) != Bigint("0")) {
        Bigint c = a % b;
        a = b;
        b = c;
    }
    return b;
}

//可能略快一点的
class hp {
public:
    int a[maxn];

    hp() { memset(a, 0, sizeof(a)); }

    void clear() { memset(a, 0, sizeof(a)); }

    hp(int x) {
        clear();
        while (x) {
            a[++a[0]] = x % 10;
            x /= 10;
        }
        while (a[a[0]] == 0 && a[0])a[0]--;
    }

    hp &operator=(int x) {
        clear();
        while (x) {
            a[++a[0]] = x % 10;
            x /= 10;
        }
        while (a[a[0]] == 0 && a[0])a[0]--;
        return *this;
    }

    short cmp(const hp &x) {
        if (a[0] > x.a[0])return 1;
        if (a[0] < x.a[0])return -1;
        for (int i = a[0]; i >= 1; i--) {
            if (a[i] > x.a[i])return 1;
            if (a[i] < x.a[i])return -1;
        }
        return 0;
    }

    bool operator>(const hp &x) {
        return cmp(x) == 1;
    }

    bool operator==(const hp &x) {
        return cmp(x) == 0;
    }

    bool operator<(const hp &x) {
        return cmp(x) == -1;
    }

    bool operator>=(const hp &x) {
        return !(*this < x);
    }

    bool operator<=(const hp &x) {
        return !(*this > x);
    }

    hp operator-(const hp &x) {
        hp a = *this, c;
        c.a[0] = a.a[0] > x.a[0] ? a.a[0] : x.a[0];
        for (int i = 1; i <= c.a[0]; i++) {
            c.a[i] += a.a[i] - x.a[i];
            if (c.a[i] < 0) {
                c.a[i] += 10;
                a.a[i + 1]--;
            }
        }
        while (c.a[c.a[0]] == 0 && c.a[0])c.a[0]--;
        return c;
    }

    hp operator*(const hp &x) {
        hp c;
        for (int i = 1; i <= a[0]; i++) {
            for (int j = 1; j <= x.a[0]; j++) {
                c.a[i + j - 1] += a[i] * x.a[j];
            }
        }
        c.a[0] = a[0] + x.a[0];
        for (int i = 1; i <= c.a[0]; i++) {
            if (c.a[i] >= 10) {
                c.a[i + 1] += c.a[i] / 10;
                c.a[i] %= 10;
            }
        }
        while (c.a[c.a[0]] == 0 && c.a[0] > 0)c.a[0]--;
        return c;
    }

    hp operator/(const int &x) {
        hp c;
        int t = 0, s = 0;
        bool flag = 1;
        for (int i = a[0]; i >= 1; i--) {
            t = s * 10 + a[i];
            if (t / x > 0 || t == 0) {
                c.a[++c.a[0]] = t / x;
                s = t % x;
                flag = 0;
            } else {
                s = t;
                if (!flag)c.a[++c.a[0]] = 0;
            }
        }
        reverse(c.a + 1, c.a + c.a[0] + 1);
        return c;
    }
};
if (ans.a[0] == 0) cout << '0';
else
    for (int i = ans.a[0]; i >= 1; i--)
         cout << (char) (ans.a[i] + '0');