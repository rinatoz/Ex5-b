

#pragma once

namespace itertools {
        class range {

        public:
                class iterator {
                        friend class range;
                public:
                        int operator*() const { return i_; }
                        const iterator &operator++() {
                                ++i_;
                                return *this;
                        }
                        iterator operator++(int) {
                                iterator copy(*this);
                                ++i_;
                                return copy;
                        }
                        bool operator==(const iterator &other) const {
                                 return i_ == other.i_; 
                        }
                        bool operator!=(const iterator &other) const {
                                 return i_ != other.i_; 
                        }

                protected:
                        iterator(int start) : i_(start) {}

                private:
                        int i_;
                };

                iterator begin() const { return begin_; }
                iterator end() const { return end_; }
                range(int begin, int end) : begin_(begin), end_(end) {}
                
        private:
                iterator begin_;
                iterator end_;
        };
} // namespace itertools