#include <boost/range/join.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <algorithm>    // std::next_permutation, std::sort

namespace permutation 
{
    template <typename T>
    class Permutation
    {
        T source;
    public:
        Permutation(const T &v): source(v) {}
        ~Permutation() {}
    
        class Iterateur: public boost::iterator_facade<Iterateur, const T, boost::forward_traversal_tag>
        {
            T       _source;
            size_t  _index;
        public:
            Iterateur(T & s, size_t index) : _source(s), _index(index) {}
    
            // What we implement is determined by the boost::forward_traversal_tag
            // template parameter
        private:
            friend class boost::iterator_core_access;
            friend class MyContainer;
    
            void increment() {
                if (_index == std::string::npos) {
                    return;
                }
                
                if (std::next_permutation(_source.begin(), _source.end())) {
                    ++_index;
                } else {
                    _index = std::string::npos;
                }
            }
    
            bool equal(Iterateur const& other) const {
                return this->_index == other._index;
            }
    
            const T& dereference() const {
                return _source;
            }
        };
        
        Iterateur begin() {
            return Iterateur(source, 0);
        }
    
        Iterateur end() {
            return Iterateur(source, std::string::npos);
        }
    };
}
