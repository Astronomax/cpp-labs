namespace containers {
    template<typename T>
    void my_vector<T>::init(std::size_t init_sz, std::size_t init_cp) {
        std::size_t pow_ = 1;
        while(pow_ < init_cp)
            pow_ <<= 1;

        size_ = init_sz;
        capacity_ = pow_;
        array_ = (T *) new char[pow_ * sizeof(T)];
    }

    template<typename T>
    void my_vector<T>::delete_array_() {
        if (array_ == nullptr)
            return;
        for(std::size_t i = 0; i < size_; i++)
            (array_ + i)->~T();
        delete[] (char*)array_;
        array_ = nullptr;
    }

    template<typename T>
    my_vector<T>::my_vector() {
        init(0, 1);
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) {
        init(n, n);
        for(std::size_t i = 0; i < size_; i++)
            new(array_ + i) T();
    }

    template<typename T>
    my_vector<T>::my_vector(const my_vector &other) {
        init(other.size_, other.capacity_);
        for (std::size_t i = 0; i < size_; i++)
            new(array_ + i) T(other[i]);
    }

    template<typename T>
    my_vector<T> &my_vector<T>::operator=(my_vector other) {
        std::swap(array_, other.array_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        return *this;
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        delete_array_();
    }

    template<typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() {
        return !size_;
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        if(size_ == n)
            return;
        reserve(n);

        if (n < size_)
            for (std::size_t i = n; i < size_; i++)
                (array_ + i)->~T();
        else
            for (std::size_t i = size_; i < n; i++)
                new(array_ + i) T();
        size_ = n;
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t n) {
        if (n <= capacity_)
            return;
        std::size_t pow_ = 1;
        while(pow_ < n)
            pow_ <<= 1;

        T *temp_ = (T *) new char[pow_ * sizeof(T)];
        for (std::size_t i = 0; i < size_; i++)
            new (temp_ + i) T(array_[i]);
        delete_array_();
        array_ = temp_;
        capacity_ = pow_;
    }

    template<typename T>
    T &my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }

    template<typename T>
    void my_vector<T>::push_back(T t) {
        reserve(size_ + 1);
        new(array_ + size_) T(t);
        ++size_;
    }

    template<typename T>
    void my_vector<T>::pop_back() {
    	if(empty())
    		return;
        (array_ + size_ - 1)->~T();
        --size_;
    }

    template<typename T>
    void my_vector<T>::clear() {
        for (std::size_t i = 0; i < size_; i++)
            (array_ + i)->~T();
        size_ = 0;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const my_vector<T> &v) {
        for (std::size_t i = 0; i < v.size(); i++)
            out << v[i] << " ";
        return out;
    }
}
