#include "VigenereForwardIterator.h"

// Constructor definition
VigenereForwardIterator::VigenereForwardIterator(
    const std::string& aKeyword,
    const std::string& aSource,
    EVigenereMode aMode) noexcept
    : fMode(aMode), fKeys(aKeyword, aSource), fSource(aSource), fIndex(0), fCurrentChar('\0') {
    initializeTable(); // Call initializeTable() without arguments
    if (fKeys != fKeys.end()) {
        if (fMode == EVigenereMode::Encode) {
            encodeCurrentChar();
        }
        else {
            decodeCurrentChar();
        }
    }
}

// Inline implementation of initializeTable() function
inline void VigenereForwardIterator::initializeTable() {
    for (size_t row = 0; row < CHARACTERS; row++) {
        char lChar = static_cast<char>('A' + row);
        for (size_t column = 0; column < CHARACTERS; column++) {
            if (lChar > 'Z')
                lChar = 'A';
            fMappingTable[row][column] = lChar++;
        }
    }
}

// Method to encode the current character
void VigenereForwardIterator::encodeCurrentChar() noexcept {
    char currentChar = fSource[fIndex];
    if (std::isalpha(currentChar)) {
        char key = *fKeys;
        if (std::islower(currentChar)) {
            fCurrentChar = std::tolower(fMappingTable[key - 'A'][currentChar - 'a']);
        }
        else {
            fCurrentChar = fMappingTable[key - 'A'][currentChar - 'A'];
        }
        ++fKeys;
    }
    else {
        fCurrentChar = currentChar; // Non-alphabetic character remains unchanged
    }
}

// Method to decode the current character
void VigenereForwardIterator::decodeCurrentChar() noexcept {
    char currentChar = fSource[fIndex];
    if (std::isalpha(currentChar)) {
        char key = *fKeys;
        if (std::islower(currentChar)) {
            for (size_t i = 0; i < CHARACTERS; ++i) {
                if (fMappingTable[key - 'A'][i] == std::toupper(currentChar)) {
                    fCurrentChar = 'a' + i;
                    break;
                }
            }
        }
        else {
            for (size_t i = 0; i < CHARACTERS; ++i) {
                if (fMappingTable[key - 'A'][i] == currentChar) {
                    fCurrentChar = 'A' + i;
                    break;
                }
            }
        }
        ++fKeys;
    }
    else {
        fCurrentChar = currentChar; // Non-alphabetic character remains unchanged
    }
}

// Dereference operator
char VigenereForwardIterator::operator*() const noexcept {
    return fCurrentChar;
}

// Prefix increment operator
VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept {
    ++fIndex;
    if (fKeys != fKeys.end()) {
        if (fMode == EVigenereMode::Encode) {
            encodeCurrentChar();
        }
        else {
            decodeCurrentChar();
        }
    }
    return *this;
}

// Postfix increment operator
VigenereForwardIterator VigenereForwardIterator::operator++(int) noexcept {
    VigenereForwardIterator temp = *this;
    ++(*this);
    return temp;
}

// Equality operator
bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept {
    return (fSource == aOther.fSource) && (fIndex == aOther.fIndex);
}

// Inequality operator
bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const noexcept {
    return !(*this == aOther);
}

// Begin method
VigenereForwardIterator VigenereForwardIterator::begin() const noexcept {
    VigenereForwardIterator beginIt = *this;
    beginIt.fIndex = 0;
    if (beginIt.fKeys != beginIt.fKeys.end()) {
        if (fMode == EVigenereMode::Encode) {
            beginIt.encodeCurrentChar();
        }
        else {
            beginIt.decodeCurrentChar();
        }
    }
    return beginIt;
}

// End method
VigenereForwardIterator VigenereForwardIterator::end() const noexcept {
    VigenereForwardIterator endIt = *this;
    endIt.fIndex = fSource.size();
    return endIt;
}
