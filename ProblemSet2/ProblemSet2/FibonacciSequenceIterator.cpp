#include <stdio.h>
#include <cassert>
#include "FibonacciSequenceIterator.h"

FibonacciSequenceIterator::FibonacciSequenceIterator(const FibonacciSequenceGenerator& aSequenceObject, long long aStart) noexcept
    : fSequenceObject(aSequenceObject), fIndex(aStart) {}

const long long& FibonacciSequenceIterator::operator*() const noexcept {
    return *fSequenceObject;
}

FibonacciSequenceIterator& FibonacciSequenceIterator::operator++() noexcept {
    ++fIndex;
    if (!fSequenceObject.hasNext()) {
        fIndex = std::numeric_limits<long long>::max();
    }
    else {
        fSequenceObject.next();
    }
    return *this;
}

FibonacciSequenceIterator FibonacciSequenceIterator::operator++(int) noexcept {
    FibonacciSequenceIterator var = *this;
    ++(*this);
    return var;
}

bool FibonacciSequenceIterator::operator==(const FibonacciSequenceIterator& aOther) const noexcept {
    return fSequenceObject.id() == aOther.fSequenceObject.id() && fIndex == aOther.fIndex;
}

bool FibonacciSequenceIterator::operator!=(const FibonacciSequenceIterator& aOther) const noexcept {
    return !(*this == aOther);
}

FibonacciSequenceIterator FibonacciSequenceIterator::begin() const noexcept {
    FibonacciSequenceIterator beginIterator = *this;
    beginIterator.fIndex = 1;
    beginIterator.fSequenceObject.reset();
    return beginIterator;
}

FibonacciSequenceIterator FibonacciSequenceIterator::end() const noexcept {
    return FibonacciSequenceIterator(fSequenceObject, std::numeric_limits<long long>::max());
}