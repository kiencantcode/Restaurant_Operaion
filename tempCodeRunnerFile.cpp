 string last15Bits = encodedString;
    if (encodedString.size() > 15)
        last15Bits = encodedString.substr(encodedString.size() - 15);
    int decimal = binaryToDecimal(last15Bits);
    cout << last15Bits << endl;
    cout << decimal << endl;
