#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) { length = capacity; }

size_t ByteStream::write(const string &data) {
    size_t cur_length = byte_stream.length() + data.length();
    size_t res;
    if(cur_length > length){
    	std::string msg = data.substr(0,(length - byte_stream.length()));
    	byte_stream += msg;
    	hasWrite += msg.length();
    	res = msg.length();
    }else{
    	byte_stream += data;
    	hasWrite += data.length();
    	res = data.length();
    }
    if(empty){
    	if(byte_stream.length()){
    		empty = false;
    	  }
    }
    return res;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    std::string msg;
    if(len > byte_stream.length()){
    	msg = byte_stream.substr(0,byte_stream.length());
    }else{
    	msg = byte_stream.substr(0,len);
    }
    return msg;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    if(len > byte_stream.length()){
    	byte_stream.erase(0,byte_stream.length());
    	hasRead += byte_stream.length();
    } else{
    	byte_stream.erase(0,len);
    	hasRead += len;
    }
    if(!byte_stream.length()){
    	empty = true;
    }else{
    	empty = false;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    //DUMMY_CODE(len);
    std::string msg;
    if(len > byte_stream.length()){
    	msg = peek_output(byte_stream.length());
    	pop_output(byte_stream.length());
    }else{
    	msg = peek_output(len);
    	pop_output(len);
    }
    return msg;
}

void ByteStream::end_input() {is_end = true;}

bool ByteStream::input_ended() const { return is_end; }

size_t ByteStream::buffer_size() const { return byte_stream.length(); }

bool ByteStream::buffer_empty() const { return empty; }

bool ByteStream::eof() const { return is_end&&empty; }

size_t ByteStream::bytes_written() const { return hasWrite; }

size_t ByteStream::bytes_read() const { return hasRead; }

size_t ByteStream::remaining_capacity() const { return (length - byte_stream.length()); }
