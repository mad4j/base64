[![Build Status](https://travis-ci.org/mad4j/base64.svg?branch=master)](https://travis-ci.org/mad4j/base64)

# base64
Clean and clear implementation of Base64 algorithm.

## Algorithm

Conversion of a stream of bytes in a stream of printable chars.

Each 3 input bytes will be convetered in 4 chars. 
Inputs bytes will be splitted in 4 blocks of 6 bits. Each block will be convetered in a printable char using a predefined dictionary.

Padding.

