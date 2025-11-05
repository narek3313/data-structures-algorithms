class Complex {
   private:
    int m_real;
    int m_imag;

   public:
    Complex(int real, int imag) {
        this->m_real = real;
        this->m_imag = imag;
    }

    Complex operator+(const Complex& other) const {
        return Complex(m_real + other.m_real, m_imag + other.m_imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(m_real - other.m_real, m_imag - other.m_imag);
    }

    Complex& operator=(const Complex& other) {
        if (this != &other) {
            m_real = other.m_real;
            m_imag = other.m_imag;
        }

        return *this;
    }

    Complex& operator++() {
        m_real++;
        m_imag++;
        return *this;
    }

    Complex& operator--() {
        m_real--;
        m_imag--;
        return *this;
    }

    bool operator==(const Complex& other) { return this == &other; }

    int getImage() const { return this->m_imag; }
    int getReal() const { return this->m_real; }
};
