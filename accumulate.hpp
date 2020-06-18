
#pragma once

namespace itertools
{
        typedef struct {
                template <typename K>
                K operator ()(K a, K b) const {
                        return a+b;
                }
        } plus;

        template<typename T, typename F = plus>
        class accumulate {
                T the_iterable;
                F func;
        public:
                accumulate(T con, F f = plus()) 
                : the_iterable(con), func(f) {}

                class iterator {
                        typename T::iterator inner_iter;
                        typename T::iterator end_iter;
                        decltype(*(the_iterable.begin())) sum;
                        F func;
                public:
                        iterator(typename T::iterator start, typename T::iterator end, F f) 
                                : inner_iter(start), end_iter(end), func(f), sum(*inner_iter){}

                        auto operator*() const { 
                                return sum;
                        }
                        iterator& operator++() {
                                ++inner_iter;
                                if(inner_iter != end_iter)
                                        sum = func(sum, *inner_iter);
                                return *this;
                        }
                        iterator& operator++(int) {
                                iterator copy = *this;
                                ++inner_iter;
                                if(inner_iter != end_iter)
                                        sum = func(sum, *inner_iter);
                                return copy;
                        }
                        iterator& operator=(const iterator& other) {
                                if (*this != other){
                                        this->end_iter = other.end_iter;
                                        this->sum = other.sum;
                                        this->inner_iter = other.inner_iter;
                                        this->func = other.func;
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

                iterator begin() { return iterator(the_iterable.begin(), the_iterable.end(), func); }
                iterator end() { return iterator(the_iterable.end(), the_iterable.end(), func); }
        };
} // namespace itertools