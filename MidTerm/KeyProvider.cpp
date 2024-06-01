#include "KeyProvider.h"
#include <cassert>
#include <cctype> 

std::string KeyProvider::preprocessString(const std::string& aString) noexcept {
    std::string result;
    for (char a : aString) {
        if (std::isalpha(a)) {
            result += std::toupper(a);
        }
    }
    return result;
}

KeyProvider::KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept
    : fKeys(), fIndex(0) {

    std::string processedKeyword = preprocessString(aKeyword);
 
    size_t sourceLength = preprocessString(aSource).size();
    size_t keywordLength = processedKeyword.size();

   
    while (fKeys.size() < sourceLength) {
        fKeys += processedKeyword;
    }

    fKeys.resize(sourceLength);

    assert(fKeys.size() == sourceLength);
}

char KeyProvider::operator*() const noexcept {
    return fKeys[fIndex];
}

KeyProvider& KeyProvider::operator++() noexcept {
    ++fIndex;
    return *this;
}

KeyProvider KeyProvider::operator++(int) noexcept {
    KeyProvider temp = *this;
    ++(*this);
    return temp;
}
bool KeyProvider::operator==(const KeyProvider& aOther) const noexcept {
    return (fKeys == aOther.fKeys) && (fIndex == aOther.fIndex);
}
bool KeyProvider::operator!=(const KeyProvider& aOther) const noexcept {
    return !(*this == aOther);
}

KeyProvider KeyProvider::begin() const noexcept {
    return KeyProvider(*this); 
}
KeyProvider KeyProvider::end() const noexcept {
    KeyProvider temp(*this); 
    temp.fIndex = fKeys.size(); 
    return temp;
}