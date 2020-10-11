// A checksum is a small-sized value generated from some digital data. The checksum is used to
// detect errors in transmission or storage of the data. The checksum is sent or stored with its
// corresponding data. After data together with the checksum is sent or retrieved, a check for errors
// is performed on the data and confirmed using the checksum value.
// For example, an ASCII character may be represented as seven bits (a value between 0 and 127). If
// you are storing such a character as a byte, you can just have the leading bit always be zero. If you
// are transmitting an ASCII character, you could set this leading bit to 0 if the number of bits set to
// 1 is even, and 1 if the number of bits set to 1 is odd. Thus, a capital-G is stored as the seven bits
// 1000111, and because the number of bits set to 1 is even, the leading bit would be set to zero, so a
// capital G would be encoded as 01000111. Capital-H and -I are stored as 1001000 and 1001001,
// respectively, and the first has two bits set to 1 while the second has three bits set to 1, so these
// would be transmitted as 01001000 and 11001001, respectively. Now, if during the transmission
// of one of these characters, if noise were to cause one of the bits to flip (change from a 0 to a 1 or
// vice versa), the receiver could determine the transmitted character is invalid. For example, if
// either 00110111 or 11010000 was received, the receiver would know that these are invalid, as the
// first byte has five bits set to 1 after the first bit, and the second has two bits set to 1 after the first
// bit. Consequently, the receiver would know that one (or three or five or seven) bits were flipped
// during transmission and could request that the byte be resent. 

#include <iostream>
#include <climits>

#ifndef MARMOSET_TESTING
int main();
#endif

unsigned int add_checksum( unsigned int n );
void add_checksum(unsigned int array[], std::size_t capacity );
bool verify_checksum(unsigned int n);
unsigned int remove_checksum( unsigned int n );
void remove_checksum( unsigned int array[], std::size_t capacity );

unsigned int add_checksum( unsigned int n ){

    if(n > 99999999){
        return UINT_MAX;
    }
	
	int size = 0;
	int n2 = n;
	int n3 = n;

	for(int k = 0; n2 > 0; k++){
		n2 = n2/10;
		size++;
	}
	int num[size];

	//Step 1:
	int count = 0;
	for(int k = size - 1; k >= 0; k--){
		num[k] = n%10;
		n = n/10;
		if(count%2 == 0){
			num[k] = num[k]*2;
			if(num[k] > 9){
				num[k] = 1 + num[k]%10;
			}
		}
		count++;

	}

	//Step2:
	unsigned int checksum = 0;
	for(int k = 0; k < size; k++){
		checksum += num[k];
	}

	//Step3:
	 checksum = checksum*9;

	//Step4:
	 checksum = checksum%10;

	//Plug d into original number:
	unsigned int res = n3*10 + checksum;

	return res;
}

bool verify_checksum(unsigned int n){

    if(n <= 999999999){
        unsigned int n_add_checksum = add_checksum(n/10);
        unsigned int c_checksum = n_add_checksum%10;
        unsigned int checksum = n%10;
        if(c_checksum == checksum){
            return true;
        }
    }

    return false;
}

void add_checksum(unsigned int array[], std::size_t capacity ){

    for(int k = 0; k < capacity; k++){
        array[k] = add_checksum(array[k]);
    }

	//std::cout << array[capacity -1 ] << std::endl;
}

unsigned int remove_checksum(unsigned int n){
    bool res = verify_checksum(n);
    if(res == 0){
        return UINT_MAX;
    }
    else{
        n = n/10;
        return n;
    }
}

void remove_checksum(unsigned int array[], std::size_t capacity){
    for(int k = 0; k < capacity; k++){
        array[k] = remove_checksum(array[k]);
    }

    //std::cout << array[capacity - 1] << std::endl;
}
#ifndef MARMOSET_TESTING
int main() {

	 unsigned int value_to_protect{21352411};
	 unsigned int protected_value = add_checksum(value_to_protect);

	 std::cout << "The value " << value_to_protect  << " with the checksum added is "
	 		<< protected_value << "." << std::endl;

	 if (verify_checksum(protected_value)) {
	 	std::cout << "The checksum is valid." << std::endl;
	 }

	 else   {
	 	std::cout << "The checksum is invalid." << std::endl;
	 }

	 const std::size_t qty_values {3};
	 unsigned int value_series[qty_values] {20201122, 20209913, 20224012};

	 add_checksum(value_series, qty_values);
	 std::cout << "Series with checksums added: ";

	 for (std::size_t series_index {0}; series_index < qty_values; series_index++){
	 	std::cout << value_series[series_index] << " ";
	 }
	 std::cout << std::endl;


}
#endif

