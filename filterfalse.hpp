
#pragma once

namespace itertools {
        template<typename T, typename F>
        class filterfalse {
                T the_iterable;
                F filter;
        public:
                filterfalse(F f, T con) : the_iterable(con), filter(f) {}

                class iterator {
                        typename T::iterator inner_iter;
                        typename T::iterator end_iter;
                        F filter;
                public:
                        iterator(typename T::iterator start, typename T::iterator end, F f) 
                                : inner_iter(start), end_iter(end), filter(f){}

                        auto operator*() { 
                                if(filter(*inner_iter)) {
                                        ++(*this);
                                }
                                return *inner_iter;

                        }
                        iterator& operator++() {
                                do { inner_iter++;}
                                while(inner_iter!= end_iter && filter(*inner_iter));
                                return *this;
                                ++inner_iter;
                        }
                        iterator& operator++(int) {
                                iterator copy = *this;
                                ++(*this);
                                return copy;
                        }
                        iterator& operator=(const iterator& other) {
                                if (*this != other) {
                                        this->end_iter = other.end_iter;
                                        this->inner_iter = other.inner_iter;
                                        this->filter = other.filter;
                                }
                                return *this;
                        }
                        bool operator==(const iterator &other) const {
                                return inner_iter == other.inner_iter;
                        }
                        bool operator!=(const iterator &other) const {
                                return inner_iter != other.inner_iter;
                        }
                };

                iterator begin() { return iterator(the_iterable.begin(), the_iterable.end(), filter); }
                iterator end() { return iterator(the_iterable.end(), the_iterable.end(), filter); }
        };
} // namespace itertools