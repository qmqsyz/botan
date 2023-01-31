/*
* SSL/TLS Protocol Constants
* (C) 2004-2010 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_TLS_PROTOCOL_MAGIC_H_
#define BOTAN_TLS_PROTOCOL_MAGIC_H_

#include <vector>

#include <botan/types.h>

//BOTAN_FUTURE_INTERNAL_HEADER(tls_magic.h)

namespace Botan {

namespace TLS {

/**
* Protocol Constants for SSL/TLS
*
* TODO: this should not be an enum
*/
enum Size_Limits : size_t {
   TLS_HEADER_SIZE    = 5,
   DTLS_HEADER_SIZE   = TLS_HEADER_SIZE + 8,

   // The "TLSInnerPlaintext" length, i.e. the maximum amount of plaintext
   // application data that can be transmitted in a single TLS record.
   MAX_PLAINTEXT_SIZE = 16*1024,

   MAX_COMPRESSED_SIZE = MAX_PLAINTEXT_SIZE + 1024,
   MAX_CIPHERTEXT_SIZE = MAX_COMPRESSED_SIZE + 1024,

   // RFC 8446 5.2:
   //   This limit is derived from the maximum TLSInnerPlaintext length of 2^14
   //   octets + 1 octet for ContentType + the maximum AEAD expansion of 255
   //   octets.
   MAX_AEAD_EXPANSION_SIZE_TLS13 = 255,
   MAX_CIPHERTEXT_SIZE_TLS13 = MAX_PLAINTEXT_SIZE + MAX_AEAD_EXPANSION_SIZE_TLS13 + 1
};

enum class Connection_Side {
   Client = 1,
   Server = 2,

   CLIENT BOTAN_DEPRECATED("Use Connection_Side::Client") = Client,
   SERVER BOTAN_DEPRECATED("Use Connection_Side::Server") = Server,
};

enum class Record_Type: uint8_t {
   Invalid            = 0,  // RFC 8446 (TLS 1.3)

   ChangeCipherSpec   = 20,
   Alert              = 21,
   Handshake          = 22,
   ApplicationData    = 23,

   Heartbeat          = 24, // RFC 6520 (TLS 1.3)
};

enum class Handshake_Type {
   HELLO_REQUEST        = 0,
   CLIENT_HELLO         = 1,
   SERVER_HELLO         = 2,
   HELLO_VERIFY_REQUEST = 3,
   NEW_SESSION_TICKET   = 4, // RFC 5077

   END_OF_EARLY_DATA    = 5, // RFC 8446 (TLS 1.3)
   ENCRYPTED_EXTENSIONS = 8, // RFC 8446 (TLS 1.3)

   CERTIFICATE          = 11,
   SERVER_KEX           = 12,
   CERTIFICATE_REQUEST  = 13,
   SERVER_HELLO_DONE    = 14,
   CERTIFICATE_VERIFY   = 15,
   CLIENT_KEX           = 16,
   FINISHED             = 20,

   CERTIFICATE_URL      = 21,
   CERTIFICATE_STATUS   = 22,

   KEY_UPDATE           = 24,  // RFC 8446 (TLS 1.3)

   HELLO_RETRY_REQUEST  = 253, // Not a wire value (HRR appears as an ordinary Server Hello)
   HANDSHAKE_CCS        = 254, // Not a wire value (TLS 1.3 uses this value for 'message_hash' -- RFC 8446 4.4.1)
   HANDSHAKE_NONE       = 255  // Null value
};

BOTAN_TEST_API const char* handshake_type_to_string(Handshake_Type t);

using Transcript_Hash = std::vector<uint8_t>;

}

}

#endif
