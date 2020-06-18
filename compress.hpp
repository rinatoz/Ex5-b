

#pragma once

namespace itertools {
        template<typename T, typename K>
        class compress {
                T container;
                K filter;
        public:
                compress(T con, K f) : container(con), filter(f) {}

                class iterator {
                        typename T::iterator c_i;
                        typename T::iterator c_end;
                        typename K::iterator f_i;
                        typename K::iterator f_end;
                public:
                        iterator(typename T::iterator c_i, typename T::iterator c_end, typename K::iterator f_i, typename K::iterator f_end) 
                                : c_i(c_i), c_end(c_end), f_i(f_i), f_end(f_end){}

                        auto operator*() { 
                                if(!(*f_i)) {
                                        ++(*this);
                                }
                                return *c_i;  
                        }
                        iterator& operator++() {
                                do {
                                        ++f_i;
                                        ++c_i;
                                }
                                while(f_i != f_end && !*f_i);
                                return *this;
                        }
                        iterator& operator++(int) {
                                iterator copy = *this;
                                ++(*this);
                                return copy;
                        }
                        iterator& operator=(const iterator& other) {
                                if (*this != other) {
                                        this->c_i = other.c_i;
                                        this->c_end = other.c_end;
                                        this->f_i = other.f_i;
                                        this->f_end = other.f_end;
                                }
                                return *this;
                        }
                        bool operator==(const iterator &other) const {
                                return (c_i == other.c_i) && (f_i == other.f_i);
                        }
                        bool operator!=(const iterator &other) const {
                                return (c_i != other.c_i) || (f_i != other.f_i);
                        }
                };

                iterator begin() { return iterator(container.begin(), container.end(), filter.begin(), filter.end()); }
                iterator end() { return iterator(container.end(), container.end(), filter.end(), filter.end()); }
        };
} // namespace itertools